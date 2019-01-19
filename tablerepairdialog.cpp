//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "tablerepairdialog.h"
#include "ui_tablerepairdialog.h"

#include <qvariant.h>
#include <qbuttongroup.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

TableRepairDialog::TableRepairDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::TableRepairDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->sellerInvoiceButton, SIGNAL( clicked() ), this, SLOT( repairSellerInvoiceTables() ) );
    connect( ui->printerButton, SIGNAL( clicked() ), this, SLOT( repairPrinterTables() ) );
    connect( ui->permButton, SIGNAL( clicked() ), this, SLOT( repairPermanantTable() ) );
    connect( ui->displayButton, SIGNAL( clicked() ), this, SLOT( repairDisplayTables() ) );
    connect( ui->dailySellerButton, SIGNAL( clicked() ), this, SLOT( repairDailySellerTables() ) );
    connect( ui->dailyBuyerButton, SIGNAL( clicked() ), this, SLOT( repairDailyBuyerTables() ) );
    connect( ui->commissionButton, SIGNAL( clicked() ), this, SLOT( repairCommissionTables() ) );
    connect( ui->codeButton, SIGNAL( clicked() ), this, SLOT( repairCodeTable() ) );
    connect( ui->checkButton, SIGNAL( clicked() ), this, SLOT( repairCheckTables() ) );
    connect( ui->chargeButton, SIGNAL( clicked() ), this, SLOT( repairChargeTables() ) );
    connect( ui->buyerInvoiceButton, SIGNAL( clicked() ), this, SLOT( repairBuyerInvoiceTables() ) );
    connect( ui->brandButton, SIGNAL( clicked() ), this, SLOT( repairBrandTable() ) );
    connect( ui->backtagButton, SIGNAL( clicked() ), this, SLOT( repairTagTable() ) );
    connect( ui->allButton, SIGNAL( clicked() ), this, SLOT( repairAllTables() ) );
    connect( ui->zipCodeButton, SIGNAL( clicked() ), this, SLOT( repairZipCodeTable() ) );
    connect( ui->truckingButton, SIGNAL( clicked() ), this, SLOT( repairTruckinTable() ) );
    connect( ui->transButton, SIGNAL( clicked() ), this, SLOT( repairTransactionTables() ) );
    connect( ui->setupButton, SIGNAL( clicked() ), this, SLOT( repairSetupTable() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
TableRepairDialog::~TableRepairDialog()
{
    delete ui;
}

#include "dao/databasemanager.h"
#include "qmessagebox.h"
#include <string>

using namespace std;

void TableRepairDialog::init()
{

}

void TableRepairDialog::repairTagTable()
{
    QStringList tableList("backtags");
    repairTableList(tableList, "Tags");
}

void TableRepairDialog::repairBrandTable()
{
    QStringList tableList("brand");
    repairTableList(tableList, "Brands");
}

void TableRepairDialog::repairDailyBuyerTables()
{
    QStringList tableList;
    tableList << "buyer" << "buyer_commission" << "charge_adjustment" << "trucking_record";
    repairTableList(tableList, "Daily Buyer");
}

void TableRepairDialog::repairDailySellerTables()
{
    QStringList tableList;
    tableList << "seller" << "charge_adjustment" << "trucking_record" << "checkfactory";
    repairTableList(tableList, "Daily Seller");
}

void TableRepairDialog::repairChargeTables()
{
    QStringList tableList;
    tableList << "charge" << "charge_adjustment" << "charge_code_rel" << "charge_break";
    repairTableList(tableList, "Charges");
}

void TableRepairDialog::repairCheckTables()
{
    QStringList tableList;
    tableList << "checkreg" << "depositreg" << "checkfactory" << "prorate" << "proratedata";
    repairTableList(tableList, "Check Register");
}

void TableRepairDialog::repairCodeTable()
{
    QStringList tableList("codes");
    repairTableList(tableList, "Animal Code");
}

void TableRepairDialog::repairCommissionTables()
{
    QStringList tableList;
    tableList << "comm_code_rel" << "commission" << "commission_break";
    repairTableList(tableList, "Commission");
}

void TableRepairDialog::repairPermanantTable()
{
    QStringList tableList("customer");
    repairTableList(tableList, "Permanant");
}

void TableRepairDialog::repairPrinterTables()
{
    QStringList tableList;
    tableList << "setup" << "default_printers";
    repairTableList(tableList, "Printer");
}


void TableRepairDialog::repairDisplayTables()
{
    QStringList tableList;
    tableList << "displays" << "disprows";
    repairTableList(tableList, "Displays");
}

void TableRepairDialog::repairSellerInvoiceTables()
{
    QStringList tableList;
    tableList << "sellerinvoice" << "sellerinvoicesummary" << "sellerchargesummary";
    repairTableList(tableList, "Seller Invoices");
}

void TableRepairDialog::repairBuyerInvoiceTables()
{
    QStringList tableList;
    tableList << "buyerinvoice" << "buyerinvoicesummary", "buyerchargesummary";
    repairTableList(tableList, "Buyer Invoices");
}

void TableRepairDialog::repairSetupTable()
{
    QStringList tableList("setup");
    repairTableList(tableList, "Setup");
}

void TableRepairDialog::repairTransactionTables()
{
    QStringList tableList;
    tableList << "trans" << "marketreport";
    repairTableList(tableList, "Transaction");
}

void TableRepairDialog::repairTruckinTable()
{
    QStringList tableList("trucking_record");
    repairTableList(tableList, "Trucking");
}

void TableRepairDialog::repairZipCodeTable()
{
    QStringList tableList("zip_code");
    repairTableList(tableList, "Zip Code");
}


void TableRepairDialog::repairAllTables()
{
    QStringList tableList;
    tableList << "backtags"<< "brand" << "buyer" << "buyerchargesummary" << "buyercommission"
              << "buyerinvoice" << "buyerinvoicesummary" << "charge" << "charge_adjustment"
              << "charge_code_rel" << "checkfactory" << "checkreg" << "codes" << "comm_code_rel"
              << "commission" << "commission_break" << "customer" << "default_printers" << "depositreg"
              << "displays" << "disprows" << "market_report" << "prorate" << "proratedata"  << "rfid_tag"
              << "sales" << "seller" << "sellerchargesummary" << "sellerinvoice" << "sellerinvoicesummary"
              << "setup" << "trans" << "trucking_record" << "zip_code";

    repairTableList(tableList, "All Tables");

}

void TableRepairDialog::repairTableList(QStringList tableList, QString listDescription)
{
    setCursor(Qt::WaitCursor);

    int errorCount = 0;
    for(unsigned int i = 0; i < tableList.size(); i++)
    {
        errorCount += repairTable(tableList[i]);
    }

    setCursor(Qt::ArrowCursor);
    QMessageBox::information(this, "Finished",
                             listDescription + " repair finished with: " + QString::number(errorCount) + " errors",
                             QMessageBox::Ok);
}


int TableRepairDialog::repairTable(QString tableName)
{
    int errorCount = 0;
    QString queryString = QString("REPAIR TABLE ").append(tableName).append(" EXTENDED");
    QSqlQuery repairQuery = DatabaseManager::defaultManager.query(queryString);
    if( !repairQuery.first())
    {
        QMessageBox::information(this, "ERROR", "Could not repair the: " + tableName + " table", QMessageBox::Ok);
        errorCount ++;
    }
    return errorCount;
}

