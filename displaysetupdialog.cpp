//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "displaysetupdialog.h"
#include "ui_displaysetupdialog.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qspinbox.h>
#include <Q3Table>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include <QFileDialog>

DisplaySetupDialog::DisplaySetupDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::DisplaySetupDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->rowsSpinBox, SIGNAL( valueChanged(int) ), this, SLOT( initRowsTable() ) );
    connect( ui->saveButton, SIGNAL( clicked() ), this, SLOT( save() ) );
    connect( ui->cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->browseButton, SIGNAL( clicked() ), this, SLOT( browse() ) );
    connect( ui->saveButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
DisplaySetupDialog::~DisplaySetupDialog()
{
    delete ui;
}

void DisplaySetupDialog::init()
{
    itemList << "Nothing" << "Head Count" << "Average Weight" << "Total Weight" << "Bid Price"
             << "Alt Bid"  << "Seller No" << "Seller Pen" << "Buyer No" << "Buyer Pen" << "Special - DDC Auctioneers" << "Special - Penback";
    ui->rowsTable->setColumnWidth(0, ui->rowsTable->width() - (50 + ui->rowsTable->columnWidth(1) + ui->rowsTable->columnWidth(2)));
}

void DisplaySetupDialog::init(SetupDAO::DisplayRecord display)
{
    this->display = display;
    ui->displayNameEdit->setText(QString::fromStdString(display.name));
    QStringList portList = QStringList::split(",", QString::fromStdString(display.port), true);

    ui->devicePathEdit->setText(portList[0]);
    ui->baudCombo->setCurrentText(portList[1]);
    ui->dataBitCombo->setCurrentText(portList[2]);

    int index = 0;

    switch(portList[3].upper().ascii()[0])
    {
    case 'N':
    default:
        index = 0;
        break;

    case 'O':
        index = 1;
        break;

    case 'E':
        index = 2;
        break;

    }
    ui->parityCombo->setCurrentItem(index);
    ui->stopBitCombo->setCurrentText(portList[4]);
    ui->typeCombo->setCurrentItem(display.type);
    ui->transCombo->setCurrentItem(display.which);
    ui->baseSpinBox->setValue(display.base);
    ui->rowsSpinBox->setValue(display.rows);

    int row = 0;

    for(unsigned int i = 0; i < display.rowList.size(); i++)
    {
        if(display.rowList[i].row < ui->rowsTable->numRows())
        {
            row = display.rowList[i].row;
            ((Q3ComboTableItem*)ui->rowsTable->item(row, 0))->setCurrentItem(display.rowList[i].item);
            ui->rowsTable->setText(row, 1, QString::number(display.rowList[i].length));
            ((Q3CheckTableItem*)ui->rowsTable->item(row, 2))->setChecked(display.rowList[i].reversed);
        }
    }
}

void DisplaySetupDialog::initRowsTable()
{
    int currentRows = ui->rowsTable->numRows();
    ui->rowsTable->setNumRows(ui->rowsSpinBox->value());

    for(int i = currentRows; i < ui->rowsTable->numRows(); i++)
    {
        ui->rowsTable->setItem(i, 0, new Q3ComboTableItem(ui->rowsTable, itemList));
        ui->rowsTable->setItem(i , 2, new Q3CheckTableItem(ui->rowsTable, ""));
    }
}

void DisplaySetupDialog::browse()
{
    QString path = QFileDialog::getOpenFileName("/dev/", "Serial Ports (ttyS0 ttyS1 ttyS2 ttyS3 ttyS4 ttyUSB0 ttyUSB1 ttyUSB2 ttyUSB3 ttyUSB4)");

    if(path != QString::null)
    {
        ui->devicePathEdit->setText(path);
    }
}

void DisplaySetupDialog::save()
{
    display.name = ui->displayNameEdit->text().ascii();

    QStringList portList;
    portList << ui->devicePathEdit->text() << ui->baudCombo->currentText() << ui->dataBitCombo->currentText();

    switch(ui->parityCombo->currentItem())
    {
    case 0:
    default:
        portList += "N";
        break;

    case 1:
        portList += "O";
        break;

    case 2:
        portList += "E";
        break;
    }

    portList += ui->stopBitCombo->currentText();

    display.port = portList.join(",").ascii();
    display.type = ui->typeCombo->currentItem();
    display.which = ui->transCombo->currentItem();
    display.base = ui->baseSpinBox->value();
    display.rows = ui->rowsSpinBox->value();

    vector<SetupDAO::DispRowsRecord> recordList;
    SetupDAO::DispRowsRecord temp;

    for(int i = 0; i < ui->rowsTable->numRows(); i++)
    {
        temp.row = i;
        temp.item = ((Q3ComboTableItem*)ui->rowsTable->item(i, 0))->currentItem();
        temp.length = ui->rowsTable->text(i, 1).toInt();
        temp.reversed = ((Q3CheckTableItem*)ui->rowsTable->item(i, 2))->isChecked();

        recordList.push_back(temp);
    }

    display.rowList = recordList;

    setup.saveDisplay(display);
}
