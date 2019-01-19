/********************************************************************************
** Form generated from reading UI file 'checksetup.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKSETUP_H
#define UI_CHECKSETUP_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QPainter>
#include <types/dragwidget.h>
#include "dao/checkdao.h"
#include "reports/textcheck.h"

QT_BEGIN_NAMESPACE

class Ui_CheckSetup
{
public:
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout;
    QCheckBox *showDate;
    QCheckBox *showMemo;
    QCheckBox *showAddress1;
    QCheckBox *showHead;
    QCheckBox *showTextAmount;
    QCheckBox *showNumber;
    QCheckBox *showPayee;
    QCheckBox *showAmount;
    QCheckBox *showAddress2;
    QCheckBox *showCity;
    QCheckBox *showSignature;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *sigFilePathEdit;
    QPushButton *browseButton;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    DragWidget *checkSetupWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *textLabel1;
    QLineEdit *preSpace;
    QLabel *textLabel2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *saveButton;

    void setupUi(QDialog *CheckSetup)
    {
        if (CheckSetup->objectName().isEmpty())
            CheckSetup->setObjectName(QString::fromUtf8("CheckSetup"));
        CheckSetup->setWindowModality(Qt::ApplicationModal);
        CheckSetup->resize(842, 496);
        QFont font;
        font.setPointSize(13);
        CheckSetup->setFont(font);
        CheckSetup->setMouseTracking(true);
        CheckSetup->setAutoFillBackground(false);
        gridLayout_3 = new QGridLayout(CheckSetup);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(CheckSetup);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QFont font1;
        font1.setPointSize(9);
        groupBox->setFont(font1);
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        showDate = new QCheckBox(groupBox);
        showDate->setObjectName(QString::fromUtf8("showDate"));
        showDate->setFont(font1);

        gridLayout->addWidget(showDate, 0, 0, 1, 1);

        showMemo = new QCheckBox(groupBox);
        showMemo->setObjectName(QString::fromUtf8("showMemo"));
        showMemo->setFont(font1);

        gridLayout->addWidget(showMemo, 0, 1, 1, 1);

        showAddress1 = new QCheckBox(groupBox);
        showAddress1->setObjectName(QString::fromUtf8("showAddress1"));
        showAddress1->setFont(font1);

        gridLayout->addWidget(showAddress1, 0, 2, 1, 1);

        showHead = new QCheckBox(groupBox);
        showHead->setObjectName(QString::fromUtf8("showHead"));
        showHead->setFont(font1);

        gridLayout->addWidget(showHead, 0, 3, 1, 1);

        showTextAmount = new QCheckBox(groupBox);
        showTextAmount->setObjectName(QString::fromUtf8("showTextAmount"));
        showTextAmount->setFont(font1);

        gridLayout->addWidget(showTextAmount, 0, 4, 1, 1);

        showNumber = new QCheckBox(groupBox);
        showNumber->setObjectName(QString::fromUtf8("showNumber"));
        showNumber->setFont(font1);

        gridLayout->addWidget(showNumber, 0, 5, 1, 1);

        showPayee = new QCheckBox(groupBox);
        showPayee->setObjectName(QString::fromUtf8("showPayee"));
        showPayee->setFont(font1);

        gridLayout->addWidget(showPayee, 1, 0, 1, 1);

        showAmount = new QCheckBox(groupBox);
        showAmount->setObjectName(QString::fromUtf8("showAmount"));
        showAmount->setFont(font1);

        gridLayout->addWidget(showAmount, 1, 1, 1, 1);

        showAddress2 = new QCheckBox(groupBox);
        showAddress2->setObjectName(QString::fromUtf8("showAddress2"));
        showAddress2->setFont(font1);

        gridLayout->addWidget(showAddress2, 1, 2, 1, 1);

        showCity = new QCheckBox(groupBox);
        showCity->setObjectName(QString::fromUtf8("showCity"));
        showCity->setFont(font1);

        gridLayout->addWidget(showCity, 1, 3, 1, 1);

        showSignature = new QCheckBox(groupBox);
        showSignature->setObjectName(QString::fromUtf8("showSignature"));
        showSignature->setFont(font1);

        gridLayout->addWidget(showSignature, 1, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 5, 1, 1);


        gridLayout_4->addLayout(gridLayout, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        sigFilePathEdit = new QLineEdit(CheckSetup);
        sigFilePathEdit->setObjectName(QString::fromUtf8("sigFilePathEdit"));

        horizontalLayout->addWidget(sigFilePathEdit);

        browseButton = new QPushButton(CheckSetup);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));

        horizontalLayout->addWidget(browseButton);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(CheckSetup);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFont(font1);
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        checkSetupWidget = new DragWidget(groupBox_2);
        checkSetupWidget->setObjectName(QString::fromUtf8("checkSetupWidget"));
        checkSetupWidget->setMinimumSize(QSize(800, 260));
        checkSetupWidget->setMaximumSize(QSize(800, 260));
        checkSetupWidget->setAutoFillBackground(true);

        gridLayout_5->addWidget(checkSetupWidget, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        textLabel1 = new QLabel(CheckSetup);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setWordWrap(false);

        horizontalLayout_2->addWidget(textLabel1);

        preSpace = new QLineEdit(CheckSetup);
        preSpace->setObjectName(QString::fromUtf8("preSpace"));
        preSpace->setMaximumSize(QSize(80, 16777215));
        preSpace->setAlignment(Qt::AlignRight);

        horizontalLayout_2->addWidget(preSpace);

        textLabel2 = new QLabel(CheckSetup);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setWordWrap(false);

        horizontalLayout_2->addWidget(textLabel2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        saveButton = new QPushButton(CheckSetup);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        horizontalLayout_2->addWidget(saveButton);


        gridLayout_2->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        gridLayout_2->setRowStretch(0, 1);
        gridLayout_2->setRowStretch(1, 1);
        gridLayout_2->setRowStretch(2, 10);
        gridLayout_2->setRowStretch(3, 1);

        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        retranslateUi(CheckSetup);

        QMetaObject::connectSlotsByName(CheckSetup);
    } // setupUi

    void retranslateUi(QDialog *CheckSetup)
    {
        CheckSetup->setWindowTitle(QApplication::translate("CheckSetup", "Setup Check Formatting", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("CheckSetup", "Check items ", 0, QApplication::UnicodeUTF8));
        showDate->setText(QApplication::translate("CheckSetup", "Date", 0, QApplication::UnicodeUTF8));
        showMemo->setText(QApplication::translate("CheckSetup", "Memo", 0, QApplication::UnicodeUTF8));
        showAddress1->setText(QApplication::translate("CheckSetup", "Address 1", 0, QApplication::UnicodeUTF8));
        showHead->setText(QApplication::translate("CheckSetup", "Head Count", 0, QApplication::UnicodeUTF8));
        showTextAmount->setText(QApplication::translate("CheckSetup", "Text Amount", 0, QApplication::UnicodeUTF8));
        showNumber->setText(QApplication::translate("CheckSetup", "Number", 0, QApplication::UnicodeUTF8));
        showPayee->setText(QApplication::translate("CheckSetup", "Payee", 0, QApplication::UnicodeUTF8));
        showAmount->setText(QApplication::translate("CheckSetup", "Amount", 0, QApplication::UnicodeUTF8));
        showAddress2->setText(QApplication::translate("CheckSetup", "Address 2", 0, QApplication::UnicodeUTF8));
        showCity->setText(QApplication::translate("CheckSetup", "City, St Zip", 0, QApplication::UnicodeUTF8));
        showSignature->setText(QApplication::translate("CheckSetup", "Signature", 0, QApplication::UnicodeUTF8));
        browseButton->setText(QApplication::translate("CheckSetup", "&Browse", 0, QApplication::UnicodeUTF8));
        browseButton->setShortcut(QApplication::translate("CheckSetup", "Alt+B", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("CheckSetup", "Position items using mouse", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("CheckSetup", "Line space", 0, QApplication::UnicodeUTF8));
        preSpace->setText(QApplication::translate("CheckSetup", "0", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("CheckSetup", "lines before printing check.", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("CheckSetup", "Save", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CheckSetup: public Ui_CheckSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKSETUP_H
