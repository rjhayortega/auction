#include "check.h"

#include <cstdio>

BankTransaction::BankTransaction(long id, long number, double amount, STATUS status, Date date, string comment)
{
  this->id = id;
  setNumber(number);
  setAmount(amount);
  setStatus(status);
  setDate(date);
  setComment(comment);
}

void BankTransaction::setId(long id)
{
  this->id = id;
}

void BankTransaction::setNumber(long number)
{
  this->number = number;
}

void BankTransaction::setAmount(double amount)
{
  this->amount = amount;
}

void BankTransaction::setStatus(STATUS status)
{
  this->status = status;
}

void BankTransaction::setDate(Date date)
{
  this->date = date;
}

void BankTransaction::setComment(string comment)
{
  this->comment = comment;
}

long BankTransaction::getId()
{
  return id;
}

long BankTransaction::getNumber()
{
  return number;
}

double BankTransaction::getAmount()
{
  return getDollarAmount(amount);
}

BankTransaction::STATUS BankTransaction::getStatus()
{
  return status;
}

Date BankTransaction::getDate()
{
  return date;
}

string BankTransaction::getComment()
{
  return comment;
}

Check::Check(long id, long number, string payee, double amount, STATUS status, Date date, string comment, Type type, long invoiceId) : BankTransaction(id, number, amount, status, date, comment)
{
  setPayee(payee);
  this->type = type;
  this->invoiceId = invoiceId;
}

long Check::getInvoiceId()
{
  return invoiceId;
}

string Check::createSellerPayeeLine(Customer customer)
{
    string mortgage = customer.getCompany();
    string payeeString = customer.getName().getLast();
    int slashIndex;
    if((slashIndex = payeeString.find_first_of("/")) != string::npos)
    {
      string lastName = payeeString.substr(0, slashIndex);
      string firstName = (slashIndex + 1 < payeeString.length()? payeeString.substr(slashIndex + 1) : "");
      payeeString = firstName + lastName;
    }
 
    payeeString += (mortgage.length() > 0 ? " & " : "") + mortgage;
    return payeeString;
}

void Check::setInvoiceId(long invoiceId)
{
  this->invoiceId = invoiceId;
}

void Check::setType(Type type)
{
  this->type = type;
}

Check::Type Check::getType()
{
  return type;
}

void Check::setPayee(string payee)
{
  this->payee = payee;
}

string Check::getPayee()
{
  return payee;
}

string Check::getTextAmount()
{
  return getTextDollarAmount() + " DOLLARS AND " + getTextCentAmount() + " CENTS";
}


vector<Check> Check::prorateCheck(vector<PRORATE_REC> prorateRecord)
{
  vector<PRORATE_REC>::iterator current;
  vector<Check> proratedChecks;

  for(current = prorateRecord.begin(); current != prorateRecord.end(); current++)
  {
    if(current->amount > getAmount())
    {
      current->amount = getAmount();
    }

    proratedChecks.push_back(Check(0, 0, current->alternatePayee, current->amount, Out, Date::currentDate(), getComment()));

    setAmount(getAmount() - current->amount);
  }

  return proratedChecks;
}

///////////////////////////////////////////////////////////////////
//

string Check::getTextDollarAmount()
{       
  double amount = getAmount();
  int globalDepth = 0; 
  string depthText[6] = {"", "THOUSAND", "MILLION", "BILLION", "TRILLION", "ERROR-TOO MUCH MONEY, GIMME GIMME"};

  char buf[30];

  string amtText = "";
  string temp;

  sprintf(buf, "%ld", abs(long(amount)));
  string amtStr = buf;

  int nextBlockSize;
  int nextBlockBegin;

  nextBlockBegin = amtStr.size();

  while(nextBlockBegin != 0)
  {
    nextBlockSize = (nextBlockBegin - 3 >= 0 ? 3 : nextBlockBegin); // seperate the numbers into blocks of 3
    nextBlockBegin -= nextBlockSize;

    string cur = amtStr.substr(nextBlockBegin, nextBlockSize);
    temp = numberText(atoi(cur.c_str()));

    if(temp.length() > 0)
    {
      amtText = temp + (globalDepth > 0 ? " " + depthText[globalDepth%6] + " " + amtText : "");
    }
    globalDepth++;
  }

  if(amtText.length() == 0)
  {
    amtText = "NO";
  }

  if(amount < 0)
  {
    amtText = "NEGATIVE " + amtText;
  }

  return amtText;
}

//////////////////////////////////////////////////////
//

string Check::numberText(int amount)
{
  string ones[10]  = {"ZERO",    "ONE",   "TWO",    "THREE",    "FOUR",     "FIVE",    "SIX",     "SEVEN",     "EIGHT",     "NINE"};   
  string teens[10] = {"TEN",    "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN", "EIGHTEEN", "NINETEEN"};
  string tens[10]  = {"ZEROTY", "ONETY",  "TWENTY", "THIRTY",   "FORTY",    "FIFTY",   "SIXTY",   "SEVENTY",   "EIGHTY",    "NINETY"};

  // first 2 of tens[] & first of ones[] are dummies, should never be accessed, makes the math a little neater later.

  string text = "";

  if(amount > 999)  // gets text for 0 < numbers < 1000
  {
    return "";
  }

  if(99 < amount && amount < 1000)
  {
    text += ones[amount / 100] + " HUNDRED";
    amount -= (long(amount / 100)) * 100;

    if(amount > 0)
    {
      text += " ";
    }
  }

  if(amount < 100 && amount > 19) 
  {
    text += tens[amount / 10];
    amount -= (long(amount / 10)) * 10;

    if(amount > 0)
    {
      text += "-";
    }
  }

  if(amount < 20 && amount > 9) // get text
  {
    text += teens[amount - 10];
    amount -= amount;
  }

  if(amount > 0)
  {
    text += ones[amount];
    amount -= amount;
  }

  return text;
}

//////////////////////////////////////////////////
//

string Check::getTextCentAmount()
{
  char buf[30];
  sprintf (buf, "%.2f", getAmount()); 
  string centStr = buf;
  centStr = centStr.substr(centStr.length() - 2);
  if(centStr == "00")
  {
    centStr = "NO";
  }

  return centStr;
}

bool Check::operator==(string name)
{
  return this->payee == name;
}

bool Check::compareDatesLT(Check a, Check b)
{
  return a.getDate() < b.getDate();
}

bool Check::compareNumbersLT(Check a, Check b)
{
  return a.getNumber() < b.getNumber();
}

bool Check::comparePayeesLT(Check a, Check b)
{
  return a.getPayee() < b.getPayee();
}

bool Check::compareAmountsLT(Check a, Check b)
{
  return a.getAmount() < b.getAmount();
}

bool Check::compareStatusLT(Check a, Check b)
{
  return a.getStatus() < b.getStatus();
}

Deposit::Deposit(long id, long number, double amount, Deposit::STATUS status, Date date, string comment) : BankTransaction(id, number, amount, status, date, comment)
{
}
