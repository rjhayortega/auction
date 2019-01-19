
#ifndef _INVOICE_DAO_H
#define _INVOICE_DAO_H

/* uncomment the following line
 * to make the invoice loader function
 * (getInvoiceByCondition()) output
 * timing data.
*/
//#define DEBUG_INVOICE_TIME

#include "transactiondao.h"
#include "databasemanager.h"
#include "truckingrecorddao.h"
#include "../types/sellerinvoice.h"
#include "../types/date.h" 
#include "customerdao.h"
#include "../types/dbug.h"
#include "setupdao.h"
#include "../reports/textinvoice.h"
#include <vector>
#include "salemanager.h"
#include "../reports/buyerrecap.h"
#include <string>
#include <sstream>
#include "../reports/buyerar.h"
#include "../types/summaryrecord.h"
#include "checkdao.h"
#include "../timer.h"

using namespace std;

class InvoiceDAO
{
public:

  typedef void (*ProgressCallback) (int, int);
 
  // debugging functions
  void resetTiming();
  void printTiming();
  // end debugging functions


  void setProgressCallback(ProgressCallback);
typedef struct discrep
{
  string customer;
  double originalValue;
  double recalculatedValue;
  long originalHead;
  long recalculatedHead;
  bool checkDiscrep;
}DISCREPANCY;

typedef struct summary
{
  long head;
  long noSaleHead;
  double total;
}SUMMARY;

  InvoiceDAO();
  virtual ~InvoiceDAO();
//  virtual Invoice* getInvoiceByCustomer(Customer);
  virtual Invoice* getInvoiceByCustomer(string, CommissionDAO::COLOR_GROUP=CommissionDAO::INVALID, bool=false);


  void saveInvoice(Invoice );
  bool invoiceExists(string);
  void saveSummary(Invoice);
  SUMMARY getSummary(CommissionDAO::COLOR_GROUP=CommissionDAO::INVALID);
  void deleteSummary(Customer);
  vector<string> getUnprintedCustomerList(CommissionDAO::COLOR_GROUP=CommissionDAO::INVALID);
  vector<DISCREPANCY> getDiscrepancyList(CommissionDAO::COLOR_GROUP=CommissionDAO::INVALID);
  bool printed(Invoice);
  void freeInvoice();
  vector<string> getNumbersMatching(string);

  /*
   * these functions exist to access the setup table ->
   */

  vector<string> getInvKeyList();
  vector<int> getColumnList();
  void saveColumnList(vector<int>);
  virtual bool checkOnInvoice();
  virtual void setCheckOnInvoice(bool);
  virtual unsigned int checkStart();
  virtual unsigned int chkStartCopy();
  virtual void setCheckStart(unsigned int);
  virtual void setShowName(bool);
  virtual bool showName();
  
  unsigned int pageHeight();
  void setPageHeight(unsigned int);
  unsigned int topSkip();
  void setTopSkip(unsigned int);
  virtual Customer::Type customerType();
  virtual unsigned int laserCopyCount();
  virtual bool isSecondCopyPrintNeeded();
  /*
   * <- end of functions used to access the setup table
   */

  virtual vector <string>getReadyList(bool=false);
  virtual vector<Charge> getManualChargeList(CommissionDAO::COLOR_GROUP=CommissionDAO::INVALID);
  void adjustChargeList(vector<Charge>&, Invoice*);
  vector<InvoiceSummaryRecord> getInvoiceSummaryRecordList(AnimalCode::Group=AnimalCode::Invalid);
//  static DatabaseManager listManager;
  virtual vector<Charge> getCompleteChargeList(CommissionDAO::COLOR_GROUP);
ProgressCallback getProgressCallback();
protected:
  SetupDAO setup;
  virtual void loadInvoiceTrans(Invoice*);
  virtual Invoice* getInvoiceByCondition(string, CommissionDAO::COLOR_GROUP=CommissionDAO::INVALID, bool=false);
  virtual Invoice* createInvoice(long, Date, string,Invoice::STATUS status = Invoice::UNPAID);
  virtual string keyPrefix();
  virtual string summaryTableName();
  virtual string totalColumnName();
  virtual void saveChargeList(Invoice);
  virtual string chargeSummaryTable();
  virtual string customerTypeString();
  virtual double getInvoiceNet(string, long&);
  virtual double addCharge(double,double);
  virtual Customer getCustomer(string);
  virtual string invoiceTableName();
  virtual bool invoiceReady(string);
  virtual ChargeDAO::CUST_TYPE chargeType();
  virtual bool otherDiscrep(DISCREPANCY&, long);
  virtual string extraTransConditions();


  virtual long noSaleHead(CommissionDAO::COLOR_GROUP);
  TransactionDAO transDao;
  virtual vector<string> getCustomerCheckList(string);

