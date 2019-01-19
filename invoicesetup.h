/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef INVOICESETUP_H
#define INVOICESETUP_H

#include <qvariant.h>
#include <qdialog.h>
#include "dao/invoicedao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QComboBox;
class QCheckBox;
class QLabel;
class QSpinBox;
class QGroupBox;
class QTable;
class QTextEdit;
class QPushButton;

namespace Ui {
  class InvoiceSetup;
}

class InvoiceSetup : public QDialog
{
    Q_OBJECT

public:
    InvoiceSetup( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~InvoiceSetup();

    typedef enum {Seller, Buyer}CUST_TYPE;

public slots:
    void init( Customer::Type custType );
    void load();
    void save();
    void enableCheckOnInvoiceOptions( bool enable );

protected:

protected slots:

private:
    InvoiceDAO* dao;
    QStringList menu;
    string commentKey;
    Customer::Type customerType;
    string disclaimerKey;
    string showNumberKey;
    string showCommentKey;
    string groupChargesKey;
    string headerSizeKey;
    string transOverrideColumnKey;
    string transOverrideLengthKey;
    string replaceAddressCoMatchKey;
    string m_laserPrinterCopyCountKey;


    void init();
    void destroy();

    Ui::InvoiceSetup *ui;
  
};

#endif // INVOICESETUP_H
