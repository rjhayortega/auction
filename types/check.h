
#ifndef _CHECK_H_
#define _CHECK_H_

#include "date.h"
#include <math.h>
#include <string>
#include <iostream>
#include <vector>
#include "numbers.h"
#include "customer.h"

using namespace std;

class BankTransaction
{
public:
  typedef enum status
  {
    Out=0,
    Void=1,
    Cleared=2
  }STATUS;

  BankTransaction(long=0, long=0, double=0.0, STATUS=Out, Date=Date::currentDate(), string="");
  void setId(long);
  void setNumber(long);
  void setAmount(double);
  void setStatus(STATUS);
  void setDate(Date);
  void setComment(string);

  long getId();
  long getNumber();
  double getAmount();
  Date getDate();
  STATUS getStatus();
  string getComment();

private:
  long id;
  long number;
  double amount;
  STATUS status;
  string comment;
  Date date;
};

class Check : public BankTransaction
{
public:

typedef struct prorateRec
{
  string alternatePayee;
  double amount;
}PRORATE_REC;

typedef enum {Unknown, Invoice, Trucker, Buyer, Misc}Type;

Check(long=0, long=0, string="", double=0.0, STATUS=Out, Date=Date::currentDate(), string="", Type=Unknown, long=0);

  void setPayee(string);
  string getPayee();

  string getTextAmount();

  vector<Check> prorateCheck(vector<PRORATE_REC> prorateRec);
  void setType(Type);
  Type getType();
  bool operator==(string);
  long getInvoiceId();
  void setInvoiceId(long);

  static bool compareNumbersLT(Check, Check);
  static bool compareDatesLT(Check, Check);
  static bool comparePayeesLT(Check, Check);
  static bool compareAmountsLT(Check, Check);
  static bool compareStatusLT(Check, Check);
  static string createSellerPayeeLine(Customer);

private:
  string getTextDollarAmount();
  string getTextCentAmount();

  long number;
  string payee;
  Type type;
  long invoiceId;
  string numberText(int);
};


class Deposit : public BankTransaction
{
public:
  Deposit(long=0, long=0, double=0.00, Deposit::STATUS=Out, Date=Date::currentDate(), string="");

};

#endif
