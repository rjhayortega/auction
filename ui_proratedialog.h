/********************************************************************************
** Form generated from reading UI file 'proratedialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRORATEDIALOG_H
#define UI_PRORATEDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3Header>
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
#include <QtGui/QPushButton>
#include "dao/proratedao.h"
#include "types/checkfactory.h"
#include "types/invoice.h"
#include "types/prorate.h"

QT_BEGIN_NAMESPACE

class Ui_ProrateDialog
{
public:
    QLabel *primaryPayee;
    QLabel *primaryShare;
    QLabel *primaryCharge;
    QLabel *textLabel2;
    QPushButton *buttonDelete;
    QPushButton *buttonNew;
    Q3Table *prorateTable;
    QPushButton *buttonCancel;
    QPushButton *buttonOk;
    QCheckBox *chkShareChgs;
    QComboBox *comboProrateMode;

    void setupUi(QDialog *ProrateDialog)
    {
        if (ProrateDialog->objectName().isEmpty())
            ProrateDialog->setObjectName(QString::fromUtf8("ProrateDialog"));
        ProrateDialog->setWindowModality(Qt::ApplicationModal);
        ProrateDialog->resize(548, 568);
        QFont font;
        font.setPointSize(13);
        ProrateDialog->setFont(font);
        ProrateDialog->setSizeGripEnabled(true);
        primaryPayee = new QLabel(ProrateDialog);
        primaryPayee->setObjectName(QString::fromUtf8("primaryPayee"));
        primaryPayee->setGeometry(QRect(40, 60, 210, 30));
        primaryPayee->setWordWrap(false);
        primaryShare = new QLabel(ProrateDialog);
        primaryShare->setObjectName(QString::fromUtf8("primaryShare"));
        primaryShare->setGeometry(QRect(250, 60, 101, 30));
        primaryShare->setWordWrap(false);
        primaryCharge = new QLabel(ProrateDialog);
        primaryCharge->setObjectName(QString::fromUtf8("primaryCharge"));
        primaryCharge->setGeometry(QRect(370, 60, 101, 30));
        primaryCharge->setWordWrap(false);
        textLabel2 = new QLabel(ProrateDialog);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setGeometry(QRect(13, 10, 130, 30));
        textLabel2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2->setWordWrap(false);
        buttonDelete = new QPushButton(ProrateDialog);
        buttonDelete->setObjectName(QString::fromUtf8("buttonDelete"));
        buttonDelete->setGeometry(QRect(20, 100, 100, 30));
        buttonDelete->setAutoDefault(true);
        buttonDelete->setDefault(true);
        buttonNew = new QPushButton(ProrateDialog);
        buttonNew->setObjectName(QString::fromUtf8("buttonNew"));
        buttonNew->setGeometry(QRect(430, 100, 100, 30));
        buttonNew->setAutoDefault(true);
        buttonNew->setDefault(true);
        prorateTable = new Q3Table(ProrateDialog);
        prorateTable->setObjectName(QString::fromUtf8("prorateTable"));
        prorateTable->setGeometry(QRect(20, 150, 515, 350));
        prorateTable->setFocusPolicy(Qt::ClickFocus);
        prorateTable->setNumRows(0);
        prorateTable->setNumCols(4);
        prorateTable->setSelectionMode(Q3Table::Single);
        buttonCancel = new QPushButton(ProrateDialog);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setGeometry(QRect(320, 520, 100, 30));
        buttonCancel->setAutoDefault(true);
        buttonOk = new QPushButton(ProrateDialog);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setGeometry(QRect(430, 520, 100, 30));
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);
        chkShareChgs = new QCheckBox(ProrateDialog);
        chkShareChgs->setObjectName(QString::fromUtf8("chkShareChgs"));
        chkShareChgs->setGeometry(QRect(330, 10, 200, 30));
        comboProrateMode = new QComboBox(ProrateDialog);
        comboProrateMode->setObjectName(QString::fromUtf8("comboProrateMode"));
        comboProrateMode->setGeometry(QRect(150, 10, 160, 30));

        retranslateUi(ProrateDialog);

        QMetaObject::connectSlotsByName(ProrateDialog);
    } // setupUi

    void retranslateUi(QDialog *ProrateDialog)
    {
        ProrateDialog->setWindowTitle(QApplication::translate("ProrateDialog", "Prorate Checks", 0, QApplication::UnicodeUTF8));
        primaryPayee->setText(QString());
        primaryShare->setText(QString());
        primaryCharge->setText(QString());
        textLabel2->setText(QApplication::translate("ProrateDialog", "Prorate By:", 0, QApplication::UnicodeUTF8));
        buttonDelete->setText(QApplication::translate("ProrateDialog", "Delete", 0, QApplication::UnicodeUTF8));
        buttonDelete->setShortcut(QString());
        buttonNew->setText(QApplication::translate("ProrateDialog", "New", 0, QApplication::UnicodeUTF8));
        buttonNew->setShortcut(QString());
        prorateTable->horizontalHeader()->setLabel(0, QApplication::translate("ProrateDialog", "Payee", 0, QApplication::UnicodeUTF8));
        prorateTable->horizontalHeader()->setLabel(1, QApplication::translate("ProrateDialog", "Values", 0, QApplication::UnicodeUTF8));
        prorateTable->horizontalHeader()->setLabel(2, QApplication::translate("ProrateDialog", "Share", 0, QApplication::UnicodeUTF8));
        prorateTable->horizontalHeader()->setLabel(3, QApplication::translate("ProrateDialog", "Charges", 0, QApplication::UnicodeUTF8));
        buttonCancel->setText(QApplication::translate("ProrateDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
        buttonOk->setText(QApplication::translate("ProrateDialog", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QApplication::translate("ProrateDialog", "Alt+O", 0, QApplication::UnicodeUTF8));
        chkShareChgs->setText(QApplication::translate("ProrateDialog", "Share Charges?", 0, QApplication::UnicodeUTF8));
        comboProrateMode->clear();
        comboProrateMode->insertItems(0, QStringList()
         << QApplication::translate("ProrateDialog", "Percentage", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ProrateDialog", "Sex", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ProrateDialog", "Transaction", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ProrateDialog", "Head", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ProrateDialog", "Flat Amount", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class ProrateDialog: public Ui_ProrateDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRORATEDIALOG_H
