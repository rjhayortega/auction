
#ifndef _TRUCKING_RECORD_DAO_H_
#define _TRUCKING_RECORD_DAO_H_

#include "databasemanager.h"
#include "../types/truckingrecord.h"
#include "../types/customer.h"
#include <vector>
#include "salemanager.h"
#include "chargedao.h"

using namespace std;

class TruckingRecordDAO
{
public:

class TruckerCustomer
{
public:
  string number;
  ChargeDAO::CUST_TYPE type;

  bool operator==(TruckerCustomer that)
  {
    return this->number == that.number && this->type == that.type;
  }
};

  TruckingRecordDAO();
  TruckingRecord getCustomerTruckingRecord(Customer, ChargeDAO::CUST_TYPE);
  vector<TruckingRecord> getTruckingRecordList();
  vector<TruckingRecord> getTruckingRecordList(Customer, ChargeDAO::CUST_TYPE);
  void saveTruckingRecord(TruckingRecord, Customer, ChargeDAO::CUST_TYPE);
  void deleteTruckingRecord(TruckingRecord);
  vector<TruckerCustomer> getTruckingCustomerList(bool=false, Customer::Type=Customer::Both);
  vector<TruckingRecord> getTruckingRecordList(Customer::Type);
  void deleteTruckingRecordList(Customer, Customer::Type);

private:
  TruckingRecord getTruckingRecordByCondition(string);
  vector<TruckingRecord> getTruckingRecordListByCondition(string);
  SaleManager sale;
};

#endif
