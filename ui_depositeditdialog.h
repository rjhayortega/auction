/********************************************************************************
** Form generated from reading UI file 'depositeditdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPOSITEDITDIALOG_H
#define UI_DEPOSITEDITDIALOG_H

#include <Qt3Support/Q3DateEdit>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include "dao/checkdao.h"

QT_BEGIN_NAMESPACE

class Ui_DepositEditDialog
{
public:
    QLabel *textLabel2;
    QLabel *textLabelNum;
    QLabel *textLabeDate;
    QLineEdit *lineEditMemo;
    QPushButton *buttonOk;
    QLabel *textLabelAmt;
    QLabel *textLabelMemo;
    QPushButton *buttonCleared;
    QPushButton *buttonVoid;
    QPushButton *buttonOutst;
    QPushButton *buttonCancel;
    Q3DateEdit *depositDate;
    QLineEdit *lineEditAmt;

    void setupUi(QDialog *DepositEditDialog)
    {
        if (DepositEditDialog->objectName().isEmpty())
            DepositEditDialog->setObjectName(QString::fromUtf8("DepositEditDialog"));
        DepositEditDialog->setWindowModality(Qt::ApplicationModal);
        DepositEditDialog->resize(753, 330);
        QFont font;
        font.setPointSize(13);
        DepositEditDialog->setFont(font);
        DepositEditDialog->setSizeGripEnabled(false);
        DepositEditDialog->setModal(true);
        textLabel2 = new QLabel(DepositEditDialog);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setGeometry(QRect(10, 10, 100, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Luxi Sans"));
        font1.setPointSize(12);
        textLabel2->setFont(font1);
        textLabel2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2->setWordWrap(false);
        textLabelNum = new QLabel(DepositEditDialog);
        textLabelNum->setObjectName(QString::fromUtf8("textLabelNum"));
        textLabelNum->setGeometry(QRect(130, 10, 100, 30));
        textLabelNum->setFont(font1);
        textLabelNum->setWordWrap(false);
        textLabeDate = new QLabel(DepositEditDialog);
        textLabeDate->setObjectName(QString::fromUtf8("textLabeDate"));
        textLabeDate->setGeometry(QRect(120, 80, 80, 30));
        textLabeDate->setFont(font1);
        textLabeDate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabeDate->setWordWrap(false);
        lineEditMemo = new QLineEdit(DepositEditDialog);
        lineEditMemo->setObjectName(QString::fromUtf8("lineEditMemo"));
        lineEditMemo->setGeometry(QRect(210, 200, 381, 30));
        buttonOk = new QPushButton(DepositEditDialog);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setGeometry(QRect(640, 280, 100, 30));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonOk->sizePolicy().hasHeightForWidth());
        buttonOk->setSizePolicy(sizePolicy);
        buttonOk->setMinimumSize(QSize(88, 27));
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);
        textLabelAmt = new QLabel(DepositEditDialog);
        textLabelAmt->setObjectName(QString::fromUtf8("textLabelAmt"));
        textLabelAmt->setGeometry(QRect(130, 120, 70, 30));
        textLabelAmt->setFont(font1);
        textLabelAmt->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabelAmt->setWordWrap(false);
        textLabelMemo = new QLabel(DepositEditDialog);
        textLabelMemo->setObjectName(QString::fromUtf8("textLabelMemo"));
        textLabelMemo->setGeometry(QRect(120, 200, 80, 30));
        textLabelMemo->setFont(font1);
        textLabelMemo->setFrameShape(QFrame::NoFrame);
        textLabelMemo->setFrameShadow(QFrame::Plain);
        textLabelMemo->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabelMemo->setWordWrap(false);
        buttonCleared = new QPushButton(DepositEditDialog);
        buttonCleared->setObjectName(QString::fromUtf8("buttonCleared"));
        buttonCleared->setGeometry(QRect(20, 280, 140, 30));
        buttonVoid = new QPushButton(DepositEditDialog);
        buttonVoid->setObjectName(QString::fromUtf8("buttonVoid"));
        buttonVoid->setGeometry(QRect(170, 280, 140, 30));
        sizePolicy.setHeightForWidth(buttonVoid->sizePolicy().hasHeightForWidth());
        buttonVoid->setSizePolicy(sizePolicy);
        buttonVoid->setMinimumSize(QSize(88, 27));
        buttonVoid->setAutoDefault(true);
        buttonVoid->setDefault(true);
        buttonOutst = new QPushButton(DepositEditDialog);
        buttonOutst->setObjectName(QString::fromUtf8("buttonOutst"));
        buttonOutst->setGeometry(QRect(320, 280, 140, 30));
        buttonCancel = new QPushButton(DepositEditDialog);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setGeometry(QRect(530, 280, 100, 30));
        sizePolicy.setHeightForWidth(buttonCancel->sizePolicy().hasHeightForWidth());
        buttonCancel->setSizePolicy(sizePolicy);
        buttonCancel->setMinimumSize(QSize(88, 27));
        buttonCancel->setAutoDefault(true);
        depositDate = new Q3DateEdit(DepositEditDialog);
        depositDate->setObjectName(QString::fromUtf8("depositDate"));
        depositDate->setGeometry(QRect(210, 80, 150, 32));
        depositDate->setOrder(Q3DateEdit::YMD);
        depositDate->setDate(QDate(2000, 1, 1));
        lineEditAmt = new QLineEdit(DepositEditDialog);
        lineEditAmt->setObjectName(QString::fromUtf8("lineEditAmt"));
        lineEditAmt->setGeometry(QRect(210, 120, 150, 31));
        lineEditAmt->setAlignment(Qt::AlignRight);
        QWidget::setTabOrder(depositDate, lineEditAmt);
        QWidget::setTabOrder(lineEditAmt, lineEditMemo);
        QWidget::setTabOrder(lineEditMemo, buttonOk);
        QWidget::setTabOrder(buttonOk, buttonCancel);
        QWidget::setTabOrder(buttonCancel, buttonCleared);
        QWidget::setTabOrder(buttonCleared, buttonVoid);
        QWidget::setTabOrder(buttonVoid, buttonOutst);

        retranslateUi(DepositEditDialog);

        QMetaObject::connectSlotsByName(DepositEditDialog);
    } // setupUi

    void retranslateUi(QDialog *DepositEditDialog)
    {
        DepositEditDialog->setWindowTitle(QApplication::translate("DepositEditDialog", "Deposit", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("DepositEditDialog", "Number", 0, QApplication::UnicodeUTF8));
        textLabelNum->setText(QApplication::translate("DepositEditDialog", "Number", 0, QApplication::UnicodeUTF8));
        textLabeDate->setText(QApplication::translate("DepositEditDialog", "Date", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("DepositEditDialog", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QString());
        textLabelAmt->setText(QApplication::translate("DepositEditDialog", "Amount", 0, QApplication::UnicodeUTF8));
        textLabelMemo->setText(QApplication::translate("DepositEditDialog", "Memo", 0, QApplication::UnicodeUTF8));
        buttonCleared->setText(QApplication::translate("DepositEditDialog", "Cleared", 0, QApplication::UnicodeUTF8));
        buttonCleared->setShortcut(QString());
        buttonVoid->setText(QApplication::translate("DepositEditDialog", "&Void", 0, QApplication::UnicodeUTF8));
        buttonVoid->setShortcut(QApplication::translate("DepositEditDialog", "Alt+V", 0, QApplication::UnicodeUTF8));
        buttonOutst->setText(QApplication::translate("DepositEditDialog", "Outstanding", 0, QApplication::UnicodeUTF8));
        buttonCancel->setText(QApplication::translate("DepositEditDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
        lineEditAmt->setInputMask(QApplication::translate("DepositEditDialog", "00000000.00; ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DepositEditDialog: public Ui_DepositEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPOSITEDITDIALOG_H
