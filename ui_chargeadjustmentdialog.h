/********************************************************************************
** Form generated from reading UI file 'chargeadjustmentdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARGEADJUSTMENTDIALOG_H
#define UI_CHARGEADJUSTMENTDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GroupBox>
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
#include "dao/chargedao.h"
#include "dao/invoicedao.h"
#include "types/commission.h"
#include "types/invoice.h"

QT_BEGIN_NAMESPACE

class Ui_ChargeAdjustmentDialog
{
public:
    QPushButton *cancelButton;
    QComboBox *groupCombo;
    QPushButton *acceptButton;
    QPushButton *creditButton;
    QLabel *groupLabel;
    Q3GroupBox *buyerCommissionGroup;
    QLabel *textLabel1_3;
    QLineEdit *buyerCommAmount;
    QLabel *textLabel1_4;
    QLabel *textLabel1_2;
    QComboBox *buyerCommMode;
    QLabel *textLabel1;
    QLabel *buyerCommExtension;
    QComboBox *payeeCombo;
    Q3Table *adjustmentTable;

    void setupUi(QDialog *ChargeAdjustmentDialog)
    {
        if (ChargeAdjustmentDialog->objectName().isEmpty())
            ChargeAdjustmentDialog->setObjectName(QString::fromUtf8("ChargeAdjustmentDialog"));
        ChargeAdjustmentDialog->setWindowModality(Qt::ApplicationModal);
        ChargeAdjustmentDialog->resize(310, 419);
        QFont font;
        font.setPointSize(13);
        ChargeAdjustmentDialog->setFont(font);
        cancelButton = new QPushButton(ChargeAdjustmentDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(10, 381, 90, 30));
        groupCombo = new QComboBox(ChargeAdjustmentDialog);
        groupCombo->setObjectName(QString::fromUtf8("groupCombo"));
        groupCombo->setGeometry(QRect(210, 340, 90, 30));
        acceptButton = new QPushButton(ChargeAdjustmentDialog);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));
        acceptButton->setGeometry(QRect(210, 380, 90, 30));
        creditButton = new QPushButton(ChargeAdjustmentDialog);
        creditButton->setObjectName(QString::fromUtf8("creditButton"));
        creditButton->setGeometry(QRect(110, 380, 90, 30));
        groupLabel = new QLabel(ChargeAdjustmentDialog);
        groupLabel->setObjectName(QString::fromUtf8("groupLabel"));
        groupLabel->setGeometry(QRect(10, 340, 190, 30));
        groupLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        groupLabel->setWordWrap(false);
        buyerCommissionGroup = new Q3GroupBox(ChargeAdjustmentDialog);
        buyerCommissionGroup->setObjectName(QString::fromUtf8("buyerCommissionGroup"));
        buyerCommissionGroup->setGeometry(QRect(10, 0, 290, 140));
        textLabel1_3 = new QLabel(buyerCommissionGroup);
        textLabel1_3->setObjectName(QString::fromUtf8("textLabel1_3"));
        textLabel1_3->setGeometry(QRect(100, 30, 61, 21));
        textLabel1_3->setWordWrap(false);
        buyerCommAmount = new QLineEdit(buyerCommissionGroup);
        buyerCommAmount->setObjectName(QString::fromUtf8("buyerCommAmount"));
        buyerCommAmount->setGeometry(QRect(10, 60, 80, 31));
        textLabel1_4 = new QLabel(buyerCommissionGroup);
        textLabel1_4->setObjectName(QString::fromUtf8("textLabel1_4"));
        textLabel1_4->setGeometry(QRect(190, 30, 90, 21));
        textLabel1_4->setWordWrap(false);
        textLabel1_2 = new QLabel(buyerCommissionGroup);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(10, 30, 80, 21));
        textLabel1_2->setWordWrap(false);
        buyerCommMode = new QComboBox(buyerCommissionGroup);
        buyerCommMode->setObjectName(QString::fromUtf8("buyerCommMode"));
        buyerCommMode->setGeometry(QRect(100, 60, 80, 30));
        textLabel1 = new QLabel(buyerCommissionGroup);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(10, 100, 90, 31));
        textLabel1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1->setWordWrap(false);
        buyerCommExtension = new QLabel(buyerCommissionGroup);
        buyerCommExtension->setObjectName(QString::fromUtf8("buyerCommExtension"));
        buyerCommExtension->setGeometry(QRect(190, 60, 80, 30));
        buyerCommExtension->setWordWrap(false);
        payeeCombo = new QComboBox(buyerCommissionGroup);
        payeeCombo->setObjectName(QString::fromUtf8("payeeCombo"));
        payeeCombo->setGeometry(QRect(100, 100, 180, 31));
        adjustmentTable = new Q3Table(ChargeAdjustmentDialog);
        adjustmentTable->setObjectName(QString::fromUtf8("adjustmentTable"));
        adjustmentTable->setGeometry(QRect(10, 150, 290, 180));
        adjustmentTable->setNumRows(0);
        adjustmentTable->setNumCols(2);

        retranslateUi(ChargeAdjustmentDialog);

        QMetaObject::connectSlotsByName(ChargeAdjustmentDialog);
    } // setupUi

    void retranslateUi(QDialog *ChargeAdjustmentDialog)
    {
        ChargeAdjustmentDialog->setWindowTitle(QApplication::translate("ChargeAdjustmentDialog", "Adjust Charges", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("ChargeAdjustmentDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        groupCombo->clear();
        groupCombo->insertItems(0, QStringList()
         << QApplication::translate("ChargeAdjustmentDialog", "0-69", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ChargeAdjustmentDialog", "70-79", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ChargeAdjustmentDialog", "80-89", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ChargeAdjustmentDialog", "90-99", 0, QApplication::UnicodeUTF8)
        );
        acceptButton->setText(QApplication::translate("ChargeAdjustmentDialog", "Accept", 0, QApplication::UnicodeUTF8));
        creditButton->setText(QApplication::translate("ChargeAdjustmentDialog", "Credit", 0, QApplication::UnicodeUTF8));
        groupLabel->setText(QApplication::translate("ChargeAdjustmentDialog", "Charge Group:", 0, QApplication::UnicodeUTF8));
        buyerCommissionGroup->setTitle(QApplication::translate("ChargeAdjustmentDialog", "Buyer Commission", 0, QApplication::UnicodeUTF8));
        textLabel1_3->setText(QApplication::translate("ChargeAdjustmentDialog", "Mode", 0, QApplication::UnicodeUTF8));
        textLabel1_4->setText(QApplication::translate("ChargeAdjustmentDialog", "Extension", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("ChargeAdjustmentDialog", "Amount", 0, QApplication::UnicodeUTF8));
        buyerCommMode->clear();
        buyerCommMode->insertItems(0, QStringList()
         << QApplication::translate("ChargeAdjustmentDialog", "CWT", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ChargeAdjustmentDialog", "Head", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ChargeAdjustmentDialog", "Flat", 0, QApplication::UnicodeUTF8)
        );
        textLabel1->setText(QApplication::translate("ChargeAdjustmentDialog", "Applies To:", 0, QApplication::UnicodeUTF8));
        buyerCommExtension->setText(QApplication::translate("ChargeAdjustmentDialog", "0.0", 0, QApplication::UnicodeUTF8));
        payeeCombo->clear();
        payeeCombo->insertItems(0, QStringList()
         << QApplication::translate("ChargeAdjustmentDialog", "Buyer", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ChargeAdjustmentDialog", "Company", 0, QApplication::UnicodeUTF8)
        );
        adjustmentTable->horizontalHeader()->setLabel(0, QApplication::translate("ChargeAdjustmentDialog", "Charge Name", 0, QApplication::UnicodeUTF8));
        adjustmentTable->horizontalHeader()->setLabel(1, QApplication::translate("ChargeAdjustmentDialog", "Entry", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ChargeAdjustmentDialog: public Ui_ChargeAdjustmentDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARGEADJUSTMENTDIALOG_H
