/********************************************************************************
** Form generated from reading UI file 'transactionbrowser.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSACTIONBROWSER_H
#define UI_TRANSACTIONBROWSER_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Table>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include "dao/salemanager.h"
#include "dao/setupdao.h"
#include "dao/transactiondao.h"
#include "types/transaction.h"

QT_BEGIN_NAMESPACE

class Ui_TransactionBrowser
{
public:
    QLabel *textLabel1;
    QLabel *textLabel1_2;
    QLineEdit *searchEdit;
    QPushButton *searchButton;
    QPushButton *printTransactionButton;
    QPushButton *buttRefresh;
    Q3Table *transactionTable;
    QComboBox *indexCombo;
    QPushButton *buttNew;
    QPushButton *buttDelete;
    QPushButton *buttDone;

    void setupUi(QDialog *TransactionBrowser)
    {
        if (TransactionBrowser->objectName().isEmpty())
            TransactionBrowser->setObjectName(QString::fromUtf8("TransactionBrowser"));
        TransactionBrowser->setWindowModality(Qt::ApplicationModal);
        TransactionBrowser->resize(1000, 432);
        TransactionBrowser->setMaximumSize(QSize(1000, 760));
        QFont font;
        font.setPointSize(13);
        TransactionBrowser->setFont(font);
        textLabel1 = new QLabel(TransactionBrowser);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(10, 10, 848, 30));
        QFont font1;
        font1.setPointSize(12);
        textLabel1->setFont(font1);
        textLabel1->setWordWrap(false);
        textLabel1_2 = new QLabel(TransactionBrowser);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(10, 40, 110, 30));
        textLabel1_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_2->setWordWrap(false);
        searchEdit = new QLineEdit(TransactionBrowser);
        searchEdit->setObjectName(QString::fromUtf8("searchEdit"));
        searchEdit->setGeometry(QRect(310, 40, 110, 31));
        searchButton = new QPushButton(TransactionBrowser);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));
        searchButton->setGeometry(QRect(430, 40, 100, 30));
        searchButton->setAutoDefault(false);
        printTransactionButton = new QPushButton(TransactionBrowser);
        printTransactionButton->setObjectName(QString::fromUtf8("printTransactionButton"));
        printTransactionButton->setGeometry(QRect(510, 390, 110, 30));
        printTransactionButton->setAutoDefault(false);
        buttRefresh = new QPushButton(TransactionBrowser);
        buttRefresh->setObjectName(QString::fromUtf8("buttRefresh"));
        buttRefresh->setGeometry(QRect(390, 390, 110, 30));
        buttRefresh->setAutoDefault(false);
        transactionTable = new Q3Table(TransactionBrowser);
        transactionTable->setObjectName(QString::fromUtf8("transactionTable"));
        transactionTable->setGeometry(QRect(10, 100, 980, 280));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(transactionTable->sizePolicy().hasHeightForWidth());
        transactionTable->setSizePolicy(sizePolicy);
        transactionTable->setResizePolicy(Q3ScrollView::Manual);
        transactionTable->setVScrollBarMode(Q3ScrollView::AlwaysOn);
        transactionTable->setNumRows(0);
        transactionTable->setNumCols(10);
        transactionTable->setSorting(false);
        transactionTable->setSelectionMode(Q3Table::SingleRow);
        transactionTable->setFocusStyle(Q3Table::FollowStyle);
        indexCombo = new QComboBox(TransactionBrowser);
        indexCombo->setObjectName(QString::fromUtf8("indexCombo"));
        indexCombo->setGeometry(QRect(130, 40, 150, 30));
        buttNew = new QPushButton(TransactionBrowser);
        buttNew->setObjectName(QString::fromUtf8("buttNew"));
        buttNew->setGeometry(QRect(630, 390, 110, 30));
        buttNew->setAutoDefault(false);
        buttDelete = new QPushButton(TransactionBrowser);
        buttDelete->setObjectName(QString::fromUtf8("buttDelete"));
        buttDelete->setGeometry(QRect(750, 390, 110, 30));
        buttDelete->setAutoDefault(false);
        buttDone = new QPushButton(TransactionBrowser);
        buttDone->setObjectName(QString::fromUtf8("buttDone"));
        buttDone->setGeometry(QRect(870, 390, 110, 30));
        buttDone->setAutoDefault(false);
        buttDone->setDefault(false);
        QWidget::setTabOrder(transactionTable, buttDone);
        QWidget::setTabOrder(buttDone, buttDelete);
        QWidget::setTabOrder(buttDelete, buttNew);
        QWidget::setTabOrder(buttNew, printTransactionButton);
        QWidget::setTabOrder(printTransactionButton, buttRefresh);

        retranslateUi(TransactionBrowser);

        QMetaObject::connectSlotsByName(TransactionBrowser);
    } // setupUi

    void retranslateUi(QDialog *TransactionBrowser)
    {
        TransactionBrowser->setWindowTitle(QApplication::translate("TransactionBrowser", "Transaction Browser", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("TransactionBrowser", "Double click a transaction to edit it:", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("TransactionBrowser", "Index By:", 0, QApplication::UnicodeUTF8));
        searchButton->setText(QApplication::translate("TransactionBrowser", "Search", 0, QApplication::UnicodeUTF8));
        printTransactionButton->setText(QApplication::translate("TransactionBrowser", "Print List", 0, QApplication::UnicodeUTF8));
        buttRefresh->setText(QApplication::translate("TransactionBrowser", "Refresh", 0, QApplication::UnicodeUTF8));
        transactionTable->horizontalHeader()->setLabel(0, QApplication::translate("TransactionBrowser", "Number", 0, QApplication::UnicodeUTF8));
        transactionTable->horizontalHeader()->setLabel(1, QApplication::translate("TransactionBrowser", "Seller #", 0, QApplication::UnicodeUTF8));
        transactionTable->horizontalHeader()->setLabel(2, QApplication::translate("TransactionBrowser", "Buyer #", 0, QApplication::UnicodeUTF8));
        transactionTable->horizontalHeader()->setLabel(3, QApplication::translate("TransactionBrowser", "Head", 0, QApplication::UnicodeUTF8));
        transactionTable->horizontalHeader()->setLabel(4, QApplication::translate("TransactionBrowser", "Tot Wt.", 0, QApplication::UnicodeUTF8));
        transactionTable->horizontalHeader()->setLabel(5, QApplication::translate("TransactionBrowser", "Avg Wt.", 0, QApplication::UnicodeUTF8));
        transactionTable->horizontalHeader()->setLabel(6, QApplication::translate("TransactionBrowser", "Description", 0, QApplication::UnicodeUTF8));
        transactionTable->horizontalHeader()->setLabel(7, QApplication::translate("TransactionBrowser", "Bid Price", 0, QApplication::UnicodeUTF8));
        transactionTable->horizontalHeader()->setLabel(8, QApplication::translate("TransactionBrowser", "Amount", 0, QApplication::UnicodeUTF8));
        transactionTable->horizontalHeader()->setLabel(9, QApplication::translate("TransactionBrowser", "Pen", 0, QApplication::UnicodeUTF8));
        indexCombo->clear();
        indexCombo->insertItems(0, QStringList()
         << QApplication::translate("TransactionBrowser", "Trans#", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransactionBrowser", "Seller#", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransactionBrowser", "Buyer#", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransactionBrowser", "Head", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransactionBrowser", "Total Weight", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransactionBrowser", "Average Weight", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransactionBrowser", "Description", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransactionBrowser", "Price", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransactionBrowser", "Amount", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransactionBrowser", "Pen", 0, QApplication::UnicodeUTF8)
        );
        buttNew->setText(QApplication::translate("TransactionBrowser", "New", 0, QApplication::UnicodeUTF8));
        buttDelete->setText(QApplication::translate("TransactionBrowser", "Delete", 0, QApplication::UnicodeUTF8));
        buttDone->setText(QApplication::translate("TransactionBrowser", "Done", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TransactionBrowser: public Ui_TransactionBrowser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSACTIONBROWSER_H
