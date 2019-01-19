/********************************************************************************
** Form generated from reading UI file 'brandbrowserdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BRANDBROWSERDIALOG_H
#define UI_BRANDBROWSERDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Table>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <vector>
#include "dao/branddao.h"

QT_BEGIN_NAMESPACE

class Ui_BrandBrowserDialog
{
public:
    QPushButton *backButton;
    QPushButton *pageUpButton;
    QPushButton *pageDownButton;
    Q3Table *brandTable;
    QPushButton *goTopButton;
    QPushButton *goBottomButton;

    void setupUi(QDialog *BrandBrowserDialog)
    {
        if (BrandBrowserDialog->objectName().isEmpty())
            BrandBrowserDialog->setObjectName(QString::fromUtf8("BrandBrowserDialog"));
        BrandBrowserDialog->setWindowModality(Qt::ApplicationModal);
        BrandBrowserDialog->resize(759, 480);
        QFont font;
        font.setPointSize(13);
        BrandBrowserDialog->setFont(font);
        backButton = new QPushButton(BrandBrowserDialog);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(650, 10, 101, 60));
        pageUpButton = new QPushButton(BrandBrowserDialog);
        pageUpButton->setObjectName(QString::fromUtf8("pageUpButton"));
        pageUpButton->setGeometry(QRect(640, 120, 101, 60));
        pageDownButton = new QPushButton(BrandBrowserDialog);
        pageDownButton->setObjectName(QString::fromUtf8("pageDownButton"));
        pageDownButton->setGeometry(QRect(640, 200, 101, 60));
        brandTable = new Q3Table(BrandBrowserDialog);
        brandTable->setObjectName(QString::fromUtf8("brandTable"));
        brandTable->setGeometry(QRect(10, 80, 500, 390));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(brandTable->sizePolicy().hasHeightForWidth());
        brandTable->setSizePolicy(sizePolicy);
        brandTable->setNumRows(8);
        brandTable->setNumCols(4);
        goTopButton = new QPushButton(BrandBrowserDialog);
        goTopButton->setObjectName(QString::fromUtf8("goTopButton"));
        goTopButton->setGeometry(QRect(520, 120, 101, 60));
        goBottomButton = new QPushButton(BrandBrowserDialog);
        goBottomButton->setObjectName(QString::fromUtf8("goBottomButton"));
        goBottomButton->setGeometry(QRect(520, 200, 101, 60));

        retranslateUi(BrandBrowserDialog);

        QMetaObject::connectSlotsByName(BrandBrowserDialog);
    } // setupUi

    void retranslateUi(QDialog *BrandBrowserDialog)
    {
        BrandBrowserDialog->setWindowTitle(QApplication::translate("BrandBrowserDialog", "Review Brands", 0, QApplication::UnicodeUTF8));
        backButton->setText(QApplication::translate("BrandBrowserDialog", "&Back", 0, QApplication::UnicodeUTF8));
        backButton->setShortcut(QApplication::translate("BrandBrowserDialog", "Alt+B", 0, QApplication::UnicodeUTF8));
        pageUpButton->setText(QApplication::translate("BrandBrowserDialog", "PGUP", 0, QApplication::UnicodeUTF8));
        pageUpButton->setShortcut(QApplication::translate("BrandBrowserDialog", "PgUp", 0, QApplication::UnicodeUTF8));
        pageDownButton->setText(QApplication::translate("BrandBrowserDialog", "PGDN", 0, QApplication::UnicodeUTF8));
        pageDownButton->setShortcut(QApplication::translate("BrandBrowserDialog", "PgDown", 0, QApplication::UnicodeUTF8));
        brandTable->horizontalHeader()->setLabel(0, QApplication::translate("BrandBrowserDialog", "------", 0, QApplication::UnicodeUTF8));
        brandTable->horizontalHeader()->setLabel(1, QApplication::translate("BrandBrowserDialog", "------", 0, QApplication::UnicodeUTF8));
        brandTable->horizontalHeader()->setLabel(2, QApplication::translate("BrandBrowserDialog", "------", 0, QApplication::UnicodeUTF8));
        brandTable->horizontalHeader()->setLabel(3, QApplication::translate("BrandBrowserDialog", "------", 0, QApplication::UnicodeUTF8));
        brandTable->verticalHeader()->setLabel(0, QApplication::translate("BrandBrowserDialog", "*", 0, QApplication::UnicodeUTF8));
        brandTable->verticalHeader()->setLabel(1, QApplication::translate("BrandBrowserDialog", "TAG#", 0, QApplication::UnicodeUTF8));
        brandTable->verticalHeader()->setLabel(2, QApplication::translate("BrandBrowserDialog", "HD#", 0, QApplication::UnicodeUTF8));
        brandTable->verticalHeader()->setLabel(3, QApplication::translate("BrandBrowserDialog", "POS:", 0, QApplication::UnicodeUTF8));
        brandTable->verticalHeader()->setLabel(4, QApplication::translate("BrandBrowserDialog", "TRAN# ", 0, QApplication::UnicodeUTF8));
        brandTable->verticalHeader()->setLabel(5, QApplication::translate("BrandBrowserDialog", "Save", 0, QApplication::UnicodeUTF8));
        brandTable->verticalHeader()->setLabel(6, QApplication::translate("BrandBrowserDialog", "Delete", 0, QApplication::UnicodeUTF8));
        brandTable->verticalHeader()->setLabel(7, QApplication::translate("BrandBrowserDialog", "Copy", 0, QApplication::UnicodeUTF8));
        goTopButton->setText(QApplication::translate("BrandBrowserDialog", "TOP", 0, QApplication::UnicodeUTF8));
        goBottomButton->setText(QApplication::translate("BrandBrowserDialog", "BOTTOM", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BrandBrowserDialog: public Ui_BrandBrowserDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BRANDBROWSERDIALOG_H
