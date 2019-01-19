/********************************************************************************
** Form generated from reading UI file 'printersetupdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINTERSETUPDIALOG_H
#define UI_PRINTERSETUPDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Table>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <Qt3Support/Q3Process>
#include "dao/printerdao.h"

QT_BEGIN_NAMESPACE

class Ui_PrinterSetupDialog
{
public:
    QPushButton *refreshButton;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    QCheckBox *CondensedFontCheckBox;
    Q3Table *defaultPrinterTable;
    Q3Table *printerMapTable;

    void setupUi(QDialog *PrinterSetupDialog)
    {
        if (PrinterSetupDialog->objectName().isEmpty())
            PrinterSetupDialog->setObjectName(QString::fromUtf8("PrinterSetupDialog"));
        PrinterSetupDialog->setWindowModality(Qt::ApplicationModal);
        PrinterSetupDialog->resize(425, 539);
        QFont font;
        font.setPointSize(13);
        PrinterSetupDialog->setFont(font);
        refreshButton = new QPushButton(PrinterSetupDialog);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));
        refreshButton->setGeometry(QRect(10, 500, 180, 30));
        saveButton = new QPushButton(PrinterSetupDialog);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(310, 500, 100, 30));
        cancelButton = new QPushButton(PrinterSetupDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(200, 500, 100, 30));
        CondensedFontCheckBox = new QCheckBox(PrinterSetupDialog);
        CondensedFontCheckBox->setObjectName(QString::fromUtf8("CondensedFontCheckBox"));
        CondensedFontCheckBox->setGeometry(QRect(10, 460, 330, 28));
        defaultPrinterTable = new Q3Table(PrinterSetupDialog);
        defaultPrinterTable->setObjectName(QString::fromUtf8("defaultPrinterTable"));
        defaultPrinterTable->setGeometry(QRect(10, 290, 400, 160));
        defaultPrinterTable->setProperty("numRows", QVariant(6));
        defaultPrinterTable->setProperty("numCols", QVariant(2));
        printerMapTable = new Q3Table(PrinterSetupDialog);
        printerMapTable->setObjectName(QString::fromUtf8("printerMapTable"));
        printerMapTable->setGeometry(QRect(20, 10, 270, 261));
        printerMapTable->setProperty("numRows", QVariant(10));
        printerMapTable->setProperty("numCols", QVariant(2));

        retranslateUi(PrinterSetupDialog);

        QMetaObject::connectSlotsByName(PrinterSetupDialog);
    } // setupUi

    void retranslateUi(QDialog *PrinterSetupDialog)
    {
        PrinterSetupDialog->setWindowTitle(QApplication::translate("PrinterSetupDialog", "Setup Printers", 0, QApplication::UnicodeUTF8));
        refreshButton->setText(QApplication::translate("PrinterSetupDialog", "Refresh Printer &List", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("PrinterSetupDialog", "Save", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("PrinterSetupDialog", "C&ancel", 0, QApplication::UnicodeUTF8));
        CondensedFontCheckBox->setText(QApplication::translate("PrinterSetupDialog", "Print ever&ything in condensed font.", 0, QApplication::UnicodeUTF8));
        CondensedFontCheckBox->setShortcut(QApplication::translate("PrinterSetupDialog", "Alt+Y", 0, QApplication::UnicodeUTF8));
        defaultPrinterTable->horizontalHeader()->setLabel(0, QApplication::translate("PrinterSetupDialog", "Station Name", 0, QApplication::UnicodeUTF8));
        defaultPrinterTable->horizontalHeader()->setLabel(1, QApplication::translate("PrinterSetupDialog", "Default Printer", 0, QApplication::UnicodeUTF8));
        defaultPrinterTable->verticalHeader()->setLabel(0, QApplication::translate("PrinterSetupDialog", "Server ", 0, QApplication::UnicodeUTF8));
        defaultPrinterTable->verticalHeader()->setLabel(1, QApplication::translate("PrinterSetupDialog", "Station 1", 0, QApplication::UnicodeUTF8));
        defaultPrinterTable->verticalHeader()->setLabel(2, QApplication::translate("PrinterSetupDialog", "Station 2", 0, QApplication::UnicodeUTF8));
        defaultPrinterTable->verticalHeader()->setLabel(3, QApplication::translate("PrinterSetupDialog", "Station 3", 0, QApplication::UnicodeUTF8));
        defaultPrinterTable->verticalHeader()->setLabel(4, QApplication::translate("PrinterSetupDialog", "Station 4", 0, QApplication::UnicodeUTF8));
        defaultPrinterTable->verticalHeader()->setLabel(5, QApplication::translate("PrinterSetupDialog", "Station 5", 0, QApplication::UnicodeUTF8));
        printerMapTable->horizontalHeader()->setLabel(0, QApplication::translate("PrinterSetupDialog", "Station", 0, QApplication::UnicodeUTF8));
        printerMapTable->verticalHeader()->setLabel(0, QApplication::translate("PrinterSetupDialog", "Seller Invoice", 0, QApplication::UnicodeUTF8));
        printerMapTable->verticalHeader()->setLabel(1, QApplication::translate("PrinterSetupDialog", "Buyer Invoice", 0, QApplication::UnicodeUTF8));
        printerMapTable->verticalHeader()->setLabel(2, QApplication::translate("PrinterSetupDialog", "Check", 0, QApplication::UnicodeUTF8));
        printerMapTable->verticalHeader()->setLabel(3, QApplication::translate("PrinterSetupDialog", "Reports", 0, QApplication::UnicodeUTF8));
        printerMapTable->verticalHeader()->setLabel(4, QApplication::translate("PrinterSetupDialog", "Ticket", 0, QApplication::UnicodeUTF8));
        printerMapTable->verticalHeader()->setLabel(5, QApplication::translate("PrinterSetupDialog", "Scale", 0, QApplication::UnicodeUTF8));
        printerMapTable->verticalHeader()->setLabel(6, QApplication::translate("PrinterSetupDialog", "Check In", 0, QApplication::UnicodeUTF8));
        printerMapTable->verticalHeader()->setLabel(7, QApplication::translate("PrinterSetupDialog", "Check In Office", 0, QApplication::UnicodeUTF8));
        printerMapTable->verticalHeader()->setLabel(8, QApplication::translate("PrinterSetupDialog", "Loadout", 0, QApplication::UnicodeUTF8));
        printerMapTable->verticalHeader()->setLabel(9, QApplication::translate("PrinterSetupDialog", "Second copy", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PrinterSetupDialog: public Ui_PrinterSetupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINTERSETUPDIALOG_H
