/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef TABLEREPAIRDIALOG_H
#define TABLEREPAIRDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QButtonGroup;
class QPushButton;

namespace Ui {
  class TableRepairDialog;
}


class TableRepairDialog : public QDialog
{
    Q_OBJECT

public:
    TableRepairDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~TableRepairDialog();

    int repairTable( QString tableName );

public slots:
    void repairTagTable();
    void repairBrandTable();
    void repairDailyBuyerTables();
    void repairDailySellerTables();
    void repairChargeTables();
    void repairCheckTables();
    void repairCodeTable();
    void repairCommissionTables();
    void repairPermanantTable();
    void repairPrinterTables();
    void repairDisplayTables();
    void repairSellerInvoiceTables();
    void repairBuyerInvoiceTables();
    void repairSetupTable();
    void repairTransactionTables();
    void repairTruckinTable();
    void repairZipCodeTable();
    void repairAllTables();
    void repairTableList( QStringList tableList, QString listDescription );

protected:

protected slots:

private:
    void init();
  
    Ui::TableRepairDialog *ui;
};

#endif // TABLEREPAIRDIALOG_H
