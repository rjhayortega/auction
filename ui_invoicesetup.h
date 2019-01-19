/********************************************************************************
** Form generated from reading UI file 'invoicesetup.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVOICESETUP_H
#define UI_INVOICESETUP_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Table>
#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include "dao/invoicedao.h"

QT_BEGIN_NAMESPACE

class Ui_InvoiceSetup
{
public:
    QComboBox *commissionDefaultCombo;
    QCheckBox *showNumberBox;
    QLabel *textLabel1_2;
    QSpinBox *invoiceHeight;
    QLabel *commissionDefaultLabel;
    QSpinBox *topSkip;
    QCheckBox *showNameBox;
    Q3GroupBox *checkOnInvoiceGroup;
    QCheckBox *checkOnInvoice;
    QSpinBox *checkStartLine;
    QCheckBox *prorateInvoiceCheckBox;
    QLabel *checkLineLabel;
    QCheckBox *checkPrinterOption;
    QLabel *textLabel1;
    Q3Table *transTableSetup;
    QLabel *textLabel1_3;
    QSpinBox *minHeaderSizeSpin;
    QLabel *textLabel1_3_2_2;
    QLabel *textLabel1_3_2_3;
    QLabel *textLabel1_3_2;
    QSpinBox *transOverrideColumnSpin;
    QLabel *textLabel1_3_2_2_2;
    QSpinBox *transOverrideLengthSpin;
    Q3TextEdit *marketInvoiceComment;
    QLabel *textLabel1_2_2_2;
    QCheckBox *totalNSCheckBox;
    Q3TextEdit *marketInvoiceDisclaimer;
    QPushButton *saveButton;
    QCheckBox *brandOptionCheckBox;
    QCheckBox *averageOptionCheckBox;
    QCheckBox *averageOnLeftCheckBox;
    QCheckBox *showTransactionCommentBox;
    QLabel *textLabel1_2_2;
    QCheckBox *groupChargesBox;
    QCheckBox *showTagsAtBottomOfInvoiceCheckBox;
    QSpinBox *lpCopyCountSpinBox;
    QLabel *label;
    QLabel *laserPrinterChecksOnlyPrintAtLabel;
    QCheckBox *checkBoxLaserCheckTop;
    QCheckBox *checkBoxLaserCheckBottom;
    QCheckBox *checkBoxLaserCheckMiddle;
    QLineEdit *linesPerCheck;
    QLabel *linesPerCheckLabel;
    QFrame *secondCopyFrame;
    QCheckBox *secondCopyPrinterOption;
    QLabel *checkLineCopyLabel;
    QSpinBox *checkLineStartCopy;

    void setupUi(QDialog *InvoiceSetup)
    {
        if (InvoiceSetup->objectName().isEmpty())
            InvoiceSetup->setObjectName(QString::fromUtf8("InvoiceSetup"));
        InvoiceSetup->setWindowModality(Qt::ApplicationModal);
        InvoiceSetup->setEnabled(true);
        InvoiceSetup->resize(953, 642);
        QFont font;
        font.setPointSize(13);
        InvoiceSetup->setFont(font);
        commissionDefaultCombo = new QComboBox(InvoiceSetup);
        commissionDefaultCombo->setObjectName(QString::fromUtf8("commissionDefaultCombo"));
        commissionDefaultCombo->setGeometry(QRect(820, 10, 120, 31));
        showNumberBox = new QCheckBox(InvoiceSetup);
        showNumberBox->setObjectName(QString::fromUtf8("showNumberBox"));
        showNumberBox->setGeometry(QRect(490, 10, 180, 30));
        textLabel1_2 = new QLabel(InvoiceSetup);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(240, 10, 150, 30));
        textLabel1_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_2->setWordWrap(false);
        invoiceHeight = new QSpinBox(InvoiceSetup);
        invoiceHeight->setObjectName(QString::fromUtf8("invoiceHeight"));
        invoiceHeight->setGeometry(QRect(400, 10, 60, 30));
        invoiceHeight->setMinimum(10);
        invoiceHeight->setMaximum(68);
        invoiceHeight->setValue(45);
        commissionDefaultLabel = new QLabel(InvoiceSetup);
        commissionDefaultLabel->setObjectName(QString::fromUtf8("commissionDefaultLabel"));
        commissionDefaultLabel->setGeometry(QRect(670, 10, 131, 31));
        commissionDefaultLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        commissionDefaultLabel->setWordWrap(false);
        topSkip = new QSpinBox(InvoiceSetup);
        topSkip->setObjectName(QString::fromUtf8("topSkip"));
        topSkip->setGeometry(QRect(170, 10, 60, 30));
        topSkip->setMinimum(0);
        topSkip->setMaximum(35);
        topSkip->setValue(0);
        showNameBox = new QCheckBox(InvoiceSetup);
        showNameBox->setObjectName(QString::fromUtf8("showNameBox"));
        showNameBox->setGeometry(QRect(20, 190, 200, 30));
        checkOnInvoiceGroup = new Q3GroupBox(InvoiceSetup);
        checkOnInvoiceGroup->setObjectName(QString::fromUtf8("checkOnInvoiceGroup"));
        checkOnInvoiceGroup->setGeometry(QRect(300, 180, 650, 120));
        checkOnInvoice = new QCheckBox(checkOnInvoiceGroup);
        checkOnInvoice->setObjectName(QString::fromUtf8("checkOnInvoice"));
        checkOnInvoice->setGeometry(QRect(20, 30, 230, 30));
        checkStartLine = new QSpinBox(checkOnInvoiceGroup);
        checkStartLine->setObjectName(QString::fromUtf8("checkStartLine"));
        checkStartLine->setGeometry(QRect(440, 30, 60, 30));
        checkStartLine->setMinimum(1);
        checkStartLine->setMaximum(64);
        checkStartLine->setValue(45);
        prorateInvoiceCheckBox = new QCheckBox(checkOnInvoiceGroup);
        prorateInvoiceCheckBox->setObjectName(QString::fromUtf8("prorateInvoiceCheckBox"));
        prorateInvoiceCheckBox->setGeometry(QRect(20, 70, 230, 30));
        checkLineLabel = new QLabel(checkOnInvoiceGroup);
        checkLineLabel->setObjectName(QString::fromUtf8("checkLineLabel"));
        checkLineLabel->setGeometry(QRect(270, 30, 160, 30));
        checkLineLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        checkLineLabel->setWordWrap(false);
        checkPrinterOption = new QCheckBox(checkOnInvoiceGroup);
        checkPrinterOption->setObjectName(QString::fromUtf8("checkPrinterOption"));
        checkPrinterOption->setGeometry(QRect(260, 70, 380, 31));
        textLabel1 = new QLabel(InvoiceSetup);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(30, 10, 130, 30));
        textLabel1->setFrameShape(QFrame::NoFrame);
        textLabel1->setFrameShadow(QFrame::Plain);
        textLabel1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1->setWordWrap(false);
        transTableSetup = new Q3Table(InvoiceSetup);
        transTableSetup->setObjectName(QString::fromUtf8("transTableSetup"));
        transTableSetup->setGeometry(QRect(10, 90, 930, 88));
        transTableSetup->setProperty("numRows", QVariant(1));
        transTableSetup->setProperty("numCols", QVariant(11));
        textLabel1_3 = new QLabel(InvoiceSetup);
        textLabel1_3->setObjectName(QString::fromUtf8("textLabel1_3"));
        textLabel1_3->setGeometry(QRect(9, 50, 151, 30));
        textLabel1_3->setFrameShape(QFrame::NoFrame);
        textLabel1_3->setFrameShadow(QFrame::Plain);
        textLabel1_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_3->setWordWrap(false);
        minHeaderSizeSpin = new QSpinBox(InvoiceSetup);
        minHeaderSizeSpin->setObjectName(QString::fromUtf8("minHeaderSizeSpin"));
        minHeaderSizeSpin->setGeometry(QRect(170, 50, 60, 30));
        minHeaderSizeSpin->setMinimum(0);
        minHeaderSizeSpin->setMaximum(15);
        minHeaderSizeSpin->setValue(0);
        textLabel1_3_2_2 = new QLabel(InvoiceSetup);
        textLabel1_3_2_2->setObjectName(QString::fromUtf8("textLabel1_3_2_2"));
        textLabel1_3_2_2->setGeometry(QRect(460, 50, 140, 30));
        textLabel1_3_2_2->setFrameShape(QFrame::NoFrame);
        textLabel1_3_2_2->setFrameShadow(QFrame::Plain);
        textLabel1_3_2_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        textLabel1_3_2_2->setWordWrap(false);
        textLabel1_3_2_3 = new QLabel(InvoiceSetup);
        textLabel1_3_2_3->setObjectName(QString::fromUtf8("textLabel1_3_2_3"));
        textLabel1_3_2_3->setGeometry(QRect(610, 50, 80, 30));
        textLabel1_3_2_3->setFrameShape(QFrame::NoFrame);
        textLabel1_3_2_3->setFrameShadow(QFrame::Plain);
        textLabel1_3_2_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_3_2_3->setWordWrap(false);
        textLabel1_3_2 = new QLabel(InvoiceSetup);
        textLabel1_3_2->setObjectName(QString::fromUtf8("textLabel1_3_2"));
        textLabel1_3_2->setGeometry(QRect(240, 50, 140, 30));
        textLabel1_3_2->setFrameShape(QFrame::NoFrame);
        textLabel1_3_2->setFrameShadow(QFrame::Plain);
        textLabel1_3_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_3_2->setWordWrap(false);
        transOverrideColumnSpin = new QSpinBox(InvoiceSetup);
        transOverrideColumnSpin->setObjectName(QString::fromUtf8("transOverrideColumnSpin"));
        transOverrideColumnSpin->setGeometry(QRect(390, 50, 60, 30));
        transOverrideColumnSpin->setMinimum(0);
        transOverrideColumnSpin->setMaximum(11);
        transOverrideColumnSpin->setValue(0);
        textLabel1_3_2_2_2 = new QLabel(InvoiceSetup);
        textLabel1_3_2_2_2->setObjectName(QString::fromUtf8("textLabel1_3_2_2_2"));
        textLabel1_3_2_2_2->setGeometry(QRect(770, 50, 140, 30));
        textLabel1_3_2_2_2->setFrameShape(QFrame::NoFrame);
        textLabel1_3_2_2_2->setFrameShadow(QFrame::Plain);
        textLabel1_3_2_2_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        textLabel1_3_2_2_2->setWordWrap(false);
        transOverrideLengthSpin = new QSpinBox(InvoiceSetup);
        transOverrideLengthSpin->setObjectName(QString::fromUtf8("transOverrideLengthSpin"));
        transOverrideLengthSpin->setGeometry(QRect(700, 50, 60, 30));
        transOverrideLengthSpin->setMinimum(0);
        transOverrideLengthSpin->setMaximum(96);
        transOverrideLengthSpin->setValue(0);
        marketInvoiceComment = new Q3TextEdit(InvoiceSetup);
        marketInvoiceComment->setObjectName(QString::fromUtf8("marketInvoiceComment"));
        marketInvoiceComment->setGeometry(QRect(10, 480, 480, 110));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bitstream Vera Sans Mono"));
        font1.setPointSize(13);
        marketInvoiceComment->setFont(font1);
        textLabel1_2_2_2 = new QLabel(InvoiceSetup);
        textLabel1_2_2_2->setObjectName(QString::fromUtf8("textLabel1_2_2_2"));
        textLabel1_2_2_2->setGeometry(QRect(500, 450, 480, 21));
        textLabel1_2_2_2->setWordWrap(false);
        totalNSCheckBox = new QCheckBox(InvoiceSetup);
        totalNSCheckBox->setObjectName(QString::fromUtf8("totalNSCheckBox"));
        totalNSCheckBox->setGeometry(QRect(700, 600, 141, 30));
        marketInvoiceDisclaimer = new Q3TextEdit(InvoiceSetup);
        marketInvoiceDisclaimer->setObjectName(QString::fromUtf8("marketInvoiceDisclaimer"));
        marketInvoiceDisclaimer->setGeometry(QRect(500, 480, 440, 110));
        marketInvoiceDisclaimer->setFont(font1);
        marketInvoiceDisclaimer->setProperty("overwriteMode", QVariant(true));
        saveButton = new QPushButton(InvoiceSetup);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(860, 600, 81, 31));
        brandOptionCheckBox = new QCheckBox(InvoiceSetup);
        brandOptionCheckBox->setObjectName(QString::fromUtf8("brandOptionCheckBox"));
        brandOptionCheckBox->setGeometry(QRect(500, 600, 191, 31));
        averageOptionCheckBox = new QCheckBox(InvoiceSetup);
        averageOptionCheckBox->setObjectName(QString::fromUtf8("averageOptionCheckBox"));
        averageOptionCheckBox->setGeometry(QRect(20, 600, 201, 31));
        averageOnLeftCheckBox = new QCheckBox(InvoiceSetup);
        averageOnLeftCheckBox->setObjectName(QString::fromUtf8("averageOnLeftCheckBox"));
        averageOnLeftCheckBox->setGeometry(QRect(240, 600, 240, 31));
        showTransactionCommentBox = new QCheckBox(InvoiceSetup);
        showTransactionCommentBox->setObjectName(QString::fromUtf8("showTransactionCommentBox"));
        showTransactionCommentBox->setGeometry(QRect(20, 230, 260, 30));
        textLabel1_2_2 = new QLabel(InvoiceSetup);
        textLabel1_2_2->setObjectName(QString::fromUtf8("textLabel1_2_2"));
        textLabel1_2_2->setGeometry(QRect(10, 450, 480, 21));
        textLabel1_2_2->setWordWrap(false);
        groupChargesBox = new QCheckBox(InvoiceSetup);
        groupChargesBox->setObjectName(QString::fromUtf8("groupChargesBox"));
        groupChargesBox->setGeometry(QRect(20, 270, 260, 30));
        showTagsAtBottomOfInvoiceCheckBox = new QCheckBox(InvoiceSetup);
        showTagsAtBottomOfInvoiceCheckBox->setObjectName(QString::fromUtf8("showTagsAtBottomOfInvoiceCheckBox"));
        showTagsAtBottomOfInvoiceCheckBox->setEnabled(true);
        showTagsAtBottomOfInvoiceCheckBox->setGeometry(QRect(20, 310, 321, 28));
        lpCopyCountSpinBox = new QSpinBox(InvoiceSetup);
        lpCopyCountSpinBox->setObjectName(QString::fromUtf8("lpCopyCountSpinBox"));
        lpCopyCountSpinBox->setGeometry(QRect(380, 350, 54, 31));
        lpCopyCountSpinBox->setValue(1);
        label = new QLabel(InvoiceSetup);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 350, 351, 31));
        laserPrinterChecksOnlyPrintAtLabel = new QLabel(InvoiceSetup);
        laserPrinterChecksOnlyPrintAtLabel->setObjectName(QString::fromUtf8("laserPrinterChecksOnlyPrintAtLabel"));
        laserPrinterChecksOnlyPrintAtLabel->setGeometry(QRect(20, 390, 261, 16));
        checkBoxLaserCheckTop = new QCheckBox(InvoiceSetup);
        checkBoxLaserCheckTop->setObjectName(QString::fromUtf8("checkBoxLaserCheckTop"));
        checkBoxLaserCheckTop->setGeometry(QRect(290, 390, 79, 19));
        checkBoxLaserCheckBottom = new QCheckBox(InvoiceSetup);
        checkBoxLaserCheckBottom->setObjectName(QString::fromUtf8("checkBoxLaserCheckBottom"));
        checkBoxLaserCheckBottom->setGeometry(QRect(290, 430, 79, 19));
        checkBoxLaserCheckMiddle = new QCheckBox(InvoiceSetup);
        checkBoxLaserCheckMiddle->setObjectName(QString::fromUtf8("checkBoxLaserCheckMiddle"));
        checkBoxLaserCheckMiddle->setGeometry(QRect(290, 410, 79, 19));
        linesPerCheck = new QLineEdit(InvoiceSetup);
        linesPerCheck->setObjectName(QString::fromUtf8("linesPerCheck"));
        linesPerCheck->setGeometry(QRect(530, 410, 41, 21));
        linesPerCheckLabel = new QLabel(InvoiceSetup);
        linesPerCheckLabel->setObjectName(QString::fromUtf8("linesPerCheckLabel"));
        linesPerCheckLabel->setGeometry(QRect(400, 410, 131, 21));
        secondCopyFrame = new QFrame(InvoiceSetup);
        secondCopyFrame->setObjectName(QString::fromUtf8("secondCopyFrame"));
        secondCopyFrame->setGeometry(QRect(460, 320, 441, 81));
        secondCopyFrame->setFrameShape(QFrame::StyledPanel);
        secondCopyFrame->setFrameShadow(QFrame::Raised);
        secondCopyPrinterOption = new QCheckBox(secondCopyFrame);
        secondCopyPrinterOption->setObjectName(QString::fromUtf8("secondCopyPrinterOption"));
        secondCopyPrinterOption->setGeometry(QRect(60, 0, 311, 31));
        checkLineCopyLabel = new QLabel(secondCopyFrame);
        checkLineCopyLabel->setObjectName(QString::fromUtf8("checkLineCopyLabel"));
        checkLineCopyLabel->setGeometry(QRect(50, 40, 221, 30));
        checkLineCopyLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        checkLineCopyLabel->setWordWrap(false);
        checkLineStartCopy = new QSpinBox(secondCopyFrame);
        checkLineStartCopy->setObjectName(QString::fromUtf8("checkLineStartCopy"));
        checkLineStartCopy->setGeometry(QRect(280, 40, 60, 30));
        checkLineStartCopy->setMinimum(1);
        checkLineStartCopy->setMaximum(64);
        checkLineStartCopy->setValue(45);
        QWidget::setTabOrder(topSkip, invoiceHeight);
        QWidget::setTabOrder(invoiceHeight, checkOnInvoice);
        QWidget::setTabOrder(checkOnInvoice, checkStartLine);
        QWidget::setTabOrder(checkStartLine, transTableSetup);
        QWidget::setTabOrder(transTableSetup, saveButton);

        retranslateUi(InvoiceSetup);

        QMetaObject::connectSlotsByName(InvoiceSetup);
    } // setupUi

    void retranslateUi(QDialog *InvoiceSetup)
    {
        InvoiceSetup->setWindowTitle(QApplication::translate("InvoiceSetup", "Setup Invoice", 0, QApplication::UnicodeUTF8));
        commissionDefaultCombo->clear();
        commissionDefaultCombo->insertItems(0, QStringList()
         << QApplication::translate("InvoiceSetup", "Buyer", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("InvoiceSetup", "Company", 0, QApplication::UnicodeUTF8)
        );
        showNumberBox->setText(QApplication::translate("InvoiceSetup", "Show Invoice# ?", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("InvoiceSetup", "Height of invoice", 0, QApplication::UnicodeUTF8));
        commissionDefaultLabel->setText(QApplication::translate("InvoiceSetup", "Comm Default:", 0, QApplication::UnicodeUTF8));
        showNameBox->setText(QApplication::translate("InvoiceSetup", "Show Names?", 0, QApplication::UnicodeUTF8));
        checkOnInvoiceGroup->setTitle(QApplication::translate("InvoiceSetup", "Check On Invoice Options", 0, QApplication::UnicodeUTF8));
        checkOnInvoice->setText(QApplication::translate("InvoiceSetup", "Print Chec&k On Invoice?", 0, QApplication::UnicodeUTF8));
        prorateInvoiceCheckBox->setText(QApplication::translate("InvoiceSetup", "Invoice Each Prorate?", 0, QApplication::UnicodeUTF8));
        checkLineLabel->setText(QApplication::translate("InvoiceSetup", "First Check Line", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        checkPrinterOption->setToolTip(QApplication::translate("InvoiceSetup", "Check this option to use the check printer for checks on invoices.<BR> If the check on invoice button is checked and no checks are printed,<BR> then the seller invoice printer is used.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        checkPrinterOption->setText(QApplication::translate("InvoiceSetup", "Print Checks W/ Invoices On Check Printer", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("InvoiceSetup", "Skip Lines:", 0, QApplication::UnicodeUTF8));
        textLabel1_3->setText(QApplication::translate("InvoiceSetup", "Min. Header Size:", 0, QApplication::UnicodeUTF8));
        textLabel1_3_2_2->setText(QApplication::translate("InvoiceSetup", "Table Columns", 0, QApplication::UnicodeUTF8));
        textLabel1_3_2_3->setText(QApplication::translate("InvoiceSetup", "Into:", 0, QApplication::UnicodeUTF8));
        textLabel1_3_2->setText(QApplication::translate("InvoiceSetup", "Force The Last:", 0, QApplication::UnicodeUTF8));
        textLabel1_3_2_2_2->setText(QApplication::translate("InvoiceSetup", "Text Columns", 0, QApplication::UnicodeUTF8));
        textLabel1_2_2_2->setText(QApplication::translate("InvoiceSetup", "Invoice Footer Comment", 0, QApplication::UnicodeUTF8));
        totalNSCheckBox->setText(QApplication::translate("InvoiceSetup", "N/S in total", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("InvoiceSetup", "Save", 0, QApplication::UnicodeUTF8));
        brandOptionCheckBox->setText(QApplication::translate("InvoiceSetup", "&Brands On Invoice", 0, QApplication::UnicodeUTF8));
        averageOptionCheckBox->setText(QApplication::translate("InvoiceSetup", "Show Sex Summar&y", 0, QApplication::UnicodeUTF8));
        averageOnLeftCheckBox->setText(QApplication::translate("InvoiceSetup", "&Overall Avg. / CWT On left", 0, QApplication::UnicodeUTF8));
        showTransactionCommentBox->setText(QApplication::translate("InvoiceSetup", "Show Transaction Comments?", 0, QApplication::UnicodeUTF8));
        textLabel1_2_2->setText(QApplication::translate("InvoiceSetup", "Invoice Header Comment", 0, QApplication::UnicodeUTF8));
        groupChargesBox->setText(QApplication::translate("InvoiceSetup", "&Group Charges By Name", 0, QApplication::UnicodeUTF8));
        groupChargesBox->setShortcut(QApplication::translate("InvoiceSetup", "Alt+G", 0, QApplication::UnicodeUTF8));
        showTagsAtBottomOfInvoiceCheckBox->setText(QApplication::translate("InvoiceSetup", "Show tag list at bottom of invoice", 0, QApplication::UnicodeUTF8));
        showTagsAtBottomOfInvoiceCheckBox->setShortcut(QString());
        label->setText(QApplication::translate("InvoiceSetup", "Number of copies (only for laser printer)", 0, QApplication::UnicodeUTF8));
        laserPrinterChecksOnlyPrintAtLabel->setText(QApplication::translate("InvoiceSetup", "Laser Printer, checks only. Print at:", 0, QApplication::UnicodeUTF8));
        checkBoxLaserCheckTop->setText(QApplication::translate("InvoiceSetup", "Top", 0, QApplication::UnicodeUTF8));
        checkBoxLaserCheckBottom->setText(QApplication::translate("InvoiceSetup", "Bottom", 0, QApplication::UnicodeUTF8));
        checkBoxLaserCheckMiddle->setText(QApplication::translate("InvoiceSetup", "Middle", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        linesPerCheck->setToolTip(QApplication::translate("InvoiceSetup", "<html><head/><body><p>This is normally 20. Calculated at 6 lines per inch, with 10 inches per page (two half inch margins, top and bottom). If it's not lining up for you, try changing this number by one and try again.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        linesPerCheck->setText(QApplication::translate("InvoiceSetup", "20", 0, QApplication::UnicodeUTF8));
        linesPerCheckLabel->setText(QApplication::translate("InvoiceSetup", "Lines per check:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        secondCopyPrinterOption->setToolTip(QApplication::translate("InvoiceSetup", "<html><head/><body><p>Check this option to use a second printer for a copy of the invoice.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        secondCopyPrinterOption->setText(QApplication::translate("InvoiceSetup", "Print copies on Second Copy Printer", 0, QApplication::UnicodeUTF8));
        checkLineCopyLabel->setText(QApplication::translate("InvoiceSetup", "First Check Line on copy: ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class InvoiceSetup: public Ui_InvoiceSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVOICESETUP_H
