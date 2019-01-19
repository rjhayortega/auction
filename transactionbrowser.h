/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef TRANSACTIONBROWSER_H
#define TRANSACTIONBROWSER_H

#include <qvariant.h>
#include <qdialog.h>
#include "types/transaction.h"
#include "dao/setupdao.h"
#include "dao/salemanager.h"
#include "dao/transactiondao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QPushButton;
class Q3Table;
class QComboBox;
class TransactionDialog;

namespace Ui {
    class TransactionBrowser;
}

class TransactionBrowser : public QDialog
{
    Q_OBJECT

public:
    TransactionBrowser( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~TransactionBrowser();


public slots:
    void init();
    void newTransaction();
    void deleteCurrentTransaction();
    void editTransaction( int row, int col, int butt, const QPoint & mouse_pos );
    void printTransactions();
    void populateTransactionTable();
    void showTransactionTable();
    void sortTransactionsByIndex();
    void updateTableRow( int row, Transaction transaction );
    void printTransactionList();
    void searchListByIndex();
    void keyPressEvent( QKeyEvent * event );

protected:

protected slots:

private:
    vector<Transaction> transactionList;
    SetupDAO setup;
    SaleManager sale;

    Ui::TransactionBrowser *ui;

    TransactionDialog * m_transEditDialog;
};

#endif // TRANSACTIONBROWSER_H
