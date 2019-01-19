
#ifndef _CHECK_REPORT_H_
#define _CHECK_REPORT_H_

#include "../types/check.h"
#include "textreport.h"

class CheckReport : public TextReport
{
public:
  typedef enum {OnlyCheck, OnlyDeposit, CheckAndDeposit}DisplayMode;

  CheckReport(vector<Check> =vector<Check>(), vector<Deposit> =vector<Deposit>(), bool=true, bool=true, bool=true, DisplayMode=OnlyCheck);
  virtual string text();
  void setStatementBalance(double);
private:
  vector<Check> checkList;
  vector<Deposit> depositList;
  TextReportTable checkTable();
  TextReportTable checkSummaryTable();
  TextReportTable depositTable();
  TextReportTable depositSummaryTable();
  TextReportTable totalSummaryTable();
  TextReportTable checkTableHeader();
  TextReportTable depositTableHeader();
  TextReportTable totalSummaryTableHeader();
  TextReportTable reconciliationTable();

  void clearCheckTotals();
  void clearDepositTotals();

  double clearedTotal;
  double voidTotal;
  double outTotal;
  double uncodedTotal;

  double invoiceTotal;
  double truckerTotal;
  double miscTotal;
  double buyerTotal;
  double unknownTotal;

  double clearedDepositTotal;
  double voidDepositTotal;
  double outDepositTotal;
  double uncodedDepositTotal;

  bool showCleared;
  bool showVoid;
  bool showOut;

  double statementBalance;
  bool showStatementBalance;

  DisplayMode mode;
};
#endif
