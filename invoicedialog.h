/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef INVOICEDIALOG_H
#define INVOICEDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <qprogressdialog.h>
#include "./dao/invoicedao.h"
#include "dao/checkdao.h"
#include "reports/textcheck.h"
#include "dao/proratedao.h"
#include "dao/salemanager.h"
#include "dao/setupdao.h"
#include "permsearchdialog.h"
#include "dao/printerdao.h"
#include <QTextDocument>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QPushButton;
class QComboBox;
class QLineEdit;
class QButtonGroup;
class QRadioButton;
class Q3Table;

#include "ui_invoicedialog.h"
#include "ui_faxsenddialog.h"

class InvoiceDialog : public QDialog
{
    Q_OBJECT

public:
    InvoiceDialog( QWidget* parent = 0);
    virtual ~InvoiceDialog();


    bool allowPermSearch;

    vector<Check> getInvoiceCheckList( bool printChecks, vector<double> & chargeShareList );
    string getInvoiceText( bool showCheck, vector<Check> checkList, vector<double> chargeShareList,vector<TextCheck>& finalCheckList );
    Check getInvoiceCheck();
    Customer::Type getCustomerType();
    string getInvoicePagesText( deque<string> pages, Check check, bool showCheck, unsigned int firstCheckLine,
                                CheckFormatData format, bool allPages,
                                bool showAddressOnCheck,vector<TextCheck> & finalCheckList );
//    void invoiceCheckTextList(vector<Check> &checkList, bool printChks, QStringList & checkTextList, int pageCount);
    string formatName(string);

public slots:
    void init( Customer::Type custType );
    void loadInvoiceFromId();
    void initInvoiceById();
    void showInvoice();
    void saveCustomerAsDaily();
    void showPreview();
    void editClickedTransaction( int row, int col );
    void printInvoice();
//    void previewInvoice();
    void startTruckingDialog();
    bool startChargeAdjustment();
    void showReadySellers();
    void startProrate();
    void changeCustomerType( int buttonId );
    void startBuyerRecap();
    void resetInvoice();
    void startPermSearch();
    void loadNumberList();
    void loadCityStateZipFromCity();
    void loadCityStateZipFromZip();
    void autoLoadCityStateZip( vector<Address> zipCodeList );
    void globalBuyerChange();
    void globalPenChange();
    void faxInvoice();
    void setInvoiceStatus();
    void overrideAddress();
    void emailInvoice();
    bool fileExists(QString);
    void showMissingBuyers();

protected:
    int newVariable;


protected slots:

private:
    void printLaserInvoiceWithCheck(PrinterBase &printer, QTextDocument &textReportDoc, vector<TextCheck> &checkList, bool printChks);
    void adjustInvoiceTextForMatrixPrinter(const string & inputString,string &result, int invoiceHeight, int checkStart, int secCheckStart);

    int transOverrideLength;
    int transOverrideColumn;
    int minimumHeaderSize;
    bool groupCharges;
    bool averageOnLeft;
    CheckDAO checkDao;
    CheckFormatData format;
    SetupDAO setup;
    SaleManager sale;
    Customer::Type customerType;
    Invoice *m_invoice;
    InvoiceDAO *invoiceDao;
    bool blockInit;
    vector<string> numberList;

    unsigned int topSkip;
    unsigned int pageHeight;
    unsigned int checkStart;
    bool chkOnInvoice;
    bool showSexSummary;
    bool binvTotalNS;
    int checkCount; // [KLN] add

    void init();
    //Printers
    PrinterBase* m_invoicePrinter;
    PrinterBase* m_checkPrinter;
    //Dialog form
    Ui::InvoiceDialog ui;
    Ui::sendFaxDialog sendFaxDialog;

    QTextDocument* m_textDocument;

};

#endif // INVOICEDIALOG_H
