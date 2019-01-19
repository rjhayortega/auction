//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "setupdialog.h"
#include "ui_setupdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qspinbox.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
//#include "video/videosetupdialog.h"
#include "faxsetupdialog.h"
#include "salemanagersetupdialog.h"

SetupDialog::SetupDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::SetupDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->chargeEditButton, SIGNAL( clicked() ), this, SLOT( startChargeEdit() ) );
    connect( ui->commEditButton, SIGNAL( clicked() ), this, SLOT( startCommEdit() ) );
    connect( ui->codeEditButton, SIGNAL( clicked() ), this, SLOT( startCodeEdit() ) );
    connect( ui->startSellerSetup, SIGNAL( clicked() ), this, SLOT( startSellerInvoiceSetup() ) );
    connect( ui->startBuyerSetup, SIGNAL( clicked() ), this, SLOT( startBuyerInvoiceSetup() ) );
    connect( ui->checkSetupButton, SIGNAL( clicked() ), this, SLOT( startCheckSetup() ) );
    connect( ui->printerSetupButton, SIGNAL( clicked() ), this, SLOT( setupPrinter() ) );
    connect( ui->externSetupButton, SIGNAL( clicked() ), this, SLOT( extrasSetupDialog() ) );
    connect( ui->saveMarketButton, SIGNAL( clicked() ), this, SLOT( saveMarketInfo() ) );
    connect( ui->marketReportSetupButton, SIGNAL( clicked() ), this, SLOT( startMarketReportSetup() ) );
    connect( ui->reportSetupButton, SIGNAL( clicked() ), this, SLOT( startReportSetup() ) );
    connect( ui->setupScaleButton, SIGNAL( clicked() ), this, SLOT( startScaleSetup() ) );
    connect( ui->setupDisplaysButton, SIGNAL( clicked() ), this, SLOT( startDisplaysSetup() ) );
    connect( ui->saveWebAuctionsButton, SIGNAL( clicked() ), this, SLOT( saveWebAuctions() ) );
//    connect( ui->saveCattleUSASetupButton, SIGNAL( clicked() ), this, SLOT( saveCattleUSASetup() ) );
//    connect( ui->saveDVAuction, SIGNAL( clicked() ), this, SLOT( saveDVAuctionSetup() ) );
    connect( ui->setupVideoCameraButton, SIGNAL( clicked() ), this, SLOT( startVideoCameraSetup() ) );
    connect( ui->setupFaxModemButton, SIGNAL( clicked() ), this, SLOT( startFaxModemSetup() ) );
    connect( ui->setupSaleManagerButton, SIGNAL( clicked() ), this, SLOT( startSaleManagerSetup() ) );
    // tab order
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
SetupDialog::~SetupDialog()
{
    delete ui;
}

#include "commissiondialog.h"
#include "chargedialog.h"
#include "codedialog.h"
#include "invoicesetup.h"
#include "checksetup.h"
#include "printersetupdialog.h"
#include "clerksetupdialog.h"
#include "marketreportsetupdialog.h"
#include "reportsetupdialog.h"
#include "scalesetupdialog.h"
#include "displaybrowserdialog.h"

///////////////////////////////////////////////////////////////////////////////
//
// name:    init()
//
// purpose: constructor like function
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

