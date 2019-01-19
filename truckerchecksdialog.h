/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef TRUCKERCHECKSDIALOG_H
#define TRUCKERCHECKSDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "dao/truckingrecorddao.h"
#include "types/truckingrecord.h"
#include "dao/invoicedao.h"
#include "dao/setupdao.h"
#include "reports/textcheck.h"
#include "dao/checkdao.h"
#include "lineprinter.h"
#include "reports/truckercheckreport.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QPushButton;
class Q3ListBox;
class QListBoxItem;
class QCheckBox;

namespace Ui {
  class TruckerChecksDialog;
}

class TruckerChecksDialog : public QDialog
{
    Q_OBJECT

public:
    TruckerChecksDialog( QWidget* parent = 0);
    ~TruckerChecksDialog();

    Invoice getInvoice( string consignerNo, Customer::Type consignerType );

public slots:
    void populateTruckerList();
    void populateTruckerList( Q3ListBox * turckerList, vector<TruckingRecord> & truckingList, Customer::Type customerType );
    void printChecks();
    void printChecks( Q3ListBox * truckerList, vector<TruckingRecord> truckingList );

protected:

protected slots:
private:
    void printLaserReportWithCheck(PrinterBase &printer, QStringList &checkTextList, QStringList &reportText);
private:
    PrinterBase* m_checkPrinter;
    CheckDAO checkDao;
    SellerInvoiceDAO sinvDao;
    BuyerInvoiceDAO binvDao;
    SellerInvoiceDAO setupInvoiceDao;
    SetupDAO setup;
    TruckingRecordDAO truckingDao;
    PrinterBase* m_reportPrinter;
    PrinterBase* m_invoicePrinter;
    PrinterBase *m_secondCopyPrinter;
    vector<TruckingRecord> sellerTruckingList;
    vector<TruckingRecord> buyerTruckingList;
    string getFormFeed(int, int);

    void init();
    
    Ui::TruckerChecksDialog *ui;

};

#endif // TRUCKERCHECKSDIALOG_H
