#ifndef _COMMISSION_DAO_H_
#define _COMMISSION_DAO_H_

#include "../types/commission.h"
#include "databasemanager.h"
#include <vector>
#include <list>
#include <string>
#include "salemanager.h"

using namespace std;

class CommissionDAO
{
public:

  class CommissionTable
  {
  public:
    CommissionTable(AnimalCode code, Commission comm)
    {
      this->commission = comm;
      this->code = code;
    }

    bool operator==(AnimalCode code)
    {
      return this->code == code;
    }

    Commission commission;
    AnimalCode code;
  };

  class BuyerCommissionTable
    {
    public:
      BuyerCommissionTable(string _id, Commission _commission) : id(_id), commission(_commission) {}

      bool operator==(string id)
	{ return this->id == id; }
      string id;
      Commission commission;
    };
typedef enum
{
  FIRST,
  SECOND,
  THIRD,
  FOURTH,
  INVALID
}COLOR_GROUP;

  CommissionDAO();
  Commission getCommission(AnimalCode);
  Commission getBuyerCommission(string);
  void saveBuyerCommission(double, CommissionBreak::BuyerMode, string);
  void getBuyerCommissionData(CommissionBreak::BuyerMode&, double&, string);
  vector<Commission> getCommissionList(COLOR_GROUP=INVALID);
  long saveCommission(Commission, list<AnimalCode> codeList=list<AnimalCode>(), COLOR_GROUP=FIRST);
  void deleteCommission(Commission);
  void deleteBreak(CommissionBreak);
  void deleteBreaks(Commission);

  vector<CommissionBreak> getBreakList(long=0);
  list<AnimalCode> getCodeRelList(long=0);
  void saveBreak(CommissionBreak, long=0);

  vector<string> getCommissionedBuyerIdList();

  static COLOR_GROUP getColorGroup(short);

  void setBuyerCheckNo(string, long);
  long getBuyerCheckNo(string);

private:

  string getCommissionIdString(AnimalCode);
  void saveBreakList(vector<CommissionBreak>, long=0);
  void saveCodeRelationships(list<AnimalCode>, COLOR_GROUP, long);
  SaleManager sale;
  CommissionBreak::BuyerMode defaultMode;

};
#endif
