/********************************************************************************
** Form generated from reading UI file 'tablebrowserdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLEBROWSERDIALOG_H
#define UI_TABLEBROWSERDIALOG_H

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
#include <QtCore/QStringList>
#include <vector>

QT_BEGIN_NAMESPACE

class Ui_TableBrowserDialog
{
public:
    QPushButton *cancelButton;
    QPushButton *okButton;
    Q3ListBox *itemListBox;

    void setupUi(QDialog *TableBrowserDialog)
    {
        if (TableBrowserDialog->objectName().isEmpty())
            TableBrowserDialog->setObjectName(QString::fromUtf8("TableBrowserDialog"));
        TableBrowserDialog->setWindowModality(Qt::ApplicationModal);
        TableBrowserDialog->resize(601, 461);
        QFont font;
        font.setPointSize(13);
        TableBrowserDialog->setFont(font);
        cancelButton = new QPushButton(TableBrowserDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(370, 420, 101, 31));
        cancelButton->setAutoDefault(false);
        okButton = new QPushButton(TableBrowserDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(490, 420, 101, 31));
        okButton->setDefault(true);
        itemListBox = new Q3ListBox(TableBrowserDialog);
        itemListBox->setObjectName(QString::fromUtf8("itemListBox"));
        itemListBox->setGeometry(QRect(10, 10, 580, 401));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bitstream Vera Sans Mono"));
        font1.setPointSize(13);
        itemListBox->setFont(font1);

        retranslateUi(TableBrowserDialog);

        QMetaObject::connectSlotsByName(TableBrowserDialog);
    } // setupUi

    void retranslateUi(QDialog *TableBrowserDialog)
    {
        TableBrowserDialog->setWindowTitle(QApplication::translate("TableBrowserDialog", "Select an Item", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("TableBrowserDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
        cancelButton->setShortcut(QApplication::translate("TableBrowserDialog", "Alt+C", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("TableBrowserDialog", "&Ok", 0, QApplication::UnicodeUTF8));
        okButton->setShortcut(QApplication::translate("TableBrowserDialog", "Alt+O", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TableBrowserDialog: public Ui_TableBrowserDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLEBROWSERDIALOG_H
