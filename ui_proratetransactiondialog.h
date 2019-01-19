/********************************************************************************
** Form generated from reading UI file 'proratetransactiondialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRORATETRANSACTIONDIALOG_H
#define UI_PRORATETRANSACTIONDIALOG_H

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
#include "types/prorate.h"
#include "types/transaction.h"

QT_BEGIN_NAMESPACE

class Ui_ProrateTransactionDialog
{
public:
    Q3Table *transTable;
    QPushButton *okButton;

    void setupUi(QDialog *ProrateTransactionDialog)
    {
        if (ProrateTransactionDialog->objectName().isEmpty())
            ProrateTransactionDialog->setObjectName(QString::fromUtf8("ProrateTransactionDialog"));
        ProrateTransactionDialog->setWindowModality(Qt::ApplicationModal);
        ProrateTransactionDialog->resize(512, 405);
        QFont font;
        font.setPointSize(13);
        ProrateTransactionDialog->setFont(font);
        transTable = new Q3Table(ProrateTransactionDialog);
        transTable->setObjectName(QString::fromUtf8("transTable"));
        transTable->setGeometry(QRect(10, 10, 490, 330));
        transTable->setNumRows(0);
        transTable->setNumCols(4);
        transTable->setShowGrid(true);
        transTable->setSelectionMode(Q3Table::Single);
        okButton = new QPushButton(ProrateTransactionDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(401, 360, 100, 30));

        retranslateUi(ProrateTransactionDialog);

        QMetaObject::connectSlotsByName(ProrateTransactionDialog);
    } // setupUi

    void retranslateUi(QDialog *ProrateTransactionDialog)
    {
        ProrateTransactionDialog->setWindowTitle(QApplication::translate("ProrateTransactionDialog", "Choose Transactions To Include", 0, QApplication::UnicodeUTF8));
        transTable->horizontalHeader()->setLabel(0, QApplication::translate("ProrateTransactionDialog", "X", 0, QApplication::UnicodeUTF8));
        transTable->horizontalHeader()->setLabel(1, QApplication::translate("ProrateTransactionDialog", "Description", 0, QApplication::UnicodeUTF8));
        transTable->horizontalHeader()->setLabel(2, QApplication::translate("ProrateTransactionDialog", "Desired Head", 0, QApplication::UnicodeUTF8));
        transTable->horizontalHeader()->setLabel(3, QApplication::translate("ProrateTransactionDialog", "Available Head", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("ProrateTransactionDialog", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ProrateTransactionDialog: public Ui_ProrateTransactionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRORATETRANSACTIONDIALOG_H
