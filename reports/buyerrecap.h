#ifndef _BUYER_RECAP_H_
#define _BUYER_RECAP_H_

#include "textreport.h"
#include "../types/invoice.h"
#include "../types/buyerinvoice.h"

#include "../types/chargerecord.h"
#include "../types/numbers.h"
#include <algorithm>

class BuyerRecap : public TextReport
{
public:
  virtual string text();
  BuyerRecap(vector<BuyerInvoice>, string, Date, vector<string> =vector<string>(), bool=false, vector<ChargeRecord> =vector<ChargeRecord>());

private:
  TextReportTable makeBuyerTable();
  TextReportTable makeRecapTable();
  TextReportTable makeSummaryTable();
  TextReportTable makeTotalTable();
  void appendChargeRecordList(vector<ChargeRecord>&, vector<ChargeRecord>);
  vector<BuyerInvoice> invoiceList;
  string owner;
  Date date;

  double recapChargeTotal();

  double recapTotal;
  double chargeTotal;
  vector<string> unprintedBuyerList;
  bool consolidateCharges;
  vector<ChargeRecord> recapCharges;
};
#endif
