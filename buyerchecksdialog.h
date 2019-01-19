/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef BUYERCHECKSDIALOG_H
#define BUYERCHECKSDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "dao/commissiondao.h"
#include "types/invoice.h"
#include "dao/invoicedao.h"
#include "dao/checkdao.h"
#include "dao/setupdao.h"
#include "reports/textcheck.h"
#include "dao/printerdao.h"
#include "reports/buyercheckreport.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class Q3ListBox;
class Q3ListBoxItem;
class QCheckBox;

namespace Ui {
    class BuyerChecksDialog;
}

class BuyerChecksDialog : public QDialog
{
    Q_OBJECT

public:
    BuyerChecksDialog(QWidget* parent = 0);
    ~BuyerChecksDialog();

public slots:
    void populateBuyerChecksList();
    void printChecks();

protected:

protected slots:
    
private:

    vector<BuyerInvoice> buyerInvoiceList;
    BuyerInvoiceDAO binvDao;
    CommissionDAO commDao;
    CheckDAO checkDao;
    SetupDAO setup;
    SellerInvoiceDAO setupInvoiceDao;

    PrinterBase *m_reportPrinter;
    PrinterBase *m_checkPrinter;
    PrinterBase *m_invoicePrinter;
    PrinterBase *m_secondCopyPrinter;

    void init();
    string getFormFeed(int, int, bool);
    string fixLaserCheckFormat(string, int, int, int);
    Ui::BuyerChecksDialog *ui;
};

#endif // BUYERCHECKSDIALOG_H
