/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef PRORATETRANSACTIONDIALOG_H
#define PRORATETRANSACTIONDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "types/prorate.h"
#include "types/transaction.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class Q3Table;
class QPushButton;

namespace Ui {
  class ProrateTransactionDialog;
}

class ProrateTransactionDialog : public QDialog
{
    Q_OBJECT

public:
    ProrateTransactionDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~ProrateTransactionDialog();

    vector<Prorate::Data> getProrateData();

public slots:
    void init( vector<Transaction> transactionList, vector<Prorate> proratedList, unsigned int row );
    void addProrateToTable( Prorate prorate, bool currentPayee );
    void addDataToTable( Prorate::Data data, bool currentPayee );

protected:

protected slots:

private:
    unsigned int prorateRow;
    vector<Prorate> proratedList;
    vector<Transaction> transactionList;
    QString xChar;

    void init();
    Ui::ProrateTransactionDialog *ui;
};

#endif // PRORATETRANSACTIONDIALOG_H
