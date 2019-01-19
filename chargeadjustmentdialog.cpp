//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "chargeadjustmentdialog.h"
#include "ui_chargeadjustmentdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qgroupbox.h>
#include <qlineedit.h>
#include <Q3Table>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "chargecreditdialog.h"

ChargeAdjustmentDialog::ChargeAdjustmentDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::ChargeAdjustmentDialog)
{
  ui->setupUi(this);
    // signals and slots connections
    connect( ui->acceptButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( ui->cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->creditButton, SIGNAL( clicked() ), this, SLOT( creditCharges() ) );
    connect( ui->buyerCommAmount, SIGNAL( textChanged(const QString&) ), this, SLOT( doCalclulateBuyerCommission() ) );
    connect( ui->buyerCommMode, SIGNAL( activated(int) ), this, SLOT( doCalclulateBuyerCommission() ) );
    connect( ui->groupCombo, SIGNAL( activated(int) ), this, SLOT( changeGroup(int) ) );
    connect( ui->buyerCommAmount, SIGNAL( lostFocus() ), ui->buyerCommAmount, SLOT( selectAll() ) );
    init();
}

ChargeAdjustmentDialog::~ChargeAdjustmentDialog()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////
//
// name: init()
// 
// purpose: sets up the dialog as a neutral dialog that neither buyers nor sellers
//          can use
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
void ChargeAdjustmentDialog::init()
{
  invoice = NULL;
  ui->buyerCommissionGroup->hide();
  setIsBuyer(false); 
  invoiceDao = NULL;
  ui->groupLabel->hide();
  ui->groupCombo->hide();
  ui->buyerCommMode->setCurrentItem(0);
  int columnWidth = 0.5 * (ui->adjustmentTable->width() - 40);
  ui->adjustmentTable->setColumnWidth(0, columnWidth);
  ui->adjustmentTable->setColumnWidth(1,columnWidth);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: init(Invoice*)
// 
// purpose: initializes the dialog with information from an invoice
//
// calling params: Invoice* invoice - pointer to the invoice which will 
//                                    calculate the various charges
// 
// return params: void
//
// Notes: 
//        
// Todo: 
//
///////////////////////////////////////////////////////////////////////////////
void ChargeAdjustmentDialog::init(Invoice *invoice)
{
  this->invoice = invoice;
 
  if(invoice == NULL)
  {
    return;
  }

  populateChargeList();
  ui->acceptButton->setFocus();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setInvoiceDAORef(InvoiceDAO* invoiceDao)
// 
// purpose: sets a pointer to the DAO used to access the invoice tables in the 
//          database
//
// calling params: InvoiceDAO* invoiceDao - a pointer to the DAO used to access
//                                          the invoice in the database
// 
// return params: void
//
// Notes: 
//        
// Todo: 
//
///////////////////////////////////////////////////////////////////////////////
void ChargeAdjustmentDialog::setInvoiceDAORef(InvoiceDAO* invoiceDao)
{
  this->invoiceDao = invoiceDao;
  ui->groupLabel->show();
  ui->groupCombo->show();
  changeGroup(0);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: changeGroup(int)
// 
// purpose: changes the color group that the charges will apply to.
//
// calling params: int selected - the color group (as a cardinal number)
// 
// return params: void
//
// Notes: 
//        
// Todo: 
//
///////////////////////////////////////////////////////////////////////////////
void ChargeAdjustmentDialog::changeGroup(int selected)
{
  if(invoiceDao != NULL)
  {
    invoice->setManualCharges(invoiceDao->getManualChargeList(CommissionDAO::COLOR_GROUP(selected)));
    invoice->setChargeStubList(invoiceDao->getCompleteChargeList(CommissionDAO::COLOR_GROUP(selected)));
    populateChargeList();
  }
}


///////////////////////////////////////////////////////////////////////////////
//
// name: populateChargeList()
// 
// purpose: loads the list of manual and multiplier charges into the list
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
void ChargeAdjustmentDialog::populateChargeList()
{
  if(invoice == NULL)
  {
    return;
  }

  vector<Charge> chargeList = invoice->getUniqueChargeList(); 
  

  if(invoiceDao != NULL)
  {
    invoiceDao->adjustChargeList(chargeList, invoice);
    invoice->adjustCharges(chargeList);
  }
  vector<Charge>::iterator current;
  
  multiplierList = vector<Charge>();
  for(unsigned int i = 0; i < chargeList.size(); i++)
  {
    if(chargeList[i].needsMultiplier() || chargeList[i].getExpression() == "0")
    {
      multiplierList.push_back(chargeList[i]);
    }
  }
 

  ui->adjustmentTable->setNumRows(multiplierList.size());
  int row = 0;
  QString entry;
  QStringList rowLabels;
  double entryAmount;
  for(current = multiplierList.begin(); current != multiplierList.end(); current++)
  {  
    entryAmount  = 0 - current->getAdjustment().getAdjustment();
  
    if(entryAmount < 0.01 && entryAmount > -0.01)
    {
      entryAmount = 0.000000;
    }
   
    entry = (current->getExpression() == "0" ? QString::number(entryAmount, 'f', 2) : 
	     QString::number(current->getAdjustment().getMultiplier(), 'f' ,2));
    rowLabels += (current->getExpression() == "0" ? "(  )" : "x");
  
  
    ui->adjustmentTable->setItem(row, 0, new Q3TableItem(ui->adjustmentTable, Q3TableItem::Never, QString::fromStdString(current->getDescrip())));
    ui->adjustmentTable->setItem(row, 1, new Q3TableItem(ui->adjustmentTable, Q3TableItem::Always, entry));
    row++;
  }

  ui->adjustmentTable->setRowLabels(rowLabels);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: accept()
// 
// purpose: processes dialog
//
// calling params: void
// 
// return params: void
//
// Notes: saves the changes to the charge adjustments and closes the dialog
//        with an 'Accepted' status
//        
// Todo: 
//
///////////////////////////////////////////////////////////////////////////////
void ChargeAdjustmentDialog::accept()
{
  if(invoice == NULL)
  {
    QDialog::reject();
  }
  vector<Charge>::iterator current;
 
  int row = 0;
  for(current = multiplierList.begin(); current != multiplierList.end(); current++)
  {
    if(multiplierList[row].getExpression() != "0")
    {
      multiplierList[row].setAdjustment(ChargeAdjustment(ui->adjustmentTable->text(row, 1).toDouble(), 0.0, true));
    }
    else
    {
      multiplierList[row].setAdjustment(ChargeAdjustment(1, 0 - ui->adjustmentTable->text(row, 1).toDouble(), false)); 
    }
 
 
    dao.saveAdjustment(*current,*invoice, multiplierList[row].getAdjustment());
    row++;
  }
 
  if(isBuyer)
  {
    CommissionDAO().saveBuyerCommission(ui->buyerCommAmount->text().toDouble(), 
					CommissionBreak::BuyerMode(ui->buyerCommMode->currentItem() + (ui->payeeCombo->currentItem() * 3)), 
					invoice->getCustomer().getNumber());
    Commission comm = calculateBuyerCommission();
    invoice->initCommissions(comm);
   
  }
 
  invoice->adjustCharges(multiplierList);
  QDialog::accept();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: creditCharges()
// 
// purpose: starts the charge credit dialog (adjust auto charges)
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
void ChargeAdjustmentDialog::creditCharges()
{
  ChargeCreditDialog dialog(this);
  dialog.init(invoice, isBuyer);
  dialog.exec();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: doCalculateBuyerCommission()
// 
// purpose: slot to access the calculateBuyerCommission() function with a
//          void return type (so that a signal can be connected)
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
void ChargeAdjustmentDialog::doCalclulateBuyerCommission()
{
  calculateBuyerCommission();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: calculateBuyerCommission()
// 
// purpose: calculates the buyer commission by the inputted data
//
// calling params: void
// 
// return params: Commission - the buyer commission
//
// Notes: 
//        
// Todo: 
//
///////////////////////////////////////////////////////////////////////////////
Commission ChargeAdjustmentDialog::calculateBuyerCommission()
{
  if(isBuyer)
  {
    Invoice temp(*invoice);
    CommissionBreak::BuyerMode buyerMode = CommissionBreak::BuyerMode(ui->buyerCommMode->currentItem());
    
    double amount = ui->buyerCommAmount->text().toDouble();   
    Commission comm = Commission::buyerCommission(buyerMode,amount);
    temp.initCommissions(comm);
    ui->buyerCommExtension->setText(QString::number(temp.getCommissionTotal(), 'f', 2));
    return comm;
  }
 
  return Commission();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setIsBuyer(bool)
// 
// purpose: sets the isBuyer flag to denote the customer type of the dialog
//
// calling params: bool isBuyer - the new truth value of the isBuyer flag
// 
// return params: void
//
// Notes: most dialogs use the Customer::Type type to implement this 
//        functionality, which is probably more correct as this is
//        one of the earlier attempts to separate these. But this is
//        here now and stable so I have no plans to change it to be
//        homogenous with the other dual purpose dialogs
//
//        changes the geometry of the dialog.
//        
// Todo: 
//
///////////////////////////////////////////////////////////////////////////////
void ChargeAdjustmentDialog::setIsBuyer( bool isBuyer)
{
  this->isBuyer = isBuyer;
  double amount = 0.0;
  SetupDAO setup;
  string defaultPayee = setup.get("binvDefaultCommissionPayee");
  CommissionBreak::BuyerMode mode = CommissionBreak::CWT;
  
  if(defaultPayee == "1")
  {
      mode = CommissionBreak::CompanyCWT;
  }


  if(isBuyer)
  {
      
    ui->buyerCommissionGroup->show();
    ui->adjustmentTable->setGeometry(10, 150, ui->adjustmentTable->width(), 220);
    CommissionDAO().getBuyerCommissionData(mode, amount, invoice->getCustomer().getNumber());
    if(mode > 2)
    {
	ui->payeeCombo->setCurrentItem(1);
	mode = CommissionBreak::BuyerMode(int(mode) - 3);
    }
    ui->buyerCommMode->setCurrentItem(mode);
    if(amount != 0.00)
    {
      ui->buyerCommAmount->setText(QString::number(amount, 'f', 2));
      ui->buyerCommAmount->selectAll();
    }
  }
  else
  {
    ui->buyerCommissionGroup->hide();
    ui->adjustmentTable->setGeometry(10, 10, ui->adjustmentTable->width(), 320);
  }
}



