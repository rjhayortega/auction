/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef CHARGECREDITDIALOG_H
#define CHARGECREDITDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "types/invoice.h"
#include "dao/chargedao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class Q3Table;

namespace Ui {
  class ChargeCreditDialog;
}

class ChargeCreditDialog : public QDialog
{
    Q_OBJECT

public:
    ChargeCreditDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~ChargeCreditDialog();

public slots:
    void init( Invoice * invoice, bool isBuyer );
    void populateAdjustmentTable();
    void showTotals();
    void accept();

protected:

protected slots:

private:
    vector<Charge> chargeList;
    Invoice *invoice;
    bool isBuyer;

    void init();
    Ui::ChargeCreditDialog *ui;

};

#endif // CHARGECREDITDIALOG_H
