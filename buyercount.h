#ifndef _BUYER_COUNT_H_
#define _BUYER_COUNT_H_

#include "reports/textreport.h"
#include "types/invoice.h"
#include "types/buyerinvoice.h"

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class BuyerCount : public TextReport
{
public:
  BuyerCount(vector<BuyerInvoice> =vector<BuyerInvoice>(), Date=Date());
  virtual string text();

private:
  Date saleDate;
  TextReportTable headerTable();
  TextReportTable buyerTable();
  vector<BuyerInvoice> buyerInvoiceList;

};
#endif
