
#ifndef _BUYER_AR_H_
#define _BUYER_AR_H_

#include "../types/invoice.h"
#include "textreport.h"
#include <ctype.h>
#include <algorithm>
#include <vector>

using namespace std;

class BuyerAR : public TextReport
{
public:
  typedef enum{NameSort, NumberSort}SortOption;

  class Record
  {
  public:
    Record(string number="", string name="",string company="", Invoice::STATUS status=Invoice::UNPAID, double amount=0.0, bool printed=false)
    {
      this->number = number;
      this->name = name;
      this->status = status;
      this->amount = amount;
      this->printed = printed;
      this->company = company;
    }

    bool operator==(Record comparator)
    {
      return this->name == comparator.name;
    }

    static bool compareName(Record a, Record b)
    {
      return a.name < b.name;
    }

    static bool compareNameEQ(Record a, Record b)
    {
      return a.name == b.name;
    }

    static bool compareId(Record a, Record b)
    {
      string buf = "";
      for(unsigned int i = 0; i < a.number.size(); i++)
      {
	if(isdigit(a.number[i]))
	{
	  buf += a.number[i];
	}
	else break;
      } 

      buf = "";
      for(unsigned int i = 0; i < b.number.size(); i++)
      {
	if(isdigit(b.number[i]))
	{
	  buf += b.number[i];
	}
	else break;
      } 
      return atol(a.number.c_str()) < atol(b.number.c_str());
    }

    static bool compareIdEQ(Record a, Record b)
    {

      string buf = "";
      for(unsigned int i = 0; i < a.number.size(); i++)
      {
	if(isdigit(a.number[i]))
	{
	  buf += a.number[i];
	}
	else break;
      } 

      buf = "";
      for(unsigned int i = 0; i < b.number.size(); i++)
      {
	if(isdigit(b.number[i]))
	{
	  buf += b.number[i];
	}
	else break;
      } 
      return atol(a.number.c_str()) == atol(b.number.c_str());
    }

    string number;
    string name;
    Invoice::STATUS status;
    double amount;
    bool printed;
    string company;
  };

  BuyerAR(vector<Record> =vector<Record>(), bool=false, SortOption=NameSort);
  virtual string text();
  void initTable(TextReportTable&);
private:
  vector<Record>recordList;
  bool detailed;
  SortOption sortOption;

  double paidTotal;
  double companyTotal;
  double unpaidTotal;
  double unprintedTotal;
  TextReportTable detailedARTable();
  TextReportTable simpleARTable();
  TextReportTable totalTable();
  void group(vector<Record>&);
};

#endif
