
#ifndef _INVOICE_H_
#define _INVOICE_H_

#include "chargerecord.h"
#include "transaction.h"
#include "customer.h"
#include "check.h"
#include "commission.h"
#include "truckingrecord.h"
#include <string>
#include <list>
#include "numbers.h"

#include <math.h>
#include <algorithm>

using namespace std;

#define EPSILON 0.0000001


class Invoice
{
public:
  typedef enum 
  {
    UNPAID,
    BILLED,
    PAID
  }STATUS;

  Invoice(long=0, Date=Date(), Customer=Customer(), STATUS=UNPAID);
  virtual ~Invoice();

  virtual double net();
  double gross();

  void setNumber(long);
  void setCustomer(Customer);
  void setDate(Date);
  void setCharges(ChargeRecord);
  void setTransactionList(vector<Transaction>);
  void setTruckingList(vector<TruckingRecord>);
  void setStatus(STATUS);
  void setTransactionChargeList(unsigned int, vector<Charge>);
  long getNumber();
  Customer getCustomer();
  Date getDate();
  STATUS getStatus();
  double getCommissionTotal(bool=false);
  double cwt();
  double averageDolPerHead();
  double averageDolPerCW();

  long head(bool=false, bool=false);
  long noSaleHead(bool=false);
  long noSaleWeight();

  double weight(bool=false);
  double averageWeight(bool=false);
  double truckingTotal();
  double chargeTotal();
  void addTransaction(Transaction);
  void operator+=(Transaction);
  void removeTransaction(long);
  bool codeMismatch();
  string toString();
  double averageNetPerCWT();
  vector<Transaction> getTransactionList();
  vector<Charge> getUniqueChargeList(bool=false);
  vector<ChargeRecord> getChargeRecordList(bool=false);
  void setManualCharges(vector<Charge>);
  void adjustCharges(vector<Charge>);

  unsigned int transactionListLength();
  void initCommissions(Commission);
  void setCommissionAdjustment(double);
  ChargeAdjustment getCommissionAdjustment();
  vector<TruckingRecord> getTruckingList();
  double bidTotal();
  void sortTransactionList();

  static bool compareInvoiceCustomerNamesLT(Invoice, Invoice);
  vector<AnimalCode> getUniqueSexList();
  long getSexAverageWeight(AnimalCode);
  long getSexHead(AnimalCode);
  double getSexAvgDolPerCWT(AnimalCode);
  vector<Charge> chargeStubList;
  void setChargeStubList(vector<Charge>);

private:
  vector<Transaction> transactionList;
  vector<TruckingRecord> truckingList;
  vector<Charge> manualCharges;
  long number;
  Customer customer;
  Date date;
  STATUS status;
  double commissionAdjustment;
};




#endif
