/********************************************************************************
** Form generated from reading UI file 'tablerepairdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLEREPAIRDIALOG_H
#define UI_TABLEREPAIRDIALOG_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_TableRepairDialog
{
public:
    Q3ButtonGroup *buttonGroup2;
    QPushButton *backtagButton;
    QPushButton *brandButton;
    QPushButton *dailyBuyerButton;
    QPushButton *dailySellerButton;
    QPushButton *chargeButton;
    QPushButton *checkButton;
    QPushButton *commissionButton;
    QPushButton *codeButton;
    QPushButton *permButton;
    QPushButton *printerButton;
    QPushButton *displayButton;
    QPushButton *buyerInvoiceButton;
    QPushButton *sellerInvoiceButton;
    QPushButton *truckingButton;
    QPushButton *zipCodeButton;
    QPushButton *setupButton;
    QPushButton *transButton;
    QPushButton *allButton;

    void setupUi(QDialog *TableRepairDialog)
    {
        if (TableRepairDialog->objectName().isEmpty())
            TableRepairDialog->setObjectName(QString::fromUtf8("TableRepairDialog"));
        TableRepairDialog->setWindowModality(Qt::ApplicationModal);
        TableRepairDialog->resize(385, 437);
        QFont font;
        font.setPointSize(13);
        TableRepairDialog->setFont(font);
        buttonGroup2 = new Q3ButtonGroup(TableRepairDialog);
        buttonGroup2->setObjectName(QString::fromUtf8("buttonGroup2"));
        buttonGroup2->setGeometry(QRect(10, 20, 360, 410));
        backtagButton = new QPushButton(buttonGroup2);
        backtagButton->setObjectName(QString::fromUtf8("backtagButton"));
        backtagButton->setGeometry(QRect(20, 30, 141, 31));
        brandButton = new QPushButton(buttonGroup2);
        brandButton->setObjectName(QString::fromUtf8("brandButton"));
        brandButton->setGeometry(QRect(20, 70, 141, 31));
        dailyBuyerButton = new QPushButton(buttonGroup2);
        dailyBuyerButton->setObjectName(QString::fromUtf8("dailyBuyerButton"));
        dailyBuyerButton->setGeometry(QRect(20, 110, 141, 31));
        dailySellerButton = new QPushButton(buttonGroup2);
        dailySellerButton->setObjectName(QString::fromUtf8("dailySellerButton"));
        dailySellerButton->setGeometry(QRect(20, 150, 141, 31));
        chargeButton = new QPushButton(buttonGroup2);
        chargeButton->setObjectName(QString::fromUtf8("chargeButton"));
        chargeButton->setGeometry(QRect(20, 190, 141, 31));
        checkButton = new QPushButton(buttonGroup2);
        checkButton->setObjectName(QString::fromUtf8("checkButton"));
        checkButton->setGeometry(QRect(20, 230, 141, 31));
        commissionButton = new QPushButton(buttonGroup2);
        commissionButton->setObjectName(QString::fromUtf8("commissionButton"));
        commissionButton->setGeometry(QRect(20, 270, 141, 31));
        codeButton = new QPushButton(buttonGroup2);
        codeButton->setObjectName(QString::fromUtf8("codeButton"));
        codeButton->setGeometry(QRect(20, 310, 141, 31));
        permButton = new QPushButton(buttonGroup2);
        permButton->setObjectName(QString::fromUtf8("permButton"));
        permButton->setGeometry(QRect(20, 350, 141, 31));
        printerButton = new QPushButton(buttonGroup2);
        printerButton->setObjectName(QString::fromUtf8("printerButton"));
        printerButton->setGeometry(QRect(180, 30, 141, 31));
        displayButton = new QPushButton(buttonGroup2);
        displayButton->setObjectName(QString::fromUtf8("displayButton"));
        displayButton->setGeometry(QRect(180, 70, 141, 31));
        buyerInvoiceButton = new QPushButton(buttonGroup2);
        buyerInvoiceButton->setObjectName(QString::fromUtf8("buyerInvoiceButton"));
        buyerInvoiceButton->setGeometry(QRect(180, 110, 141, 31));
        sellerInvoiceButton = new QPushButton(buttonGroup2);
        sellerInvoiceButton->setObjectName(QString::fromUtf8("sellerInvoiceButton"));
        sellerInvoiceButton->setGeometry(QRect(180, 150, 141, 31));
        truckingButton = new QPushButton(buttonGroup2);
        truckingButton->setObjectName(QString::fromUtf8("truckingButton"));
        truckingButton->setGeometry(QRect(180, 270, 141, 31));
        zipCodeButton = new QPushButton(buttonGroup2);
        zipCodeButton->setObjectName(QString::fromUtf8("zipCodeButton"));
        zipCodeButton->setGeometry(QRect(180, 310, 141, 31));
        setupButton = new QPushButton(buttonGroup2);
        setupButton->setObjectName(QString::fromUtf8("setupButton"));
        setupButton->setGeometry(QRect(180, 190, 141, 31));
        transButton = new QPushButton(buttonGroup2);
        transButton->setObjectName(QString::fromUtf8("transButton"));
        transButton->setGeometry(QRect(180, 230, 141, 31));
        allButton = new QPushButton(buttonGroup2);
        allButton->setObjectName(QString::fromUtf8("allButton"));
        allButton->setGeometry(QRect(180, 350, 141, 31));

        retranslateUi(TableRepairDialog);

        QMetaObject::connectSlotsByName(TableRepairDialog);
    } // setupUi

    void retranslateUi(QDialog *TableRepairDialog)
    {
        TableRepairDialog->setWindowTitle(QApplication::translate("TableRepairDialog", "Database Maintence", 0, QApplication::UnicodeUTF8));
        buttonGroup2->setTitle(QApplication::translate("TableRepairDialog", "Choose the table to repair", 0, QApplication::UnicodeUTF8));
        backtagButton->setText(QApplication::translate("TableRepairDialog", "Backtag", 0, QApplication::UnicodeUTF8));
        brandButton->setText(QApplication::translate("TableRepairDialog", "Brand", 0, QApplication::UnicodeUTF8));
        dailyBuyerButton->setText(QApplication::translate("TableRepairDialog", "Daily Buyer", 0, QApplication::UnicodeUTF8));
        dailySellerButton->setText(QApplication::translate("TableRepairDialog", "Daily Seller", 0, QApplication::UnicodeUTF8));
        chargeButton->setText(QApplication::translate("TableRepairDialog", "Charge", 0, QApplication::UnicodeUTF8));
        checkButton->setText(QApplication::translate("TableRepairDialog", "Check", 0, QApplication::UnicodeUTF8));
        commissionButton->setText(QApplication::translate("TableRepairDialog", "Commission", 0, QApplication::UnicodeUTF8));
        codeButton->setText(QApplication::translate("TableRepairDialog", "Description", 0, QApplication::UnicodeUTF8));
        permButton->setText(QApplication::translate("TableRepairDialog", "Perm Customer", 0, QApplication::UnicodeUTF8));
        printerButton->setText(QApplication::translate("TableRepairDialog", "Printer", 0, QApplication::UnicodeUTF8));
        displayButton->setText(QApplication::translate("TableRepairDialog", "Display", 0, QApplication::UnicodeUTF8));
        buyerInvoiceButton->setText(QApplication::translate("TableRepairDialog", "Buyer Invoices", 0, QApplication::UnicodeUTF8));
        sellerInvoiceButton->setText(QApplication::translate("TableRepairDialog", "Seller Invoices", 0, QApplication::UnicodeUTF8));
        truckingButton->setText(QApplication::translate("TableRepairDialog", "Trucking", 0, QApplication::UnicodeUTF8));
        zipCodeButton->setText(QApplication::translate("TableRepairDialog", "Zip Code", 0, QApplication::UnicodeUTF8));
        setupButton->setText(QApplication::translate("TableRepairDialog", "General Setup", 0, QApplication::UnicodeUTF8));
        transButton->setText(QApplication::translate("TableRepairDialog", "Transactions", 0, QApplication::UnicodeUTF8));
        allButton->setText(QApplication::translate("TableRepairDialog", "All", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TableRepairDialog: public Ui_TableRepairDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLEREPAIRDIALOG_H
