/********************************************************************************
** Form generated from reading UI file 'checkeditdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKEDITDIALOG_H
#define UI_CHECKEDITDIALOG_H

#include <Qt3Support/Q3DateEdit>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QDate>
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
#include <QtGui/QSpinBox>
#include "dao/checkdao.h"
#include "dao/invoicedao.h"
#include "dao/printerdao.h"
#include "types/check.h"

QT_BEGIN_NAMESPACE

class Ui_CheckEditDialog
{
public:
    QPushButton *buttonOk;
    QPushButton *printButton;
    QPushButton *buttonCancel;
    QLineEdit *lineEditChkMemo;
    QLabel *textLabelChkMemo;
    QLineEdit *lineEditTxtAmt;
    QLineEdit *lineEditPayTo;
    QLineEdit *lineEditNumAmt;
    QLabel *textLabelPayTo;
    QLabel *textLabelChkHdg;
    QLabel *textLabel4;
    QPushButton *buttonOutst;
    QPushButton *buttonVoid;
    QPushButton *buttonCleared;
    QLabel *textLabelChkDate;
    QLabel *textLabelChkNum;
    Q3DateEdit *chkDate;
    QSpinBox *checkNumberSpinBox;
    QLabel *chkSig;
    QComboBox *checkTypeCombo;

    void setupUi(QDialog *CheckEditDialog)
    {
        if (CheckEditDialog->objectName().isEmpty())
            CheckEditDialog->setObjectName(QString::fromUtf8("CheckEditDialog"));
        CheckEditDialog->setWindowModality(Qt::ApplicationModal);
        CheckEditDialog->resize(810, 341);
        QFont font;
        font.setPointSize(13);
        CheckEditDialog->setFont(font);
        CheckEditDialog->setSizeGripEnabled(false);
        CheckEditDialog->setModal(true);
        buttonOk = new QPushButton(CheckEditDialog);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setGeometry(QRect(710, 300, 90, 30));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonOk->sizePolicy().hasHeightForWidth());
        buttonOk->setSizePolicy(sizePolicy);
        buttonOk->setMinimumSize(QSize(88, 27));
        buttonOk->setAutoDefault(false);
        buttonOk->setDefault(true);
        printButton = new QPushButton(CheckEditDialog);
        printButton->setObjectName(QString::fromUtf8("printButton"));
        printButton->setGeometry(QRect(600, 300, 90, 30));
        sizePolicy.setHeightForWidth(printButton->sizePolicy().hasHeightForWidth());
        printButton->setSizePolicy(sizePolicy);
        printButton->setMinimumSize(QSize(88, 27));
        printButton->setAutoDefault(false);
        printButton->setDefault(true);
        buttonCancel = new QPushButton(CheckEditDialog);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setGeometry(QRect(490, 300, 90, 30));
        sizePolicy.setHeightForWidth(buttonCancel->sizePolicy().hasHeightForWidth());
        buttonCancel->setSizePolicy(sizePolicy);
        buttonCancel->setMinimumSize(QSize(88, 27));
        buttonCancel->setAutoDefault(false);
        lineEditChkMemo = new QLineEdit(CheckEditDialog);
        lineEditChkMemo->setObjectName(QString::fromUtf8("lineEditChkMemo"));
        lineEditChkMemo->setGeometry(QRect(100, 240, 390, 30));
        textLabelChkMemo = new QLabel(CheckEditDialog);
        textLabelChkMemo->setObjectName(QString::fromUtf8("textLabelChkMemo"));
        textLabelChkMemo->setGeometry(QRect(20, 240, 70, 30));
        textLabelChkMemo->setFrameShape(QFrame::NoFrame);
        textLabelChkMemo->setFrameShadow(QFrame::Plain);
        textLabelChkMemo->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabelChkMemo->setWordWrap(false);
        lineEditTxtAmt = new QLineEdit(CheckEditDialog);
        lineEditTxtAmt->setObjectName(QString::fromUtf8("lineEditTxtAmt"));
        lineEditTxtAmt->setGeometry(QRect(10, 150, 710, 30));
        QFont font1;
        font1.setPointSize(8);
        lineEditTxtAmt->setFont(font1);
        lineEditTxtAmt->setFocusPolicy(Qt::NoFocus);
        lineEditTxtAmt->setAlignment(Qt::AlignLeading);
        lineEditTxtAmt->setReadOnly(true);
        lineEditPayTo = new QLineEdit(CheckEditDialog);
        lineEditPayTo->setObjectName(QString::fromUtf8("lineEditPayTo"));
        lineEditPayTo->setGeometry(QRect(110, 100, 550, 30));
        lineEditNumAmt = new QLineEdit(CheckEditDialog);
        lineEditNumAmt->setObjectName(QString::fromUtf8("lineEditNumAmt"));
        lineEditNumAmt->setGeometry(QRect(680, 100, 120, 30));
        lineEditNumAmt->setAlignment(Qt::AlignRight);
        textLabelPayTo = new QLabel(CheckEditDialog);
        textLabelPayTo->setObjectName(QString::fromUtf8("textLabelPayTo"));
        textLabelPayTo->setGeometry(QRect(10, 100, 90, 40));
        QFont font2;
        font2.setPointSize(10);
        textLabelPayTo->setFont(font2);
        textLabelPayTo->setTextFormat(Qt::PlainText);
        textLabelPayTo->setScaledContents(true);
        textLabelPayTo->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabelPayTo->setWordWrap(true);
        textLabelChkHdg = new QLabel(CheckEditDialog);
        textLabelChkHdg->setObjectName(QString::fromUtf8("textLabelChkHdg"));
        textLabelChkHdg->setGeometry(QRect(10, 10, 221, 77));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Luxi Sans"));
        font3.setPointSize(13);
        textLabelChkHdg->setFont(font3);
        textLabelChkHdg->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        textLabelChkHdg->setWordWrap(true);
        textLabel4 = new QLabel(CheckEditDialog);
        textLabel4->setObjectName(QString::fromUtf8("textLabel4"));
        textLabel4->setGeometry(QRect(731, 150, 70, 30));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Luxi Sans"));
        font4.setPointSize(12);
        textLabel4->setFont(font4);
        textLabel4->setWordWrap(false);
        buttonOutst = new QPushButton(CheckEditDialog);
        buttonOutst->setObjectName(QString::fromUtf8("buttonOutst"));
        buttonOutst->setGeometry(QRect(290, 300, 130, 30));
        buttonOutst->setMinimumSize(QSize(88, 27));
        buttonVoid = new QPushButton(CheckEditDialog);
        buttonVoid->setObjectName(QString::fromUtf8("buttonVoid"));
        buttonVoid->setGeometry(QRect(150, 300, 130, 30));
        sizePolicy.setHeightForWidth(buttonVoid->sizePolicy().hasHeightForWidth());
        buttonVoid->setSizePolicy(sizePolicy);
        buttonVoid->setMinimumSize(QSize(88, 27));
        buttonVoid->setAutoDefault(false);
        buttonVoid->setDefault(true);
        buttonCleared = new QPushButton(CheckEditDialog);
        buttonCleared->setObjectName(QString::fromUtf8("buttonCleared"));
        buttonCleared->setGeometry(QRect(10, 300, 130, 30));
        sizePolicy.setHeightForWidth(buttonCleared->sizePolicy().hasHeightForWidth());
        buttonCleared->setSizePolicy(sizePolicy);
        buttonCleared->setMinimumSize(QSize(88, 27));
        textLabelChkDate = new QLabel(CheckEditDialog);
        textLabelChkDate->setObjectName(QString::fromUtf8("textLabelChkDate"));
        textLabelChkDate->setGeometry(QRect(440, 50, 190, 30));
        textLabelChkDate->setFont(font4);
        textLabelChkDate->setFrameShape(QFrame::NoFrame);
        textLabelChkDate->setFrameShadow(QFrame::Plain);
        textLabelChkDate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabelChkDate->setWordWrap(false);
        textLabelChkNum = new QLabel(CheckEditDialog);
        textLabelChkNum->setObjectName(QString::fromUtf8("textLabelChkNum"));
        textLabelChkNum->setEnabled(true);
        textLabelChkNum->setGeometry(QRect(450, 10, 190, 30));
        textLabelChkNum->setFont(font4);
        textLabelChkNum->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabelChkNum->setWordWrap(false);
        chkDate = new Q3DateEdit(CheckEditDialog);
        chkDate->setObjectName(QString::fromUtf8("chkDate"));
        chkDate->setGeometry(QRect(645, 50, 160, 32));
        chkDate->setOrder(Q3DateEdit::YMD);
        chkDate->setDate(QDate(2000, 1, 1));
        checkNumberSpinBox = new QSpinBox(CheckEditDialog);
        checkNumberSpinBox->setObjectName(QString::fromUtf8("checkNumberSpinBox"));
        checkNumberSpinBox->setGeometry(QRect(650, 10, 150, 30));
        checkNumberSpinBox->setMaximum(999999999);
        chkSig = new QLabel(CheckEditDialog);
        chkSig->setObjectName(QString::fromUtf8("chkSig"));
        chkSig->setGeometry(QRect(580, 190, 220, 80));
        chkSig->setScaledContents(true);
        chkSig->setWordWrap(false);
        checkTypeCombo = new QComboBox(CheckEditDialog);
        checkTypeCombo->setObjectName(QString::fromUtf8("checkTypeCombo"));
        checkTypeCombo->setGeometry(QRect(250, 10, 170, 31));
        QWidget::setTabOrder(chkDate, lineEditPayTo);
        QWidget::setTabOrder(lineEditPayTo, lineEditNumAmt);
        QWidget::setTabOrder(lineEditNumAmt, lineEditChkMemo);
        QWidget::setTabOrder(lineEditChkMemo, buttonOk);
        QWidget::setTabOrder(buttonOk, buttonCancel);
        QWidget::setTabOrder(buttonCancel, buttonOutst);
        QWidget::setTabOrder(buttonOutst, buttonVoid);
        QWidget::setTabOrder(buttonVoid, buttonCleared);
        QWidget::setTabOrder(buttonCleared, lineEditTxtAmt);

        retranslateUi(CheckEditDialog);

        QMetaObject::connectSlotsByName(CheckEditDialog);
    } // setupUi

    void retranslateUi(QDialog *CheckEditDialog)
    {
        CheckEditDialog->setWindowTitle(QApplication::translate("CheckEditDialog", "Check", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("CheckEditDialog", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QString());
        printButton->setText(QApplication::translate("CheckEditDialog", "Print", 0, QApplication::UnicodeUTF8));
        printButton->setShortcut(QString());
        buttonCancel->setText(QApplication::translate("CheckEditDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
        textLabelChkMemo->setText(QApplication::translate("CheckEditDialog", "Memo", 0, QApplication::UnicodeUTF8));
        lineEditTxtAmt->setText(QString());
        lineEditNumAmt->setInputMask(QApplication::translate("CheckEditDialog", "00000000.00; ", 0, QApplication::UnicodeUTF8));
        textLabelPayTo->setText(QApplication::translate("CheckEditDialog", "Pay to the Order of", 0, QApplication::UnicodeUTF8));
        textLabelChkHdg->setText(QApplication::translate("CheckEditDialog", "Market Name\n"
"Address\n"
"City, State, Zip", 0, QApplication::UnicodeUTF8));
        textLabel4->setText(QApplication::translate("CheckEditDialog", "Dollars", 0, QApplication::UnicodeUTF8));
        buttonOutst->setText(QApplication::translate("CheckEditDialog", "Outstanding", 0, QApplication::UnicodeUTF8));
        buttonVoid->setText(QApplication::translate("CheckEditDialog", "&Void", 0, QApplication::UnicodeUTF8));
        buttonVoid->setShortcut(QApplication::translate("CheckEditDialog", "Alt+V", 0, QApplication::UnicodeUTF8));
        buttonCleared->setText(QApplication::translate("CheckEditDialog", "Cleared", 0, QApplication::UnicodeUTF8));
        buttonCleared->setShortcut(QString());
        textLabelChkDate->setText(QApplication::translate("CheckEditDialog", "Date", 0, QApplication::UnicodeUTF8));
        textLabelChkNum->setText(QApplication::translate("CheckEditDialog", "Check Number", 0, QApplication::UnicodeUTF8));
        checkTypeCombo->clear();
        checkTypeCombo->insertItems(0, QStringList()
         << QApplication::translate("CheckEditDialog", "Miscellaneous", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CheckEditDialog", "Invoice", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CheckEditDialog", "Trucker", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CheckEditDialog", "Buyer", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class CheckEditDialog: public Ui_CheckEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKEDITDIALOG_H
