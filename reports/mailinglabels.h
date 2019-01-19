#ifndef _MAILING_LABELS_H_
#define _MAILING_LABELS_H_

#include <vector>
#include "../types/customer.h"
#include <string>
#include "textreport.h"

using namespace std;

class MailingLabels : public TextReport
{
public:
  MailingLabels(vector<Customer> =vector<Customer>(), bool=false);
  virtual string text();


private:
  vector<Customer> customerList;
  bool showAll;
  TextReportTable labelsTable();
};

#endif
