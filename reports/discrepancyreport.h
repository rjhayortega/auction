
#ifndef _DISCREPANCY_REPORT_H_
#define _DISCREPANCY_REPORT_H_
#include "../dao/invoicedao.h"
#include "textreport.h"
#include <string>
#include <vector>
using namespace std;

class DiscrepancyReport : public TextReport
{
public:
  DiscrepancyReport(vector<string>, vector<string>, vector<InvoiceDAO::DISCREPANCY>, vector<InvoiceDAO::DISCREPANCY>);
  string text();
protected:
  TextReportTable unprintedSellersTable();
  TextReportTable unprintedBuyersTable();
  TextReportTable sellerDiscrepancyTable();
  TextReportTable buyerDiscrepancyTable();
  TextReportTable getDiscrepancyTable(vector<InvoiceDAO::DISCREPANCY>);
private:
  vector<string> unprintedSellerList;
  vector<string> unprintedBuyerList;

  vector<InvoiceDAO::DISCREPANCY> sellerDiscrepancyList;
  vector<InvoiceDAO::DISCREPANCY> buyerDiscrepancyList;
};

#endif
