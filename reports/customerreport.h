
#ifndef _CUSTOMER_REPORT_H_
#define _CUSTOMER_REPORT_H_

#include "../types/customer.h"
#include "textreport.h"
#include <algorithm>
#include "ctype.h"
#include <vector>

using namespace std;

class CustomerReport : public TextReport
{
public:
  CustomerReport(vector<Customer> =vector<Customer>());
  virtual ~CustomerReport();
  string unformattedText();
  string text();
  void setCustomerList(vector<Customer>);
  virtual string headerString();
protected:
  virtual TextReportHeader reportHeader();
  virtual void initCustomerTable(TextReportTable&);
  virtual void setCustomerTableRow(unsigned int,TextReportTable&, Customer);
  virtual void setSummaryLines(TextReportTable&, vector<Customer>);
private:
  TextReportTable customerTable();
  vector<Customer> customerList;
};

class SellerReport : public CustomerReport
{
public:
  SellerReport(vector<Seller> = vector<Seller>(), vector<string> =vector<string>());
  virtual void initCustomerTable(TextReportTable&);
  virtual void setCustomerTableRow(unsigned int, TextReportTable&, Customer);
  virtual string headerString();
protected:
  virtual TextReportHeader reportHeader();
  virtual void setSummaryLines(TextReportTable&, vector<Customer>);
private:
  vector<string> checkNumberList;
};

class BuyerReport : public CustomerReport
{
public:
  BuyerReport(vector<Buyer> = vector<Buyer>());
  virtual void initCustomerTable(TextReportTable&);
  virtual void setCustomerTableRow(unsigned int, TextReportTable&, Customer);
  virtual string headerString();
protected:
  virtual TextReportHeader reportHeader();
private:
};

#endif
