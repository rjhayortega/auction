//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "transactionbrowser.h"
#include "ui_transactionbrowser.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <Q3Table>
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

#include <QKeyEvent>


TransactionBrowser::TransactionBrowser( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::TransactionBrowser)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->buttDone, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( ui->transactionTable, SIGNAL( doubleClicked(int,int,int,const QPoint&) ), this, SLOT( editTransaction(int,int,int,const QPoint&) ) );
    connect( ui->buttNew, SIGNAL( clicked() ), this, SLOT( newTransaction() ) );
    connect( ui->buttDelete, SIGNAL( clicked() ), this, SLOT( deleteCurrentTransaction() ) );
    connect( ui->buttRefresh, SIGNAL( clicked() ), this, SLOT( populateTransactionTable() ) );
    connect( ui->printTransactionButton, SIGNAL( clicked() ), this, SLOT( printTransactionList() ) );
    connect( ui->indexCombo, SIGNAL( activated(const QString&) ), this, SLOT( showTransactionTable() ) );
    connect( ui->searchEdit, SIGNAL( returnPressed() ), this, SLOT( searchListByIndex() ) );
    connect( ui->searchButton, SIGNAL( clicked() ), this, SLOT( searchListByIndex() ) );

    // tab order
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
TransactionBrowser::~TransactionBrowser()
{
    delete ui;
}

#include "transactiondialog.h"
#include "reports/transactionlist.h"
#include "previewdialog.h"
#include <qmessagebox.h>

