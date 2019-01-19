/********************************************************************************
** Form generated from reading UI file 'salemanagerdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SALEMANAGERDIALOG_H
#define UI_SALEMANAGERDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3ListBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCalendarWidget>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include "dao/salemanager.h"

QT_BEGIN_NAMESPACE

class Ui_SaleManagerDialog
{
public:
    QPushButton *saveNewSaleButton;
    QPushButton *createButton;
    Q3ListBox *saleListBox;
    QPushButton *exitButton;
    QLabel *saleLabel;
    QPushButton *closeSaleButton;
    QCalendarWidget *saleDatePicker;
    QPushButton *openSelected;
    QPushButton *setActiveButton;

    void setupUi(QDialog *SaleManagerDialog)
    {
        if (SaleManagerDialog->objectName().isEmpty())
            SaleManagerDialog->setObjectName(QString::fromUtf8("SaleManagerDialog"));
        SaleManagerDialog->setWindowModality(Qt::ApplicationModal);
        SaleManagerDialog->resize(675, 364);
        QFont font;
        font.setPointSize(13);
        SaleManagerDialog->setFont(font);
        saveNewSaleButton = new QPushButton(SaleManagerDialog);
        saveNewSaleButton->setObjectName(QString::fromUtf8("saveNewSaleButton"));
        saveNewSaleButton->setGeometry(QRect(480, 240, 100, 30));
        createButton = new QPushButton(SaleManagerDialog);
        createButton->setObjectName(QString::fromUtf8("createButton"));
        createButton->setGeometry(QRect(120, 240, 100, 30));
        saleListBox = new Q3ListBox(SaleManagerDialog);
        saleListBox->setObjectName(QString::fromUtf8("saleListBox"));
        saleListBox->setGeometry(QRect(10, 50, 210, 180));
        exitButton = new QPushButton(SaleManagerDialog);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(10, 240, 100, 30));
        saleLabel = new QLabel(SaleManagerDialog);
        saleLabel->setObjectName(QString::fromUtf8("saleLabel"));
        saleLabel->setGeometry(QRect(60, 10, 111, 30));
        saleLabel->setWordWrap(false);
        closeSaleButton = new QPushButton(SaleManagerDialog);
        closeSaleButton->setObjectName(QString::fromUtf8("closeSaleButton"));
        closeSaleButton->setGeometry(QRect(230, 130, 140, 30));
        saleDatePicker = new QCalendarWidget(SaleManagerDialog);
        saleDatePicker->setObjectName(QString::fromUtf8("saleDatePicker"));
        saleDatePicker->setGeometry(QRect(390, 40, 264, 171));
        openSelected = new QPushButton(SaleManagerDialog);
        openSelected->setObjectName(QString::fromUtf8("openSelected"));
        openSelected->setGeometry(QRect(230, 190, 140, 30));
        setActiveButton = new QPushButton(SaleManagerDialog);
        setActiveButton->setObjectName(QString::fromUtf8("setActiveButton"));
        setActiveButton->setGeometry(QRect(230, 70, 140, 30));
        QWidget::setTabOrder(saleListBox, exitButton);
        QWidget::setTabOrder(exitButton, createButton);

        retranslateUi(SaleManagerDialog);

        QMetaObject::connectSlotsByName(SaleManagerDialog);
    } // setupUi

    void retranslateUi(QDialog *SaleManagerDialog)
    {
        SaleManagerDialog->setWindowTitle(QApplication::translate("SaleManagerDialog", "Manage Sales", 0, QApplication::UnicodeUTF8));
        saveNewSaleButton->setText(QApplication::translate("SaleManagerDialog", "Save", 0, QApplication::UnicodeUTF8));
        createButton->setText(QApplication::translate("SaleManagerDialog", "Create", 0, QApplication::UnicodeUTF8));
        saleListBox->clear();
        saleListBox->insertItem(QString());
        exitButton->setText(QApplication::translate("SaleManagerDialog", "Ok", 0, QApplication::UnicodeUTF8));
        saleLabel->setText(QApplication::translate("SaleManagerDialog", "Sale Dates:", 0, QApplication::UnicodeUTF8));
        closeSaleButton->setText(QApplication::translate("SaleManagerDialog", "Close Selected", 0, QApplication::UnicodeUTF8));
        openSelected->setText(QApplication::translate("SaleManagerDialog", "Open Selected", 0, QApplication::UnicodeUTF8));
        setActiveButton->setText(QApplication::translate("SaleManagerDialog", "Set Active", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SaleManagerDialog: public Ui_SaleManagerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SALEMANAGERDIALOG_H