void SetupDialog::init()
{
    loadMarketInfo();
    loadWebAuctions();
//    loadCattleUSASetup();
//    loadDVAuctionSetup();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    startCommEdit()
//
// purpose: starts the commission edit dialog
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

void SetupDialog::startCommEdit()
{
    CommissionDialog(this).exec();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    startChargeEdit()
//
// purpose: starts the charge edit dialog
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

void SetupDialog::startChargeEdit()
{
    ChargeDialog(this).exec();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    startCodeEdit()
//
// purpose: starts the code edit dialog
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

void SetupDialog::startCodeEdit()
{
    CodeDialog(this).exec();
}

void SetupDialog::startSellerInvoiceSetup()
{
    InvoiceSetup invoiceSetup(this);
    invoiceSetup.init(Customer::Seller);
    invoiceSetup.exec();
}

void SetupDialog::startBuyerInvoiceSetup()
{
    InvoiceSetup invoiceSetup(this);
    invoiceSetup.init(Customer::Buyer);
    invoiceSetup.exec();
}

void SetupDialog::startCheckSetup()
{
    CheckSetup(this).exec();
}

void SetupDialog::startMarketReportSetup()
{
    MarketReportSetupDialog (this).exec();
}

void SetupDialog::setupPrinter()
{
    qDebug("SetupDialog::setupPrinter()");
    PrinterSetupDialog(this).exec();
}


void SetupDialog::extrasSetupDialog()
{
    ClerkSetupDialog(this).exec();
}

void SetupDialog::startScaleSetup()
{
    qDebug("SetupDialog::startScaleSetup()");
    ScaleSetupDialog(this).exec();
}

void SetupDialog::loadMarketInfo()
{
    ui->marketNameEdit->setText(QString::fromStdString(setup.get("genMktName")));
    ui->marketAddressEdit->setText(QString::fromStdString(setup.get("genMktAddress")));
    ui->marketCityEdit->setText(QString::fromStdString(setup.get("genMktCity")));
    ui->marketStateEdit->setText(QString::fromStdString(setup.get("genMktState")));
    ui->marketZipEdit->setText(QString::fromStdString(setup.get("genMktZip")));
    ui->marketIdEdit->setText(QString::fromStdString(setup.get("genMktId")));
    ui->dailyFMPhoneMatch->setChecked(setup.getBoolean("dailyFMPhoneMatch"));
    ui->dailyFMCheckinTickets->setChecked(setup.getBoolean("dailyFMCheckinTickets"));
    ui->selectiveTagReportCheck->setChecked(setup.getBoolean("selectiveTagReport"));
    ui->countryOfOriginCheckBox->setChecked(setup.getBoolean("useCountryOfOrigin"));
    int firstTransient = -1;
    string transientStr = setup.get("firstTransientBuyer");

    if(transientStr.length() > 0)
    {
        firstTransient = atoi(transientStr.c_str());
    }

    ui->transientBuyerBox->setValue(firstTransient);
    ui->rfTagOnCheckBox->setChecked(bool(atoi(setup.get("rfIdTagsOn").c_str())));
    ui->rfPortEdit->setText(QString::fromStdString(setup.get("rfIdTagsPort")));

}

void SetupDialog::saveMarketInfo()
{
    setup.set("genMktName", ui->marketNameEdit->text().toStdString());
    setup.set("genMktAddress", ui->marketAddressEdit->text().toStdString());
    setup.set("genMktCity", ui->marketCityEdit->text().toStdString());
    setup.set("genMktZip", ui->marketZipEdit->text().toStdString());
    setup.set("genMktState", ui->marketStateEdit->text().toStdString());
    setup.set("genMktId", ui->marketIdEdit->text().toStdString());
    setup.set("firstTransientBuyer", QString::number(ui->transientBuyerBox->value()).toStdString());
    setup.set("rfIdTagsOn", QString::number(int(ui->rfTagOnCheckBox->isChecked())).toStdString());
    setup.set("rfIdTagsPort", ui->rfPortEdit->text().toStdString());
    setup.setBoolean("dailyFMPhoneMatch", ui->dailyFMPhoneMatch->isChecked());
    setup.setBoolean("dailyFMCheckinTickets", ui->dailyFMCheckinTickets->isChecked());
    setup.setBoolean("selectiveTagReport", ui->selectiveTagReportCheck->isChecked());
    setup.setBoolean("useCountryOfOrigin", ui->countryOfOriginCheckBox->isChecked());
}

void SetupDialog::startReportSetup()
{
    ReportSetupDialog(this).exec();
}

void SetupDialog::startDisplaysSetup()
{
    DisplayBrowserDialog(this).exec();
}

//MariaDB [auction6]> select * from setup where skey like "%attle%" or skey like "DVA%";
//+--------+--------------------+-----------+
//| key_id | skey               | svalue    |
//+--------+--------------------+-----------+
//|  92321 | DVAConsignor       | 1         |
//|  92320 | DVAweightboardPath | /tmp      |
//|  92319 | cattleUSAServer    | 10.2.4.10 |
//|  92318 | cattleUSAId        | 1234      |
//|  92317 | enableCattleUSA    | 1         |
//|  92322 | DVABidPrice        | 1         |
//+--------+--------------------+-----------+
//6 rows in set (0.00 sec)

void SetupDialog::loadWebAuctions() {
    // Delete old setups that are no longer used
    if (!setup.get("DVAweightboardPath").empty()) {
        setup.del("DVAweightboardPath");
        setup.del("DVAConsignor");
        setup.del("DVABidPrice");
    }
    // CattleUSA:
    if (setup.getBoolean("enableCattleUSA")) { // still have old values!
        // retrieve them:
        bool enabled = setup.getBoolean("enableCattleUSA");
        string id = setup.get("cattleUSAId");
        string server = setup.get("cattleUSAServer");
        // remove them:
        setup.del("enableCattleUSA");
        setup.del("cattleUSAId");
        setup.del("cattleUSAServer");
        // Re-save as new format:
        setup.setBoolean("webEnableCattleUSA", enabled);
        setup.set("webCattleUSAId", id);
        setup.set("webCattleUSAServer", server);
    }
    ui->enableCattleUSACheckBox->setChecked(setup.getBoolean("webEnableCattleUSA"));
    ui->cattleUSAIdLineEdit->setText(QString::fromStdString(setup.get("webCattleUSAId")));
    ui->cattleUSAServerEdit->setText(QString::fromStdString(setup.get("webCattleUSAServer")));
    // DVAuction:
    ui->enableDVAuctionCheckBox->setChecked(setup.getBoolean("webEnableDVAuction"));
    ui->dvAuctionIdLineEdit->setText(QString::fromStdString(setup.get("webDVAuctionId")));
    ui->dvAuctionServerEdit->setText(QString::fromStdString(setup.get("webDVAuctionServer")));
}

void SetupDialog::saveWebAuctions() {
    // CattleUSA:
    setup.setBoolean("webEnableCattleUSA", ui->enableCattleUSACheckBox->isChecked());
    setup.set("webCattleUSAId", ui->cattleUSAIdLineEdit->text().toStdString());
    setup.set("webCattleUSAServer", ui->cattleUSAServerEdit->text().toStdString());
    // DVAuction:
    setup.setBoolean("webEnableDVAuction", ui->enableDVAuctionCheckBox->isChecked());
    setup.set("webDVAuctionId", ui->dvAuctionIdLineEdit->text().toStdString());
    setup.set("webDVAuctionServer", ui->dvAuctionServerEdit->text().toStdString());
}



//void SetupDialog::loadCattleUSASetup()
//{
//    ui->enableCattleUSACheckBox->setChecked(setup.getBoolean("enableCattleUSA"));
//    ui->cattleUSAIdLineEdit->setText(QString::fromStdString(setup.get("cattleUSAId")));
//    ui->cattleUSAServerEdit->setText(QString::fromStdString(setup.get("cattleUSAServer")));
//}

//void SetupDialog::saveCattleUSASetup()
//{
//    setup.setBoolean("enableCattleUSA", ui->enableCattleUSACheckBox->isChecked());
//    setup.set("cattleUSAId", ui->cattleUSAIdLineEdit->text().toStdString());
//    setup.set("cattleUSAServer", ui->cattleUSAServerEdit->text().toStdString());
//}

//void SetupDialog::loadDVAuctionSetup()
//{
//    ui->lineEdit10->setText(QString::fromStdString(setup.get("DVAweightboardPath")));
//    ui->DVAConsignorCheck->setChecked(setup.getBoolean("DVAConsignor"));
//    ui->DVABidPriceCheck->setChecked(setup.getBoolean("DVABidPrice"));
//}

//void SetupDialog::saveDVAuctionSetup()
//{
////cout << "DVAuction setup saving receives " << path << endl;
//    setup.set("DVAweightboardPath", ui->lineEdit10->text().toStdString());
//    setup.setBoolean("DVAConsignor", ui->DVAConsignorCheck->isChecked());
//    setup.setBoolean("DVABidPrice", ui->DVABidPriceCheck->isChecked());
//}

void SetupDialog::startVideoCameraSetup()
{
//    VideoSetupDialog videoDlg;
//    videoDlg.exec();

}

void SetupDialog::startFaxModemSetup()
{
    FaxSetupDialog faxDlg;
    faxDlg.exec();
}

void SetupDialog::startSaleManagerSetup()
{
    SaleManagerSetupDialog saleManagerDlg;
    saleManagerDlg.exec();
}

