/********************************************************************************
** Form generated from reading UI file 'chargecreditdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARGECREDITDIALOG_H
#define UI_CHARGECREDITDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Table>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include "dao/chargedao.h"
#include "types/invoice.h"

QT_BEGIN_NAMESPACE

class Ui_ChargeCreditDialog
{
public:
    QPushButton *acceptButton;
    QPushButton *cancelButton;
    Q3Table *adjustmentTable;

    void setupUi(QDialog *ChargeCreditDialog)
    {
        if (ChargeCreditDialog->objectName().isEmpty())
            ChargeCreditDialog->setObjectName(QString::fromUtf8("ChargeCreditDialog"));
        ChargeCreditDialog->setWindowModality(Qt::ApplicationModal);
        ChargeCreditDialog->resize(429, 402);
        QFont font;
        font.setPointSize(13);
        ChargeCreditDialog->setFont(font);
        acceptButton = new QPushButton(ChargeCreditDialog);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));
        acceptButton->setGeometry(QRect(340, 350, 80, 31));
        cancelButton = new QPushButton(ChargeCreditDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(250, 350, 80, 31));
        adjustmentTable = new Q3Table(ChargeCreditDialog);
        adjustmentTable->setObjectName(QString::fromUtf8("adjustmentTable"));
        adjustmentTable->setGeometry(QRect(10, 10, 410, 330));
        adjustmentTable->setNumRows(0);
        adjustmentTable->setNumCols(3);

        retranslateUi(ChargeCreditDialog);

        QMetaObject::connectSlotsByName(ChargeCreditDialog);
    } // setupUi

    void retranslateUi(QDialog *ChargeCreditDialog)
    {
        ChargeCreditDialog->setWindowTitle(QApplication::translate("ChargeCreditDialog", "Credit Charges", 0, QApplication::UnicodeUTF8));
        acceptButton->setText(QApplication::translate("ChargeCreditDialog", "Accept", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("ChargeCreditDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        adjustmentTable->horizontalHeader()->setLabel(0, QApplication::translate("ChargeCreditDialog", "Description", 0, QApplication::UnicodeUTF8));
        adjustmentTable->horizontalHeader()->setLabel(1, QApplication::translate("ChargeCreditDialog", "Adjustment", 0, QApplication::UnicodeUTF8));
        adjustmentTable->horizontalHeader()->setLabel(2, QApplication::translate("ChargeCreditDialog", "Adj. Total", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ChargeCreditDialog: public Ui_ChargeCreditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARGECREDITDIALOG_H
