/********************************************************************************
** Form generated from reading UI file 'setupdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUPDIALOG_H
#define UI_SETUPDIALOG_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <vector>
#include "./dao/animalcodedao.h"
#include "./types/animalcode.h"
#include "dao/commissiondao.h"
#include "dao/setupdao.h"

QT_BEGIN_NAMESPACE

class Ui_SetupDialog
{
public:
    QTabWidget *setupTabWidget;
    QWidget *documentsTab;
    QPushButton *startSellerSetup;
    QPushButton *startBuyerSetup;
    QPushButton *checkSetupButton;
    QPushButton *marketReportSetupButton;
    QPushButton *reportSetupButton;
    QWidget *codesTab;
    QPushButton *commEditButton;
    QPushButton *chargeEditButton;
    QPushButton *codeEditButton;
    QWidget *systemTab;
    QPushButton *printerSetupButton;
    QPushButton *externSetupButton;
    QPushButton *setupScaleButton;
    QPushButton *setupDisplaysButton;
    QPushButton *setupVideoCameraButton;
    QPushButton *setupFaxModemButton;
    QPushButton *setupSaleManagerButton;
    QWidget *marketSetupTab;
    QLabel *textLabel3_2;
    QLabel *textLabel3_2_2;
    QLabel *textLabel3;
    QLineEdit *marketZipEdit;
    QLabel *textLabel3_2_2_2_2;
    QLineEdit *marketStateEdit;
    QLabel *textLabel3_2_2_2;
    QLineEdit *marketCityEdit;
    QLineEdit *marketNameEdit;
    QLineEdit *marketAddressEdit;
    QPushButton *saveMarketButton;
    QLabel *textLabel3_2_2_3;
    QLineEdit *marketIdEdit;
    QLineEdit *rfPortEdit;
    QSpinBox *transientBuyerBox;
    QLabel *textLabel3_2_2_3_2;
    QLabel *textLabel1;
    QCheckBox *rfTagOnCheckBox;
    QCheckBox *selectiveTagReportCheck;
    QCheckBox *countryOfOriginCheckBox;
    QCheckBox *dailyFMPhoneMatch;
    QCheckBox *dailyFMCheckinTickets;
    QWidget *webAuctionsTab;
    QWidget *layout6;
    QVBoxLayout *vboxLayout;
    QCheckBox *enableCattleUSACheckBox;
    QHBoxLayout *hboxLayout;
    QLabel *cattleUSAIdTextLabel;
    QLineEdit *cattleUSAIdLineEdit;
    QHBoxLayout *hboxLayout1;
    QLabel *textLabel1_2;
    QLineEdit *cattleUSAServerEdit;
    QSpacerItem *spacer2;
    QCheckBox *enableDVAuctionCheckBox;
    QHBoxLayout *horizontalLayout;
    QLabel *dvAuctionIdTextLabel;
    QLineEdit *dvAuctionIdLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *textLabel1_4;
    QLineEdit *dvAuctionServerEdit;
    QSpacerItem *spacer2_2;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *spacer1;
    QPushButton *saveWebAuctionsButton;

    void setupUi(QDialog *SetupDialog)
    {
        if (SetupDialog->objectName().isEmpty())
            SetupDialog->setObjectName(QString::fromUtf8("SetupDialog"));
        SetupDialog->setWindowModality(Qt::ApplicationModal);
        SetupDialog->resize(689, 560);
        QFont font;
        font.setPointSize(13);
        SetupDialog->setFont(font);
        SetupDialog->setSizeGripEnabled(true);
        setupTabWidget = new QTabWidget(SetupDialog);
        setupTabWidget->setObjectName(QString::fromUtf8("setupTabWidget"));
        setupTabWidget->setGeometry(QRect(10, 20, 670, 538));
        documentsTab = new QWidget();
        documentsTab->setObjectName(QString::fromUtf8("documentsTab"));
        startSellerSetup = new QPushButton(documentsTab);
        startSellerSetup->setObjectName(QString::fromUtf8("startSellerSetup"));
        startSellerSetup->setGeometry(QRect(30, 20, 150, 30));
        startSellerSetup->setFont(font);
        startBuyerSetup = new QPushButton(documentsTab);
        startBuyerSetup->setObjectName(QString::fromUtf8("startBuyerSetup"));
        startBuyerSetup->setGeometry(QRect(30, 60, 150, 31));
        checkSetupButton = new QPushButton(documentsTab);
        checkSetupButton->setObjectName(QString::fromUtf8("checkSetupButton"));
        checkSetupButton->setGeometry(QRect(30, 100, 150, 31));
        marketReportSetupButton = new QPushButton(documentsTab);
        marketReportSetupButton->setObjectName(QString::fromUtf8("marketReportSetupButton"));
        marketReportSetupButton->setGeometry(QRect(30, 140, 150, 31));
        reportSetupButton = new QPushButton(documentsTab);
        reportSetupButton->setObjectName(QString::fromUtf8("reportSetupButton"));
        reportSetupButton->setGeometry(QRect(30, 180, 150, 31));
        setupTabWidget->addTab(documentsTab, QString());
        codesTab = new QWidget();
        codesTab->setObjectName(QString::fromUtf8("codesTab"));
        commEditButton = new QPushButton(codesTab);
        commEditButton->setObjectName(QString::fromUtf8("commEditButton"));
        commEditButton->setGeometry(QRect(41, 30, 150, 30));
        chargeEditButton = new QPushButton(codesTab);
        chargeEditButton->setObjectName(QString::fromUtf8("chargeEditButton"));
        chargeEditButton->setGeometry(QRect(40, 80, 150, 30));
        codeEditButton = new QPushButton(codesTab);
        codeEditButton->setObjectName(QString::fromUtf8("codeEditButton"));
        codeEditButton->setGeometry(QRect(40, 130, 150, 30));
        setupTabWidget->addTab(codesTab, QString());
        systemTab = new QWidget();
        systemTab->setObjectName(QString::fromUtf8("systemTab"));
        printerSetupButton = new QPushButton(systemTab);
        printerSetupButton->setObjectName(QString::fromUtf8("printerSetupButton"));
        printerSetupButton->setGeometry(QRect(20, 20, 150, 31));
        externSetupButton = new QPushButton(systemTab);
        externSetupButton->setObjectName(QString::fromUtf8("externSetupButton"));
        externSetupButton->setGeometry(QRect(20, 70, 150, 31));
        setupScaleButton = new QPushButton(systemTab);
        setupScaleButton->setObjectName(QString::fromUtf8("setupScaleButton"));
        setupScaleButton->setGeometry(QRect(20, 120, 150, 31));
        setupDisplaysButton = new QPushButton(systemTab);
        setupDisplaysButton->setObjectName(QString::fromUtf8("setupDisplaysButton"));
        setupDisplaysButton->setGeometry(QRect(20, 170, 150, 31));
        setupVideoCameraButton = new QPushButton(systemTab);
        setupVideoCameraButton->setObjectName(QString::fromUtf8("setupVideoCameraButton"));
        setupVideoCameraButton->setGeometry(QRect(20, 230, 150, 31));
        setupFaxModemButton = new QPushButton(systemTab);
        setupFaxModemButton->setObjectName(QString::fromUtf8("setupFaxModemButton"));
        setupFaxModemButton->setGeometry(QRect(20, 290, 150, 31));
        setupSaleManagerButton = new QPushButton(systemTab);
        setupSaleManagerButton->setObjectName(QString::fromUtf8("setupSaleManagerButton"));
        setupSaleManagerButton->setGeometry(QRect(20, 340, 150, 31));
        setupTabWidget->addTab(systemTab, QString());
        marketSetupTab = new QWidget();
        marketSetupTab->setObjectName(QString::fromUtf8("marketSetupTab"));
        textLabel3_2 = new QLabel(marketSetupTab);
        textLabel3_2->setObjectName(QString::fromUtf8("textLabel3_2"));
        textLabel3_2->setGeometry(QRect(10, 60, 80, 30));
        textLabel3_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel3_2->setWordWrap(false);
        textLabel3_2_2 = new QLabel(marketSetupTab);
        textLabel3_2_2->setObjectName(QString::fromUtf8("textLabel3_2_2"));
        textLabel3_2_2->setGeometry(QRect(10, 100, 80, 30));
        textLabel3_2_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel3_2_2->setWordWrap(false);
        textLabel3 = new QLabel(marketSetupTab);
        textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
        textLabel3->setGeometry(QRect(10, 20, 80, 30));
        textLabel3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel3->setWordWrap(false);
        marketZipEdit = new QLineEdit(marketSetupTab);
        marketZipEdit->setObjectName(QString::fromUtf8("marketZipEdit"));
        marketZipEdit->setGeometry(QRect(440, 100, 70, 30));
        textLabel3_2_2_2_2 = new QLabel(marketSetupTab);
        textLabel3_2_2_2_2->setObjectName(QString::fromUtf8("textLabel3_2_2_2_2"));
        textLabel3_2_2_2_2->setGeometry(QRect(390, 100, 40, 30));
        textLabel3_2_2_2_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel3_2_2_2_2->setWordWrap(false);
        marketStateEdit = new QLineEdit(marketSetupTab);
        marketStateEdit->setObjectName(QString::fromUtf8("marketStateEdit"));
        marketStateEdit->setGeometry(QRect(330, 100, 50, 30));
        textLabel3_2_2_2 = new QLabel(marketSetupTab);
        textLabel3_2_2_2->setObjectName(QString::fromUtf8("textLabel3_2_2_2"));
        textLabel3_2_2_2->setGeometry(QRect(260, 100, 60, 30));
        textLabel3_2_2_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel3_2_2_2->setWordWrap(false);
        marketCityEdit = new QLineEdit(marketSetupTab);
        marketCityEdit->setObjectName(QString::fromUtf8("marketCityEdit"));
        marketCityEdit->setGeometry(QRect(100, 100, 150, 31));
        marketNameEdit = new QLineEdit(marketSetupTab);
        marketNameEdit->setObjectName(QString::fromUtf8("marketNameEdit"));
        marketNameEdit->setGeometry(QRect(100, 20, 410, 31));
        marketAddressEdit = new QLineEdit(marketSetupTab);
        marketAddressEdit->setObjectName(QString::fromUtf8("marketAddressEdit"));
        marketAddressEdit->setGeometry(QRect(100, 60, 410, 31));
        saveMarketButton = new QPushButton(marketSetupTab);
        saveMarketButton->setObjectName(QString::fromUtf8("saveMarketButton"));
        saveMarketButton->setGeometry(QRect(430, 450, 100, 30));
        textLabel3_2_2_3 = new QLabel(marketSetupTab);
        textLabel3_2_2_3->setObjectName(QString::fromUtf8("textLabel3_2_2_3"));
        textLabel3_2_2_3->setGeometry(QRect(30, 140, 60, 30));
        textLabel3_2_2_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel3_2_2_3->setWordWrap(false);
        marketIdEdit = new QLineEdit(marketSetupTab);
        marketIdEdit->setObjectName(QString::fromUtf8("marketIdEdit"));
        marketIdEdit->setGeometry(QRect(100, 140, 140, 31));
        rfPortEdit = new QLineEdit(marketSetupTab);
        rfPortEdit->setObjectName(QString::fromUtf8("rfPortEdit"));
        rfPortEdit->setGeometry(QRect(370, 410, 170, 31));
        transientBuyerBox = new QSpinBox(marketSetupTab);
        transientBuyerBox->setObjectName(QString::fromUtf8("transientBuyerBox"));
        transientBuyerBox->setEnabled(false);
        transientBuyerBox->setGeometry(QRect(260, 190, 80, 30));
        transientBuyerBox->setMinimum(-1);
        transientBuyerBox->setMaximum(999999999);
        transientBuyerBox->setValue(-1);
        textLabel3_2_2_3_2 = new QLabel(marketSetupTab);
        textLabel3_2_2_3_2->setObjectName(QString::fromUtf8("textLabel3_2_2_3_2"));
        textLabel3_2_2_3_2->setEnabled(false);
        textLabel3_2_2_3_2->setGeometry(QRect(20, 190, 230, 30));
        textLabel3_2_2_3_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel3_2_2_3_2->setWordWrap(false);
        textLabel1 = new QLabel(marketSetupTab);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(200, 410, 160, 30));
        textLabel1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1->setWordWrap(false);
        rfTagOnCheckBox = new QCheckBox(marketSetupTab);
        rfTagOnCheckBox->setObjectName(QString::fromUtf8("rfTagOnCheckBox"));
        rfTagOnCheckBox->setGeometry(QRect(30, 410, 160, 30));
        selectiveTagReportCheck = new QCheckBox(marketSetupTab);
        selectiveTagReportCheck->setObjectName(QString::fromUtf8("selectiveTagReportCheck"));
        selectiveTagReportCheck->setGeometry(QRect(10, 230, 330, 30));
        countryOfOriginCheckBox = new QCheckBox(marketSetupTab);
        countryOfOriginCheckBox->setObjectName(QString::fromUtf8("countryOfOriginCheckBox"));
        countryOfOriginCheckBox->setGeometry(QRect(10, 270, 330, 31));
        countryOfOriginCheckBox->setChecked(true);
        dailyFMPhoneMatch = new QCheckBox(marketSetupTab);
        dailyFMPhoneMatch->setObjectName(QString::fromUtf8("dailyFMPhoneMatch"));
        dailyFMPhoneMatch->setGeometry(QRect(10, 320, 380, 20));
        dailyFMCheckinTickets = new QCheckBox(marketSetupTab);
        dailyFMCheckinTickets->setObjectName(QString::fromUtf8("dailyFMCheckinTickets"));
        dailyFMCheckinTickets->setGeometry(QRect(8, 355, 380, 28));
        setupTabWidget->addTab(marketSetupTab, QString());
        webAuctionsTab = new QWidget();
        webAuctionsTab->setObjectName(QString::fromUtf8("webAuctionsTab"));
        layout6 = new QWidget(webAuctionsTab);
        layout6->setObjectName(QString::fromUtf8("layout6"));
        layout6->setGeometry(QRect(9, 16, 571, 480));
        vboxLayout = new QVBoxLayout(layout6);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        enableCattleUSACheckBox = new QCheckBox(layout6);
        enableCattleUSACheckBox->setObjectName(QString::fromUtf8("enableCattleUSACheckBox"));

        vboxLayout->addWidget(enableCattleUSACheckBox);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setSizeConstraint(QLayout::SetMinimumSize);
        hboxLayout->setContentsMargins(0, -1, -1, -1);
        cattleUSAIdTextLabel = new QLabel(layout6);
        cattleUSAIdTextLabel->setObjectName(QString::fromUtf8("cattleUSAIdTextLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cattleUSAIdTextLabel->sizePolicy().hasHeightForWidth());
        cattleUSAIdTextLabel->setSizePolicy(sizePolicy);
        cattleUSAIdTextLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        cattleUSAIdTextLabel->setWordWrap(false);

        hboxLayout->addWidget(cattleUSAIdTextLabel);

        cattleUSAIdLineEdit = new QLineEdit(layout6);
        cattleUSAIdLineEdit->setObjectName(QString::fromUtf8("cattleUSAIdLineEdit"));

        hboxLayout->addWidget(cattleUSAIdLineEdit);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        textLabel1_2 = new QLabel(layout6);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setWordWrap(false);

        hboxLayout1->addWidget(textLabel1_2);

        cattleUSAServerEdit = new QLineEdit(layout6);
        cattleUSAServerEdit->setObjectName(QString::fromUtf8("cattleUSAServerEdit"));

        hboxLayout1->addWidget(cattleUSAServerEdit);


        vboxLayout->addLayout(hboxLayout1);

        spacer2 = new QSpacerItem(470, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacer2);

        enableDVAuctionCheckBox = new QCheckBox(layout6);
        enableDVAuctionCheckBox->setObjectName(QString::fromUtf8("enableDVAuctionCheckBox"));

        vboxLayout->addWidget(enableDVAuctionCheckBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        dvAuctionIdTextLabel = new QLabel(layout6);
        dvAuctionIdTextLabel->setObjectName(QString::fromUtf8("dvAuctionIdTextLabel"));
        sizePolicy.setHeightForWidth(dvAuctionIdTextLabel->sizePolicy().hasHeightForWidth());
        dvAuctionIdTextLabel->setSizePolicy(sizePolicy);
        dvAuctionIdTextLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        dvAuctionIdTextLabel->setWordWrap(false);

        horizontalLayout->addWidget(dvAuctionIdTextLabel);

        dvAuctionIdLineEdit = new QLineEdit(layout6);
        dvAuctionIdLineEdit->setObjectName(QString::fromUtf8("dvAuctionIdLineEdit"));

        horizontalLayout->addWidget(dvAuctionIdLineEdit);


        vboxLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        textLabel1_4 = new QLabel(layout6);
        textLabel1_4->setObjectName(QString::fromUtf8("textLabel1_4"));
        textLabel1_4->setWordWrap(false);

        horizontalLayout_3->addWidget(textLabel1_4);

        dvAuctionServerEdit = new QLineEdit(layout6);
        dvAuctionServerEdit->setObjectName(QString::fromUtf8("dvAuctionServerEdit"));

        horizontalLayout_3->addWidget(dvAuctionServerEdit);


        vboxLayout->addLayout(horizontalLayout_3);

        spacer2_2 = new QSpacerItem(470, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacer2_2);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        spacer1 = new QSpacerItem(161, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacer1);

        saveWebAuctionsButton = new QPushButton(layout6);
        saveWebAuctionsButton->setObjectName(QString::fromUtf8("saveWebAuctionsButton"));

        hboxLayout2->addWidget(saveWebAuctionsButton);


        vboxLayout->addLayout(hboxLayout2);

        setupTabWidget->addTab(webAuctionsTab, QString());
        QWidget::setTabOrder(setupTabWidget, startSellerSetup);
        QWidget::setTabOrder(startSellerSetup, startBuyerSetup);
        QWidget::setTabOrder(startBuyerSetup, checkSetupButton);
        QWidget::setTabOrder(checkSetupButton, marketReportSetupButton);
        QWidget::setTabOrder(marketReportSetupButton, reportSetupButton);
        QWidget::setTabOrder(reportSetupButton, commEditButton);
        QWidget::setTabOrder(commEditButton, chargeEditButton);
        QWidget::setTabOrder(chargeEditButton, codeEditButton);
        QWidget::setTabOrder(codeEditButton, printerSetupButton);
        QWidget::setTabOrder(printerSetupButton, externSetupButton);
        QWidget::setTabOrder(externSetupButton, setupScaleButton);
        QWidget::setTabOrder(setupScaleButton, setupDisplaysButton);
        QWidget::setTabOrder(setupDisplaysButton, marketNameEdit);
        QWidget::setTabOrder(marketNameEdit, marketAddressEdit);
        QWidget::setTabOrder(marketAddressEdit, marketCityEdit);
        QWidget::setTabOrder(marketCityEdit, marketStateEdit);
        QWidget::setTabOrder(marketStateEdit, marketZipEdit);
        QWidget::setTabOrder(marketZipEdit, marketIdEdit);
        QWidget::setTabOrder(marketIdEdit, transientBuyerBox);
        QWidget::setTabOrder(transientBuyerBox, rfTagOnCheckBox);
        QWidget::setTabOrder(rfTagOnCheckBox, rfPortEdit);
        QWidget::setTabOrder(rfPortEdit, saveMarketButton);

        retranslateUi(SetupDialog);

        setupTabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(SetupDialog);
    } // setupUi

    void retranslateUi(QDialog *SetupDialog)
    {
        SetupDialog->setWindowTitle(QApplication::translate("SetupDialog", "Setup", 0, QApplication::UnicodeUTF8));
        startSellerSetup->setText(QApplication::translate("SetupDialog", "Seller Invoice", 0, QApplication::UnicodeUTF8));
        startBuyerSetup->setText(QApplication::translate("SetupDialog", "&Buyer Invoice", 0, QApplication::UnicodeUTF8));
        checkSetupButton->setText(QApplication::translate("SetupDialog", "Checks", 0, QApplication::UnicodeUTF8));
        marketReportSetupButton->setText(QApplication::translate("SetupDialog", "M&arket Report", 0, QApplication::UnicodeUTF8));
        reportSetupButton->setText(QApplication::translate("SetupDialog", "Reports", 0, QApplication::UnicodeUTF8));
        setupTabWidget->setTabText(setupTabWidget->indexOf(documentsTab), QApplication::translate("SetupDialog", "Docume&nts", 0, QApplication::UnicodeUTF8));
        commEditButton->setText(QApplication::translate("SetupDialog", "Commissions", 0, QApplication::UnicodeUTF8));
        chargeEditButton->setText(QApplication::translate("SetupDialog", "Charges", 0, QApplication::UnicodeUTF8));
        codeEditButton->setText(QApplication::translate("SetupDialog", "Codes", 0, QApplication::UnicodeUTF8));
        setupTabWidget->setTabText(setupTabWidget->indexOf(codesTab), QApplication::translate("SetupDialog", "Codes", 0, QApplication::UnicodeUTF8));
        printerSetupButton->setText(QApplication::translate("SetupDialog", "Printers", 0, QApplication::UnicodeUTF8));
        externSetupButton->setText(QApplication::translate("SetupDialog", "Clerk / Penner", 0, QApplication::UnicodeUTF8));
        setupScaleButton->setText(QApplication::translate("SetupDialog", "Scale", 0, QApplication::UnicodeUTF8));
        setupDisplaysButton->setText(QApplication::translate("SetupDialog", "Displays", 0, QApplication::UnicodeUTF8));
        setupVideoCameraButton->setText(QApplication::translate("SetupDialog", "Video camera", 0, QApplication::UnicodeUTF8));
        setupFaxModemButton->setText(QApplication::translate("SetupDialog", "Fax modem", 0, QApplication::UnicodeUTF8));
        setupSaleManagerButton->setText(QApplication::translate("SetupDialog", "Sale Manager", 0, QApplication::UnicodeUTF8));
        setupTabWidget->setTabText(setupTabWidget->indexOf(systemTab), QApplication::translate("SetupDialog", "S&ystem", 0, QApplication::UnicodeUTF8));
        textLabel3_2->setText(QApplication::translate("SetupDialog", "Address", 0, QApplication::UnicodeUTF8));
        textLabel3_2_2->setText(QApplication::translate("SetupDialog", "City", 0, QApplication::UnicodeUTF8));
        textLabel3->setText(QApplication::translate("SetupDialog", "Name", 0, QApplication::UnicodeUTF8));
        textLabel3_2_2_2_2->setText(QApplication::translate("SetupDialog", "Zip", 0, QApplication::UnicodeUTF8));
        textLabel3_2_2_2->setText(QApplication::translate("SetupDialog", "State", 0, QApplication::UnicodeUTF8));
        saveMarketButton->setText(QApplication::translate("SetupDialog", "Save", 0, QApplication::UnicodeUTF8));
        textLabel3_2_2_3->setText(QApplication::translate("SetupDialog", "ID #:", 0, QApplication::UnicodeUTF8));
        textLabel3_2_2_3_2->setText(QApplication::translate("SetupDialog", "First Transient Buyer:", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("SetupDialog", "RF Tag Port:", 0, QApplication::UnicodeUTF8));
        rfTagOnCheckBox->setText(QApplication::translate("SetupDialog", "Use RF Tags", 0, QApplication::UnicodeUTF8));
        selectiveTagReportCheck->setText(QApplication::translate("SetupDialog", "Select Individual Se&xes For Tag Report", 0, QApplication::UnicodeUTF8));
        selectiveTagReportCheck->setShortcut(QApplication::translate("SetupDialog", "Alt+X", 0, QApplication::UnicodeUTF8));
        countryOfOriginCheckBox->setText(QApplication::translate("SetupDialog", "Use Country Of Origin Tracking", 0, QApplication::UnicodeUTF8));
        dailyFMPhoneMatch->setText(QApplication::translate("SetupDialog", "Use phone num&ber as seller number.", 0, QApplication::UnicodeUTF8));
        dailyFMPhoneMatch->setShortcut(QApplication::translate("SetupDialog", "Alt+B", 0, QApplication::UnicodeUTF8));
        dailyFMCheckinTickets->setText(QApplication::translate("SetupDialog", "Print checkin tickets from Daily FM.", 0, QApplication::UnicodeUTF8));
        dailyFMCheckinTickets->setShortcut(QString());
        setupTabWidget->setTabText(setupTabWidget->indexOf(marketSetupTab), QApplication::translate("SetupDialog", "Mar&ket Setup", 0, QApplication::UnicodeUTF8));
        enableCattleUSACheckBox->setText(QApplication::translate("SetupDialog", "Enable Cattle USA Integration", 0, QApplication::UnicodeUTF8));
        cattleUSAIdTextLabel->setText(QApplication::translate("SetupDialog", "Cattle USA ID", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("SetupDialog", "Server", 0, QApplication::UnicodeUTF8));
        enableDVAuctionCheckBox->setText(QApplication::translate("SetupDialog", "Enable DVAuction Integration", 0, QApplication::UnicodeUTF8));
        dvAuctionIdTextLabel->setText(QApplication::translate("SetupDialog", "DVAuction ID", 0, QApplication::UnicodeUTF8));
        textLabel1_4->setText(QApplication::translate("SetupDialog", "Server", 0, QApplication::UnicodeUTF8));
        saveWebAuctionsButton->setText(QApplication::translate("SetupDialog", "Save", 0, QApplication::UnicodeUTF8));
        setupTabWidget->setTabText(setupTabWidget->indexOf(webAuctionsTab), QApplication::translate("SetupDialog", "&Web Auctions", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SetupDialog: public Ui_SetupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUPDIALOG_H
