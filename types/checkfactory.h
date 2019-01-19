#ifndef _CHECK_FACTORY_H_
#define _CHECK_FACTORY_H_
#include "prorate.h"
#include "check.h"
#include "invoice.h"
#include "numbers.h"

class CheckFactory
{
public:
  CheckFactory(Invoice, bool, vector<Prorate>);
  virtual ~CheckFactory();
  virtual vector<Check> checkList();
  vector<Prorate> getProrateList();
  vector<double> getChargeShares();

  bool sharesCharges();
  Invoice getInvoice();
  static vector<Transaction> invoiceTransactions(Invoice*);

protected:
  virtual double getAmount(Prorate&)=0;
  virtual void init() = 0;
  double invoiceGross();
  long invoiceHead();
  Invoice invoice;

private:
  long id;
  bool shareCharges;
  vector<double> chargeShares;
  vector<Prorate> prorateList;
  vector<Prorate>::iterator current;
};

class PercentageCheckFactory : public CheckFactory
{
public:
  PercentageCheckFactory(Invoice, bool, vector<Prorate>);
  virtual ~PercentageCheckFactory();
protected:
  virtual void init();
  virtual double getAmount(Prorate&);

private:
  double totalPercentage;
};

class FlatCheckFactory : public CheckFactory
{
public:
  FlatCheckFactory(Invoice, bool, vector<Prorate>);
  virtual ~FlatCheckFactory();
protected:
  virtual double getAmount(Prorate&);
  virtual void init();
private:
  double totalAmount;
};

class HeadCheckFactory : public CheckFactory
{
public:
  HeadCheckFactory(Invoice, bool, vector<Prorate>);
  virtual ~HeadCheckFactory();
protected:
  virtual double getAmount(Prorate&);
  virtual void init();
private:
  long totalHead;
};

class TransactionCheckFactory : public CheckFactory
{
public:
  TransactionCheckFactory(Invoice, bool, vector<Prorate>);
  virtual ~TransactionCheckFactory();
protected:
  virtual double getAmount(Prorate&);
  virtual void init();
private:
  vector<Transaction> availableTransactions;
  vector<long> lessHead;
};

class SexCheckFactory : public CheckFactory
{
public:
typedef struct record
{
  long sex;
  double head;
  double amount;
}CodeRecord;

  SexCheckFactory(Invoice, bool, vector<Prorate>);
  virtual ~SexCheckFactory();

  static vector<CodeRecord> getCodeList(Invoice);
protected:
  virtual double getAmount(Prorate&);
  virtual void init();

private:
  vector<CodeRecord> availableCodes;
  vector<long> lessHead;
};
#endif


