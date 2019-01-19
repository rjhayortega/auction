/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef MARKETREPORTDIALOG_H
#define MARKETREPORTDIALOG_H

#include <QDialog>
#include <Q3Table>
#include "types/transaction.h"
#include "reports/marketreport.h"
#include "dao/transactiondao.h"

namespace Ui {
class MarketReportDialog;
}

class MarketReportDialog : public QDialog {
    Q_OBJECT
public:
    MarketReportDialog(QWidget *parent = 0);
    ~MarketReportDialog();


public slots:
    void populateTransactionList();
    void sortTransactionList( int index );
    void showTransactionList();
    void copySelectedToInclude();
    void restoreMarketList();
    void moveTransactionToIncluded();
    void includeTransaction( long transNo );
    void includeTransaction( long transNo, bool redisplay );
    void removeTransactionFromIncluded();
    void displayIncludeList();
    void fillTableRow( Q3Table * table, unsigned int i, Transaction transaction );
    void clearIncludeList();
    void copyAllToInclude();
    void removeSelectedFromInclude();
    void reject();
    void printReport();
    void setComments( MarketReport & marketReport );

protected:

protected slots:

private:
    vector<Transaction> transactionList;
    vector<Transaction> includeList;
    TransactionDAO dao;
    SetupDAO setup;

    void init();

    Ui::MarketReportDialog *ui;
};

#endif // MARKETREPORTDIALOG_H
