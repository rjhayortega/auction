#ifndef _HISTORY_REPORT_H_
#define _HISTORY_REPORT_H_

#include <vector>
#include "../types/historyitem.h"
#include "textreport.h"
#include <algorithm>
#include <string>

using namespace std;

class HistoryReport : public TextReport
{
public:
  HistoryReport(vector<HistoryItem> =vector<HistoryItem>());
  void setHistoryList(vector<HistoryItem>);
  string text();

protected:
  virtual TextReportTable historyTable()=0;
  vector<HistoryItem> historyList;
  virtual TextReportTable summaryTable();
private:

};

class SellerHistoryReport : public HistoryReport
{
public:
  SellerHistoryReport(vector<HistoryItem> =vector<HistoryItem>());

  class Totals
  {
  public:
    string typeDescrip;
    long head;
    long weight;
    double gross;
  };

protected:
  virtual TextReportTable historyTable();
  virtual TextReportTable summaryTable();
private:
  void initHistoryTable(TextReportTable&);
  vector<Totals> typeTotals;
};

class BasicHistoryReport : public HistoryReport
{
public:
  BasicHistoryReport(vector<HistoryItem> =vector<HistoryItem>());
protected:
  virtual TextReportTable historyTable();

private:
  void initTable(TextReportTable&);
};

class BuyerHistoryReport : public BasicHistoryReport
{
public:
  BuyerHistoryReport(vector<HistoryItem> =vector<HistoryItem>());
};

class CodeHistoryReport : public BasicHistoryReport
{
public: 
  CodeHistoryReport(vector<HistoryItem> =vector<HistoryItem>());
};

class DateHistoryReport : public HistoryReport
{
public:
  DateHistoryReport(vector<HistoryItem> =vector<HistoryItem>());

protected:
  virtual TextReportTable historyTable();
  virtual string customerTypeString()=0;
  virtual string customerNameString(unsigned int)=0;

private:
  void initHistoryTable(TextReportTable& table);
};

class SellerDateHistoryReport : public DateHistoryReport
{
public:
  SellerDateHistoryReport(vector<HistoryItem> =vector<HistoryItem>());
protected:
  virtual string customerTypeString();
  virtual string customerNameString(unsigned int);
};


class BuyerDateHistoryReport : public DateHistoryReport
{
public:
  BuyerDateHistoryReport(vector<HistoryItem> =vector<HistoryItem>());

protected:
  virtual string customerTypeString();
  virtual string customerNameString(unsigned int);
};

#endif
