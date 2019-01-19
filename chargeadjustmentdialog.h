/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef CHARGEADJUSTMENTDIALOG_H
#define CHARGEADJUSTMENTDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "types/invoice.h"
#include "types/commission.h"
#include "dao/chargedao.h"
#include "dao/invoicedao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QComboBox;
class QLabel;
class QGroupBox;
class QLineEdit;
class Q3Table;


namespace Ui {
  class ChargeAdjustmentDialog;
}
  
class ChargeAdjustmentDialog : public QDialog
{
    Q_OBJECT

public:
    ChargeAdjustmentDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~ChargeAdjustmentDialog();

 
    Commission calculateBuyerCommission();

public slots:
    void init( Invoice * invoice );
    void setInvoiceDAORef( InvoiceDAO * invoiceDao );
    void changeGroup( int selected );
    void populateChargeList();
    void accept();
    void creditCharges();
    void doCalclulateBuyerCommission();
    void setIsBuyer( bool isBuyer );

protected:

private:
    vector<Charge> multiplierList;
    Invoice *invoice;
    bool isBuyer;
    ChargeDAO dao;
    InvoiceDAO* invoiceDao;

    Ui::ChargeAdjustmentDialog *ui;
    
    void init();

};

#endif // CHARGEADJUSTMENTDIALOG_H
