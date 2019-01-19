//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end
#define __STDC_CONSTANT_MACROS
#define __STDC_FORMAT_MACROS
#include "auctionmain.h"
#include "ui_auctionmain.h"
#include <QToolBar>
//#include "video/videosaver.h"
#include "dao/setupdao.h"
#include <QTemporaryFile>


QProgressDialog* AuctionMain::progressDialog;



AuctionMain::AuctionMain(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::AuctionMain)
{
    ui->setupUi(this);

    // signals and slots connections
    connect( ui->DailyAction, SIGNAL( activated() ), this, SLOT( startDaily() ) );
    connect( ui->startInvoiceAction, SIGNAL( activated() ), this, SLOT( startSellerInvoice() ) );
    connect( ui->SetupAction, SIGNAL( activated() ), this, SLOT( startSetupDialog() ) );
    connect( ui->TransEditAction, SIGNAL( activated() ), this, SLOT( startTransactionBrowser() ) );
    connect( ui->ToggleSQLDebugAction, SIGNAL( activated() ), this, SLOT( toggleSQLDebugLevel() ) );
    connect( ui->CheckEditAction, SIGNAL( activated() ), this, SLOT( startCheckEdit() ) );
    connect( ui->Summary, SIGNAL( activated() ), this, SLOT( showSummary() ) );
    connect( ui->DiscrepancyReportAction, SIGNAL( activated() ), this, SLOT( showDiscrepancy() ) );
    connect( ui->PermAction, SIGNAL( activated() ), this, SLOT( startPerm() ) );
    connect( ui->SaleManagerAction, SIGNAL( activated() ), this, SLOT( startSaleManager() ) );
    connect( ui->MarketReportAction, SIGNAL( activated() ), this, SLOT( startMarketReport() ) );
    connect( ui->TagReportAction, SIGNAL( activated() ), this, SLOT( showTagReport() ) );
    connect( ui->PenReportAction, SIGNAL( activated() ), this, SLOT( showPenReport() ) );
    connect( ui->ImportLienAction, SIGNAL( activated() ), this, SLOT( startLienImport() ) );
    connect( ui->BuyerARAction, SIGNAL( activated() ), this, SLOT( startBuyerAccountsReceiveable() ) );
    connect( ui->TruckerChecksAction, SIGNAL( activated() ), this, SLOT( startTruckerChecksDialog() ) );
    connect( ui->BuyerChecksAction, SIGNAL( activated() ), this, SLOT( startBuyerChecksDialog() ) );
    connect( ui->BackupAction, SIGNAL( activated() ), this, SLOT( backup() ) );
    connect( ui->RestoreAction, SIGNAL( activated() ), this, SLOT( restore() ) );
    connect( ui->BuyerListAction, SIGNAL( activated() ), this, SLOT( startBuyerCommissionReport() ) );
    connect( ui->TruckerReportAction, SIGNAL( activated() ), this, SLOT( startTruckingReport() ) );
    connect( ui->DetailedSummaryAction, SIGNAL( activated() ), this, SLOT( showDetailSummary() ) );
//    connect( ui->ImportAction, SIGNAL( activated() ), this, SLOT( startAuctionImportDialog() ) );
    connect( ui->TransferCheckAction, SIGNAL( activated() ), this, SLOT( startCheckTransfer() ) );
    connect( ui->startHistoryAction, SIGNAL( activated() ), this, SLOT( startHistory() ) );
    connect( ui->BrandEditAction, SIGNAL( activated() ), this, SLOT( startBrandEdit() ) );
    connect( ui->RepairAction, SIGNAL( activated() ), this, SLOT( startDatabaseRepair() ) );
    connect( ui->BrowseTagsAction, SIGNAL( activated() ), this, SLOT( startTagBrowser() ) );
    connect( ui->BuyerCountAction, SIGNAL( activated() ), this, SLOT( startBuyerCount() ) );
    connect( ui->VetDialogAction, SIGNAL( activated() ), this, SLOT( startVetInspectionManager() ) );

    QToolBar *toolbar = addToolBar("Main toolbar");

    QAction *quit = toolbar->addAction(QIcon(":/images/exit.png"),"Quit Application");
    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    toolbar->addSeparator();

//    m_cameraRecAction = toolbar->addAction(QIcon("://images/button_play_green.png"), "Start Video Recording");
//    m_cameraRecAction->setCheckable(true);

//    m_videoSaver = new VideoSaver();
//    connect(m_videoSaver, SIGNAL(videoStateChanged(bool)), this , SLOT(onCameraRecording(bool)));

    // KLN add
    QFontDatabase::addApplicationFont(":/fonts/Vera.ttf");
    QFontDatabase::addApplicationFont(":/fonts/VeraBd.ttf");
    QFontDatabase::addApplicationFont(":/fonts/VeraBI.ttf");
    QFontDatabase::addApplicationFont(":/fonts/VeraIt.ttf");
    QFontDatabase::addApplicationFont(":/fonts/VeraMoBd.ttf");
    QFontDatabase::addApplicationFont(":/fonts/VeraMoBI.ttf");
    QFontDatabase::addApplicationFont(":/fonts/VeraMoIt.ttf");
    QFontDatabase::addApplicationFont(":/fonts/VeraMono.ttf");
    QFontDatabase::addApplicationFont(":/fonts/VeraSe.ttf");
    QFontDatabase::addApplicationFont(":/fonts/VeraSeBd.ttf");

    // KLN add end

    init();
}

AuctionMain::~AuctionMain()
{
    delete ui;
//    m_videoSaver->stopRecording();
    // Wait for 30 seconds to finish video recording
//    m_videoSaver->wait(30*1000);
//    delete m_videoSaver;
}


//using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
// name:    init()
//
// purpose: Constructor like function, initializes the dialog
//
// calling params:
//
// return params:
//
// Notes: db_level is the verbosity level of the Database manager.
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void AuctionMain::init()
{
    SaleManager sale;
    Sale current = sale.mostRecentSale();

    if(current.date == Date())
    {
        current.date = Date::currentDate();
        sale.createSale();
    }
    showMaximized();
    SaleManager().setCurrentSale(current);
    db_level = 0;
    updateStatistics();
    // Statistics timer to update statistics every second.
    // Moved from separate thread to here, to handle SQL errors in GUI thread.
    QTimer* statTimer = new QTimer(this);
    connect(statTimer, SIGNAL(timeout()), this,SLOT(updateStatistics()));
    statTimer->start(1000);

    currentDailyType = Customer::Seller;
    currentInvoiceType = Customer::Seller;
    permanantType = Customer::Seller;
    ui->currentDateDisplay->setText(QString::fromStdString(sale.currentSaleDate().toString("mm/dd/YYYY")));

    if(!sale.currentSaleOpen())
    {
        ui->currentDateDisplay->setPaletteForegroundColor(QColor(255,0,0));
    }
    else
    {
        ui->currentDateDisplay->setPaletteForegroundColor(QColor(0, 0, 0));
    }

    progressDialog = new QProgressDialog();
    progressDialog->setModal(true);
    updateToolBarActions();

}

void AuctionMain::destroy()
{
    delete progressDialog;
    while(applicationReference != NULL && applicationReference->hasPendingEvents())
    {
        applicationReference->processEvents();
    }

    delete ui;
}
///////////////////////////////////////////////////////////////////////////////
//
// name: setApplicationReference(KApplication*)
//
// purpose: Sets up a reference to the current application
//
// calling params: KApplication* applicationReference      - A pointer to the application
//
// return params:
//
// Notes:  Allows this module to process application events in a way other than is
//         handled in the main event loop
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void AuctionMain::setApplicationReference(QApplication *applicationReference)
{
    applicationReference = applicationReference;
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    startDaily()
//
// purpose: starts the daily dialog
//
// calling params:
//
// return params:
//
// Notes: Starts the daily dialog as a buyer or seller based on the mode that
//        it was in last
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void AuctionMain::startDaily()
{
    qDebug("startDaily()");
    setCursor(Qt::WaitCursor);
    DailyDialog daily(this);
    daily.init(currentDailyType);
    setCursor(Qt::ArrowCursor);
    daily.exec();
    currentDailyType = daily.getCustomerType();
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    startSellerInvoice()
//
// purpose: starts the invoice dialog as a seller invoice
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void AuctionMain::startSellerInvoice()
{
    qDebug("startSellerInvoice()");
    InvoiceDialog invoiceDialog(this);
    invoiceDialog.init(currentInvoiceType);
    invoiceDialog.exec();
    currentInvoiceType = invoiceDialog.getCustomerType();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    startSetupDialog()
//
// purpose: starts the setup dialog
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void AuctionMain::startSetupDialog()
{
    qDebug("startSetupDialog()");
    SetupDAO setup;
    if (setup.checkEmptyDB()) {
        QMessageBox::critical(this, "Error",
                                          "There appears to be no data!\nPlease restore your latest data, or re-enter new settings.");
//        std::exit(EXIT_FAILURE); // No data, crash!

    }
    SetupDialog(this).exec();
    updateToolBarActions();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    startTransactionBrowser()
//
// purpose: starts the transaction browser
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void AuctionMain::startTransactionBrowser()
{
    qDebug("startTransactionBrowser()");
    setCursor(Qt::BusyCursor);
    TransactionBrowser transBrowser(this);
    setCursor(Qt::ArrowCursor);
    transBrowser.exec();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    startCheckEdit()
//
// purpose: starts the check register dialog
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void AuctionMain::startCheckEdit()
{
    qDebug("startCheckEdit()");
    CheckRegister(this).exec();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    toggleSQLDebugLevel()
//
// purpose: sets the verbosity of the database manager at runtime
//
// calling params:
//
// return params:
//
// Notes:  for debugging purposes only
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void AuctionMain::toggleSQLDebugLevel()
{
    qDebug("toggleSQLDebugLevel()");
    db_level = 1 - db_level;
    DatabaseManager::defaultManager.set_debug_level(db_level);
    QMessageBox::information(this, "Notice",
                             "Set SQL Debug level to " + QString::number(db_level),
                             QMessageBox::Ok);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: showSummary()
//
// purpose: shows a simple sale summary in a preview dialog
//
// calling params:
//
// return params: void
//
// Notes:  Summary can be printed from the preview dialog
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void AuctionMain::showSummary()
{
    qDebug("showSummary()");
    QStringList groupList;
    bool ok;
    groupList << "0-69" << "70-79" << "80-89" << "90-99" << "All";
    CommissionDAO::COLOR_GROUP colorGroup =
            CommissionDAO::COLOR_GROUP(groupList.findIndex(QInputDialog::getItem(this, "Select a color group",
                                                                                 "Select A Color Group To Generate A\n"
                                                                                 "Summary For",
                                                                                 groupList, 0, false, &ok)));

    AnimalCode::Group group = AnimalCode::Group(colorGroup);

    if(ok)
    {
        setCursor(Qt::WaitCursor);
        SummaryReport summary(BuyerInvoiceDAO().getSummary(colorGroup), ChargeDAO().getChargeSummary(ChargeDAO::Buyer, group), setup.getBoolean("binvGroupCharges"),
                              SellerInvoiceDAO().getSummary(colorGroup),  ChargeDAO().getChargeSummary(ChargeDAO::Seller, group), setup.getBoolean("sinvGroupCharges"));
        summary.setHeader(setup.reportHeader("Sale Summary"));
        PreviewDialog prev;
        prev.setText(QString::fromStdString(summary.reportText()));
        prev.setReport(&summary);
        prev.setShowPrint(true);
        setCursor(Qt::ArrowCursor);
        prev.exec();
    }
}

#include <time.h>


///////////////////////////////////////////////////////////////////////////////
//
// name: showDiscrepancy()

// purpose: Shows a discrepency report in a preview dialog
//
// calling params:
//
// return params: void
//
// Notes:  Report can be printed from the preview dialog
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void AuctionMain::showDiscrepancy()
{
    qDebug("showDiscrepancy()");
    if(sale.currentSaleOpen())
    {
        unsigned long unprintedSellerTime= 0;
        unsigned long unprintedBuyerTime = 0;
        unsigned long buyerDiscrepTime = 0;
        unsigned long sellerDiscrepTime = 0;


        bool ok;
        QStringList groupList;
        groupList << "0-69" << "70-79" << "80-89" << "90-99" << "All";
        CommissionDAO::COLOR_GROUP colorGroup =
                CommissionDAO::COLOR_GROUP(groupList.findIndex(QInputDialog::getItem("Select a color group",
                                                                                     "Select A Color Group To Generate A\n"
                                                                                     "Discrepancy List For",
                                                                                     groupList, 0, false, &ok)));

        if(ok)
        {

            AnimalCodeDAO::startBatchMode();
            progressDialog->setLabelText("Generating Discrepancy Report");
            progressDialog->setMinimumDuration(0);
            progressDialog->show();


#ifdef DEBUG_TIME_DISCREP
            cout << "starting discrepancy report generation" << endl;
#endif

            time_t start;
            time_t end;

            start = time(&start);
            QCursor tempCursor = cursor();
            setCursor(Qt::WaitCursor);
            BuyerInvoiceDAO buyerInvoiceDao;
            buyerInvoiceDao.setProgressCallback(progressCallback);

            MAIN_TIMER_INTERVAL;
            progressDialog->setLabelText("Task 1 of 4: Searching For Unprinted Buyers");
            vector<string> unprintedBuyers = buyerInvoiceDao.getUnprintedCustomerList();
            unprintedBuyerTime += MAIN_TIMER_INTERVAL;
            progressDialog->setLabelText("Task 2 of 4: Searching For Unprinted Sellers");

            SellerInvoiceDAO sellerInvoiceDao;
            sellerInvoiceDao.setProgressCallback(progressCallback);
            vector<string> unprintedSellers = sellerInvoiceDao.getUnprintedCustomerList();
            unprintedSellerTime += MAIN_TIMER_INTERVAL;

            progressDialog->setLabelText("Task 3 of 4: Recalculating Buyer Invoices");

            vector<InvoiceDAO::DISCREPANCY> buyerDiscrepancyList =  buyerInvoiceDao.getDiscrepancyList(colorGroup);
            buyerDiscrepTime += MAIN_TIMER_INTERVAL;

            progressDialog->setLabelText("Task 4 of 4: Recalculating Seller Invoices");

            vector<InvoiceDAO::DISCREPANCY> sellerDiscrepancyList = sellerInvoiceDao.getDiscrepancyList(colorGroup);
            sellerDiscrepTime += MAIN_TIMER_INTERVAL;

#ifdef DEBUG_TIME_DISCREP
#include <stdio.h>
            cout << "| Unprinted Buyers | Unprinted Sellers | Buyer Discrep | Seller Discrep |" << endl;
            printf("|%10.2f |%10.2f |%10.2f |%10.2f |",
                   double(unprintedBuyerTime) / 1000000,
                   double(unprintedSellerTime) / 1000000,
                   double(buyerDiscrepTime) / 1000000,
                   double(sellerDiscrepTime) / 1000000);
#endif
            AnimalCodeDAO::endBatchMode();
            DiscrepancyReport discrepancy(unprintedBuyers, unprintedSellers,
                                          buyerDiscrepancyList, sellerDiscrepancyList);

            discrepancy.setHeader(setup.reportHeader("Discrepancy List"));
            discrepancy.text();

            PreviewDialog prev;
            prev.setShowPrint(true);
            prev.setReport(&discrepancy);
            end = time(&end);

#ifdef DEBUG_TIME_DISCREP
            cout << "total time to generate discrepancy report: " <<  difftime(end, start) << endl;
#endif
            setCursor(tempCursor);
            prev.exec();
        }
    }
    else
    {
        QMessageBox::information(this, "Unable to process request",
                                 "The selected sale is closed and discrepency reports "
                                 "can not be generated for closed sales", QMessageBox::Ok);
    }
    progressDialog->hide();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: startPerm()
//
// purpose: Entry point for the permanant dialog
//
// calling params: void
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::startPerm()
{
    qDebug("startPerm()");
    setCursor(Qt::WaitCursor);
    PermanantDialog permDialog(this);
    permDialog.init(permanantType);
    setCursor(Qt::ArrowCursor);
    qDebug("startPerm() before .exec()");
    permDialog.exec();
    permanantType = permDialog.currentType();
}



///////////////////////////////////////////////////////////////////////////////
//
// name: startSaleManager()
//
// purpose: entry point for the sale manager dialog
//
// calling params: void
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::startSaleManager()
{
    SaleManagerDialog saleMan(this);
    saleMan.exec();
    ui->currentDateDisplay->setText(QString::fromStdString(sale.currentSaleDate().toString("mm/dd/YYYY")));

    if(!sale.currentSaleOpen())
    {
        ui->currentDateDisplay->setPaletteForegroundColor(QColor(255,0,0));
    }
    else
    {
        ui->currentDateDisplay->setPaletteForegroundColor(QColor(0, 0, 0));
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// name: showBuyerRecap()
//
// purpose: starts the buyer recap dialog
//
// calling params: void
//
// return params: void
//
// Notes: No longer used here, to start the buyer recap dialog go to the buyer
//        invoice dialog
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::showBuyerRecap()
{
    BuyerRecapDialog(this).exec();
}

///////////////////////////////////////////////////////////////////////////////
//
// name: startMarketReport()
//
// purpose: starts the market report dialog
//
// calling params: void
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::startMarketReport()
{
    QCursor temp = cursor();
    setCursor(Qt::WaitCursor);
    MarketReportDialog mrDialog(this);
    setCursor(temp);
    mrDialog.exec();
}

///////////////////////////////////////////////////////////////////////////////
//
// name: showTagReport()
//
// purpose: shows the tag report in a preview window
//
// calling params: void
//
// return params: void
//
// Notes: Report can be printed from the preview window
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::showTagReport()
{
    QCursor temp = cursor();
    setCursor(Qt::WaitCursor);

    bool selectiveTagReport = setup.getBoolean("selectiveTagReport");
    vector<short> tagSexes;
    if(selectiveTagReport)
    {
        string tagSexString = QInputDialog::getText("Enter Sex Codes 0-9",
                                                    "Enter sex codes for the tag report(0-9)").toStdString();

        for(unsigned int i = 0; i < tagSexString.size(); i++)
        {
            if(isdigit(tagSexString[i]))
            {
                tagSexes.push_back(tagSexString[i] - 48);
            }
        }
    }

    transDao.setProgressCallback(progressCallback);
    progressDialog->setCaption("Generating Tag Report");
    progressDialog->setLabelText("Loading Tag Data");
    progressDialog->show();
    transDao.startBatchMode(true, true, false);
    AnimalCodeDAO::startBatchMode();
    vector<Transaction> transactionList;
    if(selectiveTagReport)
    {
        transactionList = transDao.getTransactionList(tagSexes);
    }
    else
    {
        transactionList = transDao.getTransactionList();
    }
    transDao.endBatchMode();
    AnimalCodeDAO::endBatchMode();

    progressDialog->hide();
    transDao.setProgressCallback(NULL);

    TagReport tagReport(transactionList, sale.currentSaleDate(), setup.get("genMktId"));
    tagReport.setHeader(setup.reportHeader());
    setCursor(temp);
    PreviewDialog prev;
    prev.setText(QString::fromStdString(tagReport.text()));
    prev.setReport(&tagReport);
    prev.setShowPrint(true);
    prev.exec();
}

///////////////////////////////////////////////////////////////////////////////
//
// name: showPenReport()
//
// purpose: displays the pen report in a preview window
//
// calling params: void
//
// return params: void
//
// Notes: The report can be printed from the preview dialog
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::showPenReport()
{
    QStringList optionList;
    optionList << "Sort by Pen" << "Sort By Buyer ID";
    bool ok;

    QString option = QInputDialog::getItem("Sort option",
                                           "How do you want to sort the report?",
                                           optionList, 0, false, &ok);

    if(ok)
    {
        PenReport::SortOption sort = PenReport::SortByPen;
        if(option == optionList[1])
        {
            sort = PenReport::SortByNumber;
        }

        PenReport report = TransactionDAO().getPenReport(sort);
        report.setHeader(setup.reportHeader("Pen Report"));
        PreviewDialog prev;
        prev.setText(QString::fromStdString(report.text()));
        prev.setReport(&report);
        prev.setShowPrint(true);
        prev.exec();
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name: startLienImport()
//
// purpose: starts the lien import dialog
//
// calling params: void
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::startLienImport()
{
    LienImportDialog  lienImportDialog(this);
    lienImportDialog.exec();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: startBuyerAccountsRecieveable()
//
// purpose: displays the Buyer A/R Report in a preview window
//
// calling params: void
//
// return params: void
//
// Notes: The report can be printed from the preview window
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::startBuyerAccountsReceiveable()
{
    QCursor tempCursor = cursor();
    setCursor(Qt::WaitCursor);
    progressDialog->setCaption("Generating Buyer AR");
    progressDialog->setLabelText("Loading buyers");
  //  progressDialog->show();

    BuyerInvoiceDAO buyerInvoiceDao;
    buyerInvoiceDao.setProgressCallback(progressCallback);
    vector<BuyerAR::Record> recordList = buyerInvoiceDao.getBuyerAccountsList();
    progressDialog->hide();

    bool ok;
    QStringList detailLevels;
    detailLevels << "Simple" << "Detailed";

    QString level = QInputDialog::getItem("Choose Detail Level",
                                          "Choose The Detail Level For The Report",
                                          detailLevels, 0, false, &ok);

    if(!ok)
    {
        setCursor(tempCursor);
        return;
    }

    BuyerAR arReport;

    if(level == detailLevels[0])
    {
        arReport = BuyerAR(recordList, false);
    }
    else if(level == detailLevels[1])
    {
        QStringList sortOptions;
        sortOptions << "Sort By Name" << "Sort By Number";
        QString sort = QInputDialog::getItem("Sort Option", "How should the list be sorted?",
                                             sortOptions, 0, false, &ok);

        if(!ok)
        {
            setCursor(tempCursor);
            return;
        }
        else if(sort == sortOptions[0])
        {
            arReport = BuyerAR(recordList, true, BuyerAR::NameSort);
        }
        else if(sort == sortOptions[1])
        {
            arReport = BuyerAR(recordList, true, BuyerAR::NumberSort);
        }
    }
    arReport.setHeader(setup.reportHeader("              BUYER ACCOUNTS RECEIVEABLE              "));

    setCursor(tempCursor);

    PreviewDialog prev;
    prev.setShowPrint(true);
    prev.setReport(&arReport);
    prev.setText(QString::fromStdString(arReport.text()));
    prev.exec();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: startTruckerChecksDialog()
//
// purpose: Starts the trucker checks dialog (to print checks for truckers)
//
// calling params: void
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::startTruckerChecksDialog()
{
    TruckerChecksDialog(this).exec();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: startBuyerChecksDialog()
//
// purpose: starts the buyer checks dialog (to print checks for buyer commissions)
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::startBuyerChecksDialog()
{
    QCursor tempCursor = cursor();
    setCursor(Qt::WaitCursor);
    BuyerChecksDialog bcDialog(this);
    setCursor(tempCursor);
    bcDialog.exec();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: timerEvent(QTimerEvent*)
//
// purpose: handles timer events, in this case, ensures that the dialog is
//          either minimized or maximized and makes sure the statistics on
//          the main page are kept current
//
// calling params: QTimerEvent* e   - a pointer to an object holding information
//                                    about the event
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::timerEvent(QTimerEvent* e)
{
    if(!isMinimized() && !isMaximized())
    {
        showMaximized();
    }

    //  updateSessionData();
}

///////////////////////////////////////////////////////////////////////////////
//
// name: backup()
//
// purpose: create a gzipped sql dump of the database
//
// calling params: void
//
// return params: void
//
// Notes: sometimes this does a wierd 'double zip' on
//        some platforms. To restore these 'double zipped' files,
//        gunzip them once, then rename the file from <file_name>.sql
//        to <file_name>.sql.gz and then restore that file
//
//        This uses the mysqldump program to dump the database
//        the
//
// Todo: Fix the 'double zip' problem.
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::backup()
{
    backupPath = QFileDialog::getSaveFileName(QString(getenv("HOME")).append("/auction.").append(QString::fromStdString(Date::currentDate().toString("mm-dd-YYYY"))).append(".sql.gz"), "Auction Backup File ( *.sql.gz )");

    if(backupPath == QString::null)
    {
        return;
    }

    backupProgress.setMaximum(3);
    backupProgress.setLabelText("Backing Up");
    backupProgress.setValue(0);
    backupProgress.show();
    backupBuffer = "";

    QStringList backupArgs;
    backupArgs << "-h" << DatabaseManager::defaultManager.getHostname()
               << "-u" << DatabaseManager::defaultManager.getUsername()
               << "-p" + DatabaseManager::defaultManager.getPassword()
               << DatabaseManager::defaultManager.getDatabasename();

    //backupProcess.setArguments(backupCommand);
    backupProgress.setValue(1);

    QObject::connect(&backupProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readBackupProcess()));
    QObject::connect(&backupProcess, SIGNAL(finished ( int, QProcess::ExitStatus) ),
                     this, SLOT(writeBackup(int , QProcess::ExitStatus )));
    backupProcess.start("mysqldump", backupArgs);
    if(!backupProcess.waitForStarted()) {
        QMessageBox::information(this, "Error", "Could not back up the database");
        cerr << "could not start backup" << endl;
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name: readBackupProcess()
//
// purpose: Fills a buffer from the backup process
//
// calling params: void
//
// return params: void
//
// Notes: Necessary to keep the program from freezing while running the backup
//        process
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::readBackupProcess()
{
    backupProgress.setValue(2);
    backupBuffer += QString(backupProcess.readAllStandardOutput());
}


///////////////////////////////////////////////////////////////////////////////
//
// name: writeBackup()
//
// purpose: writes the backup buffer to a file
//
// calling params: void
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::writeBackup(int exitCode, QProcess::ExitStatus exitStatus)
{
    if ( exitStatus != QProcess::NormalExit ) {
        QMessageBox::information(this, "ERROR", "Backup process finished with error.", QMessageBox::Ok);
        return;
    }

    gzFile outputFile = gzopen(backupPath.ascii(), "w");

    if(outputFile == NULL)
    {
        QMessageBox::information(this, "ERROR", "Could Not Open Backup File For Writing", QMessageBox::Ok);
        return;
    }

    gzwrite(outputFile, backupBuffer.ascii(), backupBuffer.length());
    gzclose(outputFile);
    backupProgress.setValue(3);
    QMessageBox::information(this, "Backup Complete",
                             "Your backup has been saved to: '" + backupPath + "'");
}


///////////////////////////////////////////////////////////////////////////////
//
// name: restore()
//
// purpose: restores a gzipped .sql script to the database
//
// calling params: void
//
// return params: void
//
// Notes: Not necessarily just for backing up, this is also used to update
//        the database structure when needed
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::restore()
{
    this->setCursor(Qt::WaitCursor);
    QStringList restoreArgs;

    QString path = QFileDialog::getOpenFileName(QString::fromStdString(getenv("HOME")).append("/"), "Auction Backup Files ( *.sql.gz )");

    if(path == "")
    {
        setCursor(Qt::ArrowCursor);
        return;
    }

    ui->MenuBar->setEnabled(false);
    gzFile inputFile = gzopen(path.ascii(), "rb");

    if(inputFile == NULL)
    {
        QMessageBox::information(this, "Error", "Could not open backup for reading", QMessageBox::Ok);
        return;
    }

    QString buf = "";
    char temp[255];

    while(!gzeof(inputFile))
    {
        gzgets(inputFile, temp, 200);
        buf += temp;
    }

    QTemporaryFile tempSqlFile;
    if (! tempSqlFile.open()) {
        QMessageBox::information(this, "Error", "Could not open temporary file.", QMessageBox::Ok);
        return;
    }

    restoreArgs << QString("-h%1").arg(DatabaseManager::defaultManager.getHostname() )
                << QString("-u%1").arg(DatabaseManager::defaultManager.getUsername() )
                << QString("-p%1").arg(DatabaseManager::defaultManager.getPassword() )
                << DatabaseManager::defaultManager.getDatabasename();

//    int option = QMessageBox::warning(this, "Warning",
//                                      "If you are restoring from a backup file you will lose any data that you have "
//                                      "entered after the backup file was created.\n"
//                                      "If this is an update file, you can continue with no risk to your data.\n"
//                                      "\nAre you sure that you wish to continue?\n",
//                                      "Cancel", "Continue");

    QFont warnFont = QFont("Bitstream Vera Sans", 13);
    QMessageBox warnBox;
    warnBox.setWindowTitle("Warning");
    QString text =
        "If you are restoring from a backup file you will lose any data that you have entered after the backup file was created.\n\n"
        "If this is an update file, you can continue with no risk to your data.\n\n"
        "Do you want to continue? ";

    warnBox.setText(text);
    warnBox.setIcon(QMessageBox::Warning);
    warnBox.setStandardButtons(QMessageBox::No|QMessageBox::Yes);
    warnBox.setFont(warnFont);

    int option = warnBox.exec();
    cout << "QMessageBox::Yes == " << QMessageBox::Yes << endl;
    cout << "QMessageBox::No == " << QMessageBox::No << endl;
    cout << "warnBox returned: " << option << endl;

    //    if(option == 1)
    if(option == QMessageBox::Yes)
    {
        tempSqlFile.write(buf);
        QObject::connect(&restoreProcess,SIGNAL(finished ( int, QProcess::ExitStatus) ),
                         this, SLOT(autoRestoreCursor(int , QProcess::ExitStatus)));

        restoreProcess.setStandardInputFile(tempSqlFile.fileName());
        restoreProcess.start("mysql", restoreArgs);

        restoreProcess.waitForFinished(-1);
        int exitCode = restoreProcess.exitCode();
        QString output = restoreProcess.readAllStandardError().constData();
        if(output.toLower().indexOf("error") != -1 || exitCode != 0){
            QMessageBox::information(this, "Error", "Could not restore the database. Error message: " + output);
        }

    }
    else
    {
    }
    setCursor(Qt::ArrowCursor);
    ui->MenuBar->setEnabled(true);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: autoRestoreCursor()
//
// purpose: a slot to restore the cursor and menubar status to be usable
//
// calling params: void
//
// return params: void
//
// Notes: The cursor may be set to busy and the menu bar disabled for some
//        functions that require there be no changes to the database while
//        until completion. This slot should be called at the end of that stage
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::autoRestoreCursor(int exitCode, QProcess::ExitStatus exitStatus)
{
    ui->MenuBar->setEnabled(true);
    setCursor(Qt::ArrowCursor);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: startBuyerCommissionReport()
//
// purpose: shows the buyer commission report in a preview window
//
// calling params: void
//
// return params: void
//
// Notes: Report can be printed from the preview window
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::startBuyerCommissionReport()
{
    QCursor saveCursor = cursor();
    setCursor(Qt::WaitCursor);
    vector<string> commissionedBuyerIdList = CommissionDAO().getCommissionedBuyerIdList();
    vector<BuyerInvoice> invoiceList;

    BuyerInvoiceDAO invoiceDao;

    progressDialog->setCaption("Generating Buyer Commission Report");
    progressDialog->setLabelText("Loading Buyers");
    progressDialog->show();
    progressDialog->setMaximum(commissionedBuyerIdList.size());
    for(unsigned int i = 0; i < commissionedBuyerIdList.size(); i++)
    {
        invoiceList.push_back(*(invoiceDao.getInvoiceByCustomer(commissionedBuyerIdList[i])));
        invoiceDao.freeInvoice();
        //progressDialog->setProgress(i + 1, commissionedBuyerIdList.size());
        progressDialog->setValue(i + 1);
    }
    std::sort(invoiceList.begin(), invoiceList.end(), Invoice::compareInvoiceCustomerNamesLT);

    progressDialog->hide();
    BuyerCommissionReport report(invoiceList);
    report.setHeader(setup.reportHeader("BUYER COMMISSION REPORT"));
    setCursor(saveCursor);
    PreviewDialog preview(this);
    preview.setText(QString::fromStdString(report.text()));
    preview.setReport(&report);
    preview.setShowPrint(true);
    preview.exec();

}


///////////////////////////////////////////////////////////////////////////////
//
// name: startTruckingReport()
//
// purpose: shows the trucking report in a preview window
//
// calling params: void
//
// return params: void
//
// Notes: Report may be printed from the preview window
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::startTruckingReport()
{
    QStringList menu;
    menu << "Sellers" << "Buyers" << "Both";
    bool ok;
    QCursor tempCursor = cursor();
    QString option = QInputDialog::getItem("Customer Type", "For which types of customers should the report be generated?",
                                           menu, 0, false, &ok, this);

    if(ok)
    {
        setCursor(Qt::WaitCursor);
        vector<TruckingRecordDAO::TruckerCustomer> truckerCustomerList;
        TruckingRecordDAO truckingDao;
        if(option == "Sellers" || option == "Both")
        {
            truckerCustomerList = truckingDao.getTruckingCustomerList(false, Customer::Seller);
        }

        if(option == "Buyers" || option == "Both")
        {
            vector<TruckingRecordDAO::TruckerCustomer> truckerBuyerList = truckingDao.getTruckingCustomerList(false, Customer::Buyer);
            truckerCustomerList.insert(truckerCustomerList.end(), truckerBuyerList.begin(), truckerBuyerList.end());
        }

        BuyerInvoiceDAO buyerDao;
        SellerInvoiceDAO sellerDao;
        vector<Invoice> sellerInvoiceList;
        vector<Invoice> buyerInvoiceList;

        for(unsigned int i = 0; i < truckerCustomerList.size(); i++)
        {
            switch(truckerCustomerList[i].type)
            {
            case ChargeDAO::Seller:
                sellerInvoiceList.push_back(*(sellerDao.getInvoiceByCustomer(truckerCustomerList[i].number)));
                sellerDao.freeInvoice();
                break;

            case ChargeDAO::Buyer:
                buyerInvoiceList.push_back(*(buyerDao.getInvoiceByCustomer(truckerCustomerList[i].number)));
                buyerDao.freeInvoice();
                break;
            }
        }

        TruckingReport report(sellerInvoiceList, buyerInvoiceList);
        report.setHeader(setup.reportHeader("TRUCKER LIST"));
        setCursor(tempCursor);
        PreviewDialog prev;
        prev.setReport(&report);
        prev.setText(QString::fromStdString(report.text()));
        prev.setShowPrint(true);
        prev.exec();
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name: showDetailSummary()
//
// purpose: Shows a buyer detail summary, then a seller detail summary, each in
//          thier own preview window.
//
// calling params: void
//
// return params: void
//
// Notes: Reports can be printed from the preview windows
//
//        Seller summary will not be shown until after the buyer summary preview
//        is closed
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::showDetailSummary()
{
    QCursor savedCursor = cursor();
    setCursor(Qt::WaitCursor);
    InvoiceSummaryRecord tempInvRec;
    ChargeSummaryRecord tempChgRec;

    vector<InvoiceSummaryRecord> invoiceSummaryRecordList;

    QStringList groupOption;
    groupOption << "" << "" << "" << "" << "";

    groupOption[AnimalCode::First]      = "0-69";
    groupOption[AnimalCode::Second] = "70-79";
    groupOption[AnimalCode::Third]     = "80-89";
    groupOption[AnimalCode::Fourth]   = "90-99";
    groupOption[AnimalCode::Invalid]  = "ALL";
    bool ok;

    QString groupSelection = QInputDialog::getItem("Which Group",
                                                   "For which Animal Code Group(Color Group) should\n"
                                                   "the report be generated?", groupOption, 0, false, &ok);

    if(!ok)
    {
       setCursor(savedCursor);
       return;
    }

    AnimalCode::Group colorGroup = AnimalCode::Group(groupOption.findIndex(groupSelection));
    BuyerInvoiceDAO buyerInvoiceDao;
    buyerInvoiceDao.setProgressCallback(progressCallback);
    progressDialog->setCaption("Generating Buyer Detail Summary");
    progressDialog->setLabelText("Loading Buyer Detail Information");
    progressDialog->show();

    invoiceSummaryRecordList = buyerInvoiceDao.getInvoiceSummaryRecordList(colorGroup);
    std::sort(invoiceSummaryRecordList.begin(), invoiceSummaryRecordList.end(), InvoiceSummaryRecord::compareCustomerNumbersLT);
    DetailSummaryReport buyerReport(invoiceSummaryRecordList, false);

    buyerReport.setHeader(setup.reportHeader("BUYER DETAIL SUMMARY"));
    buyerReport.text();
    PreviewDialog buyerPreview(this);
    buyerPreview.setShowPrint(true);
    buyerPreview.setPrintType(LinePrinter::Small); // [KLN] was ::Normal
    setCursor(savedCursor);
    buyerPreview.setReport(&buyerReport);
    buyerPreview.exec();
    setCursor(Qt::WaitCursor);

    SellerInvoiceDAO sellerInvoiceDao;
    sellerInvoiceDao.setProgressCallback(progressCallback);
    progressDialog->setCaption("Generating Seller Detail Summary");
    progressDialog->setLabelText("Loading Seller Detail Information");
    progressDialog->show();

    invoiceSummaryRecordList = sellerInvoiceDao.getInvoiceSummaryRecordList(colorGroup);
    std::sort(invoiceSummaryRecordList.begin(), invoiceSummaryRecordList.end(), InvoiceSummaryRecord::compareCustomerNumbersLT);

    DetailSummaryReport sellerReport(invoiceSummaryRecordList, true);
    sellerReport.setHeader(setup.reportHeader("SELLER DETAIL SUMMARY"));
    sellerReport.text();
    PreviewDialog sellerPreview(this);

    sellerPreview.setShowPrint(true);
    sellerPreview.setPrintType(LinePrinter::Small); // [KLN] was ::Normal
    setCursor(savedCursor);
    sellerPreview.setReport(&sellerReport);
    progressDialog->hide();

    sellerPreview.exec();

}


///////////////////////////////////////////////////////////////////////////////
//
// name: startAuctionImportdialog()
//
// purpose: Starts the auction 4 data importer dialog
//
// calling params: void
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
//void AuctionMain::startAuctionImportDialog()
//{
//    AuctionImportDialog(this).exec();
//}


///////////////////////////////////////////////////////////////////////////////
//
// name: startCheckTransfer()
//
// purpose: starts the transfer checks dialog
//
// calling params: void
//
// return params: void
//
// Notes: Transfer checks are the checks printed from the summary charges
//        data. Useful for writing checks to the vet, brand inspector, etc.
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::startCheckTransfer()
{
    TransferCheckDialog tcd(this);
    tcd.exec();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: startHistory()
//
// purpose: starts the history dialog
//
// calling params: void
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::startHistory()
{
    History hist(this);
    hist.exec();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: startBrandEdit()
//
// purpose: starts the brand edit dialog
//
// calling params: void
//
// return params: void
//
// Notes: Stops the dialog timer (which updates the statistics) before
//        starting the brand edit dialog. The timer causes trouble with
//        the painter in the brand editor dialog. The timer is started again
//        after the brand editor is closed.
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::startBrandEdit()
{
    BrandInputDialog(this).exec();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: startDatabaseRepair()
//
// purpose: starts the database repair dialog.
//
// calling params: void
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::startDatabaseRepair()
{
    TableRepairDialog(this).exec();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: startTagBrowser()
//
// purpose: begins the tag browser dialog
//
// calling params: none
//
// return params: none
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionMain::startTagBrowser()
{
    setCursor(Qt::WaitCursor);
    TagBrowser tagBrowser(this);
    setCursor(Qt::ArrowCursor);

    tagBrowser.exec();
}


void AuctionMain::startBuyerCount()
{
    setCursor(Qt::WaitCursor);

    BuyerInvoiceDAO buyerInvoiceDao;
    buyerInvoiceDao.setProgressCallback(progressCallback);
    progressDialog->setCaption("Generating Buyer Count");
    progressDialog->setLabelText("Loading Buyers");
    progressDialog->show();
    vector<BuyerInvoice> buyerInvoiceList = buyerInvoiceDao.getBuyerInvoiceList(true, false, false);
    progressDialog->hide();
    BuyerCount buyerCount(buyerInvoiceList, sale.currentSaleDate());

    buyerCount.text();
    setCursor(Qt::ArrowCursor);
    PreviewDialog preview(this);
    preview.setReport(&buyerCount);
    preview.setShowPrint(true);
    preview.exec();
}

void AuctionMain::updateStatistics()
{
    TransactionDAO transactionDao;

    long headIn = SellerDAO::checkedInHead();
    long headSold = transactionDao.soldHead();
    double percentSold = (headSold > 0 ? double(headSold) / double(headIn) : 0) * 100.00;
    QDateTime endTime ;
    //DateTime endTime;
    double saleLength = transactionDao.currentSaleLength(endTime);
    double headPerHour = (saleLength > 0 ? headSold / saleLength : 0.00);
    long estimatedTime = (double(headIn - headSold) / headPerHour) * 60 * 60;
    QTime estimatedEnd = QTime::currentTime();
    estimatedEnd = estimatedEnd.addSecs(estimatedTime);
    estimatedEnd = estimatedEnd.addMSecs(-estimatedEnd.msec());



    int debugLevel = DatabaseManager::defaultManager.get_debug_level();
    DatabaseManager::defaultManager.set_debug_level(0);
    ui->activeDateDisplay->setText(QString::fromStdString(sale.mostRecentSale().date.toString("mm/dd/YYYY")));
    DatabaseManager::defaultManager.set_debug_level(debugLevel);

//    cout << "Head In/sold/%sold/headPerHour: " << headIn << "/" << headSold << "/" << percentSold << "/" << headPerHour << endl;

    ui->statHeadCheckedIn->setText(QString("<center><h1>") + QString::number(headIn) + "</h1></center>");
    ui->statHeadSold->setText(QString("<center><h1>") + QString::number(headSold) + "</h1></center>");
    ui->statPercentSold->setText(QString("<center><h1>") + QString::number(percentSold, 'f', 2) + "</h1></center>");
    ui->statHeadPerHour->setText(QString("<center><h1>") + QString::number(headPerHour, 'f', 2) + "</h1></center>");

    if(sale.currentSaleOpen())
    {
        ui->statGroup->setTitle(QString("Est. End Time of Sale: ") + estimatedEnd.toString("hh:mm:ss"));
    }
    else
    {
        ui->statGroup->setTitle(QString("End Time Of Sale: ").append(endTime.toString()));
    }
}

void AuctionMain::progressCallback(int progress, int total)
{
    progressDialog->setMaximum(total);
    progressDialog->setValue(progress);
    QApplication::flush();
}

void AuctionMain::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    default:
        QWidget::keyPressEvent(event);
        break;
        /*
    case 'p':
    case 'P':
//	MenuBar->activateItemAt(0);
    startPerm();
    break;

    case 'd':
    case 'D':
//	MenuBar->activateItemAt(1);
    startDaily();
    break;

    case 'i':
    case 'I':
//	MenuBar->activateItemAt(2);
//	startSellerInvoice();
    break;

    case 'h':
    case 'H':
    MenuBar->activateItemAt(3);
    startHistory();
    break;
*/

    case 'r':
    case 'R':
        ui->MenuBar->activateItemAt(4);
        break;

    case 'u':
    case 'U':
        ui->MenuBar->activateItemAt(5);
        break;
    }
}

void AuctionMain::startVetInspectionManager()
{
    VetDialog vd(this);
    vd.exec();
}


void AuctionMain::onCameraRecording(bool state)
{
//    if (state) {
//        SetupDAO setup;
//        QString cameraUrl = QString::fromStdString(setup.get("vidCameraURL"));
//        QString cameraFPS = QString::fromStdString(setup.get("vidCameraFPS"));
//        if (!cameraUrl.isEmpty()) {
//            m_cameraRecAction->setIcon(QIcon("://images/button_pause_red.png"));
//            m_cameraRecAction->setToolTip("Stop Video Recording");

//            m_videoSaver->setCameraUrl(cameraUrl);
//            m_videoSaver->setCameraFPS(cameraFPS);
//            m_videoSaver->startRecording();
//        }
//    }
//    else {
//        m_videoSaver->stopRecording();
//        m_cameraRecAction->setIcon(QIcon("://images/button_play_green.png"));
//        m_cameraRecAction->setToolTip("Start Video Recording");
//    }
}

// This function should check changes in the setup and enable/disable toolbar actions state.
// Only video button is processed for now.
void AuctionMain::updateToolBarActions()
{
//    SetupDAO setup;
//    QString cameraUrl = QString::fromStdString(setup.get("vidCameraURL"));
//    if (cameraUrl.isEmpty()) {
//        m_cameraRecAction->setVisible(false);
//        if (m_videoSaver->isRecording()){ //Stop recording if camera URL is empty, and also
//            // change icon and correct states.
//            m_videoSaver->stopRecording();
//            m_cameraRecAction->setIcon(QIcon("://images/button_play_green.png"));
//            m_cameraRecAction->setToolTip("Start Video Recording");
//            m_cameraRecAction->setChecked(false);
//        }
//    }
//    else {
//        m_cameraRecAction->setVisible(true);
//    }
}
