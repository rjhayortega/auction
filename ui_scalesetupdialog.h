/********************************************************************************
** Form generated from reading UI file 'scalesetupdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCALESETUPDIALOG_H
#define UI_SCALESETUPDIALOG_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include "dao/setupdao.h"

QT_BEGIN_NAMESPACE

class Ui_ScaleSetupDialog
{
public:
    QLabel *textLabel1;
    QLabel *textLabel2;
    QLabel *textLabel2_2;
    QLabel *textLabel2_3;
    QComboBox *baudCombo;
    QComboBox *dataBitCombo;
    QComboBox *parityCombo;
    QComboBox *stopBitCombo;
    QPushButton *browseButton;
    QLineEdit *devicePathEdit;
    QLabel *textLabel2_3_2;
    QComboBox *startCharCombo;
    QPushButton *cancelButton;
    QLabel *textLabel2_2_2;
    QLabel *textLabel2_2_2_2;
    QPushButton *saveButton;
    QLabel *textLabel1_2;
    QLineEdit *formatStringEdit;
    QComboBox *endCharCombo;
    QCheckBox *teleWeightCheckBox;
    Q3ButtonGroup *retrievalModeGroup;
    QRadioButton *continuousRadio;
    QRadioButton *demandRadio;
    QLineEdit *lineEditMotionChar;
    QLabel *labelMotionChar;

    void setupUi(QDialog *ScaleSetupDialog)
    {
        if (ScaleSetupDialog->objectName().isEmpty())
            ScaleSetupDialog->setObjectName(QString::fromUtf8("ScaleSetupDialog"));
        ScaleSetupDialog->setWindowModality(Qt::ApplicationModal);
        ScaleSetupDialog->resize(492, 484);
        QFont font;
        font.setPointSize(13);
        ScaleSetupDialog->setFont(font);
        textLabel1 = new QLabel(ScaleSetupDialog);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(20, 20, 190, 30));
        textLabel1->setWordWrap(false);
        textLabel2 = new QLabel(ScaleSetupDialog);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setGeometry(QRect(20, 90, 80, 30));
        textLabel2->setFrameShape(QFrame::NoFrame);
        textLabel2->setFrameShadow(QFrame::Plain);
        textLabel2->setWordWrap(false);
        textLabel2_2 = new QLabel(ScaleSetupDialog);
        textLabel2_2->setObjectName(QString::fromUtf8("textLabel2_2"));
        textLabel2_2->setGeometry(QRect(110, 90, 80, 30));
        textLabel2_2->setWordWrap(false);
        textLabel2_3 = new QLabel(ScaleSetupDialog);
        textLabel2_3->setObjectName(QString::fromUtf8("textLabel2_3"));
        textLabel2_3->setGeometry(QRect(200, 90, 80, 30));
        textLabel2_3->setWordWrap(false);
        baudCombo = new QComboBox(ScaleSetupDialog);
        baudCombo->setObjectName(QString::fromUtf8("baudCombo"));
        baudCombo->setGeometry(QRect(20, 130, 80, 30));
        dataBitCombo = new QComboBox(ScaleSetupDialog);
        dataBitCombo->setObjectName(QString::fromUtf8("dataBitCombo"));
        dataBitCombo->setGeometry(QRect(110, 130, 80, 30));
        parityCombo = new QComboBox(ScaleSetupDialog);
        parityCombo->setObjectName(QString::fromUtf8("parityCombo"));
        parityCombo->setGeometry(QRect(200, 130, 80, 30));
        stopBitCombo = new QComboBox(ScaleSetupDialog);
        stopBitCombo->setObjectName(QString::fromUtf8("stopBitCombo"));
        stopBitCombo->setGeometry(QRect(290, 130, 80, 30));
        browseButton = new QPushButton(ScaleSetupDialog);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));
        browseButton->setGeometry(QRect(260, 50, 100, 30));
        devicePathEdit = new QLineEdit(ScaleSetupDialog);
        devicePathEdit->setObjectName(QString::fromUtf8("devicePathEdit"));
        devicePathEdit->setGeometry(QRect(20, 50, 220, 31));
        textLabel2_3_2 = new QLabel(ScaleSetupDialog);
        textLabel2_3_2->setObjectName(QString::fromUtf8("textLabel2_3_2"));
        textLabel2_3_2->setGeometry(QRect(290, 90, 80, 30));
        textLabel2_3_2->setWordWrap(false);
        startCharCombo = new QComboBox(ScaleSetupDialog);
        startCharCombo->setObjectName(QString::fromUtf8("startCharCombo"));
        startCharCombo->setGeometry(QRect(10, 400, 140, 30));
        cancelButton = new QPushButton(ScaleSetupDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(321, 440, 80, 30));
        textLabel2_2_2 = new QLabel(ScaleSetupDialog);
        textLabel2_2_2->setObjectName(QString::fromUtf8("textLabel2_2_2"));
        textLabel2_2_2->setGeometry(QRect(10, 360, 140, 30));
        textLabel2_2_2->setWordWrap(false);
        textLabel2_2_2_2 = new QLabel(ScaleSetupDialog);
        textLabel2_2_2_2->setObjectName(QString::fromUtf8("textLabel2_2_2_2"));
        textLabel2_2_2_2->setGeometry(QRect(360, 360, 130, 30));
        textLabel2_2_2_2->setWordWrap(false);
        saveButton = new QPushButton(ScaleSetupDialog);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(411, 440, 80, 30));
        textLabel1_2 = new QLabel(ScaleSetupDialog);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(160, 360, 181, 30));
        textLabel1_2->setWordWrap(false);
        formatStringEdit = new QLineEdit(ScaleSetupDialog);
        formatStringEdit->setObjectName(QString::fromUtf8("formatStringEdit"));
        formatStringEdit->setGeometry(QRect(160, 400, 180, 30));
        endCharCombo = new QComboBox(ScaleSetupDialog);
        endCharCombo->setObjectName(QString::fromUtf8("endCharCombo"));
        endCharCombo->setGeometry(QRect(350, 400, 140, 30));
        teleWeightCheckBox = new QCheckBox(ScaleSetupDialog);
        teleWeightCheckBox->setObjectName(QString::fromUtf8("teleWeightCheckBox"));
        teleWeightCheckBox->setGeometry(QRect(20, 170, 281, 31));
        retrievalModeGroup = new Q3ButtonGroup(ScaleSetupDialog);
        retrievalModeGroup->setObjectName(QString::fromUtf8("retrievalModeGroup"));
        retrievalModeGroup->setGeometry(QRect(20, 210, 180, 90));
        continuousRadio = new QRadioButton(retrievalModeGroup);
        continuousRadio->setObjectName(QString::fromUtf8("continuousRadio"));
        continuousRadio->setGeometry(QRect(10, 20, 160, 30));
        demandRadio = new QRadioButton(retrievalModeGroup);
        demandRadio->setObjectName(QString::fromUtf8("demandRadio"));
        demandRadio->setGeometry(QRect(10, 50, 160, 30));
        demandRadio->setChecked(true);
        lineEditMotionChar = new QLineEdit(ScaleSetupDialog);
        lineEditMotionChar->setObjectName(QString::fromUtf8("lineEditMotionChar"));
        lineEditMotionChar->setGeometry(QRect(160, 320, 41, 30));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        lineEditMotionChar->setFont(font1);
        lineEditMotionChar->setAlignment(Qt::AlignCenter);
        labelMotionChar = new QLabel(ScaleSetupDialog);
        labelMotionChar->setObjectName(QString::fromUtf8("labelMotionChar"));
        labelMotionChar->setGeometry(QRect(10, 330, 141, 16));

        retranslateUi(ScaleSetupDialog);

        QMetaObject::connectSlotsByName(ScaleSetupDialog);
    } // setupUi

    void retranslateUi(QDialog *ScaleSetupDialog)
    {
        ScaleSetupDialog->setWindowTitle(QApplication::translate("ScaleSetupDialog", "Setup Scales", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("ScaleSetupDialog", "Device:", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("ScaleSetupDialog", "Baud", 0, QApplication::UnicodeUTF8));
        textLabel2_2->setText(QApplication::translate("ScaleSetupDialog", "Data Bits", 0, QApplication::UnicodeUTF8));
        textLabel2_3->setText(QApplication::translate("ScaleSetupDialog", "Parity", 0, QApplication::UnicodeUTF8));
        baudCombo->clear();
        baudCombo->insertItems(0, QStringList()
         << QApplication::translate("ScaleSetupDialog", "50", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "75", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "110", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "134", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "150", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "300", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "1200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "1800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "2400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "4800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "9600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "19200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "38400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "57600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "115200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "230400", 0, QApplication::UnicodeUTF8)
        );
        dataBitCombo->clear();
        dataBitCombo->insertItems(0, QStringList()
         << QApplication::translate("ScaleSetupDialog", "5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "8", 0, QApplication::UnicodeUTF8)
        );
        parityCombo->clear();
        parityCombo->insertItems(0, QStringList()
         << QApplication::translate("ScaleSetupDialog", "None", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "Odd", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "Even", 0, QApplication::UnicodeUTF8)
        );
        stopBitCombo->clear();
        stopBitCombo->insertItems(0, QStringList()
         << QApplication::translate("ScaleSetupDialog", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ScaleSetupDialog", "2", 0, QApplication::UnicodeUTF8)
        );
        browseButton->setText(QApplication::translate("ScaleSetupDialog", "Browse", 0, QApplication::UnicodeUTF8));
        textLabel2_3_2->setText(QApplication::translate("ScaleSetupDialog", "Stop Bits", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("ScaleSetupDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        textLabel2_2_2->setText(QApplication::translate("ScaleSetupDialog", "Start Character", 0, QApplication::UnicodeUTF8));
        textLabel2_2_2_2->setText(QApplication::translate("ScaleSetupDialog", "End Character", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("ScaleSetupDialog", "Save", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("ScaleSetupDialog", "Format String", 0, QApplication::UnicodeUTF8));
        teleWeightCheckBox->setText(QApplication::translate("ScaleSetupDialog", "TeleWeight", 0, QApplication::UnicodeUTF8));
        retrievalModeGroup->setTitle(QApplication::translate("ScaleSetupDialog", "Retrieval Mode", 0, QApplication::UnicodeUTF8));
        continuousRadio->setText(QApplication::translate("ScaleSetupDialog", "Continuous", 0, QApplication::UnicodeUTF8));
        demandRadio->setText(QApplication::translate("ScaleSetupDialog", "Demand", 0, QApplication::UnicodeUTF8));
        lineEditMotionChar->setText(QApplication::translate("ScaleSetupDialog", "M", 0, QApplication::UnicodeUTF8));
        labelMotionChar->setText(QApplication::translate("ScaleSetupDialog", "Motion Character: ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ScaleSetupDialog: public Ui_ScaleSetupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCALESETUPDIALOG_H
