/********************************************************************************
** Form generated from reading UI file 'clerksetupdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLERKSETUPDIALOG_H
#define UI_CLERKSETUPDIALOG_H

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
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTextEdit>
#include "dao/setupdao.h"

QT_BEGIN_NAMESPACE

class Ui_ClerkSetupDialog
{
public:
    Q3GroupBox *groupBox17;
    Q3Table *clerkInputTable;
    QCheckBox *clerkBuyerNamesCheckBox;
    QLabel *textLabel1;
    QSpinBox *clerkTicketLengthBox;
    QCheckBox *tagSearchBox;
    Q3ButtonGroup *buttonGroup2;
    QCheckBox *pennerPenEditable;
    QCheckBox *pennerBidEditable;
    QCheckBox *pennerBuyerEditable;
    QPushButton *cancelButton;
    QLineEdit *ticketHeadingEdit;
    QLabel *ticketHeadingLabel;
    QCheckBox *ticketFormatCheckBox;
    QCheckBox *sellerOnTicketBox;
    QCheckBox *printPermBuyersCheckBox;
    QPushButton *acceptButton;
    QFrame *frame;
    QLabel *scaleMaxWeightlabel;
    QTextEdit *scaleMaxWeightTextEdit;
    QCheckBox *zeroBalNotifycheckBox;
    QLabel *textLabelTopSkip;
    QSpinBox *clerkTicketTopSkipLinesBox;
    QCheckBox *skipSellerIfFoundBox;
    QCheckBox *presortCheckBox;
    QCheckBox *clerkLoadLastSellerNumberCheckBox;
    QCheckBox *vetTicketsOnCheckBox;
    QCheckBox *sellingOnLeftcheckBox;

    void setupUi(QDialog *ClerkSetupDialog)
    {
        if (ClerkSetupDialog->objectName().isEmpty())
            ClerkSetupDialog->setObjectName(QString::fromUtf8("ClerkSetupDialog"));
        ClerkSetupDialog->setWindowModality(Qt::ApplicationModal);
        ClerkSetupDialog->resize(507, 669);
        QFont font;
        font.setPointSize(13);
        ClerkSetupDialog->setFont(font);
        groupBox17 = new Q3GroupBox(ClerkSetupDialog);
        groupBox17->setObjectName(QString::fromUtf8("groupBox17"));
        groupBox17->setGeometry(QRect(10, 0, 210, 350));
        clerkInputTable = new Q3Table(groupBox17);
        clerkInputTable->setObjectName(QString::fromUtf8("clerkInputTable"));
        clerkInputTable->setGeometry(QRect(11, 22, 190, 270));
        clerkInputTable->setProperty("numRows", QVariant(10));
        clerkInputTable->setProperty("numCols", QVariant(1));
        clerkBuyerNamesCheckBox = new QCheckBox(groupBox17);
        clerkBuyerNamesCheckBox->setObjectName(QString::fromUtf8("clerkBuyerNamesCheckBox"));
        clerkBuyerNamesCheckBox->setGeometry(QRect(10, 310, 190, 30));
        textLabel1 = new QLabel(ClerkSetupDialog);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(300, 150, 191, 30));
        textLabel1->setWordWrap(false);
        clerkTicketLengthBox = new QSpinBox(ClerkSetupDialog);
        clerkTicketLengthBox->setObjectName(QString::fromUtf8("clerkTicketLengthBox"));
        clerkTicketLengthBox->setGeometry(QRect(230, 150, 60, 31));
        tagSearchBox = new QCheckBox(ClerkSetupDialog);
        tagSearchBox->setObjectName(QString::fromUtf8("tagSearchBox"));
        tagSearchBox->setGeometry(QRect(230, 240, 230, 31));
        buttonGroup2 = new Q3ButtonGroup(ClerkSetupDialog);
        buttonGroup2->setObjectName(QString::fromUtf8("buttonGroup2"));
        buttonGroup2->setGeometry(QRect(230, 10, 220, 130));
        pennerPenEditable = new QCheckBox(buttonGroup2);
        pennerPenEditable->setObjectName(QString::fromUtf8("pennerPenEditable"));
        pennerPenEditable->setGeometry(QRect(10, 90, 160, 30));
        pennerBidEditable = new QCheckBox(buttonGroup2);
        pennerBidEditable->setObjectName(QString::fromUtf8("pennerBidEditable"));
        pennerBidEditable->setGeometry(QRect(10, 60, 160, 30));
        pennerBuyerEditable = new QCheckBox(buttonGroup2);
        pennerBuyerEditable->setObjectName(QString::fromUtf8("pennerBuyerEditable"));
        pennerBuyerEditable->setGeometry(QRect(10, 30, 160, 30));
        cancelButton = new QPushButton(ClerkSetupDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(241, 620, 100, 30));
        ticketHeadingEdit = new QLineEdit(ClerkSetupDialog);
        ticketHeadingEdit->setObjectName(QString::fromUtf8("ticketHeadingEdit"));
        ticketHeadingEdit->setGeometry(QRect(151, 470, 320, 31));
        ticketHeadingLabel = new QLabel(ClerkSetupDialog);
        ticketHeadingLabel->setObjectName(QString::fromUtf8("ticketHeadingLabel"));
        ticketHeadingLabel->setGeometry(QRect(20, 470, 131, 31));
        ticketHeadingLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ticketHeadingLabel->setWordWrap(false);
        ticketFormatCheckBox = new QCheckBox(ClerkSetupDialog);
        ticketFormatCheckBox->setObjectName(QString::fromUtf8("ticketFormatCheckBox"));
        ticketFormatCheckBox->setGeometry(QRect(230, 390, 230, 31));
        sellerOnTicketBox = new QCheckBox(ClerkSetupDialog);
        sellerOnTicketBox->setObjectName(QString::fromUtf8("sellerOnTicketBox"));
        sellerOnTicketBox->setGeometry(QRect(230, 310, 230, 31));
        printPermBuyersCheckBox = new QCheckBox(ClerkSetupDialog);
        printPermBuyersCheckBox->setObjectName(QString::fromUtf8("printPermBuyersCheckBox"));
        printPermBuyersCheckBox->setGeometry(QRect(230, 350, 271, 31));
        acceptButton = new QPushButton(ClerkSetupDialog);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));
        acceptButton->setGeometry(QRect(360, 620, 101, 30));
        frame = new QFrame(ClerkSetupDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(30, 510, 441, 91));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        scaleMaxWeightlabel = new QLabel(frame);
        scaleMaxWeightlabel->setObjectName(QString::fromUtf8("scaleMaxWeightlabel"));
        scaleMaxWeightlabel->setEnabled(true);
        scaleMaxWeightlabel->setGeometry(QRect(30, 50, 141, 16));
        scaleMaxWeightlabel->setFont(font);
        scaleMaxWeightTextEdit = new QTextEdit(frame);
        scaleMaxWeightTextEdit->setObjectName(QString::fromUtf8("scaleMaxWeightTextEdit"));
        scaleMaxWeightTextEdit->setEnabled(true);
        scaleMaxWeightTextEdit->setGeometry(QRect(180, 40, 171, 31));
        QFont font1;
        font1.setPointSize(12);
        scaleMaxWeightTextEdit->setFont(font1);
        scaleMaxWeightTextEdit->setAcceptDrops(false);
        scaleMaxWeightTextEdit->setAcceptRichText(false);
        zeroBalNotifycheckBox = new QCheckBox(frame);
        zeroBalNotifycheckBox->setObjectName(QString::fromUtf8("zeroBalNotifycheckBox"));
        zeroBalNotifycheckBox->setGeometry(QRect(10, 10, 231, 19));
        textLabelTopSkip = new QLabel(ClerkSetupDialog);
        textLabelTopSkip->setObjectName(QString::fromUtf8("textLabelTopSkip"));
        textLabelTopSkip->setGeometry(QRect(300, 190, 161, 30));
        textLabelTopSkip->setWordWrap(false);
        clerkTicketTopSkipLinesBox = new QSpinBox(ClerkSetupDialog);
        clerkTicketTopSkipLinesBox->setObjectName(QString::fromUtf8("clerkTicketTopSkipLinesBox"));
        clerkTicketTopSkipLinesBox->setGeometry(QRect(230, 190, 60, 31));
        skipSellerIfFoundBox = new QCheckBox(ClerkSetupDialog);
        skipSellerIfFoundBox->setObjectName(QString::fromUtf8("skipSellerIfFoundBox"));
        skipSellerIfFoundBox->setGeometry(QRect(230, 280, 201, 19));
        presortCheckBox = new QCheckBox(ClerkSetupDialog);
        presortCheckBox->setObjectName(QString::fromUtf8("presortCheckBox"));
        presortCheckBox->setGeometry(QRect(60, 620, 111, 19));
        clerkLoadLastSellerNumberCheckBox = new QCheckBox(ClerkSetupDialog);
        clerkLoadLastSellerNumberCheckBox->setObjectName(QString::fromUtf8("clerkLoadLastSellerNumberCheckBox"));
        clerkLoadLastSellerNumberCheckBox->setGeometry(QRect(230, 430, 261, 20));
        vetTicketsOnCheckBox = new QCheckBox(ClerkSetupDialog);
        vetTicketsOnCheckBox->setObjectName(QString::fromUtf8("vetTicketsOnCheckBox"));
        vetTicketsOnCheckBox->setEnabled(false);
        vetTicketsOnCheckBox->setGeometry(QRect(20, 360, 151, 20));
        sellingOnLeftcheckBox = new QCheckBox(ClerkSetupDialog);
        sellingOnLeftcheckBox->setObjectName(QString::fromUtf8("sellingOnLeftcheckBox"));
        sellingOnLeftcheckBox->setGeometry(QRect(20, 399, 181, 51));

        retranslateUi(ClerkSetupDialog);

        QMetaObject::connectSlotsByName(ClerkSetupDialog);
    } // setupUi

    void retranslateUi(QDialog *ClerkSetupDialog)
    {
        ClerkSetupDialog->setWindowTitle(QApplication::translate("ClerkSetupDialog", "Setup Clerk And Penner", 0, QApplication::UnicodeUTF8));
        groupBox17->setTitle(QApplication::translate("ClerkSetupDialog", "Clerk Order of Inputs", 0, QApplication::UnicodeUTF8));
        clerkBuyerNamesCheckBox->setText(QApplication::translate("ClerkSetupDialog", "Buyer Names", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("ClerkSetupDialog", "Ticket Length (FF=0)", 0, QApplication::UnicodeUTF8));
        tagSearchBox->setText(QApplication::translate("ClerkSetupDialog", "Search Tags For Seller", 0, QApplication::UnicodeUTF8));
        buttonGroup2->setTitle(QApplication::translate("ClerkSetupDialog", "Penner Edit Fields", 0, QApplication::UnicodeUTF8));
        pennerPenEditable->setText(QApplication::translate("ClerkSetupDialog", "Pen", 0, QApplication::UnicodeUTF8));
        pennerBidEditable->setText(QApplication::translate("ClerkSetupDialog", "Bid Price", 0, QApplication::UnicodeUTF8));
        pennerBuyerEditable->setText(QApplication::translate("ClerkSetupDialog", "Buyer", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("ClerkSetupDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        ticketHeadingLabel->setText(QApplication::translate("ClerkSetupDialog", "Ticket Heading:", 0, QApplication::UnicodeUTF8));
        ticketFormatCheckBox->setText(QApplication::translate("ClerkSetupDialog", "Alternate Ticket Format", 0, QApplication::UnicodeUTF8));
        sellerOnTicketBox->setText(QApplication::translate("ClerkSetupDialog", "Seller Name On Ticket", 0, QApplication::UnicodeUTF8));
        printPermBuyersCheckBox->setText(QApplication::translate("ClerkSetupDialog", "Print Perm Buyers On Ticket", 0, QApplication::UnicodeUTF8));
        acceptButton->setText(QApplication::translate("ClerkSetupDialog", "Accept", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        scaleMaxWeightlabel->setToolTip(QApplication::translate("ClerkSetupDialog", "<html><head/><body><p>If scale weighs half this amount, or more, Zero Balance will be required.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        scaleMaxWeightlabel->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        scaleMaxWeightlabel->setText(QApplication::translate("ClerkSetupDialog", "Scale Max Weight: ", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        scaleMaxWeightTextEdit->setToolTip(QApplication::translate("ClerkSetupDialog", "<html><head/><body><p>If scale weighs half this amount, or more, Zero Balance will be required.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        zeroBalNotifycheckBox->setText(QApplication::translate("ClerkSetupDialog", "Zero Balance Notifications", 0, QApplication::UnicodeUTF8));
        textLabelTopSkip->setText(QApplication::translate("ClerkSetupDialog", "Skip lines from top", 0, QApplication::UnicodeUTF8));
        skipSellerIfFoundBox->setText(QApplication::translate("ClerkSetupDialog", "Skip Seller If Found", 0, QApplication::UnicodeUTF8));
        presortCheckBox->setText(QApplication::translate("ClerkSetupDialog", "Presort ON", 0, QApplication::UnicodeUTF8));
        clerkLoadLastSellerNumberCheckBox->setText(QApplication::translate("ClerkSetupDialog", "Preload Last Seller Number", 0, QApplication::UnicodeUTF8));
        vetTicketsOnCheckBox->setText(QApplication::translate("ClerkSetupDialog", "Vet Tickets ON", 0, QApplication::UnicodeUTF8));
        sellingOnLeftcheckBox->setText(QApplication::translate("ClerkSetupDialog", "Audience Display\n"
"Selling on Left", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ClerkSetupDialog: public Ui_ClerkSetupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLERKSETUPDIALOG_H
