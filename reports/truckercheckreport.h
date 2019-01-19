
#ifndef _TRUCKER_CHECK_REPORT_H_
#define _TRUCKER_CHECK_REPORT_H_

#include "textreport.h"
#include "../types/truckingrecord.h"
#include "../types/check.h"

class TruckerCheckReport : public TextReport
{
public:

  class TruckerCheckRecord
  {
  public:
    TruckerCheckRecord(TruckingRecord record=TruckingRecord(), string customerId="", string customerName="", double cwt=0.000)
    {
      this->record = record;
      this->customerName = customerName;
      this->customerId = customerId;
      this->cwt = cwt;
    }

    TruckingRecord record;
    string customerName;
    string customerId;
    double cwt;

  };

  class TruckerRecord
  {
  public:
    TruckerRecord(Check check, TruckerCheckRecord checkRecord)
    {
      this->check = check;
      recordList.push_back(checkRecord);
    }

    void addRecord(TruckerCheckRecord record)
    {
      recordList.push_back(record);
    }

    void setCheckAmount(double amount)
    {
      check.setAmount(amount);
    }

    bool operator==(string name)
    {
      return check == name;
    }

    vector<TruckerCheckRecord> getRecordList()
    {
      return recordList;
    }

    Check getCheck()
    {
      return check;
    }

  private:
    Check check;
    vector<TruckerCheckRecord> recordList;
  };

public:
  TruckerCheckReport(TruckerRecord);
  virtual string text();


private:
  Check check;
  vector<TruckerCheckRecord> truckerList;

  TextReportTable checkTable();
  TextReportTable detailTable();
};

#endif
