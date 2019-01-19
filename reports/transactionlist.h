
#ifndef _TRANSACTION_LIST_H_
#define _TRANSACTION_LIST_H_

#include "textreport.h"
#include "../types/transaction.h"

#include <vector>
#include <string>
using namespace std;

class TransactionList : public TextReport
{
public:
  TransactionList(vector<Transaction> =vector<Transaction>());
  string text();
protected:
private:
  TextReportHeader transactionTableHeader();
  TextReportTable transactionTable();
  vector<Transaction> transactionList;
};
#endif
