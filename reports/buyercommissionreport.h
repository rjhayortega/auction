
#ifndef _BUYER_COMMISSION_REPORT_H_
#define _BUYER_COMMISSION_REPORT_H_

#include "textreport.h"
#include "../types/invoice.h"
#include "../types/buyerinvoice.h"


class BuyerCommissionReport : public TextReport
{
public:

  BuyerCommissionReport(vector<BuyerInvoice> =vector<BuyerInvoice>());
  virtual string text();
private:

  vector<BuyerInvoice> invoiceList;
  static bool compareInvoiceNamesLT(BuyerInvoice, BuyerInvoice);
  TextReportTable buyerTable();
};
#endif
