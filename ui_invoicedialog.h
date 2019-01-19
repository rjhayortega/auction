/********************************************************************************
** Form generated from reading UI file 'invoicedialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVOICEDIALOG_H
#define UI_INVOICEDIALOG_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GroupBox>
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
#include <QtGui/QRadioButton>
#include <Qt3Support/Q3ProgressDialog>
#include "./dao/invoicedao.h"
#include "dao/checkdao.h"
#include "dao/printerdao.h"
#include "dao/proratedao.h"
#include "dao/salemanager.h"
#include "dao/setupdao.h"
#include "permsearchdialog.h"
#include "reports/textcheck.h"

QT_BEGIN_NAMESPACE

class Ui_InvoiceDialog
{
public:
    QLabel *binvUnpaid;
    QLabel *binvCompany;
    QLabel *binvPaid;
    QLabel *sinvTotals;
    QPushButton *sinvPrintButton;
    QPushButton *sinvPreviewButton;
    QPushButton *sinvListReadyButton;
    QPushButton *sinvSaveDaily;
    QPushButton *sinvChgButt;
    QPushButton *sinvTrucking;
    QComboBox *printedChecksComboBox;
    QLabel *sinvPrinted;
    QLabel *saleDateLabel;
    QLineEdit *sinvZip;
    QLineEdit *sinvState;
    QLineEdit *sinvCity;
    QLineEdit *sinvComment;
    QLabel *companyLabel;
    QLabel *textLabel3_2;
    QLineEdit *sinvName;
    QLineEdit *sinvAddress2;
    QLabel *textLabel1_2_2_2;
    QLabel *textLabel1_9_2;
    QLabel *sinvHCountWarning;
    QLabel *textLabel1_6_2;
    QPushButton *cycleButton;
    QLabel *sinvOverallAverage;
    QLabel *sinvOverallBid;
    QLabel *sinvOverallTotal;
    QLabel *sinvOverallWeight;
    QLabel *sinvOverallHead;
    QPushButton *buyerRecapButton;
    QPushButton *prorateButton;
    QPushButton *globalPenButton;
    QPushButton *faxInvoiceButton;
    QLineEdit *sinvHead;
    QLabel *headLabel;
    QPushButton *globalBuyerButton;
    Q3ButtonGroup *customerTypeButtonGroup;
    QRadioButton *sellerButton;
    QRadioButton *buyerButton;
    Q3Table *transactionTable;
    QPushButton *changeStatusButton;
    QLabel *textLabel2_9_2;
    QLineEdit *sinvCompany;
    QLineEdit *sinvAddress1;
    QLineEdit *sinvID;
    QPushButton *compAddressButton;
    QPushButton *emailInvoiceButton;
    QPushButton *showMissingBuyersButton;

    void setupUi(QDialog *InvoiceDialog)
    {
        if (InvoiceDialog->objectName().isEmpty())
            InvoiceDialog->setObjectName(QString::fromUtf8("InvoiceDialog"));
        InvoiceDialog->setWindowModality(Qt::ApplicationModal);
        InvoiceDialog->resize(913, 622);
        QFont font;
        font.setPointSize(13);
        InvoiceDialog->setFont(font);
        binvUnpaid = new QLabel(InvoiceDialog);
        binvUnpaid->setObjectName(QString::fromUtf8("binvUnpaid"));
        binvUnpaid->setEnabled(false);
        binvUnpaid->setGeometry(QRect(400, 180, 130, 30));
        binvUnpaid->setWordWrap(false);
        binvCompany = new QLabel(InvoiceDialog);
        binvCompany->setObjectName(QString::fromUtf8("binvCompany"));
        binvCompany->setEnabled(false);
        binvCompany->setGeometry(QRect(540, 180, 130, 30));
        binvCompany->setWordWrap(false);
        binvPaid = new QLabel(InvoiceDialog);
        binvPaid->setObjectName(QString::fromUtf8("binvPaid"));
        binvPaid->setEnabled(false);
        binvPaid->setGeometry(QRect(280, 180, 110, 21));
        binvPaid->setWordWrap(false);
        sinvTotals = new QLabel(InvoiceDialog);
        sinvTotals->setObjectName(QString::fromUtf8("sinvTotals"));
        sinvTotals->setGeometry(QRect(0, 500, 60, 30));
        sinvTotals->setWordWrap(false);
        sinvPrintButton = new QPushButton(InvoiceDialog);
        sinvPrintButton->setObjectName(QString::fromUtf8("sinvPrintButton"));
        sinvPrintButton->setGeometry(QRect(780, 550, 100, 30));
        sinvPrintButton->setFocusPolicy(Qt::TabFocus);
        sinvPrintButton->setAutoDefault(false);
        sinvPrintButton->setDefault(false);
        sinvPreviewButton = new QPushButton(InvoiceDialog);
        sinvPreviewButton->setObjectName(QString::fromUtf8("sinvPreviewButton"));
        sinvPreviewButton->setGeometry(QRect(670, 550, 100, 30));
        sinvPreviewButton->setFocusPolicy(Qt::TabFocus);
        sinvPreviewButton->setAutoDefault(false);
        sinvListReadyButton = new QPushButton(InvoiceDialog);
        sinvListReadyButton->setObjectName(QString::fromUtf8("sinvListReadyButton"));
        sinvListReadyButton->setGeometry(QRect(10, 550, 120, 30));
        sinvListReadyButton->setFocusPolicy(Qt::TabFocus);
        sinvListReadyButton->setAutoDefault(false);
        sinvSaveDaily = new QPushButton(InvoiceDialog);
        sinvSaveDaily->setObjectName(QString::fromUtf8("sinvSaveDaily"));
        sinvSaveDaily->setGeometry(QRect(540, 550, 120, 30));
        sinvSaveDaily->setFocusPolicy(Qt::TabFocus);
        sinvSaveDaily->setAutoDefault(false);
        sinvChgButt = new QPushButton(InvoiceDialog);
        sinvChgButt->setObjectName(QString::fromUtf8("sinvChgButt"));
        sinvChgButt->setGeometry(QRect(400, 550, 120, 30));
        sinvChgButt->setFocusPolicy(Qt::TabFocus);
        sinvChgButt->setAutoDefault(false);
        sinvTrucking = new QPushButton(InvoiceDialog);
        sinvTrucking->setObjectName(QString::fromUtf8("sinvTrucking"));
        sinvTrucking->setGeometry(QRect(270, 550, 120, 30));
        sinvTrucking->setFocusPolicy(Qt::TabFocus);
        sinvTrucking->setAutoDefault(false);
        printedChecksComboBox = new QComboBox(InvoiceDialog);
        printedChecksComboBox->setObjectName(QString::fromUtf8("printedChecksComboBox"));
        printedChecksComboBox->setGeometry(QRect(570, 180, 110, 30));
        sinvPrinted = new QLabel(InvoiceDialog);
        sinvPrinted->setObjectName(QString::fromUtf8("sinvPrinted"));
        sinvPrinted->setEnabled(false);
        sinvPrinted->setGeometry(QRect(680, 180, 130, 30));
        sinvPrinted->setWordWrap(false);
        saleDateLabel = new QLabel(InvoiceDialog);
        saleDateLabel->setObjectName(QString::fromUtf8("saleDateLabel"));
        saleDateLabel->setGeometry(QRect(720, 10, 131, 30));
        saleDateLabel->setWordWrap(false);
        sinvZip = new QLineEdit(InvoiceDialog);
        sinvZip->setObjectName(QString::fromUtf8("sinvZip"));
        sinvZip->setGeometry(QRect(620, 50, 70, 30));
        sinvState = new QLineEdit(InvoiceDialog);
        sinvState->setObjectName(QString::fromUtf8("sinvState"));
        sinvState->setGeometry(QRect(570, 50, 40, 30));
        sinvCity = new QLineEdit(InvoiceDialog);
        sinvCity->setObjectName(QString::fromUtf8("sinvCity"));
        sinvCity->setGeometry(QRect(410, 50, 150, 30));
        sinvComment = new QLineEdit(InvoiceDialog);
        sinvComment->setObjectName(QString::fromUtf8("sinvComment"));
        sinvComment->setGeometry(QRect(410, 130, 280, 30));
        companyLabel = new QLabel(InvoiceDialog);
        companyLabel->setObjectName(QString::fromUtf8("companyLabel"));
        companyLabel->setGeometry(QRect(300, 90, 100, 30));
        companyLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        companyLabel->setWordWrap(false);
        textLabel3_2 = new QLabel(InvoiceDialog);
        textLabel3_2->setObjectName(QString::fromUtf8("textLabel3_2"));
        textLabel3_2->setGeometry(QRect(300, 130, 100, 30));
        textLabel3_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel3_2->setWordWrap(false);
        sinvName = new QLineEdit(InvoiceDialog);
        sinvName->setObjectName(QString::fromUtf8("sinvName"));
        sinvName->setEnabled(true);
        sinvName->setGeometry(QRect(90, 50, 190, 30));
        sinvAddress2 = new QLineEdit(InvoiceDialog);
        sinvAddress2->setObjectName(QString::fromUtf8("sinvAddress2"));
        sinvAddress2->setGeometry(QRect(90, 130, 190, 30));
        textLabel1_2_2_2 = new QLabel(InvoiceDialog);
        textLabel1_2_2_2->setObjectName(QString::fromUtf8("textLabel1_2_2_2"));
        textLabel1_2_2_2->setGeometry(QRect(10, 50, 70, 30));
        textLabel1_2_2_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_2_2_2->setWordWrap(false);
        textLabel1_9_2 = new QLabel(InvoiceDialog);
        textLabel1_9_2->setObjectName(QString::fromUtf8("textLabel1_9_2"));
        textLabel1_9_2->setGeometry(QRect(-10, 90, 90, 30));
        textLabel1_9_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_9_2->setWordWrap(false);
        sinvHCountWarning = new QLabel(InvoiceDialog);
        sinvHCountWarning->setObjectName(QString::fromUtf8("sinvHCountWarning"));
        sinvHCountWarning->setEnabled(false);
        sinvHCountWarning->setGeometry(QRect(20, 170, 550, 40));
        sinvHCountWarning->setWordWrap(false);
        textLabel1_6_2 = new QLabel(InvoiceDialog);
        textLabel1_6_2->setObjectName(QString::fromUtf8("textLabel1_6_2"));
        textLabel1_6_2->setGeometry(QRect(1, 10, 80, 30));
        textLabel1_6_2->setFrameShape(QFrame::NoFrame);
        textLabel1_6_2->setFrameShadow(QFrame::Plain);
        textLabel1_6_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_6_2->setWordWrap(false);
        cycleButton = new QPushButton(InvoiceDialog);
        cycleButton->setObjectName(QString::fromUtf8("cycleButton"));
        cycleButton->setGeometry(QRect(170, 10, 120, 30));
        cycleButton->setAutoDefault(false);
        sinvOverallAverage = new QLabel(InvoiceDialog);
        sinvOverallAverage->setObjectName(QString::fromUtf8("sinvOverallAverage"));
        sinvOverallAverage->setGeometry(QRect(510, 500, 80, 30));
        sinvOverallAverage->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sinvOverallAverage->setWordWrap(false);
        sinvOverallBid = new QLabel(InvoiceDialog);
        sinvOverallBid->setObjectName(QString::fromUtf8("sinvOverallBid"));
        sinvOverallBid->setGeometry(QRect(670, 500, 80, 30));
        sinvOverallBid->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sinvOverallBid->setWordWrap(false);
        sinvOverallTotal = new QLabel(InvoiceDialog);
        sinvOverallTotal->setObjectName(QString::fromUtf8("sinvOverallTotal"));
        sinvOverallTotal->setGeometry(QRect(750, 500, 100, 30));
        sinvOverallTotal->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sinvOverallTotal->setWordWrap(false);
        sinvOverallWeight = new QLabel(InvoiceDialog);
        sinvOverallWeight->setObjectName(QString::fromUtf8("sinvOverallWeight"));
        sinvOverallWeight->setGeometry(QRect(590, 500, 80, 30));
        sinvOverallWeight->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sinvOverallWeight->setWordWrap(false);
        sinvOverallHead = new QLabel(InvoiceDialog);
        sinvOverallHead->setObjectName(QString::fromUtf8("sinvOverallHead"));
        sinvOverallHead->setGeometry(QRect(80, 500, 60, 30));
        sinvOverallHead->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sinvOverallHead->setWordWrap(false);
        buyerRecapButton = new QPushButton(InvoiceDialog);
        buyerRecapButton->setObjectName(QString::fromUtf8("buyerRecapButton"));
        buyerRecapButton->setGeometry(QRect(140, 550, 120, 30));
        buyerRecapButton->setFocusPolicy(Qt::TabFocus);
        buyerRecapButton->setAutoDefault(false);
        prorateButton = new QPushButton(InvoiceDialog);
        prorateButton->setObjectName(QString::fromUtf8("prorateButton"));
        prorateButton->setGeometry(QRect(140, 550, 120, 30));
        prorateButton->setFocusPolicy(Qt::TabFocus);
        prorateButton->setAutoDefault(false);
        globalPenButton = new QPushButton(InvoiceDialog);
        globalPenButton->setObjectName(QString::fromUtf8("globalPenButton"));
        globalPenButton->setGeometry(QRect(430, 10, 120, 30));
        globalPenButton->setAutoDefault(false);
        faxInvoiceButton = new QPushButton(InvoiceDialog);
        faxInvoiceButton->setObjectName(QString::fromUtf8("faxInvoiceButton"));
        faxInvoiceButton->setGeometry(QRect(560, 10, 61, 30));
        faxInvoiceButton->setAutoDefault(false);
        sinvHead = new QLineEdit(InvoiceDialog);
        sinvHead->setObjectName(QString::fromUtf8("sinvHead"));
        sinvHead->setGeometry(QRect(410, 10, 60, 30));
        headLabel = new QLabel(InvoiceDialog);
        headLabel->setObjectName(QString::fromUtf8("headLabel"));
        headLabel->setGeometry(QRect(310, 10, 90, 30));
        headLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        headLabel->setWordWrap(false);
        globalBuyerButton = new QPushButton(InvoiceDialog);
        globalBuyerButton->setObjectName(QString::fromUtf8("globalBuyerButton"));
        globalBuyerButton->setGeometry(QRect(300, 10, 120, 30));
        globalBuyerButton->setAutoDefault(false);
        customerTypeButtonGroup = new Q3ButtonGroup(InvoiceDialog);
        customerTypeButtonGroup->setObjectName(QString::fromUtf8("customerTypeButtonGroup"));
        customerTypeButtonGroup->setGeometry(QRect(700, 40, 190, 100));
        sellerButton = new QRadioButton(customerTypeButtonGroup);
        sellerButton->setObjectName(QString::fromUtf8("sellerButton"));
        sellerButton->setGeometry(QRect(10, 30, 170, 30));
        sellerButton->setChecked(true);
        buyerButton = new QRadioButton(customerTypeButtonGroup);
        buyerButton->setObjectName(QString::fromUtf8("buyerButton"));
        buyerButton->setGeometry(QRect(10, 60, 170, 30));
        buyerButton->setChecked(false);
        transactionTable = new Q3Table(InvoiceDialog);
        transactionTable->setObjectName(QString::fromUtf8("transactionTable"));
        transactionTable->setGeometry(QRect(20, 230, 871, 270));
        transactionTable->setProperty("numRows", QVariant(0));
        transactionTable->setProperty("numCols", QVariant(10));
        transactionTable->setProperty("showGrid", QVariant(false));
        transactionTable->setProperty("readOnly", QVariant(true));
        changeStatusButton = new QPushButton(InvoiceDialog);
        changeStatusButton->setObjectName(QString::fromUtf8("changeStatusButton"));
        changeStatusButton->setGeometry(QRect(10, 180, 120, 30));
        changeStatusButton->setAutoDefault(false);
        textLabel2_9_2 = new QLabel(InvoiceDialog);
        textLabel2_9_2->setObjectName(QString::fromUtf8("textLabel2_9_2"));
        textLabel2_9_2->setGeometry(QRect(300, 50, 100, 30));
        textLabel2_9_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_9_2->setWordWrap(false);
        sinvCompany = new QLineEdit(InvoiceDialog);
        sinvCompany->setObjectName(QString::fromUtf8("sinvCompany"));
        sinvCompany->setEnabled(true);
        sinvCompany->setGeometry(QRect(410, 90, 280, 30));
        sinvAddress1 = new QLineEdit(InvoiceDialog);
        sinvAddress1->setObjectName(QString::fromUtf8("sinvAddress1"));
        sinvAddress1->setGeometry(QRect(90, 90, 190, 30));
        sinvID = new QLineEdit(InvoiceDialog);
        sinvID->setObjectName(QString::fromUtf8("sinvID"));
        sinvID->setGeometry(QRect(90, 10, 70, 30));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(230, 230, 230, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(250, 250, 250, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(253, 253, 253, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(143, 143, 143, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(191, 191, 191, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush7(QColor(76, 89, 166, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush7);
        palette.setBrush(QPalette::Active, QPalette::HighlightedText, brush6);
        QBrush brush8(QColor(0, 0, 192, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Link, brush8);
        QBrush brush9(QColor(128, 0, 128, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::LinkVisited, brush9);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Link, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::LinkVisited, brush9);
        QBrush brush10(QColor(128, 128, 128, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush10);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush6);
        QBrush brush11(QColor(115, 115, 115, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush11);
        QBrush brush12(QColor(153, 153, 153, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush12);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush10);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::Link, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::LinkVisited, brush9);
        sinvID->setPalette(palette);
        compAddressButton = new QPushButton(InvoiceDialog);
        compAddressButton->setObjectName(QString::fromUtf8("compAddressButton"));
        compAddressButton->setGeometry(QRect(140, 180, 148, 32));
        compAddressButton->setAutoDefault(false);
        emailInvoiceButton = new QPushButton(InvoiceDialog);
        emailInvoiceButton->setObjectName(QString::fromUtf8("emailInvoiceButton"));
        emailInvoiceButton->setGeometry(QRect(630, 10, 71, 31));
        emailInvoiceButton->setFocusPolicy(Qt::NoFocus);
        showMissingBuyersButton = new QPushButton(InvoiceDialog);
        showMissingBuyersButton->setObjectName(QString::fromUtf8("showMissingBuyersButton"));
        showMissingBuyersButton->setGeometry(QRect(10, 590, 121, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Verdana"));
        font1.setPointSize(13);
        font1.setBold(false);
        font1.setWeight(50);
        showMissingBuyersButton->setFont(font1);
        showMissingBuyersButton->setFocusPolicy(Qt::NoFocus);
        QWidget::setTabOrder(sinvID, sinvName);
        QWidget::setTabOrder(sinvName, sinvAddress1);
        QWidget::setTabOrder(sinvAddress1, sinvAddress2);
        QWidget::setTabOrder(sinvAddress2, sinvHead);
        QWidget::setTabOrder(sinvHead, sinvCity);
        QWidget::setTabOrder(sinvCity, sinvState);
        QWidget::setTabOrder(sinvState, sinvZip);
        QWidget::setTabOrder(sinvZip, sinvCompany);
        QWidget::setTabOrder(sinvCompany, sinvComment);
        QWidget::setTabOrder(sinvComment, sinvPrintButton);
        QWidget::setTabOrder(sinvPrintButton, sinvListReadyButton);
        QWidget::setTabOrder(sinvListReadyButton, sinvTrucking);
        QWidget::setTabOrder(sinvTrucking, sinvChgButt);
        QWidget::setTabOrder(sinvChgButt, sinvSaveDaily);
        QWidget::setTabOrder(sinvSaveDaily, sinvPreviewButton);
        QWidget::setTabOrder(sinvPreviewButton, prorateButton);
        QWidget::setTabOrder(prorateButton, sellerButton);
        QWidget::setTabOrder(sellerButton, buyerRecapButton);
        QWidget::setTabOrder(buyerRecapButton, transactionTable);
        QWidget::setTabOrder(transactionTable, cycleButton);

        retranslateUi(InvoiceDialog);

        QMetaObject::connectSlotsByName(InvoiceDialog);
    } // setupUi

    void retranslateUi(QDialog *InvoiceDialog)
    {
        InvoiceDialog->setWindowTitle(QApplication::translate("InvoiceDialog", "Invoice", 0, QApplication::UnicodeUTF8));
        binvUnpaid->setText(QApplication::translate("InvoiceDialog", "<p align=\"center\">UNPAID</p>", 0, QApplication::UnicodeUTF8));
        binvCompany->setText(QApplication::translate("InvoiceDialog", "<p align=\"center\">Company</p>", 0, QApplication::UnicodeUTF8));
        binvPaid->setText(QApplication::translate("InvoiceDialog", "<p align=\"center\">PAID</p>", 0, QApplication::UnicodeUTF8));
        sinvTotals->setText(QApplication::translate("InvoiceDialog", "Total:", 0, QApplication::UnicodeUTF8));
        sinvPrintButton->setText(QApplication::translate("InvoiceDialog", "&Print", 0, QApplication::UnicodeUTF8));
        sinvPrintButton->setShortcut(QApplication::translate("InvoiceDialog", "Alt+P", 0, QApplication::UnicodeUTF8));
        sinvPreviewButton->setText(QApplication::translate("InvoiceDialog", "Previe&w", 0, QApplication::UnicodeUTF8));
        sinvPreviewButton->setShortcut(QApplication::translate("InvoiceDialog", "Alt+W", 0, QApplication::UnicodeUTF8));
        sinvListReadyButton->setText(QApplication::translate("InvoiceDialog", "&List Ready", 0, QApplication::UnicodeUTF8));
        sinvListReadyButton->setShortcut(QApplication::translate("InvoiceDialog", "Alt+L", 0, QApplication::UnicodeUTF8));
        sinvSaveDaily->setText(QApplication::translate("InvoiceDialog", "S&ave Daily", 0, QApplication::UnicodeUTF8));
        sinvSaveDaily->setShortcut(QApplication::translate("InvoiceDialog", "Alt+A", 0, QApplication::UnicodeUTF8));
        sinvChgButt->setText(QApplication::translate("InvoiceDialog", "&Charges", 0, QApplication::UnicodeUTF8));
        sinvChgButt->setShortcut(QApplication::translate("InvoiceDialog", "Alt+C", 0, QApplication::UnicodeUTF8));
        sinvTrucking->setText(QApplication::translate("InvoiceDialog", "Truc&king", 0, QApplication::UnicodeUTF8));
        sinvTrucking->setShortcut(QApplication::translate("InvoiceDialog", "Alt+K", 0, QApplication::UnicodeUTF8));
        sinvPrinted->setText(QApplication::translate("InvoiceDialog", "<p align=\"right\"><b>** Printed **</b></p>", 0, QApplication::UnicodeUTF8));
        saleDateLabel->setText(QString());
        companyLabel->setText(QApplication::translate("InvoiceDialog", "Mortgage", 0, QApplication::UnicodeUTF8));
        textLabel3_2->setText(QApplication::translate("InvoiceDialog", "Comment", 0, QApplication::UnicodeUTF8));
        textLabel1_2_2_2->setText(QApplication::translate("InvoiceDialog", "Name", 0, QApplication::UnicodeUTF8));
        textLabel1_9_2->setText(QApplication::translate("InvoiceDialog", "Address", 0, QApplication::UnicodeUTF8));
        sinvHCountWarning->setText(QApplication::translate("InvoiceDialog", "<center><h3>** Head Count Does Not Match Check-In **</h3></center>", 0, QApplication::UnicodeUTF8));
        textLabel1_6_2->setText(QApplication::translate("InvoiceDialog", "Number", 0, QApplication::UnicodeUTF8));
        cycleButton->setText(QApplication::translate("InvoiceDialog", "Re&maining", 0, QApplication::UnicodeUTF8));
        cycleButton->setShortcut(QApplication::translate("InvoiceDialog", "Alt+M", 0, QApplication::UnicodeUTF8));
        sinvOverallAverage->setText(QString());
        sinvOverallBid->setText(QString());
        sinvOverallTotal->setText(QString());
        sinvOverallWeight->setText(QString());
        sinvOverallHead->setText(QString());
        buyerRecapButton->setText(QApplication::translate("InvoiceDialog", "&Recap", 0, QApplication::UnicodeUTF8));
        buyerRecapButton->setShortcut(QApplication::translate("InvoiceDialog", "Alt+R", 0, QApplication::UnicodeUTF8));
        prorateButton->setText(QApplication::translate("InvoiceDialog", "P&rorate", 0, QApplication::UnicodeUTF8));
        prorateButton->setShortcut(QApplication::translate("InvoiceDialog", "Alt+R", 0, QApplication::UnicodeUTF8));
        globalPenButton->setText(QApplication::translate("InvoiceDialog", "Pe&n Change", 0, QApplication::UnicodeUTF8));
        globalPenButton->setShortcut(QApplication::translate("InvoiceDialog", "Alt+N", 0, QApplication::UnicodeUTF8));
        faxInvoiceButton->setText(QApplication::translate("InvoiceDialog", "Fa&x", 0, QApplication::UnicodeUTF8));
        faxInvoiceButton->setShortcut(QApplication::translate("InvoiceDialog", "Alt+X", 0, QApplication::UnicodeUTF8));
        headLabel->setText(QApplication::translate("InvoiceDialog", "Head", 0, QApplication::UnicodeUTF8));
        globalBuyerButton->setText(QApplication::translate("InvoiceDialog", "# Chan&ge", 0, QApplication::UnicodeUTF8));
        globalBuyerButton->setShortcut(QApplication::translate("InvoiceDialog", "Alt+G", 0, QApplication::UnicodeUTF8));
        customerTypeButtonGroup->setTitle(QApplication::translate("InvoiceDialog", "Customer Type", 0, QApplication::UnicodeUTF8));
        sellerButton->setText(QApplication::translate("InvoiceDialog", "Se&ller", 0, QApplication::UnicodeUTF8));
        sellerButton->setShortcut(QApplication::translate("InvoiceDialog", "Alt+S", 0, QApplication::UnicodeUTF8));
        buyerButton->setText(QApplication::translate("InvoiceDialog", "Bu&yer", 0, QApplication::UnicodeUTF8));
        buyerButton->setShortcut(QApplication::translate("InvoiceDialog", "Alt+Y", 0, QApplication::UnicodeUTF8));
        changeStatusButton->setText(QApplication::translate("InvoiceDialog", "Set Status", 0, QApplication::UnicodeUTF8));
        textLabel2_9_2->setText(QApplication::translate("InvoiceDialog", "City/St/Zip", 0, QApplication::UnicodeUTF8));
        compAddressButton->setText(QApplication::translate("InvoiceDialog", "Comp Address", 0, QApplication::UnicodeUTF8));
        compAddressButton->setShortcut(QString());
        emailInvoiceButton->setText(QApplication::translate("InvoiceDialog", "E-Mail", 0, QApplication::UnicodeUTF8));
        showMissingBuyersButton->setText(QApplication::translate("InvoiceDialog", "Show Missing", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class InvoiceDialog: public Ui_InvoiceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVOICEDIALOG_H
