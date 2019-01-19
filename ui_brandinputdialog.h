/********************************************************************************
** Form generated from reading UI file 'brandinputdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BRANDINPUTDIALOG_H
#define UI_BRANDINPUTDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <string>
#include "brandwidget.h"
#include "dao/branddao.h"
#include "QtGui/QPainter"
#include "QtGui/QPen"

QT_BEGIN_NAMESPACE

class Ui_BrandInputDialog
{
public:
    QPushButton *bhUpdateButton;
    QPushButton *clearButton;
    QPushButton *viewButton;
    QPushButton *noBrandButton;
    QPushButton *saveButton;
    QPushButton *exitButton;
    QPushButton *tagButton;
    QPushButton *headButton;
    QPushButton *positionButton;
    QPushButton *transactionButton;
    QLabel *inputLabel;
    QLineEdit *inputEdit;
    QLabel *textLabel3_2;
    QLabel *textLabel3;
    QLabel *textLabel3_3;
    QLabel *currentHeadDisplay;
    QLabel *textLabel3_4;
    QLabel *currentTagDisplay;
    QLabel *currentPositionDisplay;
    QLabel *currentTransactionDisplay;
    Q3Frame *smallBrandFrame;
    QFrame *BrandInputFrame;

    void setupUi(QDialog *BrandInputDialog)
    {
        if (BrandInputDialog->objectName().isEmpty())
            BrandInputDialog->setObjectName(QString::fromUtf8("BrandInputDialog"));
        BrandInputDialog->setWindowModality(Qt::ApplicationModal);
        BrandInputDialog->resize(920, 691);
        QFont font;
        font.setPointSize(13);
        BrandInputDialog->setFont(font);
        bhUpdateButton = new QPushButton(BrandInputDialog);
        bhUpdateButton->setObjectName(QString::fromUtf8("bhUpdateButton"));
        bhUpdateButton->setGeometry(QRect(160, 630, 110, 30));
        clearButton = new QPushButton(BrandInputDialog);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setGeometry(QRect(10, 10, 101, 60));
        viewButton = new QPushButton(BrandInputDialog);
        viewButton->setObjectName(QString::fromUtf8("viewButton"));
        viewButton->setGeometry(QRect(490, 10, 101, 60));
        noBrandButton = new QPushButton(BrandInputDialog);
        noBrandButton->setObjectName(QString::fromUtf8("noBrandButton"));
        noBrandButton->setGeometry(QRect(370, 10, 101, 60));
        saveButton = new QPushButton(BrandInputDialog);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(130, 10, 101, 60));
        exitButton = new QPushButton(BrandInputDialog);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(800, 10, 101, 60));
        tagButton = new QPushButton(BrandInputDialog);
        tagButton->setObjectName(QString::fromUtf8("tagButton"));
        tagButton->setGeometry(QRect(810, 330, 101, 60));
        headButton = new QPushButton(BrandInputDialog);
        headButton->setObjectName(QString::fromUtf8("headButton"));
        headButton->setGeometry(QRect(810, 250, 101, 60));
        positionButton = new QPushButton(BrandInputDialog);
        positionButton->setObjectName(QString::fromUtf8("positionButton"));
        positionButton->setGeometry(QRect(810, 90, 101, 60));
        transactionButton = new QPushButton(BrandInputDialog);
        transactionButton->setObjectName(QString::fromUtf8("transactionButton"));
        transactionButton->setGeometry(QRect(810, 170, 101, 60));
        inputLabel = new QLabel(BrandInputDialog);
        inputLabel->setObjectName(QString::fromUtf8("inputLabel"));
        inputLabel->setGeometry(QRect(720, 410, 190, 60));
        inputLabel->setWordWrap(false);
        inputEdit = new QLineEdit(BrandInputDialog);
        inputEdit->setObjectName(QString::fromUtf8("inputEdit"));
        inputEdit->setGeometry(QRect(720, 470, 190, 50));
        QFont font1;
        font1.setPointSize(24);
        inputEdit->setFont(font1);
        inputEdit->setCursorPosition(0);
        textLabel3_2 = new QLabel(BrandInputDialog);
        textLabel3_2->setObjectName(QString::fromUtf8("textLabel3_2"));
        textLabel3_2->setGeometry(QRect(650, 170, 150, 30));
        textLabel3_2->setWordWrap(false);
        textLabel3 = new QLabel(BrandInputDialog);
        textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
        textLabel3->setGeometry(QRect(650, 90, 150, 30));
        textLabel3->setWordWrap(false);
        textLabel3_3 = new QLabel(BrandInputDialog);
        textLabel3_3->setObjectName(QString::fromUtf8("textLabel3_3"));
        textLabel3_3->setGeometry(QRect(650, 250, 150, 30));
        textLabel3_3->setWordWrap(false);
        currentHeadDisplay = new QLabel(BrandInputDialog);
        currentHeadDisplay->setObjectName(QString::fromUtf8("currentHeadDisplay"));
        currentHeadDisplay->setGeometry(QRect(650, 280, 150, 30));
        currentHeadDisplay->setWordWrap(false);
        textLabel3_4 = new QLabel(BrandInputDialog);
        textLabel3_4->setObjectName(QString::fromUtf8("textLabel3_4"));
        textLabel3_4->setGeometry(QRect(650, 330, 150, 30));
        textLabel3_4->setWordWrap(false);
        currentTagDisplay = new QLabel(BrandInputDialog);
        currentTagDisplay->setObjectName(QString::fromUtf8("currentTagDisplay"));
        currentTagDisplay->setGeometry(QRect(650, 360, 150, 30));
        currentTagDisplay->setWordWrap(false);
        currentPositionDisplay = new QLabel(BrandInputDialog);
        currentPositionDisplay->setObjectName(QString::fromUtf8("currentPositionDisplay"));
        currentPositionDisplay->setGeometry(QRect(650, 120, 150, 30));
        currentPositionDisplay->setWordWrap(false);
        currentTransactionDisplay = new QLabel(BrandInputDialog);
        currentTransactionDisplay->setObjectName(QString::fromUtf8("currentTransactionDisplay"));
        currentTransactionDisplay->setGeometry(QRect(650, 200, 150, 30));
        currentTransactionDisplay->setWordWrap(false);
        smallBrandFrame = new Q3Frame(BrandInputDialog);
        smallBrandFrame->setObjectName(QString::fromUtf8("smallBrandFrame"));
        smallBrandFrame->setGeometry(QRect(640, 630, 48, 48));
        smallBrandFrame->setFrameShape(QFrame::StyledPanel);
        smallBrandFrame->setFrameShadow(QFrame::Raised);
        BrandInputFrame = new QFrame(BrandInputDialog);
        BrandInputFrame->setObjectName(QString::fromUtf8("BrandInputFrame"));
        BrandInputFrame->setGeometry(QRect(20, 90, 571, 581));
        BrandInputFrame->setFrameShape(QFrame::StyledPanel);
        BrandInputFrame->setFrameShadow(QFrame::Raised);

        retranslateUi(BrandInputDialog);

        QMetaObject::connectSlotsByName(BrandInputDialog);
    } // setupUi

    void retranslateUi(QDialog *BrandInputDialog)
    {
        BrandInputDialog->setWindowTitle(QApplication::translate("BrandInputDialog", "Input Brand", 0, QApplication::UnicodeUTF8));
        bhUpdateButton->setText(QApplication::translate("BrandInputDialog", "Save Brand", 0, QApplication::UnicodeUTF8));
        clearButton->setText(QApplication::translate("BrandInputDialog", "Clear", 0, QApplication::UnicodeUTF8));
        clearButton->setShortcut(QString());
        viewButton->setText(QApplication::translate("BrandInputDialog", "View", 0, QApplication::UnicodeUTF8));
        noBrandButton->setText(QApplication::translate("BrandInputDialog", "No Brand", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("BrandInputDialog", "Save", 0, QApplication::UnicodeUTF8));
        exitButton->setText(QApplication::translate("BrandInputDialog", "E&xit", 0, QApplication::UnicodeUTF8));
        exitButton->setShortcut(QApplication::translate("BrandInputDialog", "Alt+X", 0, QApplication::UnicodeUTF8));
        tagButton->setText(QApplication::translate("BrandInputDialog", "Ta&g", 0, QApplication::UnicodeUTF8));
        tagButton->setShortcut(QApplication::translate("BrandInputDialog", "Alt+G", 0, QApplication::UnicodeUTF8));
        headButton->setText(QApplication::translate("BrandInputDialog", "&Head", 0, QApplication::UnicodeUTF8));
        headButton->setShortcut(QApplication::translate("BrandInputDialog", "Alt+H", 0, QApplication::UnicodeUTF8));
        positionButton->setText(QApplication::translate("BrandInputDialog", "&Position", 0, QApplication::UnicodeUTF8));
        positionButton->setShortcut(QApplication::translate("BrandInputDialog", "Alt+P", 0, QApplication::UnicodeUTF8));
        transactionButton->setText(QApplication::translate("BrandInputDialog", "&Trans.", 0, QApplication::UnicodeUTF8));
        transactionButton->setShortcut(QApplication::translate("BrandInputDialog", "Alt+T", 0, QApplication::UnicodeUTF8));
        inputLabel->setText(QApplication::translate("BrandInputDialog", "CURRENT EDIT ITEM", 0, QApplication::UnicodeUTF8));
        inputEdit->setText(QString());
        textLabel3_2->setText(QApplication::translate("BrandInputDialog", "Transaction #", 0, QApplication::UnicodeUTF8));
        textLabel3->setText(QApplication::translate("BrandInputDialog", "Brand Position", 0, QApplication::UnicodeUTF8));
        textLabel3_3->setText(QApplication::translate("BrandInputDialog", "Head Count", 0, QApplication::UnicodeUTF8));
        currentHeadDisplay->setText(QString());
        textLabel3_4->setText(QApplication::translate("BrandInputDialog", "Tag Number", 0, QApplication::UnicodeUTF8));
        currentTagDisplay->setText(QString());
        currentPositionDisplay->setText(QString());
        currentTransactionDisplay->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BrandInputDialog: public Ui_BrandInputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BRANDINPUTDIALOG_H
