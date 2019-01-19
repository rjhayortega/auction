//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "proratesexdialog.h"
#include "ui_proratesexdialog.h"

#include <qvariant.h>
#include <Q3Table>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

ProrateSexDialog::ProrateSexDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::ProrateSexDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
ProrateSexDialog::~ProrateSexDialog()
{
    delete ui;
}


void ProrateSexDialog::init()
{
    xChar = "-";
    ui->sexTable->setColumnWidth(2, 150);
    ui->sexTable->setColumnWidth(3, 150);
}

void ProrateSexDialog::init(vector<SexCheckFactory::CodeRecord> codeList, vector<Prorate> prorateList, unsigned int prorateRow)
{
    this->codeList = codeList;
    // fill the list;
    ui->sexTable->insertRows(0, codeList.size());

    for(unsigned int i = 0; i < codeList.size(); i++)
    {
        ui->sexTable->setColumnWidth(0, 20);
        ui->sexTable->setItem(i, 1, new Q3TableItem(ui->sexTable, Q3TableItem::Never, QString::number(codeList[i].sex)));
        ui->sexTable->setItem(i, 2, new Q3TableItem(ui->sexTable, Q3TableItem::Always, "0"));//QString::number(codeList[i].head, 'f', 0)));
        ui->sexTable->setItem(i, 3, new Q3TableItem(ui->sexTable, Q3TableItem::Never, QString::number(codeList[i].head, 'f', 0)));
    }

    // remove all other defined prorates from the list

    for(unsigned int i = 0; i < prorateList.size(); i++)
    {
        if(i < prorateList.size() - 1)
        {
            removeProrateFromList(prorateList[i], prorateRow == i);
        }
    }

    // make all available sexes checkable
    for(unsigned int i = 0; i < ui->sexTable->numRows(); i++)
    {
        if(ui->sexTable->text(i, 0) != xChar)
        {
            ui->sexTable->setItem(i, 0, new Q3CheckTableItem(ui->sexTable, ""));
            ((Q3CheckTableItem*)ui->sexTable->item(i, 0))->setChecked(ui->sexTable->text(i, 2) != "0");
        }
    }
}

void ProrateSexDialog::removeProrateFromList(Prorate prorate, bool currentCustomer)
{
    vector<Prorate::Data> dataList = prorate.getDataList();

    for(unsigned int i = 0; i < dataList.size(); i++)
    {
        removeDataFromList(dataList[i], currentCustomer);
    }
}

void ProrateSexDialog::removeDataFromList(Prorate::Data data, bool currentCustomer)
{
    for(unsigned int i = 0; i < ui->sexTable->numRows(); i++)
    {
        if(data.number == ui->sexTable->text(i, 1).toLong())
        {
            if(!currentCustomer)
            {
                long head = ui->sexTable->text(i, 3).toLong();
                head -= (data.amount < head ? data.amount : head);
                ui->sexTable->setText(i, 2, "0");
                ui->sexTable->setText(i, 3, QString::number(head));

                if(head <= 0 && ui->sexTable->text(i, 0) != xChar)
                {
                    ui->sexTable->setItem(i, 0, new Q3TableItem(ui->sexTable, Q3TableItem::Never, xChar));
                }
            }
            else
            {
                ui->sexTable->setText(i, 2, QString::number(data.amount));
            }
        }
    }
}

vector<Prorate::Data> ProrateSexDialog::getProrateData()
{
    vector<Prorate::Data> dataList;
    Prorate::Data data;

    for(unsigned int i = 0; i < ui->sexTable->numRows(); i++)
    {
        if(ui->sexTable->text(i, 0) != xChar && ((Q3CheckTableItem*)ui->sexTable->item(i, 0))->isChecked())
        {
            data.number = codeList[i].sex;
            data.amount = ui->sexTable->text(i, 2).toDouble();
            dataList.push_back(data);
        }
    }
    return dataList;
}
