
#ifndef _BUYER_CHECK_REPORT_H
#define _BUYER_CHECK_REPORT_H

#include "textreport.h"
#include "../types/check.h"

class BuyerCheckReport : public TextReport
{
public:
  class BuyerCommissionRecord
  {
  public:
    BuyerCommissionRecord(string name="", string company="", double commission=0.0, string number="")
    {
	this->name = name;
	this->company = company;
	this->commission = commission;
	this->number = number;
    }

    string name;
    string company;
    double commission;
    string number;
  };

  class BuyerRecord
  {

  private:
      Check check;
      vector<BuyerCommissionRecord> commRecList;

  public:
    BuyerRecord(Check check=Check(), BuyerCommissionRecord commRec = BuyerCommissionRecord())
    {
      this->check = check;
      commRecList.push_back(commRec);
    }

    void addCommissionRecord(BuyerCommissionRecord commRec)
    {
      commRecList.push_back(commRec);
    }

    void setCheckAmount(double amount)
    {
      check.setAmount(amount);
    }

    Check getCheck()
    {
      return check;
    }

    void setCheck(Check check)
    {
      this->check = check;
    }

    vector<BuyerCommissionRecord> getCommissionList()
    {
      return commRecList;
    }

    bool operator==(string name)
    {
      return check == name;
    }

  };

  BuyerCheckReport(BuyerRecord =BuyerRecord());
  virtual string text();

private:
  Check check;
  vector<BuyerCommissionRecord> commissionList;

  TextReportTable checkTable();
  TextReportTable detailTable();
};
#endif
