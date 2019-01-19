/********************************************************************************
** Form generated from reading UI file 'buyerchecksdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUYERCHECKSDIALOG_H
#define UI_BUYERCHECKSDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3ListBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include "dao/checkdao.h"
#include "dao/commissiondao.h"
#include "dao/invoicedao.h"
#include "dao/printerdao.h"
#include "dao/setupdao.h"
#include "reports/buyercheckreport.h"
#include "reports/textcheck.h"
#include "types/invoice.h"

QT_BEGIN_NAMESPACE

class Ui_BuyerChecksDialog
{
public:
    QPushButton *printButton;
    QPushButton *cancelButton;
    Q3ListBox *buyerList;
    QCheckBox *reportCheckBox;

    void setupUi(QDialog *BuyerChecksDialog)
    {
        if (BuyerChecksDialog->objectName().isEmpty())
            BuyerChecksDialog->setObjectName(QString::fromUtf8("BuyerChecksDialog"));
        BuyerChecksDialog->setWindowModality(Qt::ApplicationModal);
        BuyerChecksDialog->resize(529, 521);
        QFont font;
        font.setPointSize(13);
        BuyerChecksDialog->setFont(font);
        printButton = new QPushButton(BuyerChecksDialog);
        printButton->setObjectName(QString::fromUtf8("printButton"));
        printButton->setGeometry(QRect(430, 480, 90, 30));
        cancelButton = new QPushButton(BuyerChecksDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(330, 480, 90, 30));
        buyerList = new Q3ListBox(BuyerChecksDialog);
        buyerList->setObjectName(QString::fromUtf8("buyerList"));
        buyerList->setGeometry(QRect(10, 20, 510, 450));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bitstream Vera Sans Mono"));
        font1.setPointSize(13);
        buyerList->setFont(font1);
        buyerList->setSelectionMode(Q3ListBox::Multi);
        reportCheckBox = new QCheckBox(BuyerChecksDialog);
        reportCheckBox->setObjectName(QString::fromUtf8("reportCheckBox"));
        reportCheckBox->setGeometry(QRect(10, 480, 311, 31));
        reportCheckBox->setChecked(true);

        retranslateUi(BuyerChecksDialog);

        QMetaObject::connectSlotsByName(BuyerChecksDialog);
    } // setupUi

    void retranslateUi(QDialog *BuyerChecksDialog)
    {
        BuyerChecksDialog->setWindowTitle(QApplication::translate("BuyerChecksDialog", "Print Buyer Checks", 0, QApplication::UnicodeUTF8));
        printButton->setText(QApplication::translate("BuyerChecksDialog", "Print", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("BuyerChecksDialog", "Exit", 0, QApplication::UnicodeUTF8));
        reportCheckBox->setText(QApplication::translate("BuyerChecksDialog", "Print A Report With The Check", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BuyerChecksDialog: public Ui_BuyerChecksDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUYERCHECKSDIALOG_H
