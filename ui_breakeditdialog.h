/********************************************************************************
** Form generated from reading UI file 'breakeditdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BREAKEDITDIALOG_H
#define UI_BREAKEDITDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Table>
#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include "dao/animalcodedao.h"
#include "dao/commissiondao.h"

QT_BEGIN_NAMESPACE

class Ui_BreakEditDialog
{
public:
    QLabel *textLabel1_2;
    QLabel *textLabel2;
    QPushButton *cancelButton;
    QPushButton *okButton;
    Q3TextEdit *commissionDescripText;
    Q3Table *breakTable;

    void setupUi(QDialog *BreakEditDialog)
    {
        if (BreakEditDialog->objectName().isEmpty())
            BreakEditDialog->setObjectName(QString::fromUtf8("BreakEditDialog"));
        BreakEditDialog->setWindowModality(Qt::ApplicationModal);
        BreakEditDialog->resize(722, 545);
        QFont font;
        font.setPointSize(13);
        BreakEditDialog->setFont(font);
        BreakEditDialog->setMouseTracking(true);
        textLabel1_2 = new QLabel(BreakEditDialog);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(10, 20, 700, 124));
        textLabel1_2->setWordWrap(false);
        textLabel2 = new QLabel(BreakEditDialog);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setGeometry(QRect(290, 170, 420, 31));
        textLabel2->setWordWrap(false);
        cancelButton = new QPushButton(BreakEditDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(500, 500, 101, 31));
        okButton = new QPushButton(BreakEditDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(610, 500, 101, 31));
        commissionDescripText = new Q3TextEdit(BreakEditDialog);
        commissionDescripText->setObjectName(QString::fromUtf8("commissionDescripText"));
        commissionDescripText->setGeometry(QRect(400, 221, 310, 270));
        commissionDescripText->setReadOnly(true);
        breakTable = new Q3Table(BreakEditDialog);
        breakTable->setObjectName(QString::fromUtf8("breakTable"));
        breakTable->setGeometry(QRect(20, 220, 370, 270));
        breakTable->setNumRows(11);
        breakTable->setNumCols(5);

        retranslateUi(BreakEditDialog);

        QMetaObject::connectSlotsByName(BreakEditDialog);
    } // setupUi

    void retranslateUi(QDialog *BreakEditDialog)
    {
        BreakEditDialog->setWindowTitle(QApplication::translate("BreakEditDialog", "Commissions", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("BreakEditDialog", "<table border=0 width=\"100%\">\n"
"<tr><th colspan=2 align=\"center\">Variables</th><th></th><th colspan=2 align=\"center\">Operators</th></tr>\n"
"<tr><td>H => Head</td><td>T => Total</td><td></td><td>+ => add</td><td>- => subtract</td></tr>\n"
"<tr><td>P => Price</td><td>W => Weight</td><td></td><td>* => multiply</td><td>/ => divide</td></tr>\n"
"</table>", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("BreakEditDialog", "Commisson Applies to:", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("BreakEditDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
        cancelButton->setShortcut(QApplication::translate("BreakEditDialog", "Alt+C", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("BreakEditDialog", "&Ok", 0, QApplication::UnicodeUTF8));
        okButton->setShortcut(QApplication::translate("BreakEditDialog", "Alt+O", 0, QApplication::UnicodeUTF8));
        breakTable->horizontalHeader()->setLabel(0, QApplication::translate("BreakEditDialog", "Expression", 0, QApplication::UnicodeUTF8));
        breakTable->horizontalHeader()->setLabel(1, QApplication::translate("BreakEditDialog", "Break Start", 0, QApplication::UnicodeUTF8));
        breakTable->horizontalHeader()->setLabel(2, QApplication::translate("BreakEditDialog", "-", 0, QApplication::UnicodeUTF8));
        breakTable->horizontalHeader()->setLabel(3, QApplication::translate("BreakEditDialog", "Min", 0, QApplication::UnicodeUTF8));
        breakTable->horizontalHeader()->setLabel(4, QApplication::translate("BreakEditDialog", "Max", 0, QApplication::UnicodeUTF8));
        breakTable->verticalHeader()->setLabel(0, QApplication::translate("BreakEditDialog", "0", 0, QApplication::UnicodeUTF8));
        breakTable->verticalHeader()->setLabel(1, QApplication::translate("BreakEditDialog", "1", 0, QApplication::UnicodeUTF8));
        breakTable->verticalHeader()->setLabel(2, QApplication::translate("BreakEditDialog", "2", 0, QApplication::UnicodeUTF8));
        breakTable->verticalHeader()->setLabel(3, QApplication::translate("BreakEditDialog", "3", 0, QApplication::UnicodeUTF8));
        breakTable->verticalHeader()->setLabel(4, QApplication::translate("BreakEditDialog", "4", 0, QApplication::UnicodeUTF8));
        breakTable->verticalHeader()->setLabel(5, QApplication::translate("BreakEditDialog", "5", 0, QApplication::UnicodeUTF8));
        breakTable->verticalHeader()->setLabel(6, QApplication::translate("BreakEditDialog", "6", 0, QApplication::UnicodeUTF8));
        breakTable->verticalHeader()->setLabel(7, QApplication::translate("BreakEditDialog", "7", 0, QApplication::UnicodeUTF8));
        breakTable->verticalHeader()->setLabel(8, QApplication::translate("BreakEditDialog", "8", 0, QApplication::UnicodeUTF8));
        breakTable->verticalHeader()->setLabel(9, QApplication::translate("BreakEditDialog", "9", 0, QApplication::UnicodeUTF8));
        breakTable->verticalHeader()->setLabel(10, QApplication::translate("BreakEditDialog", "10", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BreakEditDialog: public Ui_BreakEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BREAKEDITDIALOG_H
