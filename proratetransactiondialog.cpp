//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "proratetransactiondialog.h"
#include "ui_proratetransactiondialog.h"

#include <qvariant.h>
#include <Q3Table>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

ProrateTransactionDialog::ProrateTransactionDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::ProrateTransactionDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    init();
}

ProrateTransactionDialog::~ProrateTransactionDialog()
{
    delete ui;
}

void ProrateTransactionDialog::init()
{
    xChar = "-";
}

void ProrateTransactionDialog::init(vector<Transaction> transactionList, vector<Prorate> proratedList, unsigned int row)
{
    this->transactionList = transactionList;
    this->prorateRow = row;
    ui->transTable->insertRows(0, transactionList.size());
    ui->transTable->setColumnWidth(0, 20);
    ui->transTable->setColumnWidth(2, 150);
    ui->transTable->setColumnWidth(3, 150);
    QStringList ids;

    for(unsigned int i = 0; i < ui->transTable->numRows(); i++)
    {
        ids += QString::number(transactionList[i].getId());

        ui->transTable->setText(i, 1, QString::fromStdString(transactionList[i].getAnimalCode().getDescrip()));
        ui->transTable->setText(i, 2, QString::number(0));//transactionList[i].getHead()));
        ui->transTable->setItem(i, 3, new Q3TableItem(ui->transTable, Q3TableItem::Never, QString::number(transactionList[i].getHead())));
    }

    // fill the table with used values
    for(unsigned int i = 0; i < proratedList.size(); i++)
    {
        if(i < proratedList.size() - 1)
        {
            addProrateToTable(proratedList[i], i == prorateRow);
        }
    }

    // make sure that any items that are not 'x'-ed out can be checked
    for(unsigned int i = 0; i < ui->transTable->numRows(); i++)
    {
        if(ui->transTable->text(i, 0) != xChar && ui->transTable->text(i, 2) == "0")
        {
            ui->transTable->setItem(i, 0, new Q3CheckTableItem(ui->transTable, 0));
            ((Q3CheckTableItem*)ui->transTable->item(i, 0))->setChecked(false);
        }
    }

    ui->transTable->setRowLabels(ids);
}


void ProrateTransactionDialog::addProrateToTable(Prorate prorate, bool currentPayee)
{
    vector<Prorate::Data> dataList = prorate.getDataList();
    for(unsigned int i = 0; i < dataList.size(); i++)
    {
        addDataToTable(dataList[i], currentPayee);
    }
}

void ProrateTransactionDialog::addDataToTable(Prorate::Data data, bool currentPayee)
{
    for(unsigned int i = 0; i < transactionList.size(); i++)
    {
        if(transactionList[i].getId() == data.number)
        {
            if(!currentPayee)
            {
                double amount = ui->transTable->text(i, 3).toDouble();
                amount -= (data.amount < amount ? data.amount : amount);
                //transTable->setText(i, 2, QString::number(amount));
                ui->transTable->setText(i, 3, QString::number(amount));

                if(amount == 0 && ui->transTable->text(i, 0) != xChar)
                {
                    ui->transTable->setItem(i, 0, new Q3TableItem(ui->transTable, Q3TableItem::Never, xChar));
                }
            }
            else
            {
                ui->transTable->setText(i, 2, QString::number(data.amount));
                ui->transTable->setItem(i, 0, new Q3CheckTableItem(ui->transTable, ""));
                ((Q3CheckTableItem*)ui->transTable->item(i, 0))->setChecked(true);
            }
        }
    }
}

vector<Prorate::Data> ProrateTransactionDialog::getProrateData()
{
    Prorate::Data data;
    vector<Prorate::Data> dataList;

    for(unsigned int i = 0; i < ui->transTable->numRows(); i++)
    {
        if(ui->transTable->text(i, 0) != xChar && ((Q3CheckTableItem*)ui->transTable->item(i, 0))->isChecked())
        {
            data.number = transactionList[i].getId();
            data.amount = (ui->transTable->text(i, 2).toDouble() < ui->transTable->text(i, 3).toDouble() ? ui->transTable->text(i, 2).toDouble() : ui->transTable->text(i, 3).toDouble());

            dataList.push_back(data);
        }
    }

    return dataList;
}

