/********************************************************************************
** Form generated from reading UI file 'truckerchecksdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRUCKERCHECKSDIALOG_H
#define UI_TRUCKERCHECKSDIALOG_H

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
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include "dao/checkdao.h"
#include "dao/invoicedao.h"
#include "dao/setupdao.h"
#include "dao/truckingrecorddao.h"
#include "lineprinter.h"
#include "reports/textcheck.h"
#include "reports/truckercheckreport.h"
#include "types/truckingrecord.h"

QT_BEGIN_NAMESPACE

class Ui_TruckerChecksDialog
{
public:
    QLabel *textLabel1;
    QPushButton *cancelButton;
    QPushButton *printButton;
    QLabel *textLabel1_2;
    Q3ListBox *buyerTruckerList;
    Q3ListBox *sellerTruckerList;
    QCheckBox *reportCheckBox;

    void setupUi(QDialog *TruckerChecksDialog)
    {
        if (TruckerChecksDialog->objectName().isEmpty())
            TruckerChecksDialog->setObjectName(QString::fromUtf8("TruckerChecksDialog"));
        TruckerChecksDialog->setWindowModality(Qt::ApplicationModal);
        TruckerChecksDialog->resize(541, 546);
        QFont font;
        font.setPointSize(13);
        TruckerChecksDialog->setFont(font);
        textLabel1 = new QLabel(TruckerChecksDialog);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(10, 10, 520, 31));
        textLabel1->setWordWrap(false);
        cancelButton = new QPushButton(TruckerChecksDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(240, 510, 140, 30));
        printButton = new QPushButton(TruckerChecksDialog);
        printButton->setObjectName(QString::fromUtf8("printButton"));
        printButton->setGeometry(QRect(390, 510, 140, 30));
        textLabel1_2 = new QLabel(TruckerChecksDialog);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(10, 360, 520, 31));
        textLabel1_2->setWordWrap(false);
        buyerTruckerList = new Q3ListBox(TruckerChecksDialog);
        buyerTruckerList->setObjectName(QString::fromUtf8("buyerTruckerList"));
        buyerTruckerList->setGeometry(QRect(10, 400, 520, 100));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bitstream Vera Sans Mono"));
        font1.setPointSize(13);
        buyerTruckerList->setFont(font1);
        buyerTruckerList->setSelectionMode(Q3ListBox::Multi);
        sellerTruckerList = new Q3ListBox(TruckerChecksDialog);
        sellerTruckerList->setObjectName(QString::fromUtf8("sellerTruckerList"));
        sellerTruckerList->setGeometry(QRect(10, 50, 520, 300));
        sellerTruckerList->setFont(font1);
        sellerTruckerList->setSelectionMode(Q3ListBox::Multi);
        reportCheckBox = new QCheckBox(TruckerChecksDialog);
        reportCheckBox->setObjectName(QString::fromUtf8("reportCheckBox"));
        reportCheckBox->setGeometry(QRect(10, 510, 221, 31));
        reportCheckBox->setChecked(true);

        retranslateUi(TruckerChecksDialog);

        QMetaObject::connectSlotsByName(TruckerChecksDialog);
    } // setupUi

    void retranslateUi(QDialog *TruckerChecksDialog)
    {
        TruckerChecksDialog->setWindowTitle(QApplication::translate("TruckerChecksDialog", "Print Trucker Checks", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("TruckerChecksDialog", "<p align=\"center\">Seller Truckers</p>", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("TruckerChecksDialog", "Exit", 0, QApplication::UnicodeUTF8));
        printButton->setText(QApplication::translate("TruckerChecksDialog", "Print Selected", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("TruckerChecksDialog", "<p align=\"center\">Buyer Truckers</p>", 0, QApplication::UnicodeUTF8));
        reportCheckBox->setText(QApplication::translate("TruckerChecksDialog", "Print A Report", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TruckerChecksDialog: public Ui_TruckerChecksDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRUCKERCHECKSDIALOG_H
