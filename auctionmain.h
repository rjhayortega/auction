/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include "vetdialog.h"

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and ().
 ** These will automatically be called by the form's constructor and
 ** destructor.
 *****************************************************************************/


/******************************************************************************
-
- class:   AuctionMain
-
- purpose: Main dialog for the sale day auction system by digital development
-
- Notes:   Basic idea here is to have slots that serve as entry points into the
-          various dialogs that comprise the program. This allows the user
-          interface to be able to be changed quickly and easily
-
******************************************************************************/

#include "dailydialog.h"
#include "invoicedialog.h"
#include "setupdialog.h"
#include "transactionbrowser.h"
#include "checkregister.h"
#include "previewdialog.h"
#include "qmessagebox.h"
#include "lineprinter.h"
#include "reports/summaryreport.h"
#include "reports/discrepancyreport.h"
#include "lienimportdialog.h"
#include "transfercheckdialog.h"
#include "permanantdialog.h"
#include "history.h"
#include "brandinputdialog.h"
#include "tagbrowser.h"

#include "dao/salemanager.h"
#include "dao/transactiondao.h"

#include "salemanagerdialog.h"
#include "buyerrecapdialog.h"
#include "marketreportdialog.h"
#include "truckerchecksdialog.h"
#include "buyerchecksdialog.h"
#include "types/summaryrecord.h"

#include "reports/tagreport.h"
#include "reports/buyerar.h"
#include "reports/buyercommissionreport.h"
#include "reports/truckingreport.h"
#include "reports/detailsummaryreport.h"
#include "buyercount.h"

#include <qinputdialog.h>
#include <qprogressdialog.h>
#include <qprocess.h>
#include <qfiledialog.h>
// KLN add
#include <qfontdatabase.h>
// KLN add end

#include <string>
#include <iostream>
#include <zlib.h>
#include <ctype.h>

#include <unistd.h>
#include "auctionimportdialog.h"
#include "tablerepairdialog.h"

//#define DEBUG_TIME_DISCREP

#ifdef DEBUG_TIME_DISCREP
Timer timer;
#define MAIN_TIMER_INTERVAL timer.usecInterval()
#endif

#ifndef DEBUG_TIME_DISCREP
#define MAIN_TIMER_INTERVAL 0
#endif

class QProgressDialog;

namespace Ui {
  class AuctionMain;
}

//class VideoSaver;

class AuctionMain : public QMainWindow {
  Q_OBJECT
  public:
  AuctionMain(QWidget *parent = 0);
  ~AuctionMain();
  QApplication* applicationReference = NULL;

  static void progressCallback( int progress, int total );

  static QProgressDialog* progressDialog;


public slots:
  void updateStatistics();
  void setApplicationReference( QApplication * applicationReference );
  void startDaily();
  void startSellerInvoice();
  void startSetupDialog();
  void startTransactionBrowser();
  void startCheckEdit();
  void toggleSQLDebugLevel();
  void showSummary();
  void showDiscrepancy();
  void startPerm();
  void startSaleManager();
  void showBuyerRecap();
  void startMarketReport();
  void showTagReport();
  void showPenReport();
  void startLienImport();
  void startBuyerAccountsReceiveable();
  void startTruckerChecksDialog();
  void startBuyerChecksDialog();
  void timerEvent( QTimerEvent * e );
  void backup();
  void readBackupProcess();
  void writeBackup(int exitCode, QProcess::ExitStatus exitStatus);
  void restore();
  void autoRestoreCursor(int exitCode, QProcess::ExitStatus exitStatus);
  void startBuyerCommissionReport();
  void startTruckingReport();
  void showDetailSummary();
//  void startAuctionImportDialog();
  void startCheckTransfer();
  void startHistory();
  void startBrandEdit();
  void startDatabaseRepair();
  void startTagBrowser();
  void startBuyerCount();
//  void customEvent( QCustomEvent * event );
//  void updateStatistics( GotStatisticsEvent * event );
  void keyPressEvent( QKeyEvent * event );
  void startVetInspectionManager();

protected slots:
   void onCameraRecording(bool state);

private:
   void init();
   void destroy();
   void updateToolBarActions();
private:
  Ui::AuctionMain *ui;
  Customer::Type currentInvoiceType;
  Customer::Type currentDailyType;
  QProcess restoreProcess;
  QProgressDialog restoreProgress;
  QProgressDialog backupProgress;
  QString backupBuffer;
  QString backupPath;
  QProcess backupProcess;
  int db_level;
  SetupDAO setup;
  TransactionDAO transDao;
  SaleManager sale;
  int statusTimerId;
  Customer::Type permanantType;

  QAction    * m_cameraRecAction;
//  VideoSaver * m_videoSaver;

};

#endif // MAINWINDOW_H
