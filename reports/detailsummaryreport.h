#ifndef _DETAIL_SUMMARY_REPORT_H_
#define _DETAIL_SUMMARY_REPORT_H_

#include "textreport.h"
#include "../types/summaryrecord.h"

#include <algorithm>
#include <vector>

using namespace std;

class DetailSummaryReport : public TextReport
{
public:
  DetailSummaryReport(vector<InvoiceSummaryRecord> =vector<InvoiceSummaryRecord>(), bool=true);
  virtual string text();
private:
  TextReportTable summaryTable();
  TextReportTable extraHeaderTable();
  void createTableMap();
  unsigned int getChargeColumn(ChargeSummaryRecord);
  vector<InvoiceSummaryRecord> recordList;
  vector<ChargeSummaryRecord> tableMap;
  bool isSeller;
};

#endif
