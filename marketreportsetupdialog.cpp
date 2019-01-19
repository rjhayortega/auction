//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "marketreportsetupdialog.h"
#include "ui_marketreportsetupdialog.h"

#include <qvariant.h>
#include <qgroupbox.h>
#include <Q3Table>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "previewdialog.h"
#include <QMessageBox>
#include "textdialog.h"

MarketReportSetupDialog::MarketReportSetupDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::MarketReportSetupDialog)
{
    ui->setupUi(this);

    // signals and slots connections
    connect( ui->cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->sortTable, SIGNAL( valueChanged(int,int) ), this, SLOT( swapItem(int,int) ) );
    connect( ui->acceptButton, SIGNAL( clicked() ), this, SLOT( save() ) );
    connect( ui->okButton, SIGNAL( clicked() ), this, SLOT( save() ) );
    connect( ui->okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( ui->startWeightEdit, SIGNAL(editingFinished()), this, SLOT(checkValues()));
    connect( ui->endWeightEdit, SIGNAL(editingFinished()), this, SLOT(checkValues()));
    init();
}

MarketReportSetupDialog::~MarketReportSetupDialog()
{
    delete ui;
}

#include "reports/marketreport.h"

void MarketReportSetupDialog::init()
{
    blockSignal = true;
    sortMenu << "" << "" << "" << "" << "" << "" << "";
    sortMenu[MarketReport::Sex]     = "Sex Code";
    sortMenu[MarketReport::Seller]   =  "Seller #";
    sortMenu[MarketReport::Head]   = "# of Head";
    sortMenu[MarketReport::Price]    = "Bid Price";
    sortMenu[MarketReport::Weight] = "Avg. Weight";
    sortMenu[MarketReport::TransId] = "TransId";
    sortMenu[MarketReport::None] = "None";

    keyList << "firstMarketReportSort" << "secondMarketReportSort" << "thirdMarketReportSort"
            << "fourthMarketReportSort" << "fifthMarketReportSort" << "sixthMarketReportSort";

    QStringList options;

    int current;
    for(int i = 0; i < ui->sortTable->numRows(); i++)
    {
        ui->sortTable->setItem(i, 0, new Q3ComboTableItem(ui->sortTable, sortMenu));
        ui->sortTable->setItem(i, 1, new Q3CheckTableItem(ui->sortTable, ""));
        ui->sortTable->setColumnWidth(0, 150);
        ui->sortTable->setColumnWidth(1, 120);
        options = QStringList::split(" ", QString::fromStdString(setup.get(keyList[i].toStdString())), true);

        current = options[0].toInt();

        ((Q3ComboTableItem*)ui->sortTable->item(i, 0))->setCurrentItem(current);

        if(bool(options[1].toInt()))
            ((Q3CheckTableItem*)ui->sortTable->item(i, 1))->setChecked(true);
    }

    QString startWeight = QString::fromStdString(setup.get("MarketReportClassStarting"));
    QString endWeight = QString::fromStdString(setup.get("MarketReportClassEnding"));
    QString classSize = QString::fromStdString(setup.get("MarketReportClassSize"));

    ui->startWeightEdit->setText(startWeight.isEmpty() ? "0" : startWeight);
    ui->endWeightEdit->setText(endWeight.isEmpty() ? "2400" : endWeight);
    ui->sizeEdit->setText(classSize.isEmpty() ? "200" : classSize);
    ui->groupByWeightGroupBox->setChecked(setup.getBoolean("MarketReportClassEnabled",true));


    ui->startWeightEdit->setValidator( new QIntValidator(0, 5000, this) );
    ui->endWeightEdit->setValidator( new QIntValidator(0, 5000, this) );
    ui->sizeEdit->setValidator( new QIntValidator(1, 5000, this) );

    blockSignal = false;
}

// todo - rethink this a bit so that it will work right
//        with a 'none' option, in the meantime, do no
//        row swapping
void MarketReportSetupDialog::swapItem(int row, int col)
{
//    if(blockSignal)
//    {
//   return;
//    }
//
//     blockSignal = true;
//    vector<int> used;
//     vector<int> dirtyRows;
//     used.push_back(((QComboTableItem*)sortTable->item(row, 0))->currentItem());
//
// int temp;
//
// // add any duplicated rows to the 'dirty' row list
//
// for(unsigned int i = 0; i < sortTable->numRows(); i++)
// {
//   if(i != row)
//   {
//  temp = ((QComboTableItem*)sortTable->item(i, 0))->currentItem();
//
//  if(std::find(used.begin(), used.end(), temp) == used.end() && temp != MarketReport::None)
//  {
//      used.push_back(temp);
//  }
//  else if(temp != MarketReport::None)
//  {
//       dirtyRows.push_back(i);
//   }
//  }
//}
//
//      // fill the dirty rows with the first available unused items
//
//     for(unsigned int i = 0; i < dirtyRows.size(); i++)
//     {
//    for(unsigned int j = 0; j < 5; j++)
//    {
//   if(std::find(used.begin(), used.end(), j) == used.end())
//           {
//                 ((QComboTableItem*)sortTable->item(dirtyRows[i], 0))->setCurrentItem(j);
//                 used.push_back(j);
//                 break;
//            }
//        }
// }
//
// blockSignal = false;
}

void MarketReportSetupDialog::save()
{
    QStringList keyMap;
    QString item;
    QString isReverse;

    for(int i = 0; i < ui->sortTable->numRows(); i++)
    {
        item = QString::number(((Q3ComboTableItem*)ui->sortTable->item(i, 0))->currentItem());
        isReverse = QString::number(int(((Q3CheckTableItem*)ui->sortTable->item(i, 1))->isChecked()));
        setup.set(keyList[i].toStdString(),  item.toStdString() + " " + isReverse.toStdString());
    }

    setup.set("MarketReportClassStarting",ui->startWeightEdit->text().toStdString());
    setup.set("MarketReportClassEnding",ui->endWeightEdit->text().toStdString());
    setup.set("MarketReportClassSize",ui->sizeEdit->text().toStdString());
    setup.setBoolean("MarketReportClassEnabled", ui->groupByWeightGroupBox->isChecked());
}


void MarketReportSetupDialog::checkValues()
{
    if (blockSignal) {
        return;
    }
    QString startWeight = ui->startWeightEdit->text();
    QString endWeight = ui->endWeightEdit->text();

    if (startWeight.toInt() >= endWeight.toInt()){
        QMessageBox::critical(this, "Error","Start weight should be smaller than End Weight");
        ui->startWeightEdit->setFocus();
    }
}
