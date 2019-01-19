#ifndef _ALL_FLEX_REPORT_H_
#define _ALL_FLEX_REPORT_H_

#include "textreport.h"
#include "../types/customer.h"
#include <vector>

using namespace std;

class AllFlexReport : public TextReport
{
public:
  AllFlexReport(vector<Seller>);

  virtual string text();

private:
  TextReportTable tagTable();
  vector<Seller> sellerList;
};

#endif
