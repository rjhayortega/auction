/********************************************************************************
** Form generated from reading UI file 'dailydialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DAILYDIALOG_H
#define UI_DAILYDIALOG_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3ListBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <vector>
#include "./dao/customerdao.h"
#include "./types/customer.h"
#include "dao/radiotagdao.h"
#include "dao/salemanager.h"
#include "dao/setupdao.h"
#include "serialport.h"

QT_BEGIN_NAMESPACE

class Ui_DailyDialog
{
public:
    QLabel *formHeader;
    QLineEdit *dailyAddress2;
    QLabel *textLabel2_6_3;
    QLineEdit *dailyMortgage;
    QLabel *companyLabel;
    QLabel *textLabel2_5_2;
    QLineEdit *dailyCity;
    QLabel *textLabel2_3_2;
    QLabel *textLabel2_4_3;
    QLabel *textLabel2_8;
    QLineEdit *dailyZip;
    QLineEdit *dailyAddress1;
    QLineEdit *dailyState;
    QCheckBox *dailyBeefCouncil;
    QLineEdit *dailyName;
    QLabel *textLabel1_4_2;
    Q3ListBox *rfTagListBox;
    QCheckBox *madCowCheckBox;
    QLabel *headLabel;
    QLineEdit *dailyID;
    QLineEdit *dailyHead;
    QPushButton *deleteDaily;
    QPushButton *dailyTrucking;
    QPushButton *printDailyButton;
    QPushButton *dailySave;
    QComboBox *letterComboBox;
    Q3ListBox *dailyPermListBox;
    Q3ButtonGroup *sortGroup;
    QRadioButton *nameSortRadio;
    QRadioButton *numberSortRadio;
    QPushButton *resetRecordButton;
    QPushButton *dailyCharges;
    QPushButton *vetButton;
    QLabel *textLabel1_3;
    QLabel *textLabel2_6_2_2;
    QLineEdit *dailyComment;
    Q3ListBox *dailyListBox;
    QPushButton *tagButtonDaily;
    QLabel *opInitialsLabel;
    QLineEdit *opInitials;
    QLineEdit *descrCode;
    QLabel *descrCodeLabel;
    QLabel *descriptionLabel;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QRadioButton *sellerButton;
    QRadioButton *buyerButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *showMissingBuyersButton;
    QButtonGroup *customerTypeButtonGroup;

    void setupUi(QDialog *DailyDialog)
    {
        if (DailyDialog->objectName().isEmpty())
            DailyDialog->setObjectName(QString::fromUtf8("DailyDialog"));
        DailyDialog->setWindowModality(Qt::ApplicationModal);
        DailyDialog->resize(932, 677);
        QFont font;
        font.setPointSize(13);
        DailyDialog->setFont(font);
        formHeader = new QLabel(DailyDialog);
        formHeader->setObjectName(QString::fromUtf8("formHeader"));
        formHeader->setGeometry(QRect(30, 10, 380, 64));
        formHeader->setWordWrap(false);
        dailyAddress2 = new QLineEdit(DailyDialog);
        dailyAddress2->setObjectName(QString::fromUtf8("dailyAddress2"));
        dailyAddress2->setGeometry(QRect(130, 210, 240, 31));
        textLabel2_6_3 = new QLabel(DailyDialog);
        textLabel2_6_3->setObjectName(QString::fromUtf8("textLabel2_6_3"));
        textLabel2_6_3->setGeometry(QRect(785, 130, 50, 30));
        textLabel2_6_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_6_3->setWordWrap(false);
        dailyMortgage = new QLineEdit(DailyDialog);
        dailyMortgage->setObjectName(QString::fromUtf8("dailyMortgage"));
        dailyMortgage->setGeometry(QRect(490, 170, 430, 31));
        companyLabel = new QLabel(DailyDialog);
        companyLabel->setObjectName(QString::fromUtf8("companyLabel"));
        companyLabel->setGeometry(QRect(380, 170, 100, 30));
        companyLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        companyLabel->setWordWrap(false);
        textLabel2_5_2 = new QLabel(DailyDialog);
        textLabel2_5_2->setObjectName(QString::fromUtf8("textLabel2_5_2"));
        textLabel2_5_2->setGeometry(QRect(670, 130, 60, 30));
        textLabel2_5_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_5_2->setWordWrap(false);
        dailyCity = new QLineEdit(DailyDialog);
        dailyCity->setObjectName(QString::fromUtf8("dailyCity"));
        dailyCity->setGeometry(QRect(490, 130, 160, 31));
        textLabel2_3_2 = new QLabel(DailyDialog);
        textLabel2_3_2->setObjectName(QString::fromUtf8("textLabel2_3_2"));
        textLabel2_3_2->setGeometry(QRect(11, 170, 110, 30));
        textLabel2_3_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_3_2->setWordWrap(false);
        textLabel2_4_3 = new QLabel(DailyDialog);
        textLabel2_4_3->setObjectName(QString::fromUtf8("textLabel2_4_3"));
        textLabel2_4_3->setGeometry(QRect(390, 130, 90, 30));
        textLabel2_4_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_4_3->setWordWrap(false);
        textLabel2_8 = new QLabel(DailyDialog);
        textLabel2_8->setObjectName(QString::fromUtf8("textLabel2_8"));
        textLabel2_8->setGeometry(QRect(10, 130, 110, 30));
        textLabel2_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_8->setWordWrap(false);
        dailyZip = new QLineEdit(DailyDialog);
        dailyZip->setObjectName(QString::fromUtf8("dailyZip"));
        dailyZip->setGeometry(QRect(850, 130, 70, 30));
        dailyAddress1 = new QLineEdit(DailyDialog);
        dailyAddress1->setObjectName(QString::fromUtf8("dailyAddress1"));
        dailyAddress1->setGeometry(QRect(130, 170, 240, 31));
        dailyState = new QLineEdit(DailyDialog);
        dailyState->setObjectName(QString::fromUtf8("dailyState"));
        dailyState->setGeometry(QRect(740, 130, 40, 31));
        dailyBeefCouncil = new QCheckBox(DailyDialog);
        dailyBeefCouncil->setObjectName(QString::fromUtf8("dailyBeefCouncil"));
        dailyBeefCouncil->setGeometry(QRect(250, 90, 160, 30));
        dailyName = new QLineEdit(DailyDialog);
        dailyName->setObjectName(QString::fromUtf8("dailyName"));
        dailyName->setGeometry(QRect(130, 130, 240, 31));
        textLabel1_4_2 = new QLabel(DailyDialog);
        textLabel1_4_2->setObjectName(QString::fromUtf8("textLabel1_4_2"));
        textLabel1_4_2->setGeometry(QRect(10, 90, 110, 30));
        textLabel1_4_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_4_2->setWordWrap(false);
        rfTagListBox = new Q3ListBox(DailyDialog);
        rfTagListBox->setObjectName(QString::fromUtf8("rfTagListBox"));
        rfTagListBox->setGeometry(QRect(580, 10, 130, 104));
        rfTagListBox->setLineWidth(2);
        madCowCheckBox = new QCheckBox(DailyDialog);
        madCowCheckBox->setObjectName(QString::fromUtf8("madCowCheckBox"));
        madCowCheckBox->setGeometry(QRect(420, 90, 170, 31));
        headLabel = new QLabel(DailyDialog);
        headLabel->setObjectName(QString::fromUtf8("headLabel"));
        headLabel->setGeometry(QRect(380, 210, 100, 30));
        headLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        headLabel->setWordWrap(false);
        dailyID = new QLineEdit(DailyDialog);
        dailyID->setObjectName(QString::fromUtf8("dailyID"));
        dailyID->setGeometry(QRect(130, 90, 100, 30));
        dailyHead = new QLineEdit(DailyDialog);
        dailyHead->setObjectName(QString::fromUtf8("dailyHead"));
        dailyHead->setGeometry(QRect(490, 210, 60, 31));
        deleteDaily = new QPushButton(DailyDialog);
        deleteDaily->setObjectName(QString::fromUtf8("deleteDaily"));
        deleteDaily->setGeometry(QRect(590, 630, 90, 30));
        deleteDaily->setAutoDefault(false);
        dailyTrucking = new QPushButton(DailyDialog);
        dailyTrucking->setObjectName(QString::fromUtf8("dailyTrucking"));
        dailyTrucking->setGeometry(QRect(260, 630, 110, 30));
        dailyTrucking->setAutoDefault(false);
        printDailyButton = new QPushButton(DailyDialog);
        printDailyButton->setObjectName(QString::fromUtf8("printDailyButton"));
        printDailyButton->setGeometry(QRect(690, 630, 110, 30));
        printDailyButton->setAutoDefault(false);
        dailySave = new QPushButton(DailyDialog);
        dailySave->setObjectName(QString::fromUtf8("dailySave"));
        dailySave->setGeometry(QRect(810, 630, 110, 30));
        dailySave->setAutoDefault(false);
        dailySave->setDefault(false);
        letterComboBox = new QComboBox(DailyDialog);
        letterComboBox->setObjectName(QString::fromUtf8("letterComboBox"));
        letterComboBox->setGeometry(QRect(840, 380, 80, 30));
        dailyPermListBox = new Q3ListBox(DailyDialog);
        dailyPermListBox->setObjectName(QString::fromUtf8("dailyPermListBox"));
        dailyPermListBox->setGeometry(QRect(480, 420, 440, 200));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bitstream Vera Sans Mono"));
        font1.setPointSize(13);
        dailyPermListBox->setFont(font1);
        sortGroup = new Q3ButtonGroup(DailyDialog);
        sortGroup->setObjectName(QString::fromUtf8("sortGroup"));
        sortGroup->setGeometry(QRect(20, 340, 440, 70));
        nameSortRadio = new QRadioButton(sortGroup);
        nameSortRadio->setObjectName(QString::fromUtf8("nameSortRadio"));
        nameSortRadio->setGeometry(QRect(210, 30, 220, 30));
        numberSortRadio = new QRadioButton(sortGroup);
        numberSortRadio->setObjectName(QString::fromUtf8("numberSortRadio"));
        numberSortRadio->setGeometry(QRect(10, 30, 190, 30));
        numberSortRadio->setChecked(true);
        resetRecordButton = new QPushButton(DailyDialog);
        resetRecordButton->setObjectName(QString::fromUtf8("resetRecordButton"));
        resetRecordButton->setGeometry(QRect(10, 630, 120, 30));
        resetRecordButton->setAutoDefault(false);
        dailyCharges = new QPushButton(DailyDialog);
        dailyCharges->setObjectName(QString::fromUtf8("dailyCharges"));
        dailyCharges->setGeometry(QRect(140, 630, 110, 30));
        dailyCharges->setAutoDefault(false);
        vetButton = new QPushButton(DailyDialog);
        vetButton->setObjectName(QString::fromUtf8("vetButton"));
        vetButton->setEnabled(true);
        vetButton->setGeometry(QRect(510, 630, 71, 30));
        vetButton->setAutoDefault(false);
        textLabel1_3 = new QLabel(DailyDialog);
        textLabel1_3->setObjectName(QString::fromUtf8("textLabel1_3"));
        textLabel1_3->setGeometry(QRect(480, 380, 350, 30));
        textLabel1_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_3->setWordWrap(false);
        textLabel2_6_2_2 = new QLabel(DailyDialog);
        textLabel2_6_2_2->setObjectName(QString::fromUtf8("textLabel2_6_2_2"));
        textLabel2_6_2_2->setGeometry(QRect(10, 300, 110, 30));
        textLabel2_6_2_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_6_2_2->setWordWrap(false);
        dailyComment = new QLineEdit(DailyDialog);
        dailyComment->setObjectName(QString::fromUtf8("dailyComment"));
        dailyComment->setGeometry(QRect(130, 300, 790, 31));
        dailyListBox = new Q3ListBox(DailyDialog);
        dailyListBox->setObjectName(QString::fromUtf8("dailyListBox"));
        dailyListBox->setGeometry(QRect(20, 420, 440, 200));
        dailyListBox->setFont(font1);
        tagButtonDaily = new QPushButton(DailyDialog);
        tagButtonDaily->setObjectName(QString::fromUtf8("tagButtonDaily"));
        tagButtonDaily->setGeometry(QRect(380, 630, 100, 30));
        tagButtonDaily->setAutoDefault(false);
        opInitialsLabel = new QLabel(DailyDialog);
        opInitialsLabel->setObjectName(QString::fromUtf8("opInitialsLabel"));
        opInitialsLabel->setGeometry(QRect(610, 210, 30, 23));
        opInitialsLabel->setWordWrap(false);
        opInitials = new QLineEdit(DailyDialog);
        opInitials->setObjectName(QString::fromUtf8("opInitials"));
        opInitials->setGeometry(QRect(650, 210, 50, 30));
        descrCode = new QLineEdit(DailyDialog);
        descrCode->setObjectName(QString::fromUtf8("descrCode"));
        descrCode->setGeometry(QRect(830, 210, 90, 30));
        descrCodeLabel = new QLabel(DailyDialog);
        descrCodeLabel->setObjectName(QString::fromUtf8("descrCodeLabel"));
        descrCodeLabel->setGeometry(QRect(710, 210, 95, 23));
        descrCodeLabel->setWordWrap(false);
        descriptionLabel = new QLabel(DailyDialog);
        descriptionLabel->setObjectName(QString::fromUtf8("descriptionLabel"));
        descriptionLabel->setGeometry(QRect(570, 260, 350, 23));
        descriptionLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        descriptionLabel->setWordWrap(false);
        groupBox = new QGroupBox(DailyDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(730, 10, 191, 88));
        groupBox->setAlignment(Qt::AlignCenter);
        groupBox->setFlat(false);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        sellerButton = new QRadioButton(groupBox);
        customerTypeButtonGroup = new QButtonGroup(DailyDialog);
        customerTypeButtonGroup->setObjectName(QString::fromUtf8("customerTypeButtonGroup"));
        customerTypeButtonGroup->addButton(sellerButton);
        sellerButton->setObjectName(QString::fromUtf8("sellerButton"));
        sellerButton->setChecked(true);

        gridLayout->addWidget(sellerButton, 0, 0, 1, 1);

        buyerButton = new QRadioButton(groupBox);
        customerTypeButtonGroup->addButton(buyerButton);
        buyerButton->setObjectName(QString::fromUtf8("buyerButton"));
        buyerButton->setChecked(false);

        gridLayout->addWidget(buyerButton, 1, 0, 1, 1);

        layoutWidget = new QWidget(DailyDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        showMissingBuyersButton = new QPushButton(DailyDialog);
        showMissingBuyersButton->setObjectName(QString::fromUtf8("showMissingBuyersButton"));
        showMissingBuyersButton->setGeometry(QRect(380, 630, 121, 30));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Sans"));
        font2.setPointSize(13);
        font2.setBold(false);
        font2.setWeight(50);
        showMissingBuyersButton->setFont(font2);
        showMissingBuyersButton->setAutoDefault(false);
        QWidget::setTabOrder(dailyID, dailyName);
        QWidget::setTabOrder(dailyName, dailyAddress1);
        QWidget::setTabOrder(dailyAddress1, dailyAddress2);
        QWidget::setTabOrder(dailyAddress2, dailyCity);
        QWidget::setTabOrder(dailyCity, dailyState);
        QWidget::setTabOrder(dailyState, dailyZip);
        QWidget::setTabOrder(dailyZip, dailyMortgage);
        QWidget::setTabOrder(dailyMortgage, dailyHead);
        QWidget::setTabOrder(dailyHead, opInitials);
        QWidget::setTabOrder(opInitials, descrCode);
        QWidget::setTabOrder(descrCode, dailyComment);
        QWidget::setTabOrder(dailyComment, madCowCheckBox);
        QWidget::setTabOrder(madCowCheckBox, dailyBeefCouncil);
        QWidget::setTabOrder(dailyBeefCouncil, numberSortRadio);
        QWidget::setTabOrder(numberSortRadio, nameSortRadio);
        QWidget::setTabOrder(nameSortRadio, dailyListBox);
        QWidget::setTabOrder(dailyListBox, letterComboBox);
        QWidget::setTabOrder(letterComboBox, dailyPermListBox);
        QWidget::setTabOrder(dailyPermListBox, resetRecordButton);
        QWidget::setTabOrder(resetRecordButton, dailyCharges);
        QWidget::setTabOrder(dailyCharges, dailyTrucking);
        QWidget::setTabOrder(dailyTrucking, tagButtonDaily);
        QWidget::setTabOrder(tagButtonDaily, vetButton);
        QWidget::setTabOrder(vetButton, deleteDaily);
        QWidget::setTabOrder(deleteDaily, printDailyButton);
        QWidget::setTabOrder(printDailyButton, dailySave);
        QWidget::setTabOrder(dailySave, buyerButton);
        QWidget::setTabOrder(buyerButton, sellerButton);
        QWidget::setTabOrder(sellerButton, rfTagListBox);

        retranslateUi(DailyDialog);

        QMetaObject::connectSlotsByName(DailyDialog);
    } // setupUi

    void retranslateUi(QDialog *DailyDialog)
    {
        DailyDialog->setWindowTitle(QApplication::translate("DailyDialog", "Daily FM", 0, QApplication::UnicodeUTF8));
        formHeader->setText(QApplication::translate("DailyDialog", "<i><b><font size=\"+4\">Daily File</font></b></i>", 0, QApplication::UnicodeUTF8));
        textLabel2_6_3->setText(QApplication::translate("DailyDialog", "Zip:", 0, QApplication::UnicodeUTF8));
        companyLabel->setText(QApplication::translate("DailyDialog", "Mortgage:", 0, QApplication::UnicodeUTF8));
        textLabel2_5_2->setText(QApplication::translate("DailyDialog", "State:", 0, QApplication::UnicodeUTF8));
        textLabel2_3_2->setText(QApplication::translate("DailyDialog", "Address:", 0, QApplication::UnicodeUTF8));
        textLabel2_4_3->setText(QApplication::translate("DailyDialog", "City:", 0, QApplication::UnicodeUTF8));
        textLabel2_8->setText(QApplication::translate("DailyDialog", "Name:", 0, QApplication::UnicodeUTF8));
        dailyBeefCouncil->setText(QApplication::translate("DailyDialog", "Beef Council", 0, QApplication::UnicodeUTF8));
        textLabel1_4_2->setText(QApplication::translate("DailyDialog", "Number", 0, QApplication::UnicodeUTF8));
        madCowCheckBox->setText(QApplication::translate("DailyDialog", "Countr&y of Origin", 0, QApplication::UnicodeUTF8));
        headLabel->setText(QApplication::translate("DailyDialog", "Head Cnt:", 0, QApplication::UnicodeUTF8));
        deleteDaily->setText(QApplication::translate("DailyDialog", "&Delete", 0, QApplication::UnicodeUTF8));
        deleteDaily->setShortcut(QApplication::translate("DailyDialog", "Alt+D", 0, QApplication::UnicodeUTF8));
        dailyTrucking->setText(QApplication::translate("DailyDialog", "Truc&king", 0, QApplication::UnicodeUTF8));
        dailyTrucking->setShortcut(QApplication::translate("DailyDialog", "Alt+K", 0, QApplication::UnicodeUTF8));
        printDailyButton->setText(QApplication::translate("DailyDialog", "&Print List", 0, QApplication::UnicodeUTF8));
        printDailyButton->setShortcut(QApplication::translate("DailyDialog", "Alt+P", 0, QApplication::UnicodeUTF8));
        dailySave->setText(QApplication::translate("DailyDialog", "S&ave Daily", 0, QApplication::UnicodeUTF8));
        dailySave->setShortcut(QApplication::translate("DailyDialog", "Alt+A", 0, QApplication::UnicodeUTF8));
        sortGroup->setTitle(QApplication::translate("DailyDialog", "Sort By", 0, QApplication::UnicodeUTF8));
        nameSortRadio->setText(QApplication::translate("DailyDialog", "&Name", 0, QApplication::UnicodeUTF8));
        numberSortRadio->setText(QApplication::translate("DailyDialog", "Number", 0, QApplication::UnicodeUTF8));
        resetRecordButton->setText(QApplication::translate("DailyDialog", "&Reset Record", 0, QApplication::UnicodeUTF8));
        resetRecordButton->setShortcut(QApplication::translate("DailyDialog", "Alt+R", 0, QApplication::UnicodeUTF8));
        dailyCharges->setText(QApplication::translate("DailyDialog", "&Charges", 0, QApplication::UnicodeUTF8));
        dailyCharges->setShortcut(QApplication::translate("DailyDialog", "Alt+C", 0, QApplication::UnicodeUTF8));
        vetButton->setText(QApplication::translate("DailyDialog", "V&et", 0, QApplication::UnicodeUTF8));
        vetButton->setShortcut(QApplication::translate("DailyDialog", "Alt+E", 0, QApplication::UnicodeUTF8));
        textLabel1_3->setText(QApplication::translate("DailyDialog", "List Only Perm That Start With:", 0, QApplication::UnicodeUTF8));
        textLabel2_6_2_2->setText(QApplication::translate("DailyDialog", "Comment", 0, QApplication::UnicodeUTF8));
        tagButtonDaily->setText(QApplication::translate("DailyDialog", "Ta&gs", 0, QApplication::UnicodeUTF8));
        tagButtonDaily->setShortcut(QApplication::translate("DailyDialog", "Alt+G", 0, QApplication::UnicodeUTF8));
        opInitialsLabel->setText(QApplication::translate("DailyDialog", "Ini", 0, QApplication::UnicodeUTF8));
        descrCodeLabel->setText(QApplication::translate("DailyDialog", "Desc code", 0, QApplication::UnicodeUTF8));
        descriptionLabel->setText(QString());
        groupBox->setTitle(QApplication::translate("DailyDialog", "Customer Type", 0, QApplication::UnicodeUTF8));
        sellerButton->setText(QApplication::translate("DailyDialog", "&Seller", 0, QApplication::UnicodeUTF8));
        sellerButton->setShortcut(QApplication::translate("DailyDialog", "Alt+S", 0, QApplication::UnicodeUTF8));
        buyerButton->setText(QApplication::translate("DailyDialog", "&Buyer", 0, QApplication::UnicodeUTF8));
        buyerButton->setShortcut(QApplication::translate("DailyDialog", "Alt+B", 0, QApplication::UnicodeUTF8));
        showMissingBuyersButton->setText(QApplication::translate("DailyDialog", "Show &Missing", 0, QApplication::UnicodeUTF8));
        showMissingBuyersButton->setShortcut(QApplication::translate("DailyDialog", "Alt+M", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DailyDialog: public Ui_DailyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DAILYDIALOG_H
