/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef TRANSFERCHECKDIALOG_H
#define TRANSFERCHECKDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <vector>
#include "dao/chargedao.h"
#include "dao/checkdao.h"
#include "dao/printerdao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class Q3ListBox;
class Q3ListBoxItem;
class QComboBox;
class QLabel;

namespace Ui {
  class TransferCheckDialog;
}

class TransferCheckDialog : public QDialog
{
    Q_OBJECT

public:
    TransferCheckDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~TransferCheckDialog();

public slots:
    void populateChargeSummaryList();
    void writeCheck();

protected:

protected slots:
    
private:
    ChargeDAO dao;
    vector<ChargeDAO::SUMMARY_ITEM> summaryList;
    CheckDAO checkDao;
    PrinterBase *m_checkPrinter;
    PrinterBase *m_invoicePrinter;
    PrinterBase *m_secondCopyPrinter;

    void init();
    
    Ui::TransferCheckDialog *ui;
};

#endif // TRANSFERCHECKDIALOG_H
