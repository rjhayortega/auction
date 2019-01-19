/********************************************************************************
** Form generated from reading UI file 'displaysetupdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYSETUPDIALOG_H
#define UI_DISPLAYSETUPDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Table>
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
#include "dao/setupdao.h"

QT_BEGIN_NAMESPACE

class Ui_DisplaySetupDialog
{
public:
    QLabel *textLabel1_2;
    QLabel *textLabel1;
    QPushButton *browseButton;
    QLineEdit *devicePathEdit;
    QLabel *textLabel2;
    QLabel *textLabel2_2;
    QLabel *textLabel2_3;
    QLabel *textLabel2_3_2;
    QComboBox *stopBitCombo;
    QComboBox *parityCombo;
    QComboBox *dataBitCombo;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    QLabel *textLabel2_4_2_2_2;
    QLabel *textLabel2_4_2_2;
    QLabel *textLabel2_4_2;
    QLabel *textLabel2_4;
    QLineEdit *displayNameEdit;
    QComboBox *baudCombo;
    QSpinBox *rowsSpinBox;
    QSpinBox *baseSpinBox;
    QComboBox *transCombo;
    Q3Table *rowsTable;
    QComboBox *typeCombo;

    void setupUi(QDialog *DisplaySetupDialog)
    {
        if (DisplaySetupDialog->objectName().isEmpty())
            DisplaySetupDialog->setObjectName(QString::fromUtf8("DisplaySetupDialog"));
        DisplaySetupDialog->setWindowModality(Qt::ApplicationModal);
        DisplaySetupDialog->resize(467, 509);
        QFont font;
        font.setPointSize(13);
        DisplaySetupDialog->setFont(font);
        textLabel1_2 = new QLabel(DisplaySetupDialog);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(30, 20, 181, 30));
        textLabel1_2->setWordWrap(false);
        textLabel1 = new QLabel(DisplaySetupDialog);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(30, 90, 181, 30));
        textLabel1->setWordWrap(false);
        browseButton = new QPushButton(DisplaySetupDialog);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));
        browseButton->setGeometry(QRect(240, 120, 80, 30));
        devicePathEdit = new QLineEdit(DisplaySetupDialog);
        devicePathEdit->setObjectName(QString::fromUtf8("devicePathEdit"));
        devicePathEdit->setGeometry(QRect(30, 120, 190, 30));
        textLabel2 = new QLabel(DisplaySetupDialog);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setGeometry(QRect(30, 170, 80, 30));
        textLabel2->setWordWrap(false);
        textLabel2_2 = new QLabel(DisplaySetupDialog);
        textLabel2_2->setObjectName(QString::fromUtf8("textLabel2_2"));
        textLabel2_2->setGeometry(QRect(120, 170, 80, 30));
        textLabel2_2->setWordWrap(false);
        textLabel2_3 = new QLabel(DisplaySetupDialog);
        textLabel2_3->setObjectName(QString::fromUtf8("textLabel2_3"));
        textLabel2_3->setGeometry(QRect(210, 170, 80, 30));
        textLabel2_3->setWordWrap(false);
        textLabel2_3_2 = new QLabel(DisplaySetupDialog);
        textLabel2_3_2->setObjectName(QString::fromUtf8("textLabel2_3_2"));
        textLabel2_3_2->setGeometry(QRect(300, 170, 80, 30));
        textLabel2_3_2->setWordWrap(false);
        stopBitCombo = new QComboBox(DisplaySetupDialog);
        stopBitCombo->setObjectName(QString::fromUtf8("stopBitCombo"));
        stopBitCombo->setGeometry(QRect(300, 210, 80, 30));
        parityCombo = new QComboBox(DisplaySetupDialog);
        parityCombo->setObjectName(QString::fromUtf8("parityCombo"));
        parityCombo->setGeometry(QRect(210, 210, 80, 30));
        dataBitCombo = new QComboBox(DisplaySetupDialog);
        dataBitCombo->setObjectName(QString::fromUtf8("dataBitCombo"));
        dataBitCombo->setGeometry(QRect(120, 210, 80, 30));
        saveButton = new QPushButton(DisplaySetupDialog);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(380, 470, 80, 30));
        cancelButton = new QPushButton(DisplaySetupDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(290, 470, 80, 30));
        textLabel2_4_2_2_2 = new QLabel(DisplaySetupDialog);
        textLabel2_4_2_2_2->setObjectName(QString::fromUtf8("textLabel2_4_2_2_2"));
        textLabel2_4_2_2_2->setGeometry(QRect(410, 250, 50, 30));
        textLabel2_4_2_2_2->setWordWrap(false);
        textLabel2_4_2_2 = new QLabel(DisplaySetupDialog);
        textLabel2_4_2_2->setObjectName(QString::fromUtf8("textLabel2_4_2_2"));
        textLabel2_4_2_2->setGeometry(QRect(350, 250, 50, 30));
        textLabel2_4_2_2->setWordWrap(false);
        textLabel2_4_2 = new QLabel(DisplaySetupDialog);
        textLabel2_4_2->setObjectName(QString::fromUtf8("textLabel2_4_2"));
        textLabel2_4_2->setGeometry(QRect(230, 250, 90, 30));
        textLabel2_4_2->setWordWrap(false);
        textLabel2_4 = new QLabel(DisplaySetupDialog);
        textLabel2_4->setObjectName(QString::fromUtf8("textLabel2_4"));
        textLabel2_4->setGeometry(QRect(30, 250, 190, 21));
        textLabel2_4->setWordWrap(false);
        displayNameEdit = new QLineEdit(DisplaySetupDialog);
        displayNameEdit->setObjectName(QString::fromUtf8("displayNameEdit"));
        displayNameEdit->setGeometry(QRect(30, 50, 290, 31));
        baudCombo = new QComboBox(DisplaySetupDialog);
        baudCombo->setObjectName(QString::fromUtf8("baudCombo"));
        baudCombo->setGeometry(QRect(30, 210, 80, 30));
        rowsSpinBox = new QSpinBox(DisplaySetupDialog);
        rowsSpinBox->setObjectName(QString::fromUtf8("rowsSpinBox"));
        rowsSpinBox->setGeometry(QRect(410, 280, 50, 30));
        baseSpinBox = new QSpinBox(DisplaySetupDialog);
        baseSpinBox->setObjectName(QString::fromUtf8("baseSpinBox"));
        baseSpinBox->setGeometry(QRect(350, 280, 50, 30));
        baseSpinBox->setMaximum(256);
        transCombo = new QComboBox(DisplaySetupDialog);
        transCombo->setObjectName(QString::fromUtf8("transCombo"));
        transCombo->setGeometry(QRect(230, 280, 110, 30));
        rowsTable = new Q3Table(DisplaySetupDialog);
        rowsTable->setObjectName(QString::fromUtf8("rowsTable"));
        rowsTable->setGeometry(QRect(30, 320, 430, 140));
        rowsTable->setProperty("numRows", QVariant(0));
        rowsTable->setProperty("numCols", QVariant(3));
        typeCombo = new QComboBox(DisplaySetupDialog);
        typeCombo->setObjectName(QString::fromUtf8("typeCombo"));
        typeCombo->setGeometry(QRect(30, 280, 190, 30));

        retranslateUi(DisplaySetupDialog);

        QMetaObject::connectSlotsByName(DisplaySetupDialog);
    } // setupUi

    void retranslateUi(QDialog *DisplaySetupDialog)
    {
        DisplaySetupDialog->setWindowTitle(QApplication::translate("DisplaySetupDialog", "Setup Display", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("DisplaySetupDialog", "Name", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("DisplaySetupDialog", "Device:", 0, QApplication::UnicodeUTF8));
        browseButton->setText(QApplication::translate("DisplaySetupDialog", "&Browse", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("DisplaySetupDialog", "Baud", 0, QApplication::UnicodeUTF8));
        textLabel2_2->setText(QApplication::translate("DisplaySetupDialog", "Data Bits", 0, QApplication::UnicodeUTF8));
        textLabel2_3->setText(QApplication::translate("DisplaySetupDialog", "Parity", 0, QApplication::UnicodeUTF8));
        textLabel2_3_2->setText(QApplication::translate("DisplaySetupDialog", "Stop Bits", 0, QApplication::UnicodeUTF8));
        stopBitCombo->clear();
        stopBitCombo->insertItems(0, QStringList()
         << QApplication::translate("DisplaySetupDialog", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "2", 0, QApplication::UnicodeUTF8)
        );
        parityCombo->clear();
        parityCombo->insertItems(0, QStringList()
         << QApplication::translate("DisplaySetupDialog", "None", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "Odd", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "Even", 0, QApplication::UnicodeUTF8)
        );
        dataBitCombo->clear();
        dataBitCombo->insertItems(0, QStringList()
         << QApplication::translate("DisplaySetupDialog", "5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "8", 0, QApplication::UnicodeUTF8)
        );
        saveButton->setText(QApplication::translate("DisplaySetupDialog", "Save", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("DisplaySetupDialog", "Ca&ncel", 0, QApplication::UnicodeUTF8));
        textLabel2_4_2_2_2->setText(QApplication::translate("DisplaySetupDialog", "Rows", 0, QApplication::UnicodeUTF8));
        textLabel2_4_2_2->setText(QApplication::translate("DisplaySetupDialog", "Base", 0, QApplication::UnicodeUTF8));
        textLabel2_4_2->setText(QApplication::translate("DisplaySetupDialog", "Trans", 0, QApplication::UnicodeUTF8));
        textLabel2_4->setText(QApplication::translate("DisplaySetupDialog", "Type", 0, QApplication::UnicodeUTF8));
        baudCombo->clear();
        baudCombo->insertItems(0, QStringList()
         << QApplication::translate("DisplaySetupDialog", "50", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "75", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "110", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "134", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "150", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "300", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "1200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "1800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "2400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "4800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "9600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "19200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "38400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "57600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "115200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "230400", 0, QApplication::UnicodeUTF8)
        );
        transCombo->clear();
        transCombo->insertItems(0, QStringList()
         << QApplication::translate("DisplaySetupDialog", "Current", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "Previous", 0, QApplication::UnicodeUTF8)
        );
        typeCombo->clear();
        typeCombo->insertItems(0, QStringList()
         << QApplication::translate("DisplaySetupDialog", "Null Display", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "TD3000 serial port", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "TD3200 serial port", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "TD3000u USB port", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "LT9900u USB port", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "unused", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "unused", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "unused", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "unused", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DisplaySetupDialog", "Video Display", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class DisplaySetupDialog: public Ui_DisplaySetupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYSETUPDIALOG_H