///////////////////////////////////////////////////////////////////////////////
//
// name:    init()
//
// purpose: constructor like function
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void TransactionBrowser::init()
{
    populateTransactionTable();
    ui->transactionTable->setLeftMargin(0);

    if(!sale.currentSaleOpen())
    {
        ui->buttNew->setEnabled(false);
        ui->buttDelete->setEnabled(false);
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    newTransaction()
//
// purpose: opens a blank transaction edit dialog
//
// calling params:
//
// return params:
//
// Notes: does not refresh the entire table upon return of the trans edit
//        dialog, instead inserts the new transaction into the table
//        upon acceptance of the trans edit dialog
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void TransactionBrowser::newTransaction()
{
    TransactionDialog transEdit(this);
    if(transEdit.exec() == QDialog::Accepted)
    {
//    unsigned int newRow = transactionTable->numRows();
        Transaction newTrans = transEdit.getTransaction();
        transactionList.push_back(newTrans);
//    transactionTable->insertRows(newRow, 1);
//    updateTableRow(newRow, newTrans);
//   transactionTable->setCurrentCell(newRow, 0);
        showTransactionTable();
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    deleteCurrentTransaction()
//
// purpose: removes the current transaction in the list from the database
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void TransactionBrowser::deleteCurrentTransaction()
{
    if(ui->transactionTable->numRows() > 0)
    {
        unsigned int currentRow = ui->transactionTable->currentRow();

        if(0 <= currentRow && currentRow < transactionList.size())
        {
            long transNo = ui->transactionTable->text(currentRow, 0).replace("M", "").toLong();

            int option = QMessageBox::warning(this, "Warning",
                                              "Do you want to mark the transaction as 'Invalid'\n"
                                              "or Permanantly Remove it", "Mark Invalid", "Remove");

            if(option  == 0)
            {
                transactionList[currentRow].setMode(Transaction::Invalid);
                TransactionDAO().saveTransaction(transactionList[currentRow]);
            }
            else if(option == 1)
            {
                TransactionDAO().removeTransaction(transNo);
                //transactionTable->removeRow(currentRow);
                transactionList.erase(transactionList.begin() + currentRow);
                showTransactionTable();
            }
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    editTransaction(int, int, int, const QPoint&)
//
// purpose: opens the transaction edit dialog with the transaction represented
//          in the table at the row 'row'
//
// calling params: int row - the row clicked in the table
//                     col -  '  column clicked in the table
//                     butt - the mouse button used to click the table
//                 QPoint mouse_pos - the position of the  mouse on the table
//                                    when clicked
//
// return params:
//
// Notes: The only paramater actually used is the row paramater, the rest
//        are there to allow the clicked signal to be used to connect to
//        this slot
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void TransactionBrowser::editTransaction( int row, int col, int butt, const QPoint & mouse_pos )
{
    if(0 > row || row >= ui->transactionTable->numRows())
    {
        return;
    }

    TransactionDialog transEdit(this);
    long transNo = ui->transactionTable->text(row, 0).replace("M", "").toLong();
    transEdit.loadTransaction(transNo);
    if(transEdit.exec() == QDialog::Accepted)
    {
        Transaction transBuffer = TransactionDAO().getTransactionById(transNo);
        updateTableRow(row, transBuffer);
        *(transactionList.begin() + row) = transBuffer;
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    printTransactions()
//
// purpose: prints the transaction list
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:  anything
//
///////////////////////////////////////////////////////////////////////////////

void TransactionBrowser::printTransactions()
{

}


///////////////////////////////////////////////////////////////////////////////
//
// name:    populateTransactionTable()
//
// purpose: fills the transaction table with values from the database
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void TransactionBrowser::populateTransactionTable()
{
    TransactionDAO transDao;
    transDao.startBatchMode(false, false, false);
    AnimalCodeDAO::startBatchMode();
    transactionList = transDao.getTransactionList();
    AnimalCodeDAO::endBatchMode();
    transDao.endBatchMode();

    showTransactionTable();
}

void TransactionBrowser::showTransactionTable()
{

    sortTransactionsByIndex();

    vector<Transaction>::iterator current;

    ui->transactionTable->setNumRows(transactionList.size());
    int row = 0;

    for(current = transactionList.begin(); current != transactionList.end(); current++)
    {
        updateTableRow (row, *current);
        row++;
    }
}

void TransactionBrowser::sortTransactionsByIndex()
{
    string indexStr = ui->indexCombo->currentText().toStdString();

    if(indexStr == "Trans#")
        std::sort(transactionList.begin(), transactionList.end(), Transaction::compareIdsLT);
    else if(indexStr == "Seller#")
        std::sort(transactionList.begin(), transactionList.end(), Transaction::compareSellerIdsLT);
    else if(indexStr == "Buyer#")
        std::sort(transactionList.begin(), transactionList.end(), Transaction::compareBuyerIdsLT);
    else if(indexStr == "Head")
        std::sort(transactionList.begin(), transactionList.end(), Transaction::compareHeadLT);
    else if(indexStr == "Total Weight")
        std::sort(transactionList.begin(), transactionList.end(), Transaction::compareWeightLT);
    else if(indexStr == "Average Weight")
        std::sort(transactionList.begin(), transactionList.end(), Transaction::compareAverageWeightLT);
    else if(indexStr == "Description")
        std::sort(transactionList.begin(), transactionList.end(), Transaction::compareDescriptionLT);
    else if(indexStr == "Price")
        std::sort(transactionList.begin(), transactionList.end(), Transaction::comparePriceLT);
    else if(indexStr == "Amount")
        std::sort(transactionList.begin(), transactionList.end(), Transaction::compareAmountLT);
    else if(indexStr == "Pen")
    {
        std::sort(transactionList.begin(), transactionList.end(), Transaction::compareBuyerPenLT);
    }
    else
        cerr << "Unknown index type: " << indexStr << endl;
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    updateTableRow(int, Transaction)
//
// purpose: sets the table data in the table row 'row' with data from the
//          Transaction 'transaction'
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void TransactionBrowser::updateTableRow(int row, Transaction transaction)
{
    string amountString = QString::number(transaction.amount(), 'f', 2).toStdString();

    if(transaction.getMode() == Transaction::NoSaleHead || transaction.getMode() == Transaction::NoSaleCWT)
    {
        amountString = "N/S";
    }

    ui->transactionTable->setText(row, 0, QString::number(transaction.getId()) + (transaction.isManual() ? "M" : ""));
//  transactionTable->setText(row, 1, transaction.getSeller().getName().getLast());
    ui->transactionTable->setText(row, 1, QString::fromStdString(transaction.getSeller().getNumber()));
    ui->transactionTable->setText(row, 2, QString::fromStdString(transaction.getBuyer().getNumber()));
    ui->transactionTable->setText(row, 3, QString::number(transaction.getHead(false, false, true)));
    ui->transactionTable->setText(row, 4, QString::number(transaction.getWeight()));
    ui->transactionTable->setText(row, 5, QString::number(transaction.getAverageWeight()));
    ui->transactionTable->setText(row, 6, QString::fromStdString(transaction.getAnimalCode().getDescrip()));
    ui->transactionTable->setText(row, 7, QString::number(transaction.getPrice(), 'f', 2));
    ui->transactionTable->setText(row, 8, QString::fromStdString(amountString));
    ui->transactionTable->setText(row, 9, QString::fromStdString(transaction.getBuyerPen()));
    ui->transactionTable->setRowReadOnly(row, true);
}

void TransactionBrowser::printTransactionList()
{
    TransactionList report(transactionList);
    report.setHeader(setup.reportHeader("Transaction List"));

    PreviewDialog prev;
    prev.setText(QString::fromStdString(report.text()));
    prev.setReport(&report);
    prev.setShowPrint(true);
    prev.exec();
}

void TransactionBrowser::searchListByIndex()
{
    string indexStr = ui->indexCombo->currentText().toStdString();
    int searchColumn = -1;

    if(indexStr == "Trans#")
        searchColumn = 0;
    else if(indexStr == "Seller#")
        searchColumn = 1;
    else if(indexStr == "Buyer#")
        searchColumn = 2;
    else if(indexStr == "Head")
        searchColumn = 3;
    else if(indexStr == "Total Weight")
        searchColumn = 4;
    else if(indexStr == "Average Weight")
        searchColumn = 5;
    else if(indexStr == "Description")
        searchColumn = 6;
    else if(indexStr == "Price")
        searchColumn = 7;
    else if(indexStr == "Amount")
        searchColumn = 8;
    else if(indexStr == "Pen")
        searchColumn = 9;
    else
        cerr << "Unknown index type: " << indexStr << endl;

    QString pattern = ui->searchEdit->text();
    bool numericalKey;
    double key = pattern.toDouble(&numericalKey);

    for(int i = 0; i < ui->transactionTable->numRows() && 0 <= searchColumn; i++)
    {

        if(numericalKey)
        {
            if(atof(ui->transactionTable->text(i, searchColumn).ascii()) >= key)
            {
                ui->transactionTable->selectRow(i);
                break;
            }
        }
        else
        {
            if(ui->transactionTable->text(i, searchColumn).lower() >= pattern.lower())
            {
                ui->transactionTable->selectRow(i);
                break;
            }
        }
    }
}

void TransactionBrowser::keyPressEvent(QKeyEvent* event)
{
    int currentIndex = ui->transactionTable->currentRow();

    bool arrowPress = false;

    switch(event->key())
    {
    case Qt::Key_Up:
        currentIndex--;
        arrowPress = true;
        break;

    case Qt::Key_Down:
        currentIndex++;
        arrowPress = true;
        break;
    }

    if(currentIndex < 0)
    {
        currentIndex = 0;
    }

    if(currentIndex > ui->transactionTable->numRows() - 1)
    {
        currentIndex = ui->transactionTable->numRows() - 1;
    }

    if(arrowPress && 0 <= currentIndex && currentIndex < ui->transactionTable->numRows())
    {
        ui->transactionTable->selectRow(currentIndex);
    }

    QDialog::keyPressEvent(event);
}
