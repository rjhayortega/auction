//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "chargecreditdialog.h"
#include "ui_chargecreditdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <Q3Table>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

ChargeCreditDialog::ChargeCreditDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::ChargeCreditDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->acceptButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( ui->cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->adjustmentTable, SIGNAL( valueChanged(int,int) ), this, SLOT( showTotals() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
ChargeCreditDialog::~ChargeCreditDialog()
{
    delete ui;
}

void ChargeCreditDialog::init()
{
    isBuyer = false;
    ui->adjustmentTable->setLeftMargin(0);
    ui->adjustmentTable->setColumnWidth(0, 120);
    ui->adjustmentTable->setColumnWidth(1, 120);
    ui->adjustmentTable->setColumnWidth(0, ui->adjustmentTable->width() - (ui->adjustmentTable->columnWidth(1) + ui->adjustmentTable->columnWidth(2)) - 10);
}



///////////////////////////////////////////////////////////////////////////////
//
// name: init(Invoice*, bool)
//
// purpose: initializes the dialog with charges for the invoice
//
// calling params: Invoice* invoice - a reference to the invoice to get the
//                                    auto charges from
//                 bool isBuyer     - controls which customer type the dialog
//                                    represents, see preamble
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void ChargeCreditDialog::init(Invoice *invoice, bool isBuyer)
{
    this->invoice = invoice;
    if(invoice == NULL)
    {
        return;
    }
    this->isBuyer = isBuyer;
    vector<Charge> tempList = invoice->getUniqueChargeList(!isBuyer);
    vector<Charge>::iterator current;

    for(current = tempList.begin(); current != tempList.end(); current++)
    {
        if(!current->needsMultiplier() && current->getExpression() != "0")
        {
            chargeList.push_back(*current);
        }
    }

    populateAdjustmentTable();
}

///////////////////////////////////////////////////////////////////////////////
//
// name: populateAdjustmentTable()
//
// purpose: loads the adjustment table with values from the current invoice
//
// calling params: void
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void ChargeCreditDialog::populateAdjustmentTable()
{
    vector<ChargeRecord> recordList = invoice->getChargeRecordList(!isBuyer);
    if(invoice == NULL)
    {
        return;
    }
    ui->adjustmentTable->setNumRows(chargeList.size() + 1);
    vector<Charge>::iterator current;
    int row = 0;
    for(current = chargeList.begin(); current != chargeList.end(); current++)
    {
        ui->adjustmentTable->setItem(row, 0, new Q3TableItem(ui->adjustmentTable, Q3TableItem::Never,
                                     QString::fromStdString(current->getDescrip())));

        ui->adjustmentTable->setText(row, 1, QString::number(current->getAdjustment().getAdjustment(), 'f', 2));
        row++;
    }
    showTotals();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: showTotals()
//
// purpose: shows the total columns (after the adjustment) of the charges
//
// calling params: void
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void ChargeCreditDialog::showTotals()
{
    vector<ChargeRecord> recordList = invoice->getChargeRecordList(!isBuyer);

    double chargeTotal = 0.0;

    for(unsigned int row = 0; row < chargeList.size(); row++)
    {
        for(unsigned int i = 0; i < recordList.size(); i++)
        {
            if(chargeList[row].getId() == recordList[i].getId())
            {
                chargeTotal += recordList[i].getTotal() - ui->adjustmentTable->text(row, 1).toDouble();
                ui->adjustmentTable->setItem(row, 2, new Q3TableItem(ui->adjustmentTable, Q3TableItem::Never,
                                             QString::number(recordList[i].getTotal() - ui->adjustmentTable->text(row, 1).toDouble(), 'f', 2)));
            }
        }
    }

    ui->adjustmentTable->setItem(ui->adjustmentTable->numRows() - 1, 0, new
                                 Q3TableItem(ui->adjustmentTable, Q3TableItem::Never, "Total"));

    ui->adjustmentTable->setItem(ui->adjustmentTable->numRows() - 1, 1, new
                                 Q3TableItem(ui->adjustmentTable, Q3TableItem::Never, " "));

    ui->adjustmentTable->setItem(ui->adjustmentTable->numRows() - 1, 2, new
                                 Q3TableItem(ui->adjustmentTable, Q3TableItem::Never, QString::number(chargeTotal, 'f', 2)));
}


///////////////////////////////////////////////////////////////////////////////
//
// name: accept()
//
// purpose: Processes the 'Ok' button press
//
// calling params: void
//
// return params: void
//
// Notes: saves the adjustments to the adjustment table of the database,
//        updates the referenced invoice, and closes the dialog with an
//        Accepted state
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void ChargeCreditDialog::accept()
{
    if(invoice == NULL)
    {
        QDialog::reject();
    }
    for(unsigned int row = 0; row < chargeList.size(); row++)
    {
        chargeList[row].setAdjustment(ChargeAdjustment(1, ui->adjustmentTable->text(row, 1).toDouble(), chargeList[row].getAdjustment().needsMultiplier()));
        ChargeDAO().saveAdjustment(chargeList[row], *invoice, chargeList[row].getAdjustment());
    }

    invoice->adjustCharges(chargeList);
    QDialog::accept();
}
