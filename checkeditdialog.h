/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef CHECKEDITDIALOG_H
#define CHECKEDITDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "types/check.h"
#include "dao/checkdao.h"
#include "dao/invoicedao.h"
#include "dao/printerdao.h"

#include <QMessageBox>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLineEdit;
class QLabel;
class QDateEdit;
class QSpinBox;
class QComboBox;

namespace Ui {
  class CheckEditDialog;
}

class CheckEditDialog : public QDialog
{
    Q_OBJECT

public:
    CheckEditDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~CheckEditDialog();


public slots:
    void init( Check check, bool newCheck );
    void updateCheckNumber( int number );
    void setCheckType();
    void setAmountText( const QString & numAmount );
    void setStatusCleared();
    void setStatusVoid();
    void setStatusOutstanding();
    void okPressed();
    void saveCheck();
    void printCheck();
    void reject();

protected:

protected slots:

private:
    Check check;
    CheckDAO dao;
    bool newCheck;
    bool blockSignal;
    SellerInvoiceDAO invoiceDao;
    PrinterBase *m_checkPrinter;
    PrinterBase *m_invoicePrinter;
    PrinterBase *m_secondCopyPrinter;

    void init();
    
    Ui::CheckEditDialog *ui;

};

#endif // CHECKEDITDIALOG_H
