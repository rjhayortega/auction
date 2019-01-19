#ifndef _SUMMARY_RECORD_H_
#define _SUMMARY_RECORD_H_

#include <vector>
#include <string>
#include <iostream>
#include "customer.h"

using namespace std;

class ChargeSummaryRecord
{
public:
  ChargeSummaryRecord(long=0, string="", double=0.000);
  long getChargeId();
  string getChargeDescription();
  double getChargeTotal();
  bool operator==(ChargeSummaryRecord);
  static bool compareIdsLT(ChargeSummaryRecord, ChargeSummaryRecord);

private:
  long chargeId;
  string chargeDescription;
  double chargeTotal;
};

class InvoiceSummaryRecord
{
public:
  InvoiceSummaryRecord(string="", string="", long=0.000, double=0.000, vector<ChargeSummaryRecord> =vector<ChargeSummaryRecord>(), vector<string> =vector<string>());
  string getCustomerNumber();
  string getCustomerName();
  long getHead();
  double getNet(bool=true);
  double getGross();
  double getChargeTotal();
  unsigned int chargeListLength();
  vector<ChargeSummaryRecord> getChargeSummaryList();
  vector<string> getCheckNumberList();
  static bool compareCustomerNumbersLT(InvoiceSummaryRecord, InvoiceSummaryRecord);

private:
  string customerNumber;
  string customerName;
  long head;
  double gross;
  vector<string> checkNumberList;
  vector<ChargeSummaryRecord> chargeSummaryList;
};

#endif
