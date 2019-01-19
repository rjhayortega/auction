/********************************************************************************
** Form generated from reading UI file 'vetdatadialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VETDATADIALOG_H
#define UI_VETDATADIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include "dao/setupdao.h"

QT_BEGIN_NAMESPACE

class Ui_VetDataDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    QSpacerItem *spacer2;
    Q3GroupBox *vetDataGroup;
    QGridLayout *gridLayout1;
    Q3TextEdit *vetEdit;
    QLabel *vetDataLabel;

    void setupUi(QDialog *VetDataDialog)
    {
        if (VetDataDialog->objectName().isEmpty())
            VetDataDialog->setObjectName(QString::fromUtf8("VetDataDialog"));
        VetDataDialog->setWindowModality(Qt::ApplicationModal);
        VetDataDialog->resize(358, 307);
        QFont font;
        font.setPointSize(13);
        VetDataDialog->setFont(font);
        gridLayout = new QGridLayout(VetDataDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        saveButton = new QPushButton(VetDataDialog);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        gridLayout->addWidget(saveButton, 1, 2, 1, 1);

        cancelButton = new QPushButton(VetDataDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        gridLayout->addWidget(cancelButton, 1, 1, 1, 1);

        spacer2 = new QSpacerItem(121, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacer2, 1, 0, 1, 1);

        vetDataGroup = new Q3GroupBox(VetDataDialog);
        vetDataGroup->setObjectName(QString::fromUtf8("vetDataGroup"));
        vetDataGroup->setFont(font);
        vetDataGroup->setColumnLayout(0, Qt::Vertical);
        vetDataGroup->layout()->setSpacing(6);
        vetDataGroup->layout()->setContentsMargins(11, 11, 11, 11);
        gridLayout1 = new QGridLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(vetDataGroup->layout());
        if (boxlayout)
            boxlayout->addLayout(gridLayout1);
        gridLayout1->setAlignment(Qt::AlignTop);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        vetEdit = new Q3TextEdit(vetDataGroup);
        vetEdit->setObjectName(QString::fromUtf8("vetEdit"));
        vetEdit->setTextFormat(Qt::PlainText);
        vetEdit->setWordWrap(Q3TextEdit::NoWrap);

        gridLayout1->addWidget(vetEdit, 0, 1, 1, 1);

        vetDataLabel = new QLabel(vetDataGroup);
        vetDataLabel->setObjectName(QString::fromUtf8("vetDataLabel"));
        vetDataLabel->setAlignment(Qt::AlignTop);
        vetDataLabel->setWordWrap(false);

        gridLayout1->addWidget(vetDataLabel, 0, 0, 1, 1);


        gridLayout->addWidget(vetDataGroup, 0, 0, 1, 3);


        retranslateUi(VetDataDialog);

        QMetaObject::connectSlotsByName(VetDataDialog);
    } // setupUi

    void retranslateUi(QDialog *VetDataDialog)
    {
        VetDataDialog->setWindowTitle(QApplication::translate("VetDataDialog", "Form1", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("VetDataDialog", "Save", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("VetDataDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        vetDataGroup->setTitle(QApplication::translate("VetDataDialog", "Vet Data", 0, QApplication::UnicodeUTF8));
        vetDataLabel->setText(QApplication::translate("VetDataDialog", "Id:\n"
"Name:\n"
"Initials:\n"
"Address 1:\n"
"Address 2:\n"
"City, State Zip:\n"
"Phone:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VetDataDialog: public Ui_VetDataDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VETDATADIALOG_H
