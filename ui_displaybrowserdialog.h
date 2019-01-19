/********************************************************************************
** Form generated from reading UI file 'displaybrowserdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYBROWSERDIALOG_H
#define UI_DISPLAYBROWSERDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3ListBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include "dao/setupdao.h"

QT_BEGIN_NAMESPACE

class Ui_DisplayBrowserDialog
{
public:
    Q3ListBox *displayListBox;
    QPushButton *newButton;
    QPushButton *viewButton;
    QPushButton *deleteButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *DisplayBrowserDialog)
    {
        if (DisplayBrowserDialog->objectName().isEmpty())
            DisplayBrowserDialog->setObjectName(QString::fromUtf8("DisplayBrowserDialog"));
        DisplayBrowserDialog->setWindowModality(Qt::ApplicationModal);
        DisplayBrowserDialog->resize(384, 276);
        QFont font;
        font.setPointSize(13);
        DisplayBrowserDialog->setFont(font);
        displayListBox = new Q3ListBox(DisplayBrowserDialog);
        displayListBox->setObjectName(QString::fromUtf8("displayListBox"));
        displayListBox->setGeometry(QRect(20, 20, 350, 190));
        newButton = new QPushButton(DisplayBrowserDialog);
        newButton->setObjectName(QString::fromUtf8("newButton"));
        newButton->setGeometry(QRect(290, 220, 80, 30));
        viewButton = new QPushButton(DisplayBrowserDialog);
        viewButton->setObjectName(QString::fromUtf8("viewButton"));
        viewButton->setGeometry(QRect(200, 220, 80, 30));
        deleteButton = new QPushButton(DisplayBrowserDialog);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setGeometry(QRect(110, 220, 80, 30));
        cancelButton = new QPushButton(DisplayBrowserDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(20, 221, 80, 30));

        retranslateUi(DisplayBrowserDialog);

        QMetaObject::connectSlotsByName(DisplayBrowserDialog);
    } // setupUi

    void retranslateUi(QDialog *DisplayBrowserDialog)
    {
        DisplayBrowserDialog->setWindowTitle(QApplication::translate("DisplayBrowserDialog", "Manage Displays", 0, QApplication::UnicodeUTF8));
        newButton->setText(QApplication::translate("DisplayBrowserDialog", "New", 0, QApplication::UnicodeUTF8));
        viewButton->setText(QApplication::translate("DisplayBrowserDialog", "View", 0, QApplication::UnicodeUTF8));
        deleteButton->setText(QApplication::translate("DisplayBrowserDialog", "Delete", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("DisplayBrowserDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DisplayBrowserDialog: public Ui_DisplayBrowserDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYBROWSERDIALOG_H
