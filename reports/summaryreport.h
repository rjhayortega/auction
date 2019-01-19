
#ifndef _SUMMARY_REPORT_H_
#define _SUMMARY_REPORT_H_
#include "../dao/invoicedao.h"
#include "textreport.h"
#include <iostream>
#include <string>

using namespace std;
class SummaryReport : public TextReport
{
public:
struct chargeSummaryItem
{
  string descrip;
  double total;
};

SummaryReport(InvoiceDAO::SUMMARY, vector<ChargeDAO::SUMMARY_ITEM>, bool,
	      InvoiceDAO::SUMMARY, vector<ChargeDAO::SUMMARY_ITEM>, bool);

  void setSellerSummary(InvoiceDAO::SUMMARY);
  void setSellerChargeSummary(vector<ChargeDAO::SUMMARY_ITEM>);
  void setBuyerSummary(InvoiceDAO::SUMMARY);
  void setBuyerChargeSummary(vector<ChargeDAO::SUMMARY_ITEM>);
  virtual string reportText();

protected:
  TextReportTable buyerSummaryTable();
  TextReportTable sellerSummaryTable();

private:
  InvoiceDAO::SUMMARY sellerSummary;
  InvoiceDAO::SUMMARY buyerSummary;
  vector<ChargeDAO::SUMMARY_ITEM> sellerChargeSummary;
  vector<ChargeDAO::SUMMARY_ITEM> buyerChargeSummary;
  bool groupSellerCharges;
  bool groupBuyerCharges;

  void shrinkChargeSummary(vector<ChargeDAO::SUMMARY_ITEM>&);
  static bool compareChargeIdsLT(ChargeDAO::SUMMARY_ITEM , ChargeDAO::SUMMARY_ITEM);
};
#endif
