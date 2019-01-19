/********************************************************************************
** Form generated from reading UI file 'codedialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CODEDIALOG_H
#define UI_CODEDIALOG_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3ListBox>
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
#include <vector>
#include "dao/animalcodedao.h"
#include "dao/commissiondao.h"
#include "types/animalcode.h"

QT_BEGIN_NAMESPACE

class Ui_CodeDialog
{
public:
    Q3ListBox *codeListBox;
    Q3GroupBox *groupBox2;
    QLabel *textLabel1;
    QLabel *textLabel2_3;
    QLineEdit *lineEditCode;
    QLabel *colorGroupLabel;
    QLineEdit *codeDescrip;
    QPushButton *codeSaveButt;
    QPushButton *codeDelButt;
    QComboBox *colorComboBox;
    QCheckBox *codePair;
    Q3ButtonGroup *codeEditModeGroup;
    QRadioButton *editColorButton;
    QRadioButton *editSexButton;
    QRadioButton *editFlawButton;
    QPushButton *printListButton;

    void setupUi(QDialog *CodeDialog)
    {
        if (CodeDialog->objectName().isEmpty())
            CodeDialog->setObjectName(QString::fromUtf8("CodeDialog"));
        CodeDialog->setWindowModality(Qt::ApplicationModal);
        CodeDialog->resize(600, 480);
        QFont font;
        font.setPointSize(13);
        CodeDialog->setFont(font);
        codeListBox = new Q3ListBox(CodeDialog);
        codeListBox->setObjectName(QString::fromUtf8("codeListBox"));
        codeListBox->setGeometry(QRect(20, 220, 250, 211));
        groupBox2 = new Q3GroupBox(CodeDialog);
        groupBox2->setObjectName(QString::fromUtf8("groupBox2"));
        groupBox2->setGeometry(QRect(20, 20, 551, 180));
        textLabel1 = new QLabel(groupBox2);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(20, 10, 50, 30));
        textLabel1->setWordWrap(false);
        textLabel2_3 = new QLabel(groupBox2);
        textLabel2_3->setObjectName(QString::fromUtf8("textLabel2_3"));
        textLabel2_3->setGeometry(QRect(90, 10, 220, 30));
        textLabel2_3->setWordWrap(false);
        lineEditCode = new QLineEdit(groupBox2);
        lineEditCode->setObjectName(QString::fromUtf8("lineEditCode"));
        lineEditCode->setGeometry(QRect(20, 50, 60, 30));
        colorGroupLabel = new QLabel(groupBox2);
        colorGroupLabel->setObjectName(QString::fromUtf8("colorGroupLabel"));
        colorGroupLabel->setGeometry(QRect(20, 100, 120, 30));
        colorGroupLabel->setWordWrap(false);
        codeDescrip = new QLineEdit(groupBox2);
        codeDescrip->setObjectName(QString::fromUtf8("codeDescrip"));
        codeDescrip->setGeometry(QRect(90, 50, 310, 30));
        codeSaveButt = new QPushButton(groupBox2);
        codeSaveButt->setObjectName(QString::fromUtf8("codeSaveButt"));
        codeSaveButt->setGeometry(QRect(320, 140, 100, 30));
        codeSaveButt->setDefault(true);
        codeDelButt = new QPushButton(groupBox2);
        codeDelButt->setObjectName(QString::fromUtf8("codeDelButt"));
        codeDelButt->setGeometry(QRect(440, 140, 100, 30));
        codeDelButt->setAutoDefault(false);
        colorComboBox = new QComboBox(groupBox2);
        colorComboBox->setObjectName(QString::fromUtf8("colorComboBox"));
        colorComboBox->setGeometry(QRect(20, 140, 120, 30));
        codePair = new QCheckBox(groupBox2);
        codePair->setObjectName(QString::fromUtf8("codePair"));
        codePair->setGeometry(QRect(190, 140, 90, 30));
        codeEditModeGroup = new Q3ButtonGroup(groupBox2);
        codeEditModeGroup->setObjectName(QString::fromUtf8("codeEditModeGroup"));
        codeEditModeGroup->setGeometry(QRect(410, 10, 131, 120));
        editColorButton = new QRadioButton(codeEditModeGroup);
        editColorButton->setObjectName(QString::fromUtf8("editColorButton"));
        editColorButton->setGeometry(QRect(10, 20, 100, 30));
        editColorButton->setChecked(true);
        editSexButton = new QRadioButton(codeEditModeGroup);
        editSexButton->setObjectName(QString::fromUtf8("editSexButton"));
        editSexButton->setGeometry(QRect(10, 50, 100, 30));
        editFlawButton = new QRadioButton(codeEditModeGroup);
        editFlawButton->setObjectName(QString::fromUtf8("editFlawButton"));
        editFlawButton->setGeometry(QRect(10, 80, 100, 30));
        printListButton = new QPushButton(CodeDialog);
        printListButton->setObjectName(QString::fromUtf8("printListButton"));
        printListButton->setGeometry(QRect(170, 440, 100, 30));
        printListButton->setAutoDefault(false);
        QWidget::setTabOrder(lineEditCode, codeDescrip);
        QWidget::setTabOrder(codeDescrip, codePair);
        QWidget::setTabOrder(codePair, editColorButton);
        QWidget::setTabOrder(editColorButton, codeSaveButt);
        QWidget::setTabOrder(codeSaveButt, codeDelButt);
        QWidget::setTabOrder(codeDelButt, codeListBox);

        retranslateUi(CodeDialog);

        QMetaObject::connectSlotsByName(CodeDialog);
    } // setupUi

    void retranslateUi(QDialog *CodeDialog)
    {
        CodeDialog->setWindowTitle(QApplication::translate("CodeDialog", "Edit Codes", 0, QApplication::UnicodeUTF8));
        groupBox2->setTitle(QString());
        textLabel1->setText(QApplication::translate("CodeDialog", "Code", 0, QApplication::UnicodeUTF8));
        textLabel2_3->setText(QApplication::translate("CodeDialog", "Description", 0, QApplication::UnicodeUTF8));
        colorGroupLabel->setText(QApplication::translate("CodeDialog", "Color Code", 0, QApplication::UnicodeUTF8));
        codeSaveButt->setText(QApplication::translate("CodeDialog", "Sa&ve", 0, QApplication::UnicodeUTF8));
        codeSaveButt->setShortcut(QApplication::translate("CodeDialog", "Alt+V", 0, QApplication::UnicodeUTF8));
        codeDelButt->setText(QApplication::translate("CodeDialog", "&Delete", 0, QApplication::UnicodeUTF8));
        codeDelButt->setShortcut(QApplication::translate("CodeDialog", "Alt+D", 0, QApplication::UnicodeUTF8));
        colorComboBox->clear();
        colorComboBox->insertItems(0, QStringList()
         << QApplication::translate("CodeDialog", "0-69", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CodeDialog", "70-79", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CodeDialog", "80-89", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CodeDialog", "90-99", 0, QApplication::UnicodeUTF8)
        );
        codePair->setText(QApplication::translate("CodeDialog", "Pair?", 0, QApplication::UnicodeUTF8));
        codeEditModeGroup->setTitle(QApplication::translate("CodeDialog", "Edit Mode", 0, QApplication::UnicodeUTF8));
        editColorButton->setText(QApplication::translate("CodeDialog", "&Color", 0, QApplication::UnicodeUTF8));
        editColorButton->setShortcut(QApplication::translate("CodeDialog", "Alt+C", 0, QApplication::UnicodeUTF8));
        editSexButton->setText(QApplication::translate("CodeDialog", "&Sex", 0, QApplication::UnicodeUTF8));
        editSexButton->setShortcut(QApplication::translate("CodeDialog", "Alt+S", 0, QApplication::UnicodeUTF8));
        editFlawButton->setText(QApplication::translate("CodeDialog", "&Flaw", 0, QApplication::UnicodeUTF8));
        editFlawButton->setShortcut(QApplication::translate("CodeDialog", "Alt+F", 0, QApplication::UnicodeUTF8));
        printListButton->setText(QApplication::translate("CodeDialog", "&Print", 0, QApplication::UnicodeUTF8));
        printListButton->setShortcut(QApplication::translate("CodeDialog", "Alt+P", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CodeDialog: public Ui_CodeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CODEDIALOG_H
