
#ifndef _TRANSACTION_DAO_H_
#define _TRANSACTION_DAO_H_

#include "databasemanager.h"
#include "../types/transaction.h"
#include "customerdao.h"
#include "chargedao.h"
#include "../types/dbug.h"
#include <list>
#include <string>
#include "salemanager.h"
#include "tagdao.h"
#include "../reports/buyerrecap.h"
#include "../reports/penreport.h"
#include "../reports/marketreport.h"
#include "setupdao.h"
#include "branddao.h"

#include "../timer.h"

#include <algorithm>
#include <QDateTime>

using namespace std;

/*
 * uncomment the following line to make
 * the transaction list loader function
 * (getTransactionListByCondition())
 * to output timing data
*/

//#define DEBUG_TRANS_TIMING

#ifdef DEBUG_TRANS_TIMING
#define TIMER_INTERVAL timer.usecInterval()
#endif

#ifndef DEBUG_TRANS_TIMING
#define TIMER_INTERVAL 0
#endif

class TransactionDAO
{
public:
  typedef void (*ProgressCallback) (int, int);

  TransactionDAO();
  ~TransactionDAO();

  vector<Transaction> getTransactionListByInvoice(long invoiceId, ChargeDAO::CUST_TYPE=ChargeDAO::Seller,bool=false);
  vector<Transaction> getTransactionListBySeller(Seller, bool=false);
  vector<Transaction> getTransactionListByBuyer(Buyer);
  void saveTransactionListToInvoice(vector<Transaction>, long invoiceId);
  Transaction getTransactionById(long, ChargeDAO::CUST_TYPE=ChargeDAO::Seller, bool=false);
  Transaction getTransactionByCondition(string, ChargeDAO::CUST_TYPE=ChargeDAO::Seller, bool=false);
  long saveTransaction(Transaction);
  vector<Transaction> getTransactionList();
  vector<Transaction> getTransactionList(vector<short>);
  vector<Transaction> getTransactionList(Seller, Buyer);

  void removeTransaction(long);

  vector<Transaction> getMarketTransactionList(long=0, double=0.0, AnimalCode::Group=AnimalCode::Invalid);

  void startBatchMode(bool=true, bool=true, bool=true);
  void endBatchMode();

  PenReport getPenReport(PenReport::SortOption=PenReport::SortByPen);
  long getNoSaleHead(CommissionDAO::COLOR_GROUP);
  long soldHead();
  double currentSaleLength(DateTime& endTime);
  void saveMarketReportTransactionIdList(vector<Transaction>);
  vector<long> getMarketReportTransactionIdList();
  bool globalBuyerChange(string, string);
  bool globalPenChange(string, string, string);

  long soldHeadByGroup(AnimalCode::Group);
  vector<string> uniqueBuyerIdList();
  void setProgressCallback(ProgressCallback);
  vector<Buyer> getBuyerList(Seller);
  long lastTransactionId();
  double currentSaleLength(QDateTime& endTime);

private:
  bool batchMode;
  bool loadTags;
  bool loadCustomerInfo;
  bool loadCharges;
  vector<Seller> sellerList;
  vector<Buyer> buyerList;

  vector<ChargeDAO::ChargeTable> sellerChargeListNoBeefCouncil;
  vector<ChargeDAO::ChargeTable> sellerChargeList;
  vector<ChargeDAO::ChargeTable> buyerChargeList;

  vector<CommissionDAO::CommissionTable> sellerCommissionList;

  vector<Tag> tagList;

  ChargeDAO::ChargeTable sellerChargeTable[400];
  ChargeDAO::ChargeTable sellerChargeTableNoBeefCouncil[400];
  ChargeDAO::ChargeTable buyerChargeTable[400];
  Commission commissionTable[400];
  vector<CommissionDAO::BuyerCommissionTable> buyerCommissionTable;

  vector<Transaction> getTransactionListByCondition(string, ChargeDAO::CUST_TYPE=ChargeDAO::Seller, bool=false, Date=Date(), Date=Date());
  SaleManager sale;

  AnimalCodeDAO acDao;
  CommissionDAO commDao;
  ChargeDAO chargeDao;
  TagDAO tagDao;
  SetupDAO setup;
  BrandDAO brandDao;

  #ifdef DEBUG_TRANS_TIMING
  Timer timer;
  #endif 

  ProgressCallback progressCallback;
  static unsigned long queryInterval;
  static unsigned long sellerInterval;
  static unsigned long buyerInterval;
  static unsigned long chargeInterval;
  static unsigned long codeInterval;
  static unsigned long tagInterval;
  static unsigned long commissionInterval;

  void resetLoaded();

  void resetTiming();
  void printTiming();
};
#endif
