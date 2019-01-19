#ifndef _TRUCKING_REPORT_H_
#define _TRUCKING_REPORT_H_
#include "../types/invoice.h"
#include "textreport.h"
#include "../types/truckingrecord.h"

class TruckingReport : public TextReport
{
public:
  TruckingReport(vector<Invoice> =vector<Invoice>(), vector<Invoice> =vector<Invoice>());
  virtual string text();

private:
  vector<Invoice> sellerInvoiceList;
  vector<Invoice> buyerInvoiceList;
  vector<Invoice>* invoiceList;

  TextReportTable truckerTable();
  TextReportTable headerTable(string, int=2, int=0);
};
#endif
