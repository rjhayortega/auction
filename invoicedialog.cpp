//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui.setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "invoicedialog.h"

#include "dailydialog.h"
#include "previewdialog.h"
#include "transactiondialog.h"
#include "truckingdialog.h"
#include "readysellerdialog.h"
#include "chargeadjustmentdialog.h"
#include "proratedialog.h"
#include "buyerrecapdialog.h"
#include "zipcodedialog.h"
#include "dao/zipcodedao.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QPrinter>
#include <QPainter>

#include <QVariant>
#include <QLabel>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <Q3Table>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
#include "reports/textsellerinvoice.h"
#include "reports/textbuyerinvoice.h"
// [KLN] adds
#include <QFileInfo>

InvoiceDialog::InvoiceDialog( QWidget* parent): QDialog( parent)
{
    ui.setupUi(this);
    m_textDocument = 0;
    m_invoicePrinter = 0;
    // signals and slots connections
    connect( ui.buyerRecapButton, SIGNAL( clicked() ), this, SLOT( startBuyerRecap() ) );
    connect( ui.changeStatusButton, SIGNAL( clicked() ), this, SLOT( setInvoiceStatus() ) );
    connect( ui.compAddressButton, SIGNAL( clicked() ), this, SLOT( overrideAddress() ) );
    connect( ui.customerTypeButtonGroup, SIGNAL( clicked(int) ), this, SLOT( changeCustomerType(int) ) );
    connect( ui.cycleButton, SIGNAL( clicked() ), this, SLOT( loadNumberList() ) );
    connect( ui.faxInvoiceButton, SIGNAL( clicked() ), this, SLOT( faxInvoice() ) );
    connect( ui.emailInvoiceButton, SIGNAL( clicked() ), this, SLOT( emailInvoice() ) );
    connect( ui.globalBuyerButton, SIGNAL( clicked() ), this, SLOT( globalBuyerChange() ) );
    connect( ui.globalPenButton, SIGNAL( clicked() ), this, SLOT( globalPenChange() ) );
    connect( ui.prorateButton, SIGNAL( clicked() ), this, SLOT( startProrate() ) );
    connect( ui.sinvAddress1, SIGNAL( returnPressed() ), ui.sinvPrintButton, SLOT( setFocus() ) );
    connect( ui.sinvAddress2, SIGNAL( returnPressed() ), ui.sinvPrintButton, SLOT( setFocus() ) );
    connect( ui.sinvChgButt, SIGNAL( clicked() ), this, SLOT( startChargeAdjustment() ) );
    connect( ui.sinvCity, SIGNAL( lostFocus() ), this, SLOT( loadCityStateZipFromCity() ) );
    connect( ui.sinvComment, SIGNAL( returnPressed() ), ui.sinvPrintButton, SLOT( setFocus() ) );
    connect( ui.sinvCompany, SIGNAL( returnPressed() ), ui.sinvPrintButton, SLOT( setFocus() ) );
    connect( ui.sinvHead, SIGNAL( returnPressed() ), ui.sinvPrintButton, SLOT( setFocus() ) );
    connect( ui.sinvID, SIGNAL( lostFocus() ), this, SLOT( initInvoiceById() ) );
    connect( ui.sinvID, SIGNAL( returnPressed() ), ui.sinvName, SLOT( setFocus() ) );
    connect( ui.sinvListReadyButton, SIGNAL( clicked() ), this, SLOT( showReadySellers() ) );
    connect( ui.sinvName, SIGNAL( returnPressed() ), this, SLOT( startPermSearch() ) );
    connect( ui.sinvPreviewButton, SIGNAL( clicked() ), this, SLOT( showPreview() ) );
    connect( ui.sinvPrintButton, SIGNAL( clicked() ), this, SLOT( printInvoice() ) );
    connect( ui.sinvSaveDaily, SIGNAL( clicked() ), this, SLOT( saveCustomerAsDaily() ) );
    connect( ui.sinvState, SIGNAL( returnPressed() ), ui.sinvPrintButton, SLOT( setFocus() ) );
    connect( ui.sinvTrucking, SIGNAL( clicked() ), this, SLOT( startTruckingDialog() ) );
    connect( ui.sinvZip, SIGNAL( returnPressed() ), this, SLOT( loadCityStateZipFromZip() ) );
    connect( ui.transactionTable, SIGNAL( clicked(int,int,int,const QPoint&) ), this, SLOT( editClickedTransaction(int,int) ) );
    connect( ui.showMissingBuyersButton, SIGNAL( clicked() ), this, SLOT( showMissingBuyers() ) );

    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
InvoiceDialog::~InvoiceDialog()
{
    delete m_invoicePrinter;
    delete m_checkPrinter;
    delete m_textDocument;

    if(invoiceDao != 0)
    {
        invoiceDao->freeInvoice();
        delete invoiceDao;
        invoiceDao = 0;
    }
    qDebug("~InvoiceDialog() exited");
}


/*
08 Sep 09 rhw	Modify InvoiceDialog::loadInvoiceFromId() adding a check to make
        sure address substitution only happens when customerType is Buyer.
        Otherwise, if seller and buyer have same 'number', the buyer info
        is picked up for seller.
04 Sep 09 rhw	compAddressButton added to allow override of address on screen
        from perm file. Lookup is from Company field.
07 Jul 09 rhw	Set head count warning red when head count does not match in
        seller invoice.
06 Jul 09 rhw	For each invoice that comes up as a result of loading all
        transactions where the (presumably partial) buyer number
        is present and the format bbb-nnn or bbb/nnn is used:
        1. following loading and display of the transactions,
        2. and display of the name, address, etc., from lookup of the buyer
            number in the daily file,
        3. a lookup is performed on the 'perm_number' field of the perm file
            (i.e., customer table), and if found, the name (last name),
            address, company, and comment is substituted on the screen.
16 Jun 09 rhw	Add beep when "Head Count Does Not Match Check-In" displayed.
29 Dec 08 rhw	Modify initInvoiceById so that it does NOT pop up a message box
        to ask whether to change country of origin (mad cow) certification.
        Instead, nothing is done to the country of origin setting, and
        the seller name is displayed in red.
*/


///////////////////////////////////////////////////////////////////////////////
//
// name:    init()
// 
// purpfose: constructor like function
// 
// calling params: 
// 
// return params:
//
// Notes: 
//        
// Todo:  
//
///////////////////////////////////////////////////////////////////////////////

void InvoiceDialog::init()
{
    qDebug("InvoiceDialog::init()");
    m_invoice = NULL;
    invoiceDao = 0;
    checkCount = 0; // [KLN] add

    ui.saleDateLabel->setText("<p align='right'>" + QString::fromStdString(sale.currentSaleDate().toString("mm/dd/YYYY") + "</p>"));
    allowPermSearch = true;
    blockInit = false;

    ui.transactionTable->setLeftMargin(0);
    ui.transactionTable->setColumnWidth(0, 70); //trans
    ui.transactionTable->setColumnWidth(1, 60); //head
    ui.transactionTable->setColumnWidth(3, 140); // descrip
    ui.transactionTable->setColumnWidth(4, 70); // buyer or seller
    ui.transactionTable->setColumnWidth(5, 60); // tag
    ui.transactionTable->setColumnWidth(6, 80); // pen
    ui.transactionTable->setColumnWidth(7, 80); // avg. wt
    ui.transactionTable->setColumnWidth(8, 80); // total wt
    ui.transactionTable->setColumnWidth(9, 100); // total cost
    ui.printedChecksComboBox->hide();
    m_checkPrinter = PrinterDAO().getPrinter(PrinterDAO::Check);

    bool enableFaxModem = SetupDAO().getBoolean("faxModemEnabled");
    ui.faxInvoiceButton->setHidden(!enableFaxModem);
    ui.faxInvoiceButton->setStyleSheet(QString("background-color: #ADFF2F"));

    QString homeDir = getenv("HOME");
    QString fileName = homeDir + "/dist-auction/AuctionEmail.jar";
//    cout << " homeDir: " << homeDir.toStdString() << endl;
//    cout << "fileName: " << fileName.toStdString() << endl;
    ui.emailInvoiceButton->setHidden(!fileExists(fileName));
    ui.emailInvoiceButton->setStyleSheet(QString("background-color: #9DDFD5"));

    topSkip = 0;
    pageHeight = 0;
    checkStart = 0;
    showSexSummary = false;
    averageOnLeft = false;
    binvTotalNS = false;
    if(sale.currentSaleOpen())
    {
        ui.sinvTrucking->setEnabled(true);
        ui.prorateButton->setEnabled(true);
        ui.sinvChgButt->setEnabled(true);
        ui.sinvSaveDaily->setEnabled(true);
        ui.buyerRecapButton->setEnabled(true);
        ui.globalBuyerButton->setEnabled(true);
        ui.globalPenButton->setEnabled(true);
        ui.changeStatusButton->setEnabled(true);
        ui.compAddressButton->setEnabled(true);
    }
    else
    {
        ui.sinvTrucking->setEnabled(false);
        ui.prorateButton->setEnabled(false);
        ui.sinvChgButt->setEnabled(false);
        ui.sinvSaveDaily->setEnabled(false);
        ui.buyerRecapButton->setEnabled(false);
        ui.globalBuyerButton->setEnabled(false);
        ui.globalPenButton->setEnabled(false);
        ui.changeStatusButton->setEnabled(false);
        ui.compAddressButton->setEnabled(false);
    }
    minimumHeaderSize = 0;

    transOverrideColumn = 0;
    transOverrideLength = 0;

}

///////////////////////////////////////////////////////////////////////////////
//
// name:    init(CUSTOMER_TYPE)
// 
// purpose: sets up the invoice as a  SELLER or BUYER invoice 
// calling params: Customer::Type custType - the type of the invoice
// 
// return params:
//
// Notes: 
//        
// Todo: 
//
///////////////////////////////////////////////////////////////////////////////

void InvoiceDialog::init(Customer::Type custType)
{
    qDebug("InvoiceDialog::init(Customer::Type custType)");

//    cout << "init(Customer type) ......................." << endl;

    ui.printedChecksComboBox->hide();
    if(blockInit)
    {
        return;
    }
    blockInit = true;
    if( invoiceDao != 0 )
    {
        invoiceDao->freeInvoice();
        delete invoiceDao;
        invoiceDao = 0;
    }
    if ( m_invoicePrinter != 0 ) {
        delete m_invoicePrinter;
        m_invoicePrinter = 0;
    }

    customerType = custType;
    numberList.clear();
    ui.sinvID->setEnabled(true);
    string groupChargesKey;
    string replaceAddressCoMatchKey;
    string headerSizeKey;
    string transOverrideColumnKey;
    string transOverrideLengthKey;

    switch(custType)
    {
    case Customer::Seller:
        invoiceDao = new SellerInvoiceDAO();
        format = checkDao.getCheckFormat(true);
        ui.binvPaid->hide();
        ui.binvUnpaid->hide();
        ui.binvCompany->hide();
        ui.sinvHead->show();
        ui.headLabel->show();
        ui.companyLabel->setText("Mortgage");
        ui.sinvHCountWarning->show();
        this->setCaption("Seller Invoice");
        ui.sinvListReadyButton->setText("&List Ready");
        ui.sinvPrinted->show();
        ui.prorateButton->show();
        this->setCaption("Seller Invoice");
        ui.buyerRecapButton->hide();
        ui.sellerButton->setChecked(true);
        ui.cycleButton->setText("Re&maining");
        ui.transactionTable->horizontalHeader()->setLabel(3, "Buyer");
        ui.globalBuyerButton->hide();
        ui.globalPenButton->hide();
        m_invoicePrinter = PrinterDAO().getPrinter(PrinterDAO::SellerInvoice);
        ui.changeStatusButton->hide();
        ui.compAddressButton->hide();
        chkOnInvoice = bool(atoi(setup.get("sinvChkOnInvoice").c_str()));
        showSexSummary = setup.getBoolean("sinvShowSexAvgs");
        groupChargesKey = "sinvGroupCharges";
        headerSizeKey = "sinvMinHeaderSize";
        transOverrideColumnKey = "sinvTransOverrideColumn";
        transOverrideLengthKey = "sinvTransOverrideLength";
        ui.showMissingBuyersButton->hide();

        break;

    case Customer::Buyer:
        chkOnInvoice = false;
        ui.binvPaid->show();
        ui.binvUnpaid->show();
        ui.binvCompany->show();

        ui.sinvHead->hide();
        ui.headLabel->hide();
        ui.companyLabel->setText("Company");
        ui.sinvHCountWarning->hide();
        invoiceDao = new BuyerInvoiceDAO();
        this->setCaption("Buyer Invoice");
        ui.sinvListReadyButton->setText("&Unprinted");
        ui.sinvPrinted->hide();
        ui.prorateButton->hide();
        ui.buyerRecapButton->show();
        this->setCaption("Buyer Invoice");
        ui.cycleButton->setText("&All");
        ui.buyerButton->setChecked(true);
        ui.transactionTable->horizontalHeader()->setLabel(3, "Seller");
        ui.globalBuyerButton->show();
        ui.globalPenButton->show();
        m_invoicePrinter = PrinterDAO().getPrinter(PrinterDAO::BuyerInvoice);
        ui.changeStatusButton->show();
        ui.compAddressButton->show();
        showSexSummary =setup.getBoolean("binvShowSexAvgs");
        averageOnLeft = setup.getBoolean("binvOverallCWTOnRight");
        groupChargesKey = "binvGroupCharges";
        headerSizeKey = "binvMinHeaderSize";
        transOverrideColumnKey = "binvTransOverrideColumn";
        transOverrideLengthKey = "binvTransOverrideLength";
        binvTotalNS = setup.getBoolean("binvTotalNS");
        ui.showMissingBuyersButton->show();
    }

    ui.sinvID->setText("");
    ui.sinvID->setFocus();

    topSkip = invoiceDao->topSkip();
    pageHeight = invoiceDao->pageHeight();
    checkStart = invoiceDao->checkStart();
    groupCharges = setup.getBoolean(groupChargesKey);
    resetInvoice();
    blockInit = false;
    minimumHeaderSize = atol(setup.get(headerSizeKey).c_str());

    transOverrideColumn = atoi(setup.get(transOverrideColumnKey).c_str());
    transOverrideLength = atoi(setup.get(transOverrideLengthKey).c_str());
    //cout << "............ init(Customer type)" << endl;
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    loadInvoiceFromId
// 
// purpose: loads the invoice for customer sinvID->text() into the dialog
// 
// calling params: 
// 
// return params:
//
// Notes: 
//        
// Todo:  
//
///////////////////////////////////////////////////////////////////////////////

void InvoiceDialog::loadInvoiceFromId()
{
//    cout << "InvoiceDialog::loadInvoiceFromId ......................." << endl;
    qDebug("InvoiceDialog::loadInvoiceFromId()");
    QString invoiceID = ui.sinvID->text().stripWhiteSpace();
    checkCount = 0; // [KLN] add

    if (invoiceID.isEmpty()) {
        //Do nothing if invoice ID is empty
        qDebug("InvoiceDialog::loadInvoiceFromId() - empty invoice ID, return.");
        return;
    }
    qDebug()<< "InvoiceDialog::loadInvoiceFromId() - invoice ID = " << invoiceID;

    if(m_invoice != NULL)
    {
        qDebug()<< "InvoiceDialog::loadInvoiceFromId() m_invoice not null, free invoice" ;
        invoiceDao->freeInvoice();
        m_invoice = NULL;
    }

    setCursor(Qt::WaitCursor);
    //  invoiceDao->resetTiming();
    AnimalCodeDAO::startBatchMode();
    m_invoice = invoiceDao->getInvoiceByCustomer(invoiceID.toStdString());
    AnimalCodeDAO::endBatchMode();
    /*
  if(customerType == Customer::Buyer && invoice->getCustomer().getId() == 0 && atol(invoice->getCustomer().getNumber().c_str()) != 0)
  {
    invoice->setCustomer(CustomerDAO::loadFromPermNumber(invoice->getCustomer().getNumber()));
  }
  */

    /*
  vector<Charge>chargeList = invoice->getUniqueChargeList();
  vector<Charge>::iterator current;

  for(current = chargeList.begin(); current != chargeList.end(); current++)
  {
    current->setAdjustment(ChargeDAO().getAdjustment(*current, invoice, invoiceDao->customerType()));
  }
  
  invoice->adjustCharges(chargeList);
*/

    if(ui.sinvID->text().stripWhiteSpace() != "")
    {
        showInvoice();
    }

    //
    // If there is a daily (buyer tbl) entry, then prefer that to the perm entry.
    // Otherwise, look up the perm data (customer tbl) and show that.
    //
    if(customerType == Customer::Buyer) {
        //    [KLN] start
        QString fullBuyerID =  ui.sinvID->text().stripWhiteSpace();
        QString baseBuyerID; // will always be empty unless fullBuyerID has a slash or dash
        int posDash  = fullBuyerID.find('-', 0, false);
        int posSlash = fullBuyerID.find('/', 0, false);
        int position = posDash > 0 ? posDash : posSlash > 0 ? posSlash : 0;
        if (position > 0) {
            baseBuyerID = fullBuyerID.left(position);
        }
        string buyerNum = baseBuyerID.isEmpty() ? fullBuyerID.toStdString() : baseBuyerID.toStdString();
//        cout << "Buyer numbers:" << endl;
//        cout << "fullBuyerID: " << fullBuyerID.toStdString() << endl;
//        cout << "baseBuyerID: " << baseBuyerID.toStdString() << endl;
//        cout << "   buyerNum: " << buyerNum << endl;
        //    [KLN] end

        BuyerDAO buyerdao;
//        cout << "LOOK UP BUYER " << ui.sinvID->text().toStdString() << " IN Buyer AND DISPLAY ADDR" << endl;
//        Buyer tempbuyer = BuyerDAO::loadFromNumber(ui.sinvID->text().stripWhiteSpace().toStdString());
//        cout << "LOOK UP BUYER " << buyerNum << " IN Buyer AND DISPLAY ADDR" << endl;
        Buyer tempbuyer = BuyerDAO::loadFromNumber(fullBuyerID.toStdString());
        if ( buyerdao.buyerExists(tempbuyer) ) {
            //    [KLN] start
//            cout << "From BUYER table:" << endl;
//            cout << "----          buyer name: " << tempbuyer.getName().getLast() << endl;
//            cout << "----              number: " << tempbuyer.getNumber() << endl;
//            cout << "----customerPartOfNumber: " << tempbuyer.getCustomerPartOfNumber() << endl;
//            cout << "----          permNumber: " << tempbuyer.getPermNumber().toStdString() << endl;
            //    [KLN] end
            //cout << "----buyer name:" << tempbuyer.getName().getLast() << " comment:" << tempbuyer.getComment() << endl;
            ui.sinvName->setText(QString::fromStdString(tempbuyer.getName().getLast()));
            ui.sinvAddress1->setText(QString::fromStdString(tempbuyer.getAddress().getAddress1()));
            ui.sinvAddress2->setText(QString::fromStdString(tempbuyer.getAddress().getAddress2()));
            ui.sinvCity->setText(QString::fromStdString(tempbuyer.getAddress().getCity()));
            ui.sinvState->setText(QString::fromStdString(tempbuyer.getAddress().getState()));
            ui.sinvZip->setText(QString::fromStdString(tempbuyer.getAddress().getZip()));
            ui.sinvComment->setText(QString::fromStdString(tempbuyer.getComment()));
            ui.sinvCompany->setText(QString::fromStdString(tempbuyer.getCompany()));

        } else {
            cout << "Buyer not in buyer table, checking perm table" << endl;
            // look up customer in perm file (customer table) and display address
            // from perm
//            if(customerType == Customer::Buyer) {
//            cout << "LOOK UP CUSTOMER " << ui.sinvID->text().toStdString() << " IN PERM AND DISPLAY ADDR" << endl;
            cout << "LOOK UP CUSTOMER " << buyerNum << " IN PERM AND DISPLAY ADDR" << endl;
                //Customer CustomerDAO::loadFromPermNumber(string number, bool loadSplits)
//            Customer tempcust = CustomerDAO::loadFromPermNumber(ui.sinvID->text().stripWhiteSpace().toStdString(), false);
            Customer tempcust = CustomerDAO::loadFromPermNumber(buyerNum, false);
                if ( tempcust.getId() == 0 )	{
                    // failed to find a perm customer for this buyer number
                    cout << "----failed to find perm customer for buyer " << buyerNum << endl;

                    // see if we can strip an order number from the ID and still find in buyer table. If
                    // found, then use that.
                    tempbuyer = BuyerDAO::loadFromBuyerByNumber(buyerNum);
                    if ( tempbuyer.getId() != 0 ) {
                        // ok, found this by the root buyer number
                        cout << "----FOUND the buyer, name, id: " << buyerNum << "  " << tempbuyer.getName().getLast() << "  " << tempbuyer.getId() << endl;
                        ui.sinvName->setText(QString::fromStdString(tempbuyer.getName().getLast()));
                        ui.sinvAddress1->setText(QString::fromStdString(tempbuyer.getAddress().getAddress1()));
                        ui.sinvAddress2->setText(QString::fromStdString(tempbuyer.getAddress().getAddress2()));
                        ui.sinvCity->setText(QString::fromStdString(tempbuyer.getAddress().getCity()));
                        ui.sinvState->setText(QString::fromStdString(tempbuyer.getAddress().getState()));
                        ui.sinvZip->setText(QString::fromStdString(tempbuyer.getAddress().getZip()));
                        ui.sinvComment->setText(QString::fromStdString(tempbuyer.getComment()));
                        ui.sinvCompany->setText(QString::fromStdString(tempbuyer.getCompany()));
                    } else {
                        // clear screen data and focus to Name
                        cout << "----clear screen to spaces, no find on buyer: " << buyerNum << endl;
                        ui.sinvName->setText("");
                        ui.sinvAddress1->setText("");
                        ui.sinvAddress2->setText("");
                        ui.sinvCity->setText("");
                        ui.sinvState->setText("");
                        ui.sinvZip->setText("");
                        ui.sinvComment->setText("");
                        ui.sinvCompany->setText("");

                        ui.sinvName->setFocus();
                    }
//                    QString qstr = QString( ui.sinvID->text().stripWhiteSpace() );
//                    //cout << "----strip out any order number down to: " << qstr << endl;
//                    int cpos = qstr.find('-', 0, false);
//                    if ( cpos > 0 )	{
//                        cout << "----found a - in the number at: " << cpos << endl;
//                        string strippedId = qstr.left(cpos).toStdString();
//                        cout << "----strippedId: " << strippedId << endl;
                        //
                        // use loadFromBuyerByNumber(numberstr) because it doesn't automatically
                        // load from perm on failure in buyer table
                        //
//                        tempbuyer = BuyerDAO::loadFromBuyerByNumber(strippedId);
//                        if ( tempbuyer.getId() != 0 ) {
//                            // ok, found this by the root buyer number
//                            cout << "----FOUND the buyer, name, id: " << strippedId << "  " << tempbuyer.getName().getLast() << "  " << tempbuyer.getId() << endl;
//                            ui.sinvName->setText(QString::fromStdString(tempbuyer.getName().getLast()));
//                            ui.sinvAddress1->setText(QString::fromStdString(tempbuyer.getAddress().getAddress1()));
//                            ui.sinvAddress2->setText(QString::fromStdString(tempbuyer.getAddress().getAddress2()));
//                            ui.sinvCity->setText(QString::fromStdString(tempbuyer.getAddress().getCity()));
//                            ui.sinvState->setText(QString::fromStdString(tempbuyer.getAddress().getState()));
//                            ui.sinvZip->setText(QString::fromStdString(tempbuyer.getAddress().getZip()));
//                            ui.sinvComment->setText(QString::fromStdString(tempbuyer.getComment()));
//                            ui.sinvCompany->setText(QString::fromStdString(tempbuyer.getCompany()));
//                        } else {
//                            // clear screen data and focus to Name
//                            cout << "----clear screen to spaces, no find on buyer: " << strippedId << endl;
//                            ui.sinvName->setText("");
//                            ui.sinvAddress1->setText("");
//                            ui.sinvAddress2->setText("");
//                            ui.sinvCity->setText("");
//                            ui.sinvState->setText("");
//                            ui.sinvZip->setText("");
//                            ui.sinvComment->setText("");
//                            ui.sinvCompany->setText("");

//                            ui.sinvName->setFocus();
//                        }
//                    }

                } else {
                    cout << "----customer name:" << tempcust.getName().getLast() << " comment:" << tempcust.getComment() << endl;
                    //    [KLN] start
//                    cout << "From CUSTOMER (perm) table:" << endl;
//                    cout << "----          buyer name: " << tempcust.getName().getLast() << endl;
//                    cout << "----              number: " << tempcust.getNumber() << endl;
//                    cout << "----customerPartOfNumber: " << tempcust.getCustomerPartOfNumber() << endl;
//                    cout << "----          permNumber: " << tempcust.getPermNumber().toStdString() << endl;
                    //    [KLN] end
                    ui.sinvName->setText(QString::fromStdString(tempcust.getName().getLast()));
                    ui.sinvAddress1->setText(QString::fromStdString(tempcust.getAddress().getAddress1()));
                    ui.sinvAddress2->setText(QString::fromStdString(tempcust.getAddress().getAddress2()));
                    ui.sinvCity->setText(QString::fromStdString(tempcust.getAddress().getCity()));
                    ui.sinvState->setText(QString::fromStdString(tempcust.getAddress().getState()));
                    ui.sinvZip->setText(QString::fromStdString(tempcust.getAddress().getZip()));
                    ui.sinvComment->setText(QString::fromStdString(tempcust.getComment()));
                    ui.sinvCompany->setText(QString::fromStdString(tempcust.getCompany()));
                }
//            }

        }

    }  //... (customerType == Customer::Buyer)


    if(m_invoice->getCustomer().getName().getLast().length() == 0)
    {
        ui.sinvName->setFocus();
    }
    else
    {
        ui.sinvPrintButton->setFocus();
    }
    // invoiceDao->printTiming();
    setCursor(Qt::ArrowCursor);

}

void InvoiceDialog::initInvoiceById()
{
    qDebug("InvoiceDialog::initInvoiceById()");
    QColor clr = QColor("black");

    loadInvoiceFromId();

    if (0 == m_invoice) {
        return; //Invoice not initialized, nothing to do.
    }
    
    if(customerType == Customer::Seller && setup.getBoolean("useCountryOfOrigin", true))
    {

        /* ***************************
    if(!invoice->getCustomer().isMadCowCertified())
    {
        int option = QMessageBox::warning(this, "Country Of Origin", "Seller is not marked as Country of origin\nWhat do you want to do?", "Ignore", "Change");

         if(option == 1)
        {
         Customer temp = invoice->getCustomer();
                 Seller tempSeller(temp);
         tempSeller.setMadCowCertified(true);
         SellerDAO::saveCustomer(tempSeller);
         SellerDAO::updateParentCountryOfOrigin(tempSeller);
         invoice->setCustomer(tempSeller);
         }
    }
    ******************* */

        // Look up the parent record for the seller in the invoice, and
        // use the isMadCowCertified() indicator for the parent/customer
        // to determine how to display the name.
        Customer ic = m_invoice->getCustomer();
        //cout << "invoicedialog.ui.h: ic is new customer" << endl;
        Seller ts(ic);
        //cout << "invoicedialog.ui.h: ts is new seller" << endl;
        //cout << "invoicedialog.ui.h: customer id for ts = " << ts.getId() << endl;
        Customer p = CustomerDAO::loadFromId(ts.getId());
        //cout << "invoicedialog.ui.h: customer p customer id = " << p.getId() << endl;
        //cout << "invoicedialog.ui.h: customer p mad_cow     = " << p.isMadCowCertified() << endl;
        //if(!invoice->getCustomer().isMadCowCertified())
        if(!p.isMadCowCertified())
        {
            //cout << "invoicedialog.ui.h: set name red" << endl;
            clr = QColor("red");
        }
        ui.sinvName->setPaletteForegroundColor( clr );
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    showInvoice()
// 
// purpose: displays the current invoice
// 
// calling params: 
// 
// return params:
//
// Notes: 
//        
// Todo:  
//
///////////////////////////////////////////////////////////////////////////////

void  InvoiceDialog::showInvoice()
{
    qDebug("InvoiceDialog::showInvoice()");
    QColor clr = QColor("black");

    if(m_invoice == NULL)
        return;


    Customer *customer;

    string customerNumber = m_invoice->getCustomer().getNumber();

    //  if(customerNumber == "")
    //  {
    //   return;
    //  }


    ui.sinvOverallAverage->setText(QString::number(m_invoice->averageWeight((customerType == Customer::Seller)), 'f', 0));
    ui.sinvOverallWeight->setText(QString::number(m_invoice->weight(customerType == Customer::Seller), 'f', 0));
    ui.sinvOverallTotal->setText(QString::number(m_invoice->gross(), 'f', 2));
    ui.sinvOverallBid->setText(QString::number(m_invoice->averageDolPerCW(), 'f' ,2));
    Seller tempSeller;
    Buyer tempBuyer;
    vector<Check> invoiceCheckList;

    ui.printedChecksComboBox->hide();

    switch(customerType)
    {
    case Customer::Seller:
        ui.sinvOverallHead->setText(QString::number(m_invoice->head(true, true)));
        tempSeller = SellerDAO::loadFromNumber(customerNumber);
        ui.sinvHead->setText(QString::number(tempSeller.getHead()));
        ui.sinvCompany->setText(QString::fromStdString(tempSeller.getMortgage()));
        customer = new Customer(tempSeller);
        ui.sinvPrinted->show();
        // KLN add
        if (invoiceDao->printed(*m_invoice)) { // true if printed
            ui.sinvPrinted->setEnabled(true);
            ui.sinvPrinted->setPaletteForegroundColor("green");
        } else {
            ui.sinvPrinted->setEnabled(false);
            ui.sinvPrinted->setPaletteForegroundColor("gray");
        }
        // KLN end add
//        ui.sinvPrinted->setEnabled(invoiceDao->printed(*m_invoice)); // KLN
        if ( tempSeller.getHead() != m_invoice->head(true, true) )	{
            ui.sinvHCountWarning->setEnabled(true);
            clr = QColor("red");
//            consoleout.beep(); // KLN
        } else {
            ui.sinvHCountWarning->setEnabled(false);
            clr = QColor("gray");
        }
        ui.sinvHCountWarning->setPaletteForegroundColor( clr );

        invoiceCheckList = checkDao.getInvoiceCheckList(m_invoice->getNumber());

        if(invoiceCheckList.size() > 0)
        {
            ui.printedChecksComboBox->show();
            QStringList checkNumberList;

            checkNumberList << QString::number(invoiceCheckList[0].getNumber());

            if(invoiceCheckList.size() > 1)
            {
                checkNumberList[0] = "*" + checkNumberList[0];
            }

            for(unsigned int i = 1; i < invoiceCheckList.size(); i++)
            {
                checkNumberList += QString::number(invoiceCheckList[i].getNumber());
            }

            ui.printedChecksComboBox->clear();
            ui.printedChecksComboBox->insertStringList(checkNumberList);

        }

        break;

    case Customer::Buyer:
        ui.sinvOverallHead->setText(QString::number(m_invoice->head(true, false)));
        ui.binvPaid->setEnabled(false);
        ui.binvUnpaid->setEnabled(false);
        ui.binvCompany->setEnabled(false);

        switch(m_invoice->getStatus())
        {
        case Invoice::PAID:
            ui.binvPaid->setEnabled(true);
            break;

        case Invoice::UNPAID:
        default:
            ui.binvUnpaid->setEnabled(true);
            break;

        case Invoice::BILLED:
            ui.binvCompany->setEnabled(true);
            break;
        }
        tempBuyer = BuyerDAO::loadFromNumber(customerNumber);
        ui.sinvCompany->setText(QString::fromStdString(tempBuyer.getCompany()));
        customer = new Customer(tempBuyer);
        ui.sinvPrinted->hide();
        break;
    }

    ui.sinvID->setText(QString::fromStdString(customer->getNumber()));
    allowPermSearch  = false;
    ui.sinvName->setText(QString::fromStdString(customer->getName().getLast()));
    allowPermSearch = true;

    Address address = customer->getAddress();
    ui.sinvAddress1->setText(QString::fromStdString(address.getAddress1()));
    ui.sinvAddress2->setText(QString::fromStdString(address.getAddress2()));
    ui.sinvCity->setText(QString::fromStdString(address.getCity()));
    ui.sinvState->setText(QString::fromStdString(address.getState()));
    ui.sinvZip->setText(QString::fromStdString(address.getZip()));

    // For Buyer invoice, if the company field is not blank, AND if
    // there is a permanent record for the buyer with an identical company
    // name recorded, then substitute the address fields from the permanent
    // record over the daily file record.
    // 2009-06-18 rhw
    //cout << "CHECKING ON binvReplaceAddress" << endl;
    if (  setup.getBoolean("binvReplaceAddress", false) )	{
        //cout << "LOOK UP ON COMPANY FOR BUYER." << endl;
        if ( customerType == Customer::Buyer && ui.sinvCompany->text() != "" )	{
            //cout << "Pull the address info from perm file rather than buyer." << endl;
            CustomerDAO *cdao;
            //Customer tempcust = cdao->loadFromId(customer->getId());
            Customer tempcust = cdao->loadFromName(customer->getName().getLast());
            //cout << "tempcust: " << tempcust.getName().getLast() << " * " << tempcust.getAddress().getAddress1() << " * " << tempcust.getComment() << endl;

            //if ( tempcust.getCompany() == customer->getCompany()  )	{
            //cout << "Company names both " << tempcust.getCompany() << endl;
            Address address = tempcust.getAddress();
            ui.sinvAddress1->setText(QString::fromStdString(address.getAddress1()));
            ui.sinvAddress2->setText(QString::fromStdString(address.getAddress2()));
            ui.sinvCity->setText(QString::fromStdString(address.getCity()));
            ui.sinvState->setText(QString::fromStdString(address.getState()));
            ui.sinvZip->setText(QString::fromStdString(address.getZip()));
            //}
        }
    }
    // end of Buyer invoice substitution change.

    ui.sinvComment->setText(QString::fromStdString(customer->getComment()));
    vector<Transaction> transList = m_invoice->getTransactionList();
    std::sort(transList.begin(), transList.end(), Transaction::compareIdsLT);

    ui.transactionTable->setNumRows(transList.size());
    AnimalCodeDAO animalDao;

    QString headStr;
    double cwt = 0.00;
    long head = 0;
    int row = 0;
    bool useCountryOfOrigin = setup.getBoolean("useCountryOfOrigin", true);

    for(unsigned int i = 0; i < transList.size(); i++)
    {
        cwt = transList[i].getCWT(false);
        head = transList[i].getHead(false, false);
        headStr = QString::number(head);

        string tagString;
        QStringList tagStringList;

        vector<Tag> tagList = transList[i].getTagList();
        sort(tagList.begin(), tagList.end(), Tag::compareTagsLT);
        if(tagList.size() > 0)
        {
            tagString = tagList[0].getTag();
            //cout << "  tag string " << tagString << endl;

            for(unsigned int i = 1; i < tagList.size(); i++)
            {
                tagStringList += QString::fromStdString(tagList[i].getTag());
            }
        }

        Q3TableItem* configureableItem = new Q3TableItem(ui.transactionTable, Q3TableItem::Never, "");
        ui.transactionTable->setItem(row, 1, configureableItem);
        configureableItem->setSpan(1, 1);
        ui.transactionTable->setText(row, 0, QString::number(transList[i].getId()) + (transList[i].isManual() ? "M" : "") + (transList[i].swapped() ? "-S" : ""));
        ui.transactionTable->setText(row, 1, headStr + (transList[i].getAnimalCode().isPair() ? "/" + headStr : ""));
        ui.transactionTable->setText(row ,2, QString::fromStdString(transList[i].getAnimalCode().getDescrip()));

        ui.transactionTable->setText(row, 3, (customerType == Customer::Seller ? QString::fromStdString(transList[i].getBuyer().getNumber()) : QString(transList[i].getSeller().isMadCowCertified() && useCountryOfOrigin ? "*": "") + QString::fromStdString(transList[i].getSeller().getNumber())));
        ui.transactionTable->setText(row, 4,  QString::fromStdString(tagString));
        ui.transactionTable->setText(row, 5, QString::fromStdString(transList[i].getBuyerPen()));
        ui.transactionTable->setText(row, 6, QString::number(transList[i].getAverageWeight(false), 'f', 0));
        ui.transactionTable->setText(row, 7, QString::number(transList[i].getWeight(false)));
        ui.transactionTable->setText(row, 8, QString::number(transList[i].getPrice(false), 'f', 2));

        QString amountText = QString::number(transList[i].amount(), 'f', 2);
        if(transList[i].getMode() == Transaction::NoSaleHead || transList[i].getMode() == Transaction::NoSaleCWT)
        {
            amountText = "N/S";
        }

        ui.transactionTable->setText(row, 9, amountText);
        row++;

        if(tagStringList.size() > 0)
        {
            ui.transactionTable->insertRows(row, 1);
            Q3TableItem *tagItem = new Q3TableItem(ui.transactionTable, Q3TableItem::Never, "");
            ui.transactionTable->setItem(row, 1, tagItem);
            ui.transactionTable->setText(row, 0, "TAGS: ");
            tagItem->setSpan(1, 9);
            ui.transactionTable->setText(row, 1, tagStringList.join(", ") + ";");
            row++;
        }
    }
    ui.transactionTable->verticalHeader()->hide();
    delete customer;
}



///////////////////////////////////////////////////////////////////////////////
//
// name:    saveCustomerAsDaily()
// 
// purpose: saves the customer to the appropriate daily table in the database
// 
// calling params: 
// 
// return params:
//
// Notes: 
//        
// Todo:  
//
///////////////////////////////////////////////////////////////////////////////

void InvoiceDialog::saveCustomerAsDaily()
{
    qDebug("InvoiceDialog::saveCustomerAsDaily()");
    if(m_invoice == NULL)
    {
        return;
    }

    Name name(ui.sinvName->text().toStdString());
    string mortgage = ui.sinvCompany->text().toStdString();
    Address address(ui.sinvAddress1->text().toStdString(), ui.sinvAddress2->text().toStdString(),
                    ui.sinvCity->text().toStdString(), ui.sinvState->text().toStdString(), ui.sinvZip->text().toStdString());

    Date date = Date::currentDate();
    long head = ui.sinvHead->text().toLong();
    string comment = ui.sinvComment->text().toStdString();

    Seller tempSeller;
    Buyer tempBuyer;
    Customer existingCustomer;

    Customer temp = m_invoice->getCustomer();

    temp.setName(name);
    temp.setAddress(address);
    temp.setCompany(mortgage);
    temp.setHead(head);
    temp.setComment(ui.sinvComment->text().toStdString());
    int opt  = 1;
    switch(customerType)
    {
    case Customer::Seller:
    {
        temp = DailyDialog::checkPayeeLength(temp, this);
        Seller tempSeller(temp, head);
        SellerDAO::saveCustomer(tempSeller);
        //    SellerDAO::updateParentCountryOfOrigin(tempSeller);
    }
        break;

    case Customer::Buyer:
        //   existingCustomer = CustomerDAO::loadFromPermNumber(temp.getNumber());
        //    if(existingCustomer.getId() != 0 && existingCustomer.getId() != temp.getId())
        //    {
        //      opt = QMessageBox::question(this, "Warning",
        //      "This number is presently in use by another buyer\n"
        //      "What should the program do?",
        //      "Don't Save", "Overwrite");
        //    }

        //    if(opt == 1)
        //    {

        BuyerDAO::saveCustomer(temp);
        //    }
        break;
    }

    loadInvoiceFromId();

}


///////////////////////////////////////////////////////////////////////////////
//
// name:    showPreview()
// 
// purpose: shows a preview of what the printed invoice will lo like
// 
// calling params: 
// 
// return params:
//
// Notes: 
//        
// Todo:  Move all report generation to a seperate class Invoice or a new class
//        InvoiceReport : TextReport ?
//
///////////////////////////////////////////////////////////////////////////////

void InvoiceDialog::showPreview()
{
    /*
    QStringList checkTextList;
    TextInvoice *textInvoice;
    int result = prepareInvoiceForPrint(checkTextList,&textInvoice);
    if ( result > 0 ) {
        PreviewDialog prev;
        prev.setPageHeight(pageHeight);
//        prev.setText(QString::fromStdString(textInvoice));
        prev.setShowPrint(true, (customerType == Customer::Seller ? PrinterDAO::SellerInvoice : PrinterDAO::BuyerInvoice));
        prev.setPrintButtonText("Loadout");
       // prev.setReport(textInvoice);

        if (checkTextList.size() > 0) {
            prev.setCheckStartLine(checkStart);
            prev.setCheckPrint(true);
            prev.setCheckTextList(checkTextList);
        }


        prev.setTextDocument(textInvoice->invoiceTextDocument());
        prev.exec();
        //delete textInvoice;
    }
*/

    qDebug("InvoiceDialog::showPreview()");
    if(m_invoice == NULL)
    {
        return;
    }

    //    saveCustomerAsDaily();

    unsigned int skipLine = topSkip;
    unsigned int pageLen= pageHeight;
    unsigned int firstCheckLine = checkStart;


    TextInvoice *textInvoice;
    string text;

    deque<string> pages;
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    m_invoice->sortTransactionList();
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    string commentKey;
    string showIdKey;
    string showCommentsKey;

    if(customerType == Customer::Seller)
    {
        qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
        commentKey = "genSinvComment";
        textInvoice = new TextSellerInvoice((SellerInvoice*)(m_invoice), skipLine, pageLen, showSexSummary, groupCharges);
        qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
        textInvoice->setFooterText(setup.get("sinvFooterText"));
        showIdKey = "sinvShowNumber";
        showCommentsKey = "sinvShowTransactionComments";
    }
    else
    {
        commentKey = "genBinvComment";
        qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
        textInvoice = new TextBuyerInvoice(m_invoice, skipLine, pageLen, showSexSummary, averageOnLeft, groupCharges, binvTotalNS);
        qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
        textInvoice->setShowBrand(bool(atol(setup.get("binvShowBrand").c_str())));
        textInvoice->setFooterText(setup.get("binvFooterText"));
        showIdKey = "binvShowNumber";
        showCommentsKey = "binvShowTransactionComments";
        qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    }
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    textInvoice->setShowNames(invoiceDao->showName());
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    textInvoice->setHeader(setup.reportHeader("", false, commentKey));
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    textInvoice->setShowId(setup.getBoolean(showIdKey));
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    textInvoice->setShowTransactionComments(setup.getBoolean(showCommentsKey));
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    textInvoice->setMinimumHeaderSize(minimumHeaderSize);
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    textInvoice->setTransFit(transOverrideColumn, transOverrideLength);
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    textInvoice->setTransColumns(invoiceDao->getColumnList());
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;


    PreviewDialog prev;
    // KLN start
    prev.setFixedSize(1024,768);
    // KLN end
    prev.setPageHeight(pageHeight);
    prev.setTopSkipLines(topSkip);
    prev.setCheckStartLine(checkStart);
    prev.setCheckPrint(true);

    QString previewText = QString::fromStdString(textInvoice->text());
    prev.setText(previewText);

    prev.setShowPrint(true, (customerType == Customer::Seller ? PrinterDAO::SellerInvoice : PrinterDAO::BuyerInvoice));
    prev.setPrintButtonText("Loadout");
    prev.setReport(textInvoice);
    prev.setTextDocument(textInvoice->invoiceTextDocument());
    prev.setLoadoutDocument(textInvoice->loadoutTextDocument());
    prev.exec();
    delete textInvoice;

}

///////////////////////////////////////////////////////////////////////////////
//
// name:    editClickedTransaction(int row, int col)
// 
// purpose: edit the transaction dialog found in the transaction list for this
//          index at the index row.
// 
// calling params: int row - The index in the transaction list of the transaction to edit
//                 int col - unused
// return params:
//
// Notes: Slot meant to connect to the doubleClicked or clicked signal in QTable* transactionTable
//        
// Todo:  
//
///////////////////////////////////////////////////////////////////////////////

void InvoiceDialog::editClickedTransaction(int row, int col)
{
    qDebug("InvoiceDialog::editClickedTransaction(int row, int col)");
    if(0 <= row && row < ui.transactionTable->numRows())
    {
        long transId = atol(ui.transactionTable->text(row, 0).ascii());
        if(transId != 0)
        {
            TransactionDialog transEdit(this);
            transEdit.loadTransaction(transId);

            if(transEdit.exec() == QDialog::Accepted)
            {
                ui.sinvID->setText(QString::fromStdString(m_invoice->getCustomer().getNumber()));
                loadInvoiceFromId();
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    printInvoice()
// 
// purpose: prints an invoice
// 
// calling params: 
// 
// return params:
//
// Notes: This has been changed over time to accomadate several
//             specific customers, and has never been properly designed
//             with all of the possible needs in mind. 
//             It has become overly complicated, and it may be worth some time to 
//           refactor when time permits.
//        
// Todo:  
//
///////////////////////////////////////////////////////////////////////////////

void InvoiceDialog::printInvoice()
{
    qDebug("InvoiceDialog::printInvoice()");
    if(m_invoice == NULL)
    {
        return;
    }


    if(sale.currentSaleOpen())
    {
        saveCustomerAsDaily();
    }

    string comment = m_invoice->getCustomer().getComment();

    if(comment.size() > 0 && comment[0] == '*')
    {
        QMessageBox::information(this, "Message", QString::fromStdString(comment), QMessageBox::Ok);
    }

    // check that the invoice has codes from only one color group

    if(m_invoice->codeMismatch())
    {
        QMessageBox::information(this, "ERROR!",
                                 "Check the color codes of the transactions in "
                                 "the transaction list. Only one color group should "
                                 "be used for an invoice. The color groups are;\n"
                                 "(0-69), (70-79), (80-89),(90-99)", QMessageBox::Ok);

        return;
    }

    // do not print checks by default
    bool printChks = false;
    int option = 0;

    // if charge adjustment dialog is accepted (both types of customer)
    // get specific customer type options for printing invoice.
    // Sellers may print checks or not
    // Buyers may set the invoice status.

    if(startChargeAdjustment())
    {
        //cout << "InvoiceDialog::printInvoice()  : startChargeAdjustment()" << endl;
        switch(customerType)
        {
        case Customer::Seller:

            option =QMessageBox::question(this, "Print Checks?", "Print Checks?", "Yes", "No", "Cancel");

            if(option == 2)
            {
                return;
            }
            printChks = (option == 0);
            break;

        case Customer::Buyer:
            printChks = false;
//            option = QMessageBox::question(this, "Status", "Select Status of Buyer Invoice", "Unpaid", "Paid", "Company", QMessageBox::Cancel);
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Status");
            msgBox.setInformativeText("Select Status of Buyer Invoice");
            QPushButton *unpaidButton = msgBox.addButton("Unpaid", QMessageBox::ActionRole);
            QPushButton *paidButton = msgBox.addButton("Paid", QMessageBox::ActionRole);
            QPushButton *companyButton = msgBox.addButton("Company", QMessageBox::ActionRole);
            QPushButton *cancelButton = msgBox.addButton("Cancel", QMessageBox::RejectRole);
            option = msgBox.exec();
//            cout << " option = " << option << endl;
            switch(option)
            {
            case 0:
                m_invoice->setStatus(Invoice::UNPAID);
                break;
            case 1:
                m_invoice->setStatus(Invoice::PAID);
                break;
            case 2:
                m_invoice->setStatus(Invoice::BILLED);
                break;
            case 3:
                return;
                break;
            default:
                return;
            }
        }


        setCursor(Qt::WaitCursor);

        vector<Check> checkList;
        vector<double> chargeShareList;

        // generate check data
        if(printChks)
        {
            checkList = getInvoiceCheckList(printChks, chargeShareList);
        }
        else
        {
            checkList = checkDao.getInvoiceCheckList(m_invoice->getNumber());
        }

        //finalCheckList stores the void and outstanding checks , saved in check registry.
        // All others should use this list for print.
        vector<TextCheck> finalCheckList;
        string invoiceText = getInvoiceText(printChks && chkOnInvoice, checkList,
                                            chargeShareList,finalCheckList);
        // Some markets that print checks with invoices want to be able to print the seller invoices
        // (without checks) to printers other than the check printer
        if(customerType == Customer::Seller && printChks && chkOnInvoice && setup.getBoolean("sinvChkOnInvoiceToChkPrinter"))
        {
            if (m_checkPrinter->isLaser()) {
                printLaserInvoiceWithCheck(*m_checkPrinter,*m_textDocument,finalCheckList,printChks);
            }
            else
            {

                string secInvoiceText;
                adjustInvoiceTextForMatrixPrinter(invoiceText,secInvoiceText,pageHeight,checkStart,invoiceDao->chkStartCopy());
                m_checkPrinter->print(secInvoiceText,*m_textDocument, LinePrinter::Normal, false);
            }

            int copies = invoiceDao->laserCopyCount();
            bool isSecCopyNeeded = invoiceDao->isSecondCopyPrintNeeded();
            if (isSecCopyNeeded) {
                PrinterBase * secCopyPrinter = PrinterDAO().getPrinter(PrinterDAO::SecondCopy);
                if ((secCopyPrinter!= 0) && (copies > 1)) {
                    for (int i = 0; i < copies -1; i++) {
                        if (secCopyPrinter->isLaser()) {
                            printLaserInvoiceWithCheck(*secCopyPrinter,*m_textDocument,finalCheckList,printChks);
                        }
                        else
                        {
                            string secInvoiceText;
                            adjustInvoiceTextForMatrixPrinter(invoiceText,secInvoiceText,pageHeight,checkStart,invoiceDao->chkStartCopy());
                            secCopyPrinter->print(secInvoiceText,*m_textDocument, LinePrinter::Normal, false);
                        }


                    }
                    delete secCopyPrinter;
                }
            }
        }
        else
        {
            cout << "Customer type in invoicePrint: " << (customerType == Customer::Seller ? "Seller" : "Buyer") << endl;
            if (m_invoicePrinter->isLaser()) {
                printLaserInvoiceWithCheck(*m_invoicePrinter,*m_textDocument,finalCheckList,printChks);
            }
            else {
                m_invoicePrinter->print(invoiceText, *m_textDocument, LinePrinter::Normal, false);
            }
            int copies = invoiceDao->laserCopyCount();
            bool isSecCopyNeeded = invoiceDao->isSecondCopyPrintNeeded();
            if (isSecCopyNeeded) {
                PrinterBase * secCopyPrinter = PrinterDAO().getPrinter(PrinterDAO::SecondCopy);
                if ((secCopyPrinter!= 0) && (copies > 1)) {
                    for (int i = 0; i < copies -1; i++) {
                        if (secCopyPrinter->isLaser()) {
                            printLaserInvoiceWithCheck(*secCopyPrinter,*m_textDocument,finalCheckList,printChks);
                        }
                        else
                        {
                            string secInvoiceText;
                            adjustInvoiceTextForMatrixPrinter(invoiceText,secInvoiceText,pageHeight,checkStart,invoiceDao->chkStartCopy());
                            secCopyPrinter->print(secInvoiceText,*m_textDocument, LinePrinter::Normal, false);
                        }
                    }
                    delete secCopyPrinter;
                }
            }
        }


        // print checks to check printer
        if(printChks && !chkOnInvoice) {
            for(unsigned int i = 0; i < checkList.size(); i++) {
                string checkText = "";
                string mortgage = m_invoice->getCustomer().getCompany();
                checkList[i].setType(Check::Invoice);
                checkList[i].setInvoiceId(m_invoice->getNumber());

                if(checkList[i].getAmount() > -0.009)
                {
                    TextCheck textCheck(checkDao.saveCheck(checkList[i]), format, *m_invoice, checkList.size() - 1 == i);
                    checkText += textCheck.getPreSpace() + textCheck.text(); // + "\f";
                }
                else
                {
                    QMessageBox::information(this, "NOTE",
                                             "A Check will not be printed because the total was less than $0.01");
                }
                if (!m_checkPrinter->isLaser()) {  //Don't add form feed to check end on laser printer.
                    checkText += "\f";
                } else { // we have a laser printer
                    int lineTotal = atoi(setup.get("sinvLinesPerCheck").c_str());
                    checkText = m_checkPrinter->adjustCheck(checkText, lineTotal);
                    //Laser printer print when adjustCheck called.
                }
                if (!m_checkPrinter->isLaser()) {
                    m_checkPrinter->print(checkText,QTextDocument(), LinePrinter::Normal, false);
                }
            }
        }

        if(sale.currentSaleOpen())
        {
            qDebug("InvoiceDialog::printInvoice() before save summary");
            invoiceDao->saveSummary(*m_invoice);
            qDebug("InvoiceDialog::printInvoice() after save summary");
        }

        qDebug("InvoiceDialog::printInvoice() before save invoice");
        invoiceDao->saveInvoice(*m_invoice);
        qDebug("InvoiceDialog::printInvoice() after save summary");
        ui.sinvPrinted->setEnabled(true);
    }

    if(numberList.size() == 0) {
        resetInvoice();
    }
    // Do not go to next invoice if All button pressed. It will allow to use fax/print after
    // pressing next button.


    // process next multiple number request (buyer all function or seller remaining)
    if(numberList.size() > 0)
    {
        ui.sinvID->setText(QString::fromStdString(numberList[0]));
        loadInvoiceFromId();
        numberList.erase(numberList.begin());
        ui.sinvID->setEnabled(false);

        if(numberList.size() == 0)
        {
            ui.sinvID->setEnabled(true);
            ui.cycleButton->setText((customerType == Customer::Seller ? "Re&maining" : "&All"));
        }
    }
    setCursor(Qt::ArrowCursor);
    qDebug("InvoiceDialog::printInvoice() exiting");
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    previewInvoice()
// 
// purpose: previews an invoice
// 
// calling params: 
// 
// return params:
//
// Notes: 
//        
// Todo:  
//
//////////////////////////////////////////////////


//void InvoiceDialog::previewInvoice()
//{
//    qDebug("InvoiceDialog::previewInvoice()");
//    if(m_invoice == NULL)
//    {
//        return;
//    }
//    saveCustomerAsDaily();
//    string text = getInvoiceText(false, vector<Check>(), vector<double>() );
//    PreviewDialog preview(this);
//    preview.setText(QString::fromStdString(text));
//    preview.setTextDocument(m_textDocument);
//    preview.exec();
//}

///////////////////////////////////////////////////////////////////////////////
//
// name: vector<Check> getInvoiceCheckList(bool printChecks, vector<double>& chargeShareList)
// 
// purpose: retrieves outstanding checks for the current invoice
// 
// calling params: 
// 
// return params:
//
// Notes: loads check data for the invoice
//        
// Todo:  
//
//////////////////////////////////////////////////

vector<Check> InvoiceDialog::getInvoiceCheckList(bool printChecks, vector<double>& chargeShareList)
{
    qDebug("InvoiceDialog::getInvoiceCheckList(bool printChecks, vector<double>& chargeShareList)");
    ProrateDAO prorateDao;
    CheckFactory *checkFactory;
    vector<Check> checkList;

    cout << "Starting InvoiceDialog::getInvoiceCheckList" << endl;

    if(printChecks)
    {
        checkDao.voidChecksByInvoice(*m_invoice);
    }

    checkFactory = prorateDao.getCheckFactory(*m_invoice);

    if(checkFactory != NULL)
    {
        checkList = checkFactory->checkList();
        chargeShareList = checkFactory->getChargeShares();
    }
    prorateDao.releaseCheckFactory();

    if(checkList.size() == 0 && printChecks)
    {
        checkList.push_back(getInvoiceCheck());
    }

    long nextCheckNo = 0;

    for(unsigned int i = 0; i < checkList.size() && printChecks; i++)
    {
        nextCheckNo = 0;

////        if(!chkOnInvoice && checkList[i].getAmount() > -0.009)
//        if( checkList[i].getAmount() > -0.009 ) {
//            //If check for print, increase number here and only here.
//            //Should work for both laser and matrix printers.
//            nextCheckNo = checkDao.getNextCheckNo();

        if(!chkOnInvoice && checkList[i].getAmount() > -0.009)
        {
            nextCheckNo = checkDao.getNextCheckNo();
            checkList[i].setNumber(nextCheckNo);
        }

        checkList[i].setType(Check::Invoice);
        checkList[i].setInvoiceId(m_invoice->getNumber());
    }

    cout << "Leaving InvoiceDialog::getInvoiceCheckList" << endl;

    return checkList;
}



///////////////////////////////////////////////////////////////////////////////
//
// name:    string getInvoiceText(bool showCheck, vector<Check> checkList, vector<double> chargeShareList)
// 
// purpose: generates invoice text from the configuration and customer choices
// 
// calling params: bool showCheck                 - whether to print checks on the invoice
//                 vector<Check> checkList        - a list of checks for this invoice
//                 vector<double> chargeShareList - corralary to the check list. A list of the
//                                                  share of the charges, each check payee 
//                                                  has paid for kind of a hack here. Should have
//                                                  combined Check && Payee Charge in a class together
//                                                  but this works, so unless we have problems it will
//                                                  probably stay
//
// return params:
//
// Notes: 
//        
// Todo:  
//
//////////////////////////////////////////////////
string InvoiceDialog::getInvoiceText(bool showCheck, vector<Check> checkList,
                                     vector<double> chargeShareList,vector<TextCheck>& finalCheckList)
{
    finalCheckList.clear();
    qDebug("InvoiceDialog::getInvoiceText(bool showCheck, vector<Check> checkList, vector<double> chargeShareList)");
    showCheck = showCheck && chkOnInvoice;
    unsigned int skipLine = topSkip;
    unsigned int pageLen= pageHeight;
    unsigned int firstCheckLine = checkStart;

    TextInvoice *textInvoice;
    string text;

    deque<string> pages;
    string checkText = "";
    string voidCheckText = "";

    m_invoice->sortTransactionList();
    string commentKey;
    string showIdKey;
    string showCommentKey;
    if(customerType == Customer::Seller)
    {
        //cout << "customerType == Customer::Seller ... " << endl;
        commentKey = "genSinvComment";
        textInvoice = new TextSellerInvoice((m_invoice), skipLine, pageLen, showSexSummary, groupCharges);
        textInvoice->setFooterText(setup.get("sinvFooterText"));

        // setShowBrand call added here for missing brands with '/xxxx' pattern
        // on 6/12/09 rhw. Otherwise showBrand is not set, defaults false.
        textInvoice->setShowBrand(bool(atol(setup.get("binvShowBrand").c_str())));

        showIdKey = "sinvShowNumber";
        showCommentKey = "sinvShowTransactionComments";
    }
    else
    {
        //cout << "It's a BUYER invoicetext   ? ? ?" << endl;
        commentKey = "genBinvComment";
        textInvoice = new TextBuyerInvoice(m_invoice, skipLine, pageLen, showSexSummary, averageOnLeft, groupCharges, binvTotalNS);
        textInvoice->setFooterText(setup.get("binvFooterText"));

        textInvoice->setShowBrand(bool(atol(setup.get("binvShowBrand").c_str())));
        showIdKey = "binvShowNumber";
        showCommentKey = "binvShowTransactionComments";
    }

    textInvoice->setShowNames(invoiceDao->showName());
    textInvoice->setShowId(setup.getBoolean(showIdKey));
    textInvoice->setHeader(setup.reportHeader("", false, commentKey));
    textInvoice->setShowTransactionComments(setup.getBoolean(showCommentKey));
    bool showFullProrate = bool(atol(setup.get("sinvFullInvoiceOnProrate").c_str()));
    textInvoice->setMinimumHeaderSize(minimumHeaderSize);
    textInvoice->setTransFit(transOverrideColumn, transOverrideLength);
    if(checkList.size() != 0)
    {

        textInvoice->setProrateList(checkList, chargeShareList);
        textInvoice->setTransColumns(invoiceDao->getColumnList());
        pages = textInvoice->paginatedText(skipLine);
        long nextCheckNo = checkDao.peekAtNextCheckNo();

        for(unsigned int i = 0; i < checkList.size() ; i++)
        {
            if(checkList[i].getNumber() == 0)
            {
                if(showFullProrate || i == checkList.size() - 1)
                {
                    nextCheckNo += pages.size() - 1;
                }

                if(checkList[i].getAmount() > -0.009)
                {
                    checkList[i].setNumber(nextCheckNo);
                }
                else
                {
                    checkList[i].setNumber(0);
                }
            }
            nextCheckNo++;
        }
        textInvoice->setProrateList(checkList, chargeShareList);
    }


    textInvoice->setTransColumns(invoiceDao->getColumnList());

    pages = textInvoice->paginatedText(skipLine);
    if (m_textDocument != 0) {
        delete m_textDocument;
    }
    m_textDocument = textInvoice->invoiceTextDocument();
    delete textInvoice;


    bool isInvoiceCheck = false;
    for(unsigned int i = 0; i < checkList.size() && showCheck; i++) // showCheck is (printChks && chkOnInvoice)
    {
        isInvoiceCheck = (i == checkList.size() - 1);
        text += getInvoicePagesText(pages,checkList[i], showCheck, firstCheckLine, format,
                                    (showFullProrate || isInvoiceCheck), isInvoiceCheck,finalCheckList);
    }

    if(!showCheck || checkList.size() == 0)
    {
        text += getInvoicePagesText(pages, Check(), false, 0, format, true, true,finalCheckList);
    }

    return text;
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    startTruckingDialog()
// 
// purpose: begins the trucking dialog for the current customer
// 
// calling params: 
// 
// return params:
//
// Notes: 
//        
// Todo:  
//
//////////////////////////////////////////////////

void InvoiceDialog::startTruckingDialog()
{
    qDebug("InvoiceDialog::startTruckingDialog()");
    ChargeDAO::CUST_TYPE chargeType = (customerType == Customer::Seller ? ChargeDAO::Seller : ChargeDAO::Buyer);

    if(m_invoice != NULL)
    {
        TruckingDialog trkgDialog(this);
        trkgDialog.init(*m_invoice, chargeType);
        trkgDialog.exec();
        string number = m_invoice->getCustomer().getNumber();
        invoiceDao->freeInvoice();
        m_invoice = NULL;
        m_invoice = invoiceDao->getInvoiceByCustomer(number);
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    getInvoiceCheck()
// 
// purpose: constructs a check for this invoice printed by itself when no
//          prorate is present, used as a base if prorates are present
// 
// calling params: 
// 
// return params:
//
// Notes: 
//        
// Todo:  
//
//////////////////////////////////////////////////

Check InvoiceDialog::getInvoiceCheck()
{
    qDebug("InvoiceDialog::getInvoiceCheck()");
    QString company = QString::fromStdString(m_invoice->getCustomer().getCompany());
    QString payee = QString::fromStdString(m_invoice->getCustomer().getName().getLast());

    if(payee.contains("/") == 1)
    {
        QStringList payeeStrList = QStringList::split("/", payee, true);

        if(payeeStrList.size() > 1)
        {
            payee = payeeStrList[1] + " " + payeeStrList[0];
        }
    }

    payee += (company.length() > 0 ? " & " : "") + company;

    double net = ((SellerInvoice*)m_invoice)->net();
    return Check(0, 0, payee.toStdString(), net, Check::Out);
}



///////////////////////////////////////////////////////////////////////////////
//
// name:    Customer::Type getCustomerType()
// 
// purpose: retrieves the value of the customerType field
// 
// calling params: 
// 
// return params:
//
// Notes: 
//        
// Todo:  
//
//////////////////////////////////////////////////
Customer::Type InvoiceDialog::getCustomerType()
{
    qDebug("InvoiceDialog::getCustomerType()");
    return customerType;
}



///////////////////////////////////////////////////////////////////////////////
//
// name:    startChargeAdjustment()
// 
// purpose: entry point for charge adjustment where the user can debit and 
//          credit charges manually
// 
// calling params: 
// 
// return params: bool - returns true if the dialog was initialized ok and 
//                       accepted by the user
//
// Notes: 
//        
// Todo:  
//
//////////////////////////////////////////////////
bool InvoiceDialog::startChargeAdjustment()
{
    qDebug("InvoiceDialog::startChargeAdjustment()");
    if(m_invoice == NULL)
    {
        return false;
    }

    if(!sale.currentSaleOpen())
    {
        return true;
    }

    ChargeAdjustmentDialog chargeAdjust(this);
    chargeAdjust.init(m_invoice);

    if(customerType == Customer::Buyer)
    {
        chargeAdjust.setIsBuyer(true);
    }
    return (chargeAdjust.exec() == QDialog::Accepted);
}



///////////////////////////////////////////////////////////////////////////////
//
// name:    showReadySellers()
// 
// purpose: Displays a list of daily customers that are ready to be processed
// 
// calling params: 
// 
// return params:
//
// Notes: 
//        
// Todo:  
//
//////////////////////////////////////////////////

void InvoiceDialog::showReadySellers()
{
    qDebug("InvoiceDialog::showReadySellers() entered" );
    ReadySellerDialog rsd(this);
    rsd.setCaption((customerType == Customer::Seller ? "Ready Sellers" : "Unprinted Buyers"));
    rsd.setDAO(invoiceDao);

    if(rsd.exec() == QDialog::Accepted)
    {
        ui.sinvID->setText(rsd.getNumber());
        loadInvoiceFromId();
    }
    qDebug("InvoiceDialog::showReadySellers() exited.");
}



///////////////////////////////////////////////////////////////////////////////
//
// name:    void startProrate()
// 
// purpose: entry point for the prorate dialog, which allows the user to 
//          print several checks from the current seller invoice
// 
// calling params: 
// 
// return params:
//
// Notes: Sellers only
//        
// Todo:  
//
//////////////////////////////////////////////////

void InvoiceDialog::startProrate()
{
    qDebug("InvoiceDialog::startProrate()");
    if(m_invoice != NULL)
    {
        ProrateDialog prorateDialog(this);
        prorateDialog.init(*m_invoice);
        prorateDialog.exec();
    }
}



///////////////////////////////////////////////////////////////////////////////
//
// name:    string getInvoicePagesText(deque<string> pages, Check check, bool showCheck, 
//                                     unsigned int firstCheckLine, CheckFormatData checkFormat,
//                                     bool allPages, bool showAddressOnCheck
//                                             
// 
// purpose: called by getInvoiceText(), this merges the paginated invoices and checks together
// 
// calling params: 
// 
// return params: string - the text to be printed
//
// Notes: 
//        
// Todo:  
//
//////////////////////////////////////////////////

string InvoiceDialog::getInvoicePagesText(deque<string> pages, Check check, bool showCheck,
                                          unsigned int firstCheckLine, CheckFormatData format,
                                          bool allPages, bool showAddressOnCheck,vector<TextCheck> & finalCheckList)
{
    qDebug("InvoiceDialog::getInvoicePagesText(deque<string> pages, Check check, bool showCheck, unsigned int firstCheckLine, CheckFormatData format, bool allPages, bool showAddressOnCheck)");
    string text = "";
    deque<string>::iterator current;
    string checkText = "";
    Check voidCheck = Check(0, 0, "Void", 0.0, Check::Void);
    bool isSecCopyNeeded = invoiceDao->isSecondCopyPrintNeeded(); // [KLN] add

    if(!allPages /*&& pages.size() > 1*/)
    {
        //pages.erase(pages.begin() + 1, pages.end());
        pages = deque<string>(1, "");
    }

    for(current = pages.begin(); current != pages.end(); current++)
    {
        if(showCheck) // printChks and chkOnInvoice both true
        {
            bool isLast = (current + 1 == pages.end());
            long nextCheckNo = checkDao.getNextCheckNo();

            if(isLast && check.getAmount() > -0.01)
            {
                check.setNumber(nextCheckNo);
                check.setInvoiceId(m_invoice->getNumber());
                check.setType(Check::Invoice);

            }
            else
            {
                voidCheck.setNumber(nextCheckNo);
                voidCheck.setType(Check::Invoice);
                voidCheck.setInvoiceId(m_invoice->getNumber());
            }

            if(check.getAmount() < -0.009)
            {
                QMessageBox::information(this, "WARNING",
                                         "A check will not be printed because the amount was less than $0.01");
            }

            TextCheck textCheck(checkDao.saveCheck((isLast && check.getAmount() > -0.009 ?check : voidCheck)), format, *m_invoice, showAddressOnCheck);
            int actualPageLength = QString::fromStdString(*current).count("\n");
            string pad = (firstCheckLine > actualPageLength ? string(firstCheckLine - actualPageLength, '\n') : "");
            checkText = pad +  textCheck.text();
            m_invoice->setStatus(Invoice::PAID);
            textCheck.setPrintOnlyCheck(!allPages);  //This indicate that only check should be printed.
            finalCheckList.push_back(textCheck);
        }
        else if(chkOnInvoice)
        {
            if(!setup.getBoolean("sinvChkOnInvoiceToChkPrinter"))
            {
                long nextCheckNo = checkDao.getNextCheckNo();
                voidCheck.setNumber(nextCheckNo);
                // [KLN] add
                if (isSecCopyNeeded) {
                    checkCount++;
                }
                cout << "  nextCheckNo = " << nextCheckNo << " in InvoiceDialog::getInvoicePagesText (chkOnInvoice) [" << __LINE__ << "]" << endl;
                cout << "   checkCount = " << checkCount << " in InvoiceDialog::getInvoicePagesText (chkOnInvoice) [" << __LINE__ << "]" << endl;
                // [KLN] add end
                voidCheck.setType(Check::Invoice);
                voidCheck.setInvoiceId(m_invoice->getNumber());
                TextCheck textCheck(checkDao.saveCheck(voidCheck), format, *m_invoice, showAddressOnCheck);
                int actualPageLength = QString::fromStdString(*current).count("\n");

                string pad = (checkStart > actualPageLength ? string(checkStart - actualPageLength, '\n') : "");
                checkText = pad +  textCheck.text();
            }
        }

        text += *current  + checkText + "\f";
//        if (!m_invoicePrinter->isLaser()) {  //Don't add form feed to invoice end on laser printer.
//            text += "\f";
//        }
    }
    return text;
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    void changeCustomerType(int buttonId)
// 
// purpose: re-initializes the dialog as a different customer type
// 
// calling params: 
// 
// return params:
//
// Notes: slot meant to be called when the customer type buttons are clicked
//        
// Todo:  
//
//////////////////////////////////////////////////
void InvoiceDialog::changeCustomerType(int buttonId)
{
    qDebug("InvoiceDialog::changeCustomerType(int buttonId)");
    switch(buttonId)
    {
    case 1:
        init(Customer::Buyer);
        break;
    case 0:
    default:
        init(Customer::Seller);
        break;
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    void startBuyerRecap()
// 
// purpose: entry point for the buyer recap dialog
// 
// calling params: 
// 
// return params:
//
// Notes: 
//        
// Todo:  
//
//////////////////////////////////////////////////
void InvoiceDialog::startBuyerRecap()
{
    qDebug("InvoiceDialog::startBuyerRecap()");
    BuyerRecapDialog(this).exec();
    ui.sinvID->setFocus();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    void resetInvoice()
// 
// purpose: resets the dialog to a null state(no customer loaded)
// 
// calling params: 
// 
// return params:
//
// Notes: 
//        
// Todo:  
//
//////////////////////////////////////////////////
void InvoiceDialog::resetInvoice()
{
    qDebug("InvoiceDialog::resetInvoice()");
    m_invoice = new Invoice();
    showInvoice();
    ui.sinvID->setText("");
    delete m_invoice;
    m_invoice = NULL;
    ui.sinvID->setFocus();
}



///////////////////////////////////////////////////////////////////////////////
//
// name:    startPermSearch()
// 
// purpose: entry point for the perm search dialog, which allows the user to 
//          quickly search permanant customer table. 
// 
// calling params: 
// 
// return params:
//
// Notes: The perm search dialog matches the first part of whatever string it 
//        initialized with, in this case, the text from the name field of the
//        invoice dialog.
//        
// Todo:  
//
//////////////////////////////////////////////////
void InvoiceDialog::startPermSearch()
{
    qDebug("InvoiceDialog::startPermSearch()");
    QString namePart = ui.sinvName->text();
    if(namePart.length() > 2 && allowPermSearch)
    {
        if(m_invoice == NULL)
        {
            loadInvoiceFromId();
        }


        Customer::Type type = Customer::Seller;

        if(ui.buyerButton->isChecked())
        {
            type = Customer::Buyer;
        }
        PermSearchDialog ps(this);
        ps.init(namePart, type);

        if(ps.exec() == QDialog::Rejected)
        {
            return;
        }


        Customer temp  = ps.getSelectedCustomer();
        if (m_invoice != 0) {
            temp.setNumber(m_invoice->getCustomer().getNumber());
        }
        if(customerType == Customer::Seller)
        {
            ui.sinvHead->setFocus();
        }
        else
        {
            ui.sinvPrintButton->setFocus();
        }


        allowPermSearch = false;
        ui.sinvName->setText(QString::fromStdString(temp.getName().getLast()));
        allowPermSearch = true;
        ui.sinvAddress1->setText(QString::fromStdString(temp.getAddress().getAddress1()));
        ui.sinvAddress2->setText(QString::fromStdString(temp.getAddress().getAddress2()));
        ui.sinvHead->setText(0);
        ui.sinvCompany->setText(QString::fromStdString(temp.getCompany()));
        ui.sinvCity->setText(QString::fromStdString(temp.getAddress().getCity()));
        ui.sinvState->setText(QString::fromStdString(temp.getAddress().getState()));
        ui.sinvZip->setText(QString::fromStdString(temp.getAddress().getZip()));
        ui.sinvComment->setText(QString::fromStdString(temp.getComment()));
        if (m_invoice != 0) {
            m_invoice->setCustomer(temp);
        }
    }
    else if(allowPermSearch)
    {
        QMessageBox::information(this, "Insufficient Length",
                                 "You must enter at least 3 characters in order to search the permanant table here.");
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    void loadNumberList()
// 
// purpose: initializes multi number tasks, such as automatically loading
//          all buyer that match the base number one after another
//          or loading all remaining sellers one after the other
// 
// calling params: 
// 
// return params:
//
// Notes: 
//        
// Todo:  
//
//////////////////////////////////////////////////
void InvoiceDialog::loadNumberList()
{
    qDebug("InvoiceDialog::loadNumberList()");
    if(invoiceDao == NULL)
    {
        return;
    }
    string cycleLabel = string((customerType == Customer::Seller ? "Remaining" : "&All"));

    if(numberList.size() < 1)
    {
        switch(customerType)
        {
        case Customer::Seller:
        default:
            numberList = invoiceDao->getUnprintedCustomerList();
            break;
        case Customer::Buyer:
            numberList = invoiceDao->getNumbersMatching(ui.sinvID->text().toStdString());
            break;
        }

        std::sort(numberList.begin(), numberList.end(), Customer::compareCustomerNumbersLT);
    }

    if(numberList.size() > 0)
    {
        ui.sinvID->setText(QString::fromStdString(numberList[0]));
        loadInvoiceFromId();
        numberList.erase(numberList.begin());

        if(numberList.size() == 0)
        {
            ui.sinvID->setEnabled(true);
            ui.cycleButton->setText(QString::fromStdString(cycleLabel));
        }
        else
        {
            ui.cycleButton->setText("&Next");
            ui.sinvID->setEnabled(false);
        }
    }

}

///////////////////////////////////////////////////////////////////////////////
//
// name:    void loadCityStateZipFromCity()
// 
// purpose: autofills the city / state / zip fields from the user entered city
// 
// calling params: 
// 
// return params:
//
// Notes: If multiple matches are found a disambiguation dialog is shown.
//        
// Todo:  
//
//////////////////////////////////////////////////
void InvoiceDialog::loadCityStateZipFromCity()
{
    qDebug("InvoiceDialog::loadCityStateZipFromCity()");
    vector<Address> zipCodeList = ZipCodeDAO().getZipCodeListByCity(ui.sinvCity->text().toStdString());
    autoLoadCityStateZip(zipCodeList);
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    void loadCityStateZipFromCity()
// 
// purpose: autofills the city / state / zip fields from the user entered zip
// 
// calling params: 
// 
// return params:
//
// Notes: If multiple matches are found a disambiguation dialog is shown.
//        
// Todo:  
//
//////////////////////////////////////////////////
void InvoiceDialog::loadCityStateZipFromZip()
{
    qDebug("InvoiceDialog::loadCityStateZipFromZip()");
    vector<Address> zipCodeList = ZipCodeDAO().getZipCodeListByZip(ui.sinvZip->text().toStdString());
    autoLoadCityStateZip(zipCodeList);
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    void autoLoadCityStateZip(vector<Address> zipCodeList)
// 
// purpose: autofills the city / state / zip fields from an item in a 
//          list of cities.
// 
// calling params: vector<Address> zipCodeList - a list of addresses, which
//                                               should each have a 
//                                               unique city/state/zip combo
//                                                                       
// 
// return params:
//
// Notes: If the size of the list is greater than 1 a city is chosen from the disambiguation dialog.
//        if the size of the list is one, that entry is used without prompting the user.
//        otherwise, no action is taken
//            
//        
// Todo:  
//
//////////////////////////////////////////////////
void InvoiceDialog::autoLoadCityStateZip(vector<Address> zipCodeList)
{
    qDebug("InvoiceDialog::autoLoadCityStateZip(vector<Address> zipCodeList)");
    string city, state, zip;

    if(zipCodeList.size() == 0)
    {
        return;
    }
    if(zipCodeList.size() == 1)
    {
        city = zipCodeList[0].getCity();
        state = zipCodeList[0].getState();
        zip = zipCodeList[0].getZip();
    }
    else if(zipCodeList.size() > 1)
    {

        ZipCodeDialog zipDialog(this);
        zipDialog.init(zipCodeList);

        if(zipDialog.exec() == QDialog::Accepted)
        {
            Address temp = zipDialog.getCurrentAddress();
            city = temp.getCity();
            state = temp.getState();
            zip = temp.getZip();
        }
        else
        {
            return;
        }
    }
    ui.sinvCity->setText(QString::fromStdString(city));
    ui.sinvState->setText(QString::fromStdString(state));
    ui.sinvZip->setText(QString::fromStdString(zip));
    ui.sinvCompany->setFocus();
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    void globalBuyerChange()
// 
// purpose: changes the buyer number of all transactions with the current invoice's
//          buyer number with a user entered number
// 
// calling params: 
// 
// return params:
//
// Notes:
//        
// Todo:  
//
//////////////////////////////////////////////////
void InvoiceDialog::globalBuyerChange()
{
    qDebug("InvoiceDialog::globalBuyerChange()");
    if(m_invoice == NULL)
    {
        return;
    }

    bool ok;
    QString newNumber = QInputDialog::getText ( "Global Buyer # Change",
                                                "What will the new buyer number be?",
                                                QLineEdit::Normal, QString::null, &ok, this);

    if(ok)
    {
        TransactionDAO().globalBuyerChange(m_invoice->getCustomer().getNumber(), newNumber.toStdString());
        invoiceDao->deleteSummary(m_invoice->getCustomer());
        resetInvoice();
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    void globalPenChange()
// 
// purpose: changes a user entered pen number for each of these buyer's transactions
//          to a different user entered pen number.
// 
// calling params: 
// 
// return params:
//
// Notes: 
//        
// Todo:  
//
//////////////////////////////////////////////////
void InvoiceDialog::globalPenChange()
{
    qDebug("InvoiceDialog::globalPenChange()");
    if(m_invoice == NULL)
    {
        return;
    }

    bool ok;
    QString oldPen;
    QString newPen;

    oldPen = QInputDialog::getText("Global Pen # Change",
                                   "Which Pen do you wish to change",
                                   QLineEdit::Normal, QString::null, &ok, this);

    if(ok)
    {
        newPen = QInputDialog::getText ( "Global Pen # Change",
                                         "What will the new pen number be?",
                                         QLineEdit::Normal, QString::null, &ok, this);

    }

    if(ok)
    {
        TransactionDAO().globalPenChange(m_invoice->getCustomer().getNumber(), oldPen.toStdString(), newPen.toStdString());
        loadInvoiceFromId();
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    void faxInvoice()
// 
// purpose: to fax an invoice to a user defined fax #
// 
// calling params: 
// 
// return params:
//
// Notes: 
//        
// Todo:  actually implement this in a way that the customer can use
//
//////////////////////////////////////////////////
void InvoiceDialog::faxInvoice()
{
    qDebug("InvoiceDialog::showPreview()");
    if(m_invoice == NULL)
    {
        return;
    }

    //    saveCustomerAsDaily();

    unsigned int skipLine = topSkip;
    unsigned int pageLen= pageHeight;
    unsigned int firstCheckLine = checkStart;


    TextInvoice *textInvoice;
    string text;

    deque<string> pages;

    m_invoice->sortTransactionList();
    string commentKey;
    string showIdKey;
    string showCommentsKey;

    if(customerType == Customer::Seller)
    {
        commentKey = "genSinvComment";
        textInvoice = new TextSellerInvoice((SellerInvoice*)(m_invoice), skipLine, pageLen, showSexSummary, groupCharges);
        textInvoice->setFooterText(setup.get("sinvFooterText"));
        showIdKey = "sinvShowNumber";
        showCommentsKey = "sinvShowTransactionComments";
    }
    else
    {
        commentKey = "genBinvComment";
        textInvoice = new TextBuyerInvoice(m_invoice, skipLine, pageLen, showSexSummary, averageOnLeft, groupCharges, binvTotalNS);
        textInvoice->setShowBrand(bool(atol(setup.get("binvShowBrand").c_str())));
        textInvoice->setFooterText(setup.get("binvFooterText"));
        showIdKey = "binvShowNumber";
        showCommentsKey = "binvShowTransactionComments";
    }

    textInvoice->setShowNames(invoiceDao->showName());
    textInvoice->setHeader(setup.reportHeader("", false, commentKey));
    textInvoice->setShowId(setup.getBoolean(showIdKey));
    textInvoice->setShowTransactionComments(setup.getBoolean(showCommentsKey));
    textInvoice->setMinimumHeaderSize(minimumHeaderSize);
    textInvoice->setTransFit(transOverrideColumn, transOverrideLength);
    textInvoice->setTransColumns(invoiceDao->getColumnList());


    PreviewDialog prev;
    prev.setPageHeight(pageHeight);
    prev.setTopSkipLines(topSkip);
    prev.setCheckStartLine(checkStart);
    prev.setCheckPrint(true);

    QString previewText = QString::fromStdString(textInvoice->text());
    prev.setText(previewText);

    prev.setShowPrint(true, (customerType == Customer::Seller ? PrinterDAO::SellerInvoice : PrinterDAO::BuyerInvoice));
    prev.setPrintButtonText("Loadout");
    prev.setReport(textInvoice);
    prev.setTextDocument(textInvoice->invoiceTextDocument());

    ui.faxInvoiceButton->setStyleSheet(QString("background-color: #FF0000"));
    ui.faxInvoiceButton->setDisabled(true);

    //Show fax number dailog, and if OK pressed, create document and try to send fax.


    QDialog sendFaxDlg;
    sendFaxDialog.setupUi(&sendFaxDlg);
    if (sendFaxDlg.exec() == QDialog::Accepted) {

        setCursor(Qt::WaitCursor);

        QPrinter faxPrinter;
        faxPrinter.setPaperSize(QPrinter::Letter);
        faxPrinter.setOutputFileName("fax.pdf");
        prev.printDocument(faxPrinter);

        QStringList convertArgs;
        convertArgs << "fax.pdf" <<  "fax.ps";
        QProcess convertProcess;
        convertProcess.start("pdf2ps", convertArgs);
        if(!convertProcess.waitForStarted()) {
            setCursor(Qt::ArrowCursor);
            QMessageBox::information(this, "Error", "Could not convert FAX output file");
        }
        if(!convertProcess.waitForFinished()) {
            setCursor(Qt::ArrowCursor);
            QMessageBox::information(this, "Error", "Could not convert FAX output file");
        }



        QString faxNumber = sendFaxDialog.lineEdit->text();
        if (faxNumber.isEmpty()) {
            setCursor(Qt::ArrowCursor);
            QMessageBox::information(this, "Error", "Please enter FAX number!");
        }
        else {

            //Prepare Customer name
            string nameString = formatName(m_invoice->getCustomer().getName().getLast());

            QString marketName = QString::fromStdString(setup.getMarketInfo());
            //

            QProcess faxSendProcess;
            QStringList faxArgs;
            faxArgs << "-r " + QString::fromStdString(nameString)   // "RE:" field on fax cover
                    << "-f " + marketName   // "FROM" field on fax cover
                    << "-d "+ faxNumber << "fax.ps";
            faxSendProcess.start("sendfax",faxArgs);
            if(!faxSendProcess.waitForStarted()) {
                setCursor(Qt::ArrowCursor);
                QMessageBox::information(this, "Error", "Could not send FAX");
            }
            if(!faxSendProcess.waitForFinished(300000)) {
                setCursor(Qt::ArrowCursor);
                QMessageBox::information(this, "Error", "Could not send FAX");
            }
            else {
                QString outputStr(faxSendProcess.readAllStandardOutput());
                QMessageBox::information(this, "Status", outputStr);
            }
        }
    }
    ui.faxInvoiceButton->setStyleSheet(QString("background-color: #ADFF2F"));
    ui.faxInvoiceButton->setDisabled(false);
    setCursor(Qt::ArrowCursor);

    delete textInvoice;

}

///////////////////////////////////////////////////////////////////////////////
//
// name:    void setInvoiceStatus()
// 
// purpose: changes the invoice status to that of a user selected status.
// 
// calling params: 
// 
// return params:
//
// Notes: Buyers only
//        
// Todo:  
//
//////////////////////////////////////////////////
void InvoiceDialog::setInvoiceStatus()
{
    qDebug("InvoiceDialog::setInvoiceStatus()");
    if(m_invoice == NULL)
    {
        return;
    }

    //    int option = QMessageBox::question(this, "Status", "Select Status of Buyer Invoice", "Unpaid", "Paid", "Company", QMessageBox::Cancel);
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Status");
    msgBox.setInformativeText("Select Status of Buyer Invoice");
    QPushButton *unpaidButton = msgBox.addButton("Unpaid", QMessageBox::ActionRole);
    QPushButton *paidButton = msgBox.addButton("Paid", QMessageBox::ActionRole);
    QPushButton *companyButton = msgBox.addButton("Company", QMessageBox::ActionRole);
    QPushButton *cancelButton = msgBox.addButton("Cancel", QMessageBox::RejectRole);
    int option = msgBox.exec();
    //            cout << " option = " << option << endl;
    switch(option)
    {
    case 0:
        m_invoice->setStatus(Invoice::UNPAID);
        break;
    case 1:
        m_invoice->setStatus(Invoice::PAID);
        break;
    case 2:
        m_invoice->setStatus(Invoice::BILLED);
        break;
    case 3:
        return;
        break;
    default:
        return;
    }

    invoiceDao->saveInvoice(*m_invoice);

    showInvoice();
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    void overrideAddress()
// 
// purpose: Overrides the address from lookup on perm on company field.
// 
// calling params: Executes on click from button compAddressButton.
// 
// return params:
//
// Notes: Buyers only
//        
// Todo:  
//
//////////////////////////////////////////////////
void InvoiceDialog::overrideAddress()
{
    qDebug("InvoiceDialog::overrideAddress()");
    if(m_invoice == NULL)
    {
        return;
    }

    if(customerType == Customer::Buyer) {
        vector<Customer> tempvector = CustomerDAO::getCustomerListForCompany(ui.sinvCompany->text().stripWhiteSpace().toStdString(), Customer::Buyer);

        if ( tempvector.size() < 1 )	{
            //cout << "NO RECORDS FOR " << sinvCompany->text() << endl;
            QMessageBox::information(this, "No Customer Found", "No perm customer was found using this company.");
            return;
        }

        //    PermBuyerSearchDialog pbsd(this);
        //    pbsd.show();

        Customer tempcust = tempvector[0];
        if ( tempcust.getId() == 0 )	{
            // failed to find a perm customer for this buyer number
            QMessageBox::information(this, "No Customer Found", "No perm customer was found using this company.");

        } else {
            ui.sinvAddress1->setText(QString::fromStdString(tempcust.getAddress().getAddress1()));
            ui.sinvAddress2->setText(QString::fromStdString(tempcust.getAddress().getAddress2()));
            ui.sinvCity->setText(QString::fromStdString(tempcust.getAddress().getCity()));
            ui.sinvState->setText(QString::fromStdString(tempcust.getAddress().getState()));
            ui.sinvZip->setText(QString::fromStdString(tempcust.getAddress().getZip()));
            ui.sinvCompany->setText(QString::fromStdString(tempcust.getCompany()));
        }
    }
}


//void InvoiceDialog::invoiceCheckTextList(vector<Check>& checkList,bool printChks,QStringList & checkTextList,
//                                         int pageCount)
//{
//    checkTextList.clear();
//    bool isInvoiceCheck = false;
//    bool showCheck = printChks && chkOnInvoice;
//    bool isSecCopyNeeded = invoiceDao->isSecondCopyPrintNeeded(); // [KLN] add
//    long nextCheckNo = -1;

//    if ( ( checkList.size() > 0 ) && showCheck ) {
//        for( int i = 0; i < pageCount-1; i++ ) {
//            Check voidCheck = Check(0, 0, "Void", 0.0, Check::Void);
//           // nextCheckNo = checkDao.getNextCheckNo();
//            cout << "  bumping next VOID check number in InvoiceDialog::invoiceCheckTextList[" << __LINE__ << "]"  << endl;
//            cout << "  check count = " << checkCount << " [" << __LINE__ << "]" << endl;
//            voidCheck.setNumber(nextCheckNo);
//            voidCheck.setType(Check::Invoice);
//            voidCheck.setInvoiceId(m_invoice->getNumber());
//            TextCheck voidTextCheck(voidCheck, format, *m_invoice, isInvoiceCheck);
//            checkTextList << QString::fromStdString(voidTextCheck.text());
//        }
//        for(unsigned int i = 0; i < checkList.size() ; i++) {
//            isInvoiceCheck = (i == checkList.size() - 1);
//            long nextCheckNo = checkDao.getNextCheckNo(); // [KLN] commented-out

//<<<<<<< HEAD
            // [KLN] add
//            if (isSecCopyNeeded && checkCount == 1) {
//                nextCheckNo = checkDao.getNextCheckNo();
//=======
//            // [KLN] add
//            if (isSecCopyNeeded && checkCount == 1) {
//              //  nextCheckNo = checkDao.getNextCheckNo();
//>>>>>>> origin/master_0919
//                checkCount++;
//                cout << "  bumping next check number in InvoiceDialog::invoiceCheckTextList (IF in 2nd FOR) [" << __LINE__ << "]" << endl;
//                cout << "  check count = " << checkCount << " [" << __LINE__ << "]" << endl;
//            }
//            cout << "  showCheck = " << showCheck << endl;
//            cout << "  isSecCopyNeeded = " << isSecCopyNeeded << endl;
//            cout << "  checkCount = " << checkCount << endl;
//            cout << "  (i) = " << i << endl;
//            cout << "  nextCheckNo = " << nextCheckNo << " in InvoiceDialog::invoiceCheckTextList (showCheck, 2nd FOR) [" << __LINE__ << "]" << endl;
//<<<<<<< HEAD
            // [KLN] add end


       //     checkList[i].setNumber(nextCheckNo);
//            checkList[i].setType(Check::Invoice);
//            checkList[i].setInvoiceId(m_invoice->getNumber());
//            TextCheck textCheck(checkList[i], format, *m_invoice, isInvoiceCheck);
//            checkTextList << QString::fromStdString(textCheck.text());
//        }
//    }
//=======
//            // [KLN] add end


//            checkList[i].setNumber(nextCheckNo);
//            checkList[i].setType(Check::Invoice);
//            checkList[i].setInvoiceId(m_invoice->getNumber());
//            TextCheck textCheck(checkList[i], format, *m_invoice, isInvoiceCheck);
//            checkTextList << QString::fromStdString(textCheck.text());
//        }
//    }
//>>>>>>> origin/master_0919

//}


void InvoiceDialog::printLaserInvoiceWithCheck(PrinterBase &printer, QTextDocument &textReportDoc,
                                               vector<TextCheck>& checkList,bool printChks
                                               )
{

    qDebug("InvoiceDialog::printLaserInvoiceWithCheck() entered");
    QStringList checkTextList;


    PreviewDialog prev;
    prev.setPageHeight(pageHeight);
    prev.setTopSkipLines(topSkip);
    prev.setTextDocument(textReportDoc.clone());

    QPrinter currentPrinter;
    currentPrinter.setPaperSize(QPrinter::Letter);
    currentPrinter.setPrinterName(printer.printerName());

 //   int  pageCnt = prev.pageCount(currentPrinter,textReportDoc.clone());
    for (int i = 0; i< checkList.size(); i++) {
        checkTextList << QString::fromStdString(checkList[i].text());
    }


//    invoiceCheckTextList(checkList,printChks,checkTextList,pageCnt);

    if (printChks && (checkTextList.size() > 0)) {

        prev.setCheckStartLine(checkStart);
        prev.setCheckPrint(true);
        prev.setCheckTextList(checkTextList);
        prev.setCheckTextList(checkList); //For process correct order of checks.
    }

    int copies = invoiceDao->laserCopyCount();
    bool isSecCopyNeeded = invoiceDao->isSecondCopyPrintNeeded();
    if (isSecCopyNeeded) {
        prev.printDocument(currentPrinter,1);
    } else {
        prev.printDocument(currentPrinter,copies);
    }
    qDebug("InvoiceDialog::printLaserInvoiceWithCheck() exited");
}

// This function create copy of original invoice text
// if start invoice line and start invoice line for second copy printer different,
// it extract lines from text to fit it on one page.
// Input - original invoice text ( not modified in the function)
// Return - copy of original invoice text with removed lines.
void InvoiceDialog::adjustInvoiceTextForMatrixPrinter(const string & inputString, string & result,int invoiceHeight, int checkStart, int secCheckStart)
{
    std::istringstream f(inputString);
    std::string line;
    int i = 0;
    int skipLinesCount = checkStart - secCheckStart;
    while (std::getline(f, line)) {
        if (line.find_first_of('\f') != string::npos) { //FF found, restart for new page.
            i = 0;
            skipLinesCount = checkStart - secCheckStart;
            result+="\f";
            continue;
        }
        if (i<invoiceHeight){
            result +=line+"\n";
            i++;
            continue;
        }
        else if (skipLinesCount > 0) { //Skip only if something to skip
            skipLinesCount--;
            i++;
            continue;
        }
        //at this point the rest of page need to be copied to result;
        result +=line+"\n";
    }
}

string InvoiceDialog::formatName(string nameString) {
    unsigned short nameLength = nameString.length();
    unsigned short slashIndex = 0;
    if((slashIndex = nameString.find_first_of('/')) < nameLength)
    {
        string lastName = nameString.substr(0, slashIndex);
        string firstName = (slashIndex + 1 < nameString.length()? nameString.substr(slashIndex + 1) : "");
        if (firstName.length() > 0 && lastName.length() > 0) {
            nameString = firstName + " " + lastName;
        } else if (firstName.length() > 0) {
            nameString = firstName;
        } else if (lastName.length() > 0) {
            nameString = lastName;
        }
    }
    return nameString;
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    bool fileExists()
//
// purpose: to eamil an invoice by calling a Java emailer
//
// calling params: QString path
//
// return params:
//
// Notes:
//
// Todo:
//
//////////////////////////////////////////////////
bool InvoiceDialog::fileExists(QString path) {
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and not a directory?
    return check_file.exists() && check_file.isFile();
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    void emailInvoice()
//
// purpose: to eamil an invoice by calling a Java emailer
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
//////////////////////////////////////////////////
void InvoiceDialog::emailInvoice()
{
    qDebug("InvoiceDialog::showPreview()");
    if(m_invoice == NULL)
    {
        return;
    }

    unsigned int skipLine = topSkip;
    unsigned int pageLen= pageHeight;
    unsigned int firstCheckLine = checkStart;

    TextInvoice *textInvoice;
    string text;

    deque<string> pages;

    m_invoice->sortTransactionList();
    string commentKey;
    string showIdKey;
    string showCommentsKey;

    if(customerType == Customer::Seller)
    {
        commentKey = "genSinvComment";
        textInvoice = new TextSellerInvoice((SellerInvoice*)(m_invoice), skipLine, pageLen, showSexSummary, groupCharges);
        textInvoice->setFooterText(setup.get("sinvFooterText"));
        showIdKey = "sinvShowNumber";
        showCommentsKey = "sinvShowTransactionComments";
    }
    else
    {
        commentKey = "genBinvComment";
        textInvoice = new TextBuyerInvoice(m_invoice, skipLine, pageLen, showSexSummary, averageOnLeft, groupCharges, binvTotalNS);
        textInvoice->setShowBrand(bool(atol(setup.get("binvShowBrand").c_str())));
        textInvoice->setFooterText(setup.get("binvFooterText"));
        showIdKey = "binvShowNumber";
        showCommentsKey = "binvShowTransactionComments";
    }

    // Prepare Customer id
    QString invoiceID = ui.sinvID->text().stripWhiteSpace();
//    cout << "    invoiceID: " << invoiceID.toStdString() << endl;
    invoiceID.replace("/", "-");
//    cout << "    invoiceID: " << invoiceID.toStdString() << endl;

    // Prepare Market Name
    QString marketName = QString::fromStdString(setup.get("genMktName "));
    if (marketName.isNull() || marketName.isEmpty()) {
        marketName = "Unknown Market Name";
    }

//    string nameString = formatName(m_invoice->getCustomer().getName().getLast());
//    QString marketName = QString::fromStdString(setup.getMarketInfo());
//    cout << "Customer Name: " << nameString << endl;
//    cout << "  Market Name: " << marketName.toStdString() << endl;

    textInvoice->setShowNames(invoiceDao->showName());
    textInvoice->setHeader(setup.reportHeader("", false, commentKey));
    textInvoice->setShowId(setup.getBoolean(showIdKey));
    textInvoice->setShowTransactionComments(setup.getBoolean(showCommentsKey));
    textInvoice->setMinimumHeaderSize(minimumHeaderSize);
    textInvoice->setTransFit(transOverrideColumn, transOverrideLength);
    textInvoice->setTransColumns(invoiceDao->getColumnList());


    PreviewDialog prev;
    prev.setPageHeight(pageHeight);
    prev.setTopSkipLines(topSkip);
    prev.setCheckStartLine(checkStart);
    prev.setCheckPrint(true);

    QString previewText = QString::fromStdString(textInvoice->text());
    prev.setText(previewText);

    prev.setShowPrint(true, (customerType == Customer::Seller ? PrinterDAO::SellerInvoice : PrinterDAO::BuyerInvoice));
    prev.setPrintButtonText("Loadout");
    prev.setReport(textInvoice);
    prev.setTextDocument(textInvoice->invoiceTextDocument());

    setCursor(Qt::WaitCursor);

    QPrinter emailPrinter;
    emailPrinter.setPaperSize(QPrinter::Letter);

    QString home = qgetenv("HOME");
//    cout << " home: " << home.toStdString() << endl;

    QDir dir(home+"/email-invoices");
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QString emailFileName = dir.path() + "/" + QString("invoice-%1.pdf").arg(invoiceID);
//    cout << "emailFilename: " << emailFileName.toStdString() << endl;
    emailPrinter.setOutputFileName(emailFileName);
    prev.printDocument(emailPrinter);

    // Call java emailer here
//    system("java -jar " + home + "/dist-auction/EmptyProject.jar" + " " + emailFileName + " '" + marketName +"'");
    system("java -jar " + home + "/dist-auction/AuctionEmail.jar" + " " + emailFileName + " '" + marketName +"'");

    setCursor(Qt::ArrowCursor);

    delete textInvoice;

}

///////////////////////////////////////////////////////////////////////////////
//
// name:    void showMissingBuyers()
//
// purpose: call a Java program to display buyers that are in transactions but
//          not in the daily buyer file.
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
//////////////////////////////////////////////////

void InvoiceDialog::showMissingBuyers() {
    QString home = qgetenv("HOME");
    system("java -jar " + home + "/dist/MissingBuyers.jar");
}









