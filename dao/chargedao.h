
#ifndef _CHARGE_DAO_H_
#define _CHARGE_DAO_H_
#include "../types/charge.h"
#include "../types/animalcode.h"
#include "../types/invoice.h"
#include "../types/summaryrecord.h"
#include <vector>
#include <list>
#include <string>
#include "databasemanager.h"
#include "commissiondao.h"


using namespace std;

class ChargeDAO
{
public:
  ChargeDAO();
  class ChargeTable
  {
  public:
    ChargeTable(AnimalCode code=AnimalCode(), vector<Charge> chargeList=vector<Charge>())
    {
      this->code = code;
      this->chargeList = chargeList;
      this->current = false;
    }

    bool operator==(AnimalCode code)
    {
      return this->code == code;
    }

    AnimalCode code;
    vector<Charge> chargeList;
    bool current; 
  };

typedef enum custType
{
  Seller=0,
  Buyer=1
}CUST_TYPE;

typedef struct chgSummItem
{
  long id;
  string descrip;
  double total;
}SUMMARY_ITEM;


vector<Charge> getChargeList(AnimalCode, CUST_TYPE=Seller, bool=false);
vector<Charge> getChargeList(CUST_TYPE, CommissionDAO::COLOR_GROUP=CommissionDAO::INVALID);
void saveCharge(Charge, CUST_TYPE=Seller, list<AnimalCode> =list<AnimalCode>());
void deleteCharge(Charge);
list<AnimalCode> getCodeList(Charge);
ChargeAdjustment getAdjustment(Charge, Invoice*, Customer::Type=Customer::Seller);
void saveAdjustment(Charge, Invoice, ChargeAdjustment);
void deleteAdjustment(Customer, Customer::Type);

vector<SUMMARY_ITEM> getChargeSummary(CUST_TYPE, AnimalCode::Group=AnimalCode::Invalid);
vector<Charge> getManualChargeList(CommissionDAO::COLOR_GROUP, CUST_TYPE=Seller);
vector<ChargeSummaryRecord> getChargeSummaryRecordList(long, CUST_TYPE);
void deleteChargeSummary(Customer, Customer::Type);
vector<Charge> getChargeHistory(Invoice*, Customer::Type);

void swapChargeAdjustmentIds(Charge, Charge);
//void swapChargeSummaryIds(Charge, Charge);
void swapChargeBreakIds(Charge, Charge);
vector<ChargeAdjustment> getAdjustments(Invoice*);

private:
void clearBeefCouncil();
vector<Charge> getChargeListByCondition(string);
SaleManager sale;
string groupIdList(CommissionDAO::COLOR_GROUP);
string codeList(AnimalCode);

void saveChargeBreakList(Charge& charge);
void decimateChargeBreakList(Charge& charge);
vector<ChargeBreak> getChargeBreakList(Charge&);

};
#endif
