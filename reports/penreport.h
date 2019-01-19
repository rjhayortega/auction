
#ifndef _PEN_REPORT_H_
#define _PEN_REPORT_H_

#include "textreport.h"
#include "../types/transaction.h"
#include <string>
#include <algorithm>
#include "../types/customer.h"

using namespace std;

class PenReport : public TextReport
{

public:
  typedef enum{SortByPen, SortByNumber}SortOption;
  class Item
  {
  public:

    Item(string pen="", long head=0, long noSaleCount=0, string buyerId="", string buyerName="", long weight=0)
    {
      this->pen = pen;
      this->head = head;
      this->noSaleCount = noSaleCount;
      this->buyerId = buyerId;
      this->buyerName = buyerName;
      this->weight = weight;
    }

    string pen;
    long head;
    long noSaleCount;
    string buyerId;
    string buyerName;
    long weight;

    static bool comparePenLT(Item a, Item b)
    {
      long digitPartA = atol(a.pen.c_str());
      long digitPartB = atol(b.pen.c_str());

      if(digitPartA != digitPartB)
      {
	return digitPartA < digitPartB;
      }

      int aIndex = a.pen.find_first_not_of("0123456789");
      int bIndex = b.pen.find_first_not_of("0123456789");

      string alphaPartA = (aIndex != (int)string::npos ? a.pen.substr(aIndex) : "");
      string alphaPartB = (bIndex != (int)string::npos ? b.pen.substr(bIndex) : "");

      return alphaPartA < alphaPartB;
    }

    static bool compareBuyerNumberLT(Item a, Item b)
    {
      return Customer::compareCustomerNumbersLT(a.buyerId, b.buyerId);
    }
  };

  PenReport(vector<PenReport::Item> =vector<Item>(), PenReport::SortOption=SortByPen);

  virtual string text();
  TextReportTable penTable();

private:
  vector<Item> penItemList;
  SortOption sortOption;
};

#endif
