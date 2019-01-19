/********************************************************************************
** Form generated from reading UI file 'chargedialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARGEDIALOG_H
#define UI_CHARGEDIALOG_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3ListBox>
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
#include <QtGui/QRadioButton>
#include <list>
#include <string>
#include <vector>
#include "dao/chargedao.h"
#include "types/animalcode.h"

QT_BEGIN_NAMESPACE

class Ui_ChargeDialog
{
public:
    QPushButton *chgNewButt;
    QPushButton *chgSaveButt;
    QPushButton *chgDelButt;
    Q3ButtonGroup *chgCustType;
    QRadioButton *chgSellButt;
    QRadioButton *chgBuyrButt;
    QPushButton *moveChargeDownButton;
    QPushButton *moveChargeUpButton;
    Q3GroupBox *groupBox1;
    QCheckBox *chgReSale;
    QCheckBox *chgNoSale;
    QCheckBox *chgPairs;
    QCheckBox *chgMult;
    QCheckBox *chgComm;
    QCheckBox *isBeefCouncil;
    QLabel *textLabel3;
    QLineEdit *chgEditAmt;
    Q3Table *breakTable;
    QLabel *textLabel1_2;
    QLineEdit *chgEditName;
    Q3Table *codeTable;
    Q3ListBox *chgListBox;
    QLineEdit *codeRelLineEdit;
    QLabel *textLabel1_3_2_2_3;
    QComboBox *colorComboBox;
    QLabel *textLabel1;
    QLabel *textLabel2;
    QLabel *textLabel3_2;
    QComboBox *breakTypeCombo;
    QLabel *textLabel1_3;
    QLabel *textLabel1_4;
    QLabel *textLabel1_4_2;
    QComboBox *scopeCombo;

    void setupUi(QDialog *ChargeDialog)
    {
        if (ChargeDialog->objectName().isEmpty())
            ChargeDialog->setObjectName(QString::fromUtf8("ChargeDialog"));
        ChargeDialog->setWindowModality(Qt::ApplicationModal);
        ChargeDialog->resize(809, 563);
        QFont font;
        font.setPointSize(13);
        ChargeDialog->setFont(font);
        chgNewButt = new QPushButton(ChargeDialog);
        chgNewButt->setObjectName(QString::fromUtf8("chgNewButt"));
        chgNewButt->setGeometry(QRect(510, 520, 90, 31));
        chgSaveButt = new QPushButton(ChargeDialog);
        chgSaveButt->setObjectName(QString::fromUtf8("chgSaveButt"));
        chgSaveButt->setGeometry(QRect(710, 520, 90, 30));
        chgDelButt = new QPushButton(ChargeDialog);
        chgDelButt->setObjectName(QString::fromUtf8("chgDelButt"));
        chgDelButt->setGeometry(QRect(610, 520, 90, 30));
        chgCustType = new Q3ButtonGroup(ChargeDialog);
        chgCustType->setObjectName(QString::fromUtf8("chgCustType"));
        chgCustType->setGeometry(QRect(560, 10, 240, 100));
        chgCustType->setExclusive(true);
        chgSellButt = new QRadioButton(chgCustType);
        chgSellButt->setObjectName(QString::fromUtf8("chgSellButt"));
        chgSellButt->setGeometry(QRect(10, 30, 210, 30));
        chgSellButt->setChecked(true);
        chgBuyrButt = new QRadioButton(chgCustType);
        chgBuyrButt->setObjectName(QString::fromUtf8("chgBuyrButt"));
        chgBuyrButt->setGeometry(QRect(10, 60, 210, 30));
        moveChargeDownButton = new QPushButton(ChargeDialog);
        moveChargeDownButton->setObjectName(QString::fromUtf8("moveChargeDownButton"));
        moveChargeDownButton->setGeometry(QRect(20, 520, 71, 30));
        moveChargeUpButton = new QPushButton(ChargeDialog);
        moveChargeUpButton->setObjectName(QString::fromUtf8("moveChargeUpButton"));
        moveChargeUpButton->setGeometry(QRect(100, 520, 71, 30));
        groupBox1 = new Q3GroupBox(ChargeDialog);
        groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
        groupBox1->setGeometry(QRect(300, 10, 230, 230));
        chgReSale = new QCheckBox(groupBox1);
        chgReSale->setObjectName(QString::fromUtf8("chgReSale"));
        chgReSale->setGeometry(QRect(10, 90, 210, 30));
        chgNoSale = new QCheckBox(groupBox1);
        chgNoSale->setObjectName(QString::fromUtf8("chgNoSale"));
        chgNoSale->setGeometry(QRect(10, 60, 210, 30));
        chgPairs = new QCheckBox(groupBox1);
        chgPairs->setObjectName(QString::fromUtf8("chgPairs"));
        chgPairs->setGeometry(QRect(10, 120, 210, 30));
        chgMult = new QCheckBox(groupBox1);
        chgMult->setObjectName(QString::fromUtf8("chgMult"));
        chgMult->setGeometry(QRect(10, 30, 210, 30));
        chgComm = new QCheckBox(groupBox1);
        chgComm->setObjectName(QString::fromUtf8("chgComm"));
        chgComm->setGeometry(QRect(10, 150, 210, 30));
        isBeefCouncil = new QCheckBox(groupBox1);
        isBeefCouncil->setObjectName(QString::fromUtf8("isBeefCouncil"));
        isBeefCouncil->setGeometry(QRect(10, 180, 210, 30));
        textLabel3 = new QLabel(ChargeDialog);
        textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
        textLabel3->setGeometry(QRect(10, 60, 280, 60));
        textLabel3->setAlignment(Qt::AlignBottom);
        textLabel3->setWordWrap(false);
        chgEditAmt = new QLineEdit(ChargeDialog);
        chgEditAmt->setObjectName(QString::fromUtf8("chgEditAmt"));
        chgEditAmt->setGeometry(QRect(10, 120, 280, 31));
        breakTable = new Q3Table(ChargeDialog);
        breakTable->setObjectName(QString::fromUtf8("breakTable"));
        breakTable->setGeometry(QRect(10, 200, 280, 111));
        breakTable->setNumRows(11);
        breakTable->setNumCols(2);
        textLabel1_2 = new QLabel(ChargeDialog);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(10, 20, 60, 30));
        textLabel1_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_2->setWordWrap(false);
        chgEditName = new QLineEdit(ChargeDialog);
        chgEditName->setObjectName(QString::fromUtf8("chgEditName"));
        chgEditName->setGeometry(QRect(80, 20, 200, 31));
        codeTable = new Q3Table(ChargeDialog);
        codeTable->setObjectName(QString::fromUtf8("codeTable"));
        codeTable->setGeometry(QRect(540, 250, 260, 260));
        codeTable->setNumRows(10);
        codeTable->setNumCols(10);
        chgListBox = new Q3ListBox(ChargeDialog);
        chgListBox->setObjectName(QString::fromUtf8("chgListBox"));
        chgListBox->setGeometry(QRect(10, 320, 500, 190));
        codeRelLineEdit = new QLineEdit(ChargeDialog);
        codeRelLineEdit->setObjectName(QString::fromUtf8("codeRelLineEdit"));
        codeRelLineEdit->setGeometry(QRect(710, 180, 90, 30));
        textLabel1_3_2_2_3 = new QLabel(ChargeDialog);
        textLabel1_3_2_2_3->setObjectName(QString::fromUtf8("textLabel1_3_2_2_3"));
        textLabel1_3_2_2_3->setGeometry(QRect(554, 180, 146, 30));
        textLabel1_3_2_2_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_3_2_2_3->setWordWrap(false);
        colorComboBox = new QComboBox(ChargeDialog);
        colorComboBox->setObjectName(QString::fromUtf8("colorComboBox"));
        colorComboBox->setGeometry(QRect(710, 140, 90, 30));
        textLabel1 = new QLabel(ChargeDialog);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(560, 140, 140, 30));
        textLabel1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1->setWordWrap(false);
        textLabel2 = new QLabel(ChargeDialog);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setGeometry(QRect(541, 220, 260, 31));
        textLabel2->setAlignment(Qt::AlignCenter);
        textLabel2->setWordWrap(false);
        textLabel3_2 = new QLabel(ChargeDialog);
        textLabel3_2->setObjectName(QString::fromUtf8("textLabel3_2"));
        textLabel3_2->setGeometry(QRect(510, 250, 30, 251));
        textLabel3_2->setAlignment(Qt::AlignCenter);
        textLabel3_2->setWordWrap(false);
        breakTypeCombo = new QComboBox(ChargeDialog);
        breakTypeCombo->setObjectName(QString::fromUtf8("breakTypeCombo"));
        breakTypeCombo->setGeometry(QRect(140, 160, 151, 31));
        textLabel1_3 = new QLabel(ChargeDialog);
        textLabel1_3->setObjectName(QString::fromUtf8("textLabel1_3"));
        textLabel1_3->setGeometry(QRect(180, 510, 320, 50));
        textLabel1_3->setWordWrap(false);
        textLabel1_4 = new QLabel(ChargeDialog);
        textLabel1_4->setObjectName(QString::fromUtf8("textLabel1_4"));
        textLabel1_4->setGeometry(QRect(11, 160, 120, 31));
        textLabel1_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_4->setWordWrap(false);
        textLabel1_4_2 = new QLabel(ChargeDialog);
        textLabel1_4_2->setObjectName(QString::fromUtf8("textLabel1_4_2"));
        textLabel1_4_2->setGeometry(QRect(300, 270, 80, 31));
        textLabel1_4_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_4_2->setWordWrap(false);
        scopeCombo = new QComboBox(ChargeDialog);
        scopeCombo->setObjectName(QString::fromUtf8("scopeCombo"));
        scopeCombo->setGeometry(QRect(390, 270, 111, 31));
        QWidget::setTabOrder(chgEditName, chgEditAmt);
        QWidget::setTabOrder(chgEditAmt, chgMult);
        QWidget::setTabOrder(chgMult, chgNoSale);
        QWidget::setTabOrder(chgNoSale, chgReSale);
        QWidget::setTabOrder(chgReSale, chgPairs);
        QWidget::setTabOrder(chgPairs, codeRelLineEdit);
        QWidget::setTabOrder(codeRelLineEdit, colorComboBox);
        QWidget::setTabOrder(colorComboBox, chgListBox);
        QWidget::setTabOrder(chgListBox, codeTable);
        QWidget::setTabOrder(codeTable, chgSellButt);
        QWidget::setTabOrder(chgSellButt, chgNewButt);
        QWidget::setTabOrder(chgNewButt, chgDelButt);
        QWidget::setTabOrder(chgDelButt, chgSaveButt);

        retranslateUi(ChargeDialog);

        QMetaObject::connectSlotsByName(ChargeDialog);
    } // setupUi

    void retranslateUi(QDialog *ChargeDialog)
    {
        ChargeDialog->setWindowTitle(QApplication::translate("ChargeDialog", "Edit Charges", 0, QApplication::UnicodeUTF8));
        chgNewButt->setText(QApplication::translate("ChargeDialog", "New", 0, QApplication::UnicodeUTF8));
        chgSaveButt->setText(QApplication::translate("ChargeDialog", "Save", 0, QApplication::UnicodeUTF8));
        chgDelButt->setText(QApplication::translate("ChargeDialog", "Delete", 0, QApplication::UnicodeUTF8));
        chgCustType->setTitle(QApplication::translate("ChargeDialog", "Customer Type", 0, QApplication::UnicodeUTF8));
        chgSellButt->setText(QApplication::translate("ChargeDialog", "Seller", 0, QApplication::UnicodeUTF8));
        chgBuyrButt->setText(QApplication::translate("ChargeDialog", "Buyer", 0, QApplication::UnicodeUTF8));
        moveChargeDownButton->setText(QApplication::translate("ChargeDialog", "\\/", 0, QApplication::UnicodeUTF8));
        moveChargeUpButton->setText(QApplication::translate("ChargeDialog", "/\\", 0, QApplication::UnicodeUTF8));
        groupBox1->setTitle(QApplication::translate("ChargeDialog", "Options", 0, QApplication::UnicodeUTF8));
        chgReSale->setText(QApplication::translate("ChargeDialog", "Charge on Re-Sale", 0, QApplication::UnicodeUTF8));
        chgNoSale->setText(QApplication::translate("ChargeDialog", "Charge on No-Sale", 0, QApplication::UnicodeUTF8));
        chgPairs->setText(QApplication::translate("ChargeDialog", "Double on Pairs", 0, QApplication::UnicodeUTF8));
        chgMult->setText(QApplication::translate("ChargeDialog", "Multiplier", 0, QApplication::UnicodeUTF8));
        chgComm->setText(QApplication::translate("ChargeDialog", "Add To Commission", 0, QApplication::UnicodeUTF8));
        isBeefCouncil->setText(QApplication::translate("ChargeDialog", "Beef Council", 0, QApplication::UnicodeUTF8));
        textLabel3->setText(QApplication::translate("ChargeDialog", "Default Expression:\n"
"(0 = manual; else H,W,T,*,+,-,/)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        chgEditAmt->setToolTip(QApplication::translate("ChargeDialog", "Expressions in the auction program<br>are calculations that you wish to<br>be performed automatically. In this<br>case the variable are:<BR>H => head, W => weight,<BR>T => transaction total", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        breakTable->horizontalHeader()->setLabel(0, QApplication::translate("ChargeDialog", "Expression", 0, QApplication::UnicodeUTF8));
        breakTable->horizontalHeader()->setLabel(1, QApplication::translate("ChargeDialog", "Break", 0, QApplication::UnicodeUTF8));
        breakTable->verticalHeader()->setLabel(0, QString());
        breakTable->verticalHeader()->setLabel(1, QString());
        breakTable->verticalHeader()->setLabel(2, QString());
        breakTable->verticalHeader()->setLabel(3, QString());
        breakTable->verticalHeader()->setLabel(4, QString());
        breakTable->verticalHeader()->setLabel(5, QString());
        breakTable->verticalHeader()->setLabel(6, QString());
        breakTable->verticalHeader()->setLabel(7, QString());
        breakTable->verticalHeader()->setLabel(8, QString());
        breakTable->verticalHeader()->setLabel(9, QString());
        breakTable->verticalHeader()->setLabel(10, QString());
        textLabel1_2->setText(QApplication::translate("ChargeDialog", "Name", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(0, QApplication::translate("ChargeDialog", "0", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(1, QApplication::translate("ChargeDialog", "1", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(2, QApplication::translate("ChargeDialog", "2", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(3, QApplication::translate("ChargeDialog", "3", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(4, QApplication::translate("ChargeDialog", "4", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(5, QApplication::translate("ChargeDialog", "5", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(6, QApplication::translate("ChargeDialog", "6", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(7, QApplication::translate("ChargeDialog", "7", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(8, QApplication::translate("ChargeDialog", "8", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(9, QApplication::translate("ChargeDialog", "9", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(0, QApplication::translate("ChargeDialog", "0", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(1, QApplication::translate("ChargeDialog", "1", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(2, QApplication::translate("ChargeDialog", "2", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(3, QApplication::translate("ChargeDialog", "3", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(4, QApplication::translate("ChargeDialog", "4", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(5, QApplication::translate("ChargeDialog", "5", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(6, QApplication::translate("ChargeDialog", "6", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(7, QApplication::translate("ChargeDialog", "7", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(8, QApplication::translate("ChargeDialog", "8", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(9, QApplication::translate("ChargeDialog", "9", 0, QApplication::UnicodeUTF8));
        textLabel1_3_2_2_3->setText(QApplication::translate("ChargeDialog", "Quick Codes", 0, QApplication::UnicodeUTF8));
        colorComboBox->clear();
        colorComboBox->insertItems(0, QStringList()
         << QApplication::translate("ChargeDialog", "0-69", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ChargeDialog", "70-79", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ChargeDialog", "80-89", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ChargeDialog", "90-99", 0, QApplication::UnicodeUTF8)
        );
        textLabel1->setText(QApplication::translate("ChargeDialog", "Color Code", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("ChargeDialog", "Sex", 0, QApplication::UnicodeUTF8));
        textLabel3_2->setText(QApplication::translate("ChargeDialog", "F\n"
"l\n"
"a\n"
"w", 0, QApplication::UnicodeUTF8));
        breakTypeCombo->clear();
        breakTypeCombo->insertItems(0, QStringList()
         << QApplication::translate("ChargeDialog", "None", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ChargeDialog", "Head", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ChargeDialog", "Avg Weight", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ChargeDialog", "Total", 0, QApplication::UnicodeUTF8)
        );
        textLabel1_3->setText(QApplication::translate("ChargeDialog", "<small><B><p color=\"0xff0000\">WARNING: Changing the order of the charges mid-sale <u>WILL</u> cause undesired side effects.</p></b></small>", 0, QApplication::UnicodeUTF8));
        textLabel1_4->setText(QApplication::translate("ChargeDialog", "Break At:", 0, QApplication::UnicodeUTF8));
        textLabel1_4_2->setText(QApplication::translate("ChargeDialog", "Scope:", 0, QApplication::UnicodeUTF8));
        scopeCombo->clear();
        scopeCombo->insertItems(0, QStringList()
         << QApplication::translate("ChargeDialog", "Transaction", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ChargeDialog", "Invoice", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class ChargeDialog: public Ui_ChargeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARGEDIALOG_H
