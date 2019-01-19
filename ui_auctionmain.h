/********************************************************************************
** Form generated from reading UI file 'auctionmain.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUCTIONMAIN_H
#define UI_AUCTIONMAIN_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AuctionMain
{
public:
    QAction *DailyAction;
    QAction *PermAction;
    QAction *startInvoiceAction;
    QAction *SetupAction;
    QAction *TransEditAction;
    QAction *ToggleSQLDebugAction;
    QAction *CheckEditAction;
    QAction *Summary;
    QAction *DiscrepancyReportAction;
    QAction *daily_fmfAction;
    QAction *SaleManagerAction;
    QAction *MarketReportAction;
    QAction *TagReportAction;
    QAction *PenReportAction;
    QAction *ImportLienAction;
    QAction *BuyerARAction;
    QAction *TruckerChecksAction;
    QAction *BuyerChecksAction;
    QAction *BackupAction;
    QAction *RestoreAction;
    QAction *BuyerListAction;
    QAction *TruckerReportAction;
    QAction *DetailedSummaryAction;
    QAction *ImportAction;
    QAction *Action;
    QAction *Action_2;
    QAction *TransferCheckAction;
    QAction *startHistoryAction;
    QAction *BrandEditAction;
    QAction *RepairAction;
    QAction *BrowseTagsAction;
    QAction *BuyerCountAction;
    QAction *VetDialogAction;
    QWidget *widget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox;
    QFormLayout *formLayout_3;
    QFormLayout *formLayout_2;
    QLabel *saleDayLabel;
    QLabel *currentDateDisplay;
    QLabel *saleDayLabel_2;
    QLabel *activeDateDisplay;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *textLabel2;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *statGroup;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *statHeadCheckedIn;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *statHeadSold;
    QGroupBox *groupBox_7;
    QHBoxLayout *horizontalLayout_6;
    QLabel *statHeadPerHour;
    QGroupBox *groupBox_11;
    QHBoxLayout *horizontalLayout_3;
    QLabel *statPercentSold;
    QLabel *statusLabel;
    QMenuBar *MenuBar;
    QMenu *Perm_FM;
    QMenu *Daily_FM;
    QMenu *InvoiceMenuItem;
    QMenu *HistoryMenuItem;
    QMenu *Reports;
    QMenu *UtilitiesMenuItem;

    void setupUi(QMainWindow *AuctionMain)
    {
        if (AuctionMain->objectName().isEmpty())
            AuctionMain->setObjectName(QString::fromUtf8("AuctionMain"));
        AuctionMain->setWindowModality(Qt::ApplicationModal);
        AuctionMain->resize(706, 621);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AuctionMain->sizePolicy().hasHeightForWidth());
        AuctionMain->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(13);
        AuctionMain->setFont(font);
        AuctionMain->setUnifiedTitleAndToolBarOnMac(false);
        DailyAction = new QAction(AuctionMain);
        DailyAction->setObjectName(QString::fromUtf8("DailyAction"));
        DailyAction->setProperty("name", QVariant(QByteArray("DailyAction")));
        PermAction = new QAction(AuctionMain);
        PermAction->setObjectName(QString::fromUtf8("PermAction"));
        PermAction->setProperty("name", QVariant(QByteArray("PermAction")));
        startInvoiceAction = new QAction(AuctionMain);
        startInvoiceAction->setObjectName(QString::fromUtf8("startInvoiceAction"));
        startInvoiceAction->setProperty("name", QVariant(QByteArray("startInvoiceAction")));
        SetupAction = new QAction(AuctionMain);
        SetupAction->setObjectName(QString::fromUtf8("SetupAction"));
        SetupAction->setProperty("name", QVariant(QByteArray("SetupAction")));
        TransEditAction = new QAction(AuctionMain);
        TransEditAction->setObjectName(QString::fromUtf8("TransEditAction"));
        TransEditAction->setProperty("name", QVariant(QByteArray("TransEditAction")));
        ToggleSQLDebugAction = new QAction(AuctionMain);
        ToggleSQLDebugAction->setObjectName(QString::fromUtf8("ToggleSQLDebugAction"));
        ToggleSQLDebugAction->setProperty("name", QVariant(QByteArray("ToggleSQLDebugAction")));
        CheckEditAction = new QAction(AuctionMain);
        CheckEditAction->setObjectName(QString::fromUtf8("CheckEditAction"));
        CheckEditAction->setProperty("name", QVariant(QByteArray("CheckEditAction")));
        Summary = new QAction(AuctionMain);
        Summary->setObjectName(QString::fromUtf8("Summary"));
        Summary->setProperty("name", QVariant(QByteArray("Summary")));
        DiscrepancyReportAction = new QAction(AuctionMain);
        DiscrepancyReportAction->setObjectName(QString::fromUtf8("DiscrepancyReportAction"));
        DiscrepancyReportAction->setProperty("name", QVariant(QByteArray("DiscrepancyReportAction")));
        daily_fmfAction = new QAction(AuctionMain);
        daily_fmfAction->setObjectName(QString::fromUtf8("daily_fmfAction"));
        daily_fmfAction->setProperty("name", QVariant(QByteArray("daily_fmfAction")));
        SaleManagerAction = new QAction(AuctionMain);
        SaleManagerAction->setObjectName(QString::fromUtf8("SaleManagerAction"));
        SaleManagerAction->setProperty("name", QVariant(QByteArray("SaleManagerAction")));
        MarketReportAction = new QAction(AuctionMain);
        MarketReportAction->setObjectName(QString::fromUtf8("MarketReportAction"));
        MarketReportAction->setProperty("name", QVariant(QByteArray("MarketReportAction")));
        TagReportAction = new QAction(AuctionMain);
        TagReportAction->setObjectName(QString::fromUtf8("TagReportAction"));
        TagReportAction->setProperty("name", QVariant(QByteArray("TagReportAction")));
        PenReportAction = new QAction(AuctionMain);
        PenReportAction->setObjectName(QString::fromUtf8("PenReportAction"));
        PenReportAction->setProperty("name", QVariant(QByteArray("PenReportAction")));
        ImportLienAction = new QAction(AuctionMain);
        ImportLienAction->setObjectName(QString::fromUtf8("ImportLienAction"));
        ImportLienAction->setProperty("name", QVariant(QByteArray("ImportLienAction")));
        BuyerARAction = new QAction(AuctionMain);
        BuyerARAction->setObjectName(QString::fromUtf8("BuyerARAction"));
        BuyerARAction->setProperty("name", QVariant(QByteArray("BuyerARAction")));
        TruckerChecksAction = new QAction(AuctionMain);
        TruckerChecksAction->setObjectName(QString::fromUtf8("TruckerChecksAction"));
        TruckerChecksAction->setProperty("name", QVariant(QByteArray("TruckerChecksAction")));
        BuyerChecksAction = new QAction(AuctionMain);
        BuyerChecksAction->setObjectName(QString::fromUtf8("BuyerChecksAction"));
        BuyerChecksAction->setProperty("name", QVariant(QByteArray("BuyerChecksAction")));
        BackupAction = new QAction(AuctionMain);
        BackupAction->setObjectName(QString::fromUtf8("BackupAction"));
        BackupAction->setProperty("name", QVariant(QByteArray("BackupAction")));
        RestoreAction = new QAction(AuctionMain);
        RestoreAction->setObjectName(QString::fromUtf8("RestoreAction"));
        RestoreAction->setProperty("name", QVariant(QByteArray("RestoreAction")));
        BuyerListAction = new QAction(AuctionMain);
        BuyerListAction->setObjectName(QString::fromUtf8("BuyerListAction"));
        BuyerListAction->setProperty("name", QVariant(QByteArray("BuyerListAction")));
        TruckerReportAction = new QAction(AuctionMain);
        TruckerReportAction->setObjectName(QString::fromUtf8("TruckerReportAction"));
        TruckerReportAction->setProperty("name", QVariant(QByteArray("TruckerReportAction")));
        DetailedSummaryAction = new QAction(AuctionMain);
        DetailedSummaryAction->setObjectName(QString::fromUtf8("DetailedSummaryAction"));
        DetailedSummaryAction->setProperty("name", QVariant(QByteArray("DetailedSummaryAction")));
        ImportAction = new QAction(AuctionMain);
        ImportAction->setObjectName(QString::fromUtf8("ImportAction"));
        ImportAction->setProperty("name", QVariant(QByteArray("ImportAction")));
        Action = new QAction(AuctionMain);
        Action->setObjectName(QString::fromUtf8("Action"));
        Action->setProperty("name", QVariant(QByteArray("Action")));
        Action_2 = new QAction(AuctionMain);
        Action_2->setObjectName(QString::fromUtf8("Action_2"));
        Action_2->setProperty("name", QVariant(QByteArray("Action_2")));
        TransferCheckAction = new QAction(AuctionMain);
        TransferCheckAction->setObjectName(QString::fromUtf8("TransferCheckAction"));
        TransferCheckAction->setEnabled(true);
        TransferCheckAction->setProperty("name", QVariant(QByteArray("TransferCheckAction")));
        startHistoryAction = new QAction(AuctionMain);
        startHistoryAction->setObjectName(QString::fromUtf8("startHistoryAction"));
        startHistoryAction->setChecked(false);
        startHistoryAction->setEnabled(true);
        startHistoryAction->setProperty("name", QVariant(QByteArray("startHistoryAction")));
        BrandEditAction = new QAction(AuctionMain);
        BrandEditAction->setObjectName(QString::fromUtf8("BrandEditAction"));
        BrandEditAction->setEnabled(true);
        BrandEditAction->setProperty("name", QVariant(QByteArray("BrandEditAction")));
        RepairAction = new QAction(AuctionMain);
        RepairAction->setObjectName(QString::fromUtf8("RepairAction"));
        RepairAction->setProperty("name", QVariant(QByteArray("RepairAction")));
        BrowseTagsAction = new QAction(AuctionMain);
        BrowseTagsAction->setObjectName(QString::fromUtf8("BrowseTagsAction"));
        BrowseTagsAction->setProperty("name", QVariant(QByteArray("BrowseTagsAction")));
        BuyerCountAction = new QAction(AuctionMain);
        BuyerCountAction->setObjectName(QString::fromUtf8("BuyerCountAction"));
        BuyerCountAction->setProperty("name", QVariant(QByteArray("BuyerCountAction")));
        VetDialogAction = new QAction(AuctionMain);
        VetDialogAction->setObjectName(QString::fromUtf8("VetDialogAction"));
        VetDialogAction->setEnabled(true);
        VetDialogAction->setProperty("name", QVariant(QByteArray("VetDialogAction")));
        widget = new QWidget(AuctionMain);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        formLayout_3 = new QFormLayout(groupBox);
        formLayout_3->setSpacing(6);
        formLayout_3->setContentsMargins(11, 11, 11, 11);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        saleDayLabel = new QLabel(groupBox);
        saleDayLabel->setObjectName(QString::fromUtf8("saleDayLabel"));
        saleDayLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        saleDayLabel->setWordWrap(false);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, saleDayLabel);

        currentDateDisplay = new QLabel(groupBox);
        currentDateDisplay->setObjectName(QString::fromUtf8("currentDateDisplay"));
        currentDateDisplay->setWordWrap(false);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, currentDateDisplay);

        saleDayLabel_2 = new QLabel(groupBox);
        saleDayLabel_2->setObjectName(QString::fromUtf8("saleDayLabel_2"));
        saleDayLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        saleDayLabel_2->setWordWrap(false);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, saleDayLabel_2);

        activeDateDisplay = new QLabel(groupBox);
        activeDateDisplay->setObjectName(QString::fromUtf8("activeDateDisplay"));
        activeDateDisplay->setWordWrap(false);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, activeDateDisplay);


        formLayout_3->setLayout(0, QFormLayout::LabelRole, formLayout_2);


        horizontalLayout->addWidget(groupBox);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        textLabel2 = new QLabel(widget);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        sizePolicy.setHeightForWidth(textLabel2->sizePolicy().hasHeightForWidth());
        textLabel2->setSizePolicy(sizePolicy);
        textLabel2->setAlignment(Qt::AlignCenter);
        textLabel2->setWordWrap(false);

        horizontalLayout_2->addWidget(textLabel2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);

        statGroup = new QGroupBox(widget);
        statGroup->setObjectName(QString::fromUtf8("statGroup"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        statGroup->setFont(font1);
        statGroup->setAlignment(Qt::AlignCenter);
        gridLayout_3 = new QGridLayout(statGroup);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox_2 = new QGroupBox(statGroup);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFont(font1);
        groupBox_2->setAlignment(Qt::AlignCenter);
        horizontalLayout_4 = new QHBoxLayout(groupBox_2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        statHeadCheckedIn = new QLabel(groupBox_2);
        statHeadCheckedIn->setObjectName(QString::fromUtf8("statHeadCheckedIn"));
        statHeadCheckedIn->setAlignment(Qt::AlignCenter);
        statHeadCheckedIn->setWordWrap(false);

        horizontalLayout_4->addWidget(statHeadCheckedIn);


        gridLayout_2->addWidget(groupBox_2, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(statGroup);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setFont(font1);
        groupBox_3->setAlignment(Qt::AlignCenter);
        horizontalLayout_5 = new QHBoxLayout(groupBox_3);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        statHeadSold = new QLabel(groupBox_3);
        statHeadSold->setObjectName(QString::fromUtf8("statHeadSold"));
        statHeadSold->setAlignment(Qt::AlignCenter);
        statHeadSold->setWordWrap(false);

        horizontalLayout_5->addWidget(statHeadSold);


        gridLayout_2->addWidget(groupBox_3, 0, 1, 1, 1);

        groupBox_7 = new QGroupBox(statGroup);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setFont(font1);
        groupBox_7->setAlignment(Qt::AlignCenter);
        horizontalLayout_6 = new QHBoxLayout(groupBox_7);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        statHeadPerHour = new QLabel(groupBox_7);
        statHeadPerHour->setObjectName(QString::fromUtf8("statHeadPerHour"));
        sizePolicy.setHeightForWidth(statHeadPerHour->sizePolicy().hasHeightForWidth());
        statHeadPerHour->setSizePolicy(sizePolicy);
        statHeadPerHour->setAlignment(Qt::AlignCenter);
        statHeadPerHour->setWordWrap(false);

        horizontalLayout_6->addWidget(statHeadPerHour);


        gridLayout_2->addWidget(groupBox_7, 0, 2, 1, 1);

        groupBox_11 = new QGroupBox(statGroup);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        groupBox_11->setFont(font1);
        groupBox_11->setAlignment(Qt::AlignCenter);
        horizontalLayout_3 = new QHBoxLayout(groupBox_11);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        statPercentSold = new QLabel(groupBox_11);
        statPercentSold->setObjectName(QString::fromUtf8("statPercentSold"));
        statPercentSold->setFrameShape(QFrame::NoFrame);
        statPercentSold->setAlignment(Qt::AlignCenter);
        statPercentSold->setWordWrap(false);

        horizontalLayout_3->addWidget(statPercentSold);


        gridLayout_2->addWidget(groupBox_11, 0, 3, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        verticalLayout->addWidget(statGroup);

        statusLabel = new QLabel(widget);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(statusLabel->sizePolicy().hasHeightForWidth());
        statusLabel->setSizePolicy(sizePolicy1);
        statusLabel->setWordWrap(false);

        verticalLayout->addWidget(statusLabel);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        AuctionMain->setCentralWidget(widget);
        MenuBar = new QMenuBar(AuctionMain);
        MenuBar->setObjectName(QString::fromUtf8("MenuBar"));
        MenuBar->setGeometry(QRect(0, 0, 706, 29));
        Perm_FM = new QMenu(MenuBar);
        Perm_FM->setObjectName(QString::fromUtf8("Perm_FM"));
        Daily_FM = new QMenu(MenuBar);
        Daily_FM->setObjectName(QString::fromUtf8("Daily_FM"));
        InvoiceMenuItem = new QMenu(MenuBar);
        InvoiceMenuItem->setObjectName(QString::fromUtf8("InvoiceMenuItem"));
        HistoryMenuItem = new QMenu(MenuBar);
        HistoryMenuItem->setObjectName(QString::fromUtf8("HistoryMenuItem"));
        Reports = new QMenu(MenuBar);
        Reports->setObjectName(QString::fromUtf8("Reports"));
        UtilitiesMenuItem = new QMenu(MenuBar);
        UtilitiesMenuItem->setObjectName(QString::fromUtf8("UtilitiesMenuItem"));
        AuctionMain->setMenuBar(MenuBar);

        MenuBar->addAction(Perm_FM->menuAction());
        MenuBar->addAction(Daily_FM->menuAction());
        MenuBar->addAction(InvoiceMenuItem->menuAction());
        MenuBar->addAction(HistoryMenuItem->menuAction());
        MenuBar->addAction(Reports->menuAction());
        MenuBar->addAction(UtilitiesMenuItem->menuAction());
        Perm_FM->addAction(PermAction);
        Daily_FM->addAction(DailyAction);
        InvoiceMenuItem->addAction(startInvoiceAction);
        HistoryMenuItem->addAction(startHistoryAction);
        Reports->addAction(Summary);
        Reports->addAction(DetailedSummaryAction);
        Reports->addAction(DiscrepancyReportAction);
        Reports->addAction(MarketReportAction);
        Reports->addAction(TagReportAction);
        Reports->addAction(PenReportAction);
        Reports->addAction(BuyerARAction);
        Reports->addAction(TruckerChecksAction);
        Reports->addAction(BuyerChecksAction);
        Reports->addAction(TransferCheckAction);
        Reports->addAction(BuyerListAction);
        Reports->addAction(TruckerReportAction);
        Reports->addAction(BuyerCountAction);
        UtilitiesMenuItem->addAction(TransEditAction);
        UtilitiesMenuItem->addAction(CheckEditAction);
        UtilitiesMenuItem->addAction(SaleManagerAction);
        UtilitiesMenuItem->addAction(SetupAction);
        UtilitiesMenuItem->addAction(ToggleSQLDebugAction);
        UtilitiesMenuItem->addAction(BackupAction);
        UtilitiesMenuItem->addAction(RestoreAction);
        UtilitiesMenuItem->addAction(BrandEditAction);
        UtilitiesMenuItem->addAction(BrowseTagsAction);
        UtilitiesMenuItem->addAction(RepairAction);
        UtilitiesMenuItem->addAction(ImportLienAction);
        UtilitiesMenuItem->addSeparator();
        UtilitiesMenuItem->addAction(VetDialogAction);

        retranslateUi(AuctionMain);

        QMetaObject::connectSlotsByName(AuctionMain);
    } // setupUi

    void retranslateUi(QMainWindow *AuctionMain)
    {
        AuctionMain->setWindowTitle(QApplication::translate("AuctionMain", "Sale Day Auction Market System By Digital Development", 0, QApplication::UnicodeUTF8));
        DailyAction->setIconText(QApplication::translate("AuctionMain", "Start Daily", 0, QApplication::UnicodeUTF8));
        DailyAction->setShortcut(QApplication::translate("AuctionMain", "D", 0, QApplication::UnicodeUTF8));
        PermAction->setIconText(QApplication::translate("AuctionMain", "Start Perm", 0, QApplication::UnicodeUTF8));
        PermAction->setShortcut(QApplication::translate("AuctionMain", "P", 0, QApplication::UnicodeUTF8));
        startInvoiceAction->setIconText(QApplication::translate("AuctionMain", "Start Invoice", 0, QApplication::UnicodeUTF8));
        startInvoiceAction->setShortcut(QApplication::translate("AuctionMain", "I", 0, QApplication::UnicodeUTF8));
        SetupAction->setIconText(QApplication::translate("AuctionMain", "Setup", 0, QApplication::UnicodeUTF8));
        TransEditAction->setIconText(QApplication::translate("AuctionMain", "Trans Edit", 0, QApplication::UnicodeUTF8));
        ToggleSQLDebugAction->setIconText(QApplication::translate("AuctionMain", "Toggle Debug", 0, QApplication::UnicodeUTF8));
        CheckEditAction->setIconText(QApplication::translate("AuctionMain", "Check Register", 0, QApplication::UnicodeUTF8));
        Summary->setIconText(QApplication::translate("AuctionMain", "Summary", 0, QApplication::UnicodeUTF8));
        DiscrepancyReportAction->setIconText(QApplication::translate("AuctionMain", "Discrepancy Report", 0, QApplication::UnicodeUTF8));
        daily_fmfAction->setText(QApplication::translate("AuctionMain", "f", 0, QApplication::UnicodeUTF8));
        daily_fmfAction->setIconText(QApplication::translate("AuctionMain", "f", 0, QApplication::UnicodeUTF8));
        SaleManagerAction->setIconText(QApplication::translate("AuctionMain", "Sale Manager", 0, QApplication::UnicodeUTF8));
        MarketReportAction->setIconText(QApplication::translate("AuctionMain", "Market Report", 0, QApplication::UnicodeUTF8));
        TagReportAction->setIconText(QApplication::translate("AuctionMain", "Tag Report", 0, QApplication::UnicodeUTF8));
        PenReportAction->setIconText(QApplication::translate("AuctionMain", "Pen Report", 0, QApplication::UnicodeUTF8));
        ImportLienAction->setIconText(QApplication::translate("AuctionMain", "Import Liens", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ImportLienAction->setToolTip(QApplication::translate("AuctionMain", "Import Liens", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        BuyerARAction->setIconText(QApplication::translate("AuctionMain", "Buyer AR", 0, QApplication::UnicodeUTF8));
        TruckerChecksAction->setIconText(QApplication::translate("AuctionMain", "Trucker Checks", 0, QApplication::UnicodeUTF8));
        BuyerChecksAction->setIconText(QApplication::translate("AuctionMain", "Buyer Checks", 0, QApplication::UnicodeUTF8));
        BackupAction->setIconText(QApplication::translate("AuctionMain", "Backup", 0, QApplication::UnicodeUTF8));
        RestoreAction->setIconText(QApplication::translate("AuctionMain", "Restore/Update", 0, QApplication::UnicodeUTF8));
        BuyerListAction->setIconText(QApplication::translate("AuctionMain", "Buyer List", 0, QApplication::UnicodeUTF8));
        TruckerReportAction->setIconText(QApplication::translate("AuctionMain", "Trucker List", 0, QApplication::UnicodeUTF8));
        DetailedSummaryAction->setIconText(QApplication::translate("AuctionMain", "Detailed Summary", 0, QApplication::UnicodeUTF8));
        ImportAction->setIconText(QApplication::translate("AuctionMain", "Import Auction 4 Data", 0, QApplication::UnicodeUTF8));
        Action->setIconText(QApplication::translate("AuctionMain", "Unnamed", 0, QApplication::UnicodeUTF8));
        Action_2->setIconText(QApplication::translate("AuctionMain", "Unnamed", 0, QApplication::UnicodeUTF8));
        TransferCheckAction->setText(QApplication::translate("AuctionMain", "Transfer Checks", 0, QApplication::UnicodeUTF8));
        TransferCheckAction->setIconText(QApplication::translate("AuctionMain", "Transfer Checks", 0, QApplication::UnicodeUTF8));
        startHistoryAction->setIconText(QApplication::translate("AuctionMain", "Start History", 0, QApplication::UnicodeUTF8));
        startHistoryAction->setShortcut(QApplication::translate("AuctionMain", "H", 0, QApplication::UnicodeUTF8));
        BrandEditAction->setIconText(QApplication::translate("AuctionMain", "Edit Brands", 0, QApplication::UnicodeUTF8));
        RepairAction->setIconText(QApplication::translate("AuctionMain", "Repair Database", 0, QApplication::UnicodeUTF8));
        BrowseTagsAction->setIconText(QApplication::translate("AuctionMain", "Browse Tags", 0, QApplication::UnicodeUTF8));
        BuyerCountAction->setIconText(QApplication::translate("AuctionMain", "Buyer Count", 0, QApplication::UnicodeUTF8));
        VetDialogAction->setIconText(QApplication::translate("AuctionMain", "Vet Insp. Manager", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("AuctionMain", "Open Sales", 0, QApplication::UnicodeUTF8));
        saleDayLabel->setText(QApplication::translate("AuctionMain", "This Session:", 0, QApplication::UnicodeUTF8));
        currentDateDisplay->setText(QApplication::translate("AuctionMain", "00/00/0000", 0, QApplication::UnicodeUTF8));
        saleDayLabel_2->setText(QApplication::translate("AuctionMain", "Active(Clerk):", 0, QApplication::UnicodeUTF8));
        activeDateDisplay->setText(QApplication::translate("AuctionMain", "00/00/0000", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("AuctionMain", "Copyright 2006 - 2019 by Sargent Communications,Inc.\n"
"310 North Center Avenue, Hardin, MT. 59034\n"
"(406) 665-3348 - Version 7.0", 0, QApplication::UnicodeUTF8));
        statGroup->setTitle(QApplication::translate("AuctionMain", "Est. End Time: 00:00:00", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("AuctionMain", "Head In", 0, QApplication::UnicodeUTF8));
        statHeadCheckedIn->setText(QApplication::translate("AuctionMain", "0", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("AuctionMain", "Head Sold", 0, QApplication::UnicodeUTF8));
        statHeadSold->setText(QApplication::translate("AuctionMain", "0", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("AuctionMain", "Head / Hr", 0, QApplication::UnicodeUTF8));
        statHeadPerHour->setText(QApplication::translate("AuctionMain", "0.0.0", 0, QApplication::UnicodeUTF8));
        groupBox_11->setTitle(QApplication::translate("AuctionMain", "Percent Sold", 0, QApplication::UnicodeUTF8));
        statPercentSold->setText(QApplication::translate("AuctionMain", "0.00", 0, QApplication::UnicodeUTF8));
        statusLabel->setText(QString());
        Perm_FM->setTitle(QApplication::translate("AuctionMain", "&Perm", 0, QApplication::UnicodeUTF8));
        Daily_FM->setTitle(QApplication::translate("AuctionMain", "&Daily FM", 0, QApplication::UnicodeUTF8));
        InvoiceMenuItem->setTitle(QApplication::translate("AuctionMain", "&Invoice", 0, QApplication::UnicodeUTF8));
        HistoryMenuItem->setTitle(QApplication::translate("AuctionMain", "&History", 0, QApplication::UnicodeUTF8));
        Reports->setTitle(QApplication::translate("AuctionMain", "&Reports", 0, QApplication::UnicodeUTF8));
        UtilitiesMenuItem->setTitle(QApplication::translate("AuctionMain", "&Utilities", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AuctionMain: public Ui_AuctionMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUCTIONMAIN_H
