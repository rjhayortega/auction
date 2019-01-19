/********************************************************************************
** Form generated from reading UI file 'marketreportdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MARKETREPORTDIALOG_H
#define UI_MARKETREPORTDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Table>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <algorithm>
#include "dao/transactiondao.h"
#include "reports/marketreport.h"

QT_BEGIN_NAMESPACE

class Ui_MarketReportDialog
{
public:
    QLineEdit *minHead;
    QLineEdit *minPrice;
    QLabel *textLabel1_2;
    QLabel *textLabel1;
    QCheckBox *suppressSellerBox;
    QPushButton *exitButton;
    QPushButton *printButton;
    QLabel *textLabel1_3;
    QCheckBox *checkBoxRound5;
    QComboBox *colorCombo;
    Q3GroupBox *groupBox1;
    QLabel *textLabel2_3;
    QLineEdit *idExcludeFilter;
    QLabel *textLabel2_2_2;
    QPushButton *excludePushButton;
    QPushButton *excludeAllPushButton;
    Q3Table *includeTable;
    QPushButton *applyFiltersButton;
    Q3GroupBox *groupBox2;
    QLineEdit *idIncludeFilter;
    QLabel *textLabel2;
    QLabel *textLabel2_2;
    QPushButton *includePushButton;
    QPushButton *includeAllPushButton;
    Q3Table *transactionTable;
    QLabel *textLabel1_4;
    QComboBox *indexComboBox;

    void setupUi(QDialog *MarketReportDialog)
    {
        if (MarketReportDialog->objectName().isEmpty())
            MarketReportDialog->setObjectName(QString::fromUtf8("MarketReportDialog"));
        MarketReportDialog->setWindowModality(Qt::ApplicationModal);
        MarketReportDialog->resize(826, 653);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MarketReportDialog->sizePolicy().hasHeightForWidth());
        MarketReportDialog->setSizePolicy(sizePolicy);
        MarketReportDialog->setMinimumSize(QSize(0, 0));
        MarketReportDialog->setMaximumSize(QSize(32767, 32767));
        MarketReportDialog->setBaseSize(QSize(0, 0));
        QFont font;
        font.setPointSize(13);
        MarketReportDialog->setFont(font);
        minHead = new QLineEdit(MarketReportDialog);
        minHead->setObjectName(QString::fromUtf8("minHead"));
        minHead->setGeometry(QRect(10, 40, 100, 30));
        minPrice = new QLineEdit(MarketReportDialog);
        minPrice->setObjectName(QString::fromUtf8("minPrice"));
        minPrice->setGeometry(QRect(140, 40, 100, 30));
        textLabel1_2 = new QLabel(MarketReportDialog);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(140, 10, 110, 30));
        textLabel1_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        textLabel1_2->setWordWrap(true);
        textLabel1 = new QLabel(MarketReportDialog);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(10, 10, 120, 30));
        textLabel1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        textLabel1->setWordWrap(true);
        suppressSellerBox = new QCheckBox(MarketReportDialog);
        suppressSellerBox->setObjectName(QString::fromUtf8("suppressSellerBox"));
        suppressSellerBox->setGeometry(QRect(270, 610, 290, 30));
        exitButton = new QPushButton(MarketReportDialog);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(580, 610, 100, 32));
        exitButton->setAutoDefault(false);
        printButton = new QPushButton(MarketReportDialog);
        printButton->setObjectName(QString::fromUtf8("printButton"));
        printButton->setGeometry(QRect(710, 610, 100, 32));
        printButton->setMaximumSize(QSize(1024, 760));
        printButton->setAutoDefault(false);
        textLabel1_3 = new QLabel(MarketReportDialog);
        textLabel1_3->setObjectName(QString::fromUtf8("textLabel1_3"));
        textLabel1_3->setGeometry(QRect(260, 40, 111, 31));
        textLabel1_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_3->setWordWrap(false);
        checkBoxRound5 = new QCheckBox(MarketReportDialog);
        checkBoxRound5->setObjectName(QString::fromUtf8("checkBoxRound5"));
        checkBoxRound5->setGeometry(QRect(280, 10, 220, 30));
        colorCombo = new QComboBox(MarketReportDialog);
        colorCombo->setObjectName(QString::fromUtf8("colorCombo"));
        colorCombo->setGeometry(QRect(390, 40, 111, 30));
        groupBox1 = new Q3GroupBox(MarketReportDialog);
        groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
        groupBox1->setGeometry(QRect(10, 330, 800, 250));
        textLabel2_3 = new QLabel(groupBox1);
        textLabel2_3->setObjectName(QString::fromUtf8("textLabel2_3"));
        textLabel2_3->setGeometry(QRect(200, 210, 260, 30));
        textLabel2_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_3->setWordWrap(false);
        idExcludeFilter = new QLineEdit(groupBox1);
        idExcludeFilter->setObjectName(QString::fromUtf8("idExcludeFilter"));
        idExcludeFilter->setGeometry(QRect(470, 210, 130, 31));
        textLabel2_2_2 = new QLabel(groupBox1);
        textLabel2_2_2->setObjectName(QString::fromUtf8("textLabel2_2_2"));
        textLabel2_2_2->setGeometry(QRect(610, 210, 180, 30));
        textLabel2_2_2->setWordWrap(false);
        excludePushButton = new QPushButton(groupBox1);
        excludePushButton->setObjectName(QString::fromUtf8("excludePushButton"));
        excludePushButton->setGeometry(QRect(10, 210, 100, 30));
        excludePushButton->setAutoDefault(false);
        excludeAllPushButton = new QPushButton(groupBox1);
        excludeAllPushButton->setObjectName(QString::fromUtf8("excludeAllPushButton"));
        excludeAllPushButton->setGeometry(QRect(120, 210, 100, 32));
        excludeAllPushButton->setAutoDefault(false);
        includeTable = new Q3Table(groupBox1);
        includeTable->setObjectName(QString::fromUtf8("includeTable"));
        includeTable->setGeometry(QRect(10, 20, 780, 180));
        includeTable->setNumRows(0);
        includeTable->setNumCols(9);
        includeTable->setShowGrid(false);
        includeTable->setRowMovingEnabled(false);
        includeTable->setSorting(false);
        includeTable->setSelectionMode(Q3Table::MultiRow);
        applyFiltersButton = new QPushButton(MarketReportDialog);
        applyFiltersButton->setObjectName(QString::fromUtf8("applyFiltersButton"));
        applyFiltersButton->setGeometry(QRect(550, 10, 240, 30));
        applyFiltersButton->setAutoDefault(false);
        groupBox2 = new Q3GroupBox(MarketReportDialog);
        groupBox2->setObjectName(QString::fromUtf8("groupBox2"));
        groupBox2->setGeometry(QRect(10, 90, 800, 240));
        idIncludeFilter = new QLineEdit(groupBox2);
        idIncludeFilter->setObjectName(QString::fromUtf8("idIncludeFilter"));
        idIncludeFilter->setGeometry(QRect(470, 200, 130, 30));
        textLabel2 = new QLabel(groupBox2);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setGeometry(QRect(210, 200, 250, 30));
        textLabel2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2->setWordWrap(false);
        textLabel2_2 = new QLabel(groupBox2);
        textLabel2_2->setObjectName(QString::fromUtf8("textLabel2_2"));
        textLabel2_2->setGeometry(QRect(610, 200, 180, 30));
        textLabel2_2->setWordWrap(false);
        includePushButton = new QPushButton(groupBox2);
        includePushButton->setObjectName(QString::fromUtf8("includePushButton"));
        includePushButton->setGeometry(QRect(10, 200, 100, 32));
        includePushButton->setAutoDefault(false);
        includeAllPushButton = new QPushButton(groupBox2);
        includeAllPushButton->setObjectName(QString::fromUtf8("includeAllPushButton"));
        includeAllPushButton->setGeometry(QRect(120, 200, 100, 32));
        includeAllPushButton->setAutoDefault(false);
        transactionTable = new Q3Table(groupBox2);
        transactionTable->setObjectName(QString::fromUtf8("transactionTable"));
        transactionTable->setGeometry(QRect(10, 20, 780, 170));
        transactionTable->setNumRows(0);
        transactionTable->setNumCols(9);
        transactionTable->setShowGrid(false);
        transactionTable->setRowMovingEnabled(false);
        transactionTable->setSorting(false);
        transactionTable->setSelectionMode(Q3Table::MultiRow);
        transactionTable->setFocusStyle(Q3Table::FollowStyle);
        textLabel1_4 = new QLabel(MarketReportDialog);
        textLabel1_4->setObjectName(QString::fromUtf8("textLabel1_4"));
        textLabel1_4->setGeometry(QRect(520, 50, 110, 31));
        textLabel1_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_4->setWordWrap(false);
        indexComboBox = new QComboBox(MarketReportDialog);
        indexComboBox->setObjectName(QString::fromUtf8("indexComboBox"));
        indexComboBox->setGeometry(QRect(640, 50, 170, 31));

        retranslateUi(MarketReportDialog);

        QMetaObject::connectSlotsByName(MarketReportDialog);
    } // setupUi

    void retranslateUi(QDialog *MarketReportDialog)
    {
        MarketReportDialog->setWindowTitle(QApplication::translate("MarketReportDialog", "Generate Market Report", 0, QApplication::UnicodeUTF8));
        minHead->setText(QApplication::translate("MarketReportDialog", "0", 0, QApplication::UnicodeUTF8));
        minPrice->setText(QApplication::translate("MarketReportDialog", "0", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("MarketReportDialog", "Min. Price", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("MarketReportDialog", "Min. Head", 0, QApplication::UnicodeUTF8));
        suppressSellerBox->setText(QApplication::translate("MarketReportDialog", "Suppress Seller Data", 0, QApplication::UnicodeUTF8));
        exitButton->setText(QApplication::translate("MarketReportDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        printButton->setText(QApplication::translate("MarketReportDialog", "Print", 0, QApplication::UnicodeUTF8));
        textLabel1_3->setText(QApplication::translate("MarketReportDialog", "Color:", 0, QApplication::UnicodeUTF8));
        checkBoxRound5->setText(QApplication::translate("MarketReportDialog", "Round to $0.05?", 0, QApplication::UnicodeUTF8));
        colorCombo->clear();
        colorCombo->insertItems(0, QStringList()
         << QApplication::translate("MarketReportDialog", "0-69", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MarketReportDialog", "70-79", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MarketReportDialog", "80-89", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MarketReportDialog", "90-99", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MarketReportDialog", "All", 0, QApplication::UnicodeUTF8)
        );
        groupBox1->setTitle(QApplication::translate("MarketReportDialog", "Included List", 0, QApplication::UnicodeUTF8));
        textLabel2_3->setText(QApplication::translate("MarketReportDialog", "Enter ID To Exclude:", 0, QApplication::UnicodeUTF8));
        textLabel2_2_2->setText(QApplication::translate("MarketReportDialog", "Then Press Enter", 0, QApplication::UnicodeUTF8));
        excludePushButton->setText(QApplication::translate("MarketReportDialog", "Selected", 0, QApplication::UnicodeUTF8));
        excludeAllPushButton->setText(QApplication::translate("MarketReportDialog", "All", 0, QApplication::UnicodeUTF8));
        includeTable->horizontalHeader()->setLabel(0, QApplication::translate("MarketReportDialog", "Name", 0, QApplication::UnicodeUTF8));
        includeTable->horizontalHeader()->setLabel(1, QApplication::translate("MarketReportDialog", "Seller", 0, QApplication::UnicodeUTF8));
        includeTable->horizontalHeader()->setLabel(2, QApplication::translate("MarketReportDialog", "Head", 0, QApplication::UnicodeUTF8));
        includeTable->horizontalHeader()->setLabel(3, QApplication::translate("MarketReportDialog", "Description", 0, QApplication::UnicodeUTF8));
        includeTable->horizontalHeader()->setLabel(4, QApplication::translate("MarketReportDialog", "Avg. Weight", 0, QApplication::UnicodeUTF8));
        includeTable->horizontalHeader()->setLabel(5, QApplication::translate("MarketReportDialog", "Price/CWT", 0, QApplication::UnicodeUTF8));
        includeTable->horizontalHeader()->setLabel(6, QApplication::translate("MarketReportDialog", "Price/Head", 0, QApplication::UnicodeUTF8));
        includeTable->horizontalHeader()->setLabel(7, QApplication::translate("MarketReportDialog", "Amount", 0, QApplication::UnicodeUTF8));
        includeTable->horizontalHeader()->setLabel(8, QApplication::translate("MarketReportDialog", "ID", 0, QApplication::UnicodeUTF8));
        applyFiltersButton->setText(QApplication::translate("MarketReportDialog", "Reload List With Filters", 0, QApplication::UnicodeUTF8));
        groupBox2->setTitle(QApplication::translate("MarketReportDialog", "Transaction List", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("MarketReportDialog", "Enter ID To Include:", 0, QApplication::UnicodeUTF8));
        textLabel2_2->setText(QApplication::translate("MarketReportDialog", "Then Press Enter", 0, QApplication::UnicodeUTF8));
        includePushButton->setText(QApplication::translate("MarketReportDialog", "Selected", 0, QApplication::UnicodeUTF8));
        includeAllPushButton->setText(QApplication::translate("MarketReportDialog", "All", 0, QApplication::UnicodeUTF8));
        transactionTable->horizontalHeader()->setLabel(0, QApplication::translate("MarketReportDialog", "Name", 0, QApplication::UnicodeUTF8));
        transactionTable->horizontalHeader()->setLabel(1, QApplication::translate("MarketReportDialog", "Seller", 0, QApplication::UnicodeUTF8));
        transactionTable->horizontalHeader()->setLabel(2, QApplication::translate("MarketReportDialog", "Head", 0, QApplication::UnicodeUTF8));
        transactionTable->horizontalHeader()->setLabel(3, QApplication::translate("MarketReportDialog", "Description", 0, QApplication::UnicodeUTF8));
        transactionTable->horizontalHeader()->setLabel(4, QApplication::translate("MarketReportDialog", "Avg. Weight", 0, QApplication::UnicodeUTF8));
        transactionTable->horizontalHeader()->setLabel(5, QApplication::translate("MarketReportDialog", "Price/CWT", 0, QApplication::UnicodeUTF8));
        transactionTable->horizontalHeader()->setLabel(6, QApplication::translate("MarketReportDialog", "Price/Head", 0, QApplication::UnicodeUTF8));
        transactionTable->horizontalHeader()->setLabel(7, QApplication::translate("MarketReportDialog", "Amount", 0, QApplication::UnicodeUTF8));
        transactionTable->horizontalHeader()->setLabel(8, QApplication::translate("MarketReportDialog", "ID", 0, QApplication::UnicodeUTF8));
        textLabel1_4->setText(QApplication::translate("MarketReportDialog", "Index By:", 0, QApplication::UnicodeUTF8));
        indexComboBox->clear();
        indexComboBox->insertItems(0, QStringList()
         << QApplication::translate("MarketReportDialog", "Name", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MarketReportDialog", "Seller", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MarketReportDialog", "Head", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MarketReportDialog", "Description", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MarketReportDialog", "Avg. Weight", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MarketReportDialog", "Price/CWT", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MarketReportDialog", "Price/Head", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MarketReportDialog", "Amount", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MarketReportDialog", "Id", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class MarketReportDialog: public Ui_MarketReportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MARKETREPORTDIALOG_H