  SaleManager sale;
  ChargeDAO chargeDao;
  SetupDAO setupDao;
  TruckingRecordDAO truckingDao;

  virtual vector<Charge> getInvoiceChargeHistory(Invoice*);
//  DatabaseManager listManager;
  ProgressCallback progressCallback;

private:
  Invoice *invoiceReference;
  bool loadCustomerData;

string printedCustomerString(CommissionDAO::COLOR_GROUP);

#ifdef DEBUG_INVOICE_TIME
static Timer timer;
#endif 

#ifdef DEBUG_INVOICE_TIME
#define INVOICE_INTERVAL timer.usecInterval()
#endif

#ifndef DEBUG_INVOICE_TIME
#define INVOICE_INTERVAL 0
#endif

static unsigned long chargeInterval;
static unsigned long transactionInterval;
static unsigned long queryInterval;
static unsigned long customerInterval;
static unsigned long truckingInterval;

};

class SellerInvoiceDAO : public InvoiceDAO
{
public:
  SellerInvoiceDAO();
  SellerInvoice getInvoiceByNum(long);
//  SellerInvoice getInvoiceByCustomer(Customer);
    virtual SellerInvoice *getInvoiceByCustomer(string, CommissionDAO::COLOR_GROUP=CommissionDAO::INVALID, bool=false);
//  void saveInvoice(SellerInvoice);
    virtual bool checkOnInvoice();
    virtual void setCheckOnInvoice(bool);
    virtual unsigned int checkStart();
    virtual void setCheckStart(unsigned int);
    virtual bool isSecondCopyPrintNeeded();

  virtual vector<Charge> getManualChargeList(CommissionDAO::COLOR_GROUP);
  virtual Customer::Type customerType();
  virtual string extraTransConditions();
  vector<string> getCustomersCheckList(vector<Seller>);
  vector<string> customersPrintedWithoutChecks();
  virtual vector<Charge> getCompleteChargeList(CommissionDAO::COLOR_GROUP);
protected:
  virtual void loadInvoiceTrans(Invoice *);
  virtual Invoice *createInvoice(long, Date, string, Invoice::STATUS status = Invoice::UNPAID);
  virtual string keyPrefix();
  virtual string totalColumnName();
  virtual string summaryTableName();
  virtual string chargeSummaryTable();
  virtual string customerTypeString();
  virtual double getInvoiceNet(string, long&);
  virtual double addCharge(double,double);
  virtual Customer getCustomer(string);
  virtual string invoiceTableName();
  virtual bool invoiceReady(string);
  virtual ChargeDAO::CUST_TYPE chargeType();
  virtual void setShowName(bool);
  virtual bool showName();
  virtual long noSaleHead(CommissionDAO::COLOR_GROUP);
  virtual vector<string> getCustomerCheckList(string);
  virtual vector<Charge> getInvoiceChargeHistory(Invoice*);
  virtual bool otherDiscrep(DISCREPANCY&, long);
//  virtual bool isSecondCopyPrintNeeded();

private:
  CheckDAO checkDao;
};

class BuyerInvoiceDAO : public InvoiceDAO
{
public:
  BuyerInvoiceDAO();
  ~BuyerInvoiceDAO();
  virtual BuyerInvoice *getInvoiceByCustomer(string, CommissionDAO::COLOR_GROUP=CommissionDAO::INVALID, bool=false);
  BuyerRecap getBuyerRecap(vector<string>, string, bool=false, vector<ChargeRecord> =vector<ChargeRecord>());
  virtual vector<string> getReadyList(bool=false);

  vector<BuyerAR::Record> getBuyerAccountsList();
  virtual vector<Charge> getManualChargeList(CommissionDAO::COLOR_GROUP);
  virtual Customer::Type customerType();
  virtual vector<Charge> getCompleteChargeList(CommissionDAO::COLOR_GROUP);
  vector<BuyerInvoice> getBuyerInvoiceList(bool=true, bool=true, bool=true);
protected:
  virtual vector<Charge> getInvoiceChargeHistory(Invoice*);
  virtual void loadInvoiceTrans(Invoice *);
  virtual Invoice *createInvoice(long, Date, string,Invoice::STATUS status = Invoice::UNPAID);
  virtual string keyPrefix();
  virtual string totalColumnName();
  virtual string summaryTableName();
  virtual string chargeSummaryTable();
  virtual string customerTypeString();
  virtual double getInvoiceNet(string, long&);
  virtual double addCharge(double,double);
  virtual Customer getCustomer(string);
  virtual string invoiceTableName();
  virtual ChargeDAO::CUST_TYPE chargeType();
  virtual void setShowName(bool);

virtual bool showName();

private:
};
#endif
