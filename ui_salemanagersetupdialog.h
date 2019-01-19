/********************************************************************************
** Form generated from reading UI file 'salemanagersetupdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SALEMANAGERSETUPDIALOG_H
#define UI_SALEMANAGERSETUPDIALOG_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include "dao/setupdao.h"

QT_BEGIN_NAMESPACE

class Ui_SaleManagerSetupDialog
{
public:
    QPushButton *cancelButton;
    QPushButton *saveButton;
    QLabel *oldPasswordLabel;
    QLineEdit *oldPasswordEdit;
    QLabel *newPasswordLabel;
    QLineEdit *newPasswordEdit;
    QLineEdit *verifyPasswordEdit;
    QLabel *verifyPasswordLabel;
    QLabel *errMsgLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SaleManagerSetupDialog)
    {
        if (SaleManagerSetupDialog->objectName().isEmpty())
            SaleManagerSetupDialog->setObjectName(QString::fromUtf8("SaleManagerSetupDialog"));
        SaleManagerSetupDialog->setWindowModality(Qt::ApplicationModal);
        SaleManagerSetupDialog->resize(380, 348);
        QFont font;
        font.setPointSize(13);
        SaleManagerSetupDialog->setFont(font);
        SaleManagerSetupDialog->setFocusPolicy(Qt::TabFocus);
        cancelButton = new QPushButton(SaleManagerSetupDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(10, 340, 80, 30));
        saveButton = new QPushButton(SaleManagerSetupDialog);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(290, 340, 80, 30));
        oldPasswordLabel = new QLabel(SaleManagerSetupDialog);
        oldPasswordLabel->setObjectName(QString::fromUtf8("oldPasswordLabel"));
        oldPasswordLabel->setGeometry(QRect(50, 40, 121, 30));
        oldPasswordLabel->setWordWrap(false);
        oldPasswordEdit = new QLineEdit(SaleManagerSetupDialog);
        oldPasswordEdit->setObjectName(QString::fromUtf8("oldPasswordEdit"));
        oldPasswordEdit->setGeometry(QRect(170, 40, 180, 30));
        oldPasswordEdit->setFocusPolicy(Qt::TabFocus);
        oldPasswordEdit->setEchoMode(QLineEdit::Password);
        newPasswordLabel = new QLabel(SaleManagerSetupDialog);
        newPasswordLabel->setObjectName(QString::fromUtf8("newPasswordLabel"));
        newPasswordLabel->setGeometry(QRect(30, 160, 131, 30));
        newPasswordLabel->setWordWrap(false);
        newPasswordEdit = new QLineEdit(SaleManagerSetupDialog);
        newPasswordEdit->setObjectName(QString::fromUtf8("newPasswordEdit"));
        newPasswordEdit->setGeometry(QRect(170, 160, 180, 30));
        newPasswordEdit->setFocusPolicy(Qt::TabFocus);
        newPasswordEdit->setEchoMode(QLineEdit::Password);
        verifyPasswordEdit = new QLineEdit(SaleManagerSetupDialog);
        verifyPasswordEdit->setObjectName(QString::fromUtf8("verifyPasswordEdit"));
        verifyPasswordEdit->setGeometry(QRect(170, 210, 180, 30));
        verifyPasswordEdit->setFocusPolicy(Qt::TabFocus);
        verifyPasswordEdit->setEchoMode(QLineEdit::Password);
        verifyPasswordLabel = new QLabel(SaleManagerSetupDialog);
        verifyPasswordLabel->setObjectName(QString::fromUtf8("verifyPasswordLabel"));
        verifyPasswordLabel->setGeometry(QRect(20, 210, 141, 30));
        verifyPasswordLabel->setWordWrap(false);
        errMsgLabel = new QLabel(SaleManagerSetupDialog);
        errMsgLabel->setObjectName(QString::fromUtf8("errMsgLabel"));
        errMsgLabel->setGeometry(QRect(30, 100, 321, 31));
        buttonBox = new QDialogButtonBox(SaleManagerSetupDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(180, 300, 166, 22));
        buttonBox->setFocusPolicy(Qt::TabFocus);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);
        QWidget::setTabOrder(oldPasswordEdit, newPasswordEdit);
        QWidget::setTabOrder(newPasswordEdit, verifyPasswordEdit);
        QWidget::setTabOrder(verifyPasswordEdit, buttonBox);

        retranslateUi(SaleManagerSetupDialog);

        QMetaObject::connectSlotsByName(SaleManagerSetupDialog);
    } // setupUi

    void retranslateUi(QDialog *SaleManagerSetupDialog)
    {
        SaleManagerSetupDialog->setWindowTitle(QApplication::translate("SaleManagerSetupDialog", "Sale Manager Password Change", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("SaleManagerSetupDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("SaleManagerSetupDialog", "Save", 0, QApplication::UnicodeUTF8));
        oldPasswordLabel->setText(QApplication::translate("SaleManagerSetupDialog", "Old Password:", 0, QApplication::UnicodeUTF8));
        newPasswordLabel->setText(QApplication::translate("SaleManagerSetupDialog", "New Password:", 0, QApplication::UnicodeUTF8));
        verifyPasswordLabel->setText(QApplication::translate("SaleManagerSetupDialog", "Verify Password:", 0, QApplication::UnicodeUTF8));
        errMsgLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SaleManagerSetupDialog: public Ui_SaleManagerSetupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SALEMANAGERSETUPDIALOG_H
