
#ifndef _TAG_REPORT_H_
#define _TAG_REPORT_H_

#include "textreport.h"
#include "../types/tag.h"
#include "../types/transaction.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class TagReport : public TextReport
{
public:
  TagReport(vector<Transaction> =vector<Transaction>(), Date=Date::currentDate(), string="");
  virtual string text();
  static bool compareTransactionTags(Transaction a, Transaction b);
private:

  vector<Transaction> transactionList;
  TextReportTable tagTableHeader();
  TextReportTable tagTable();
  unsigned int calculateTableRows();
  Date date;
  string marketId;
};

#endif
