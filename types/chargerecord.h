
#ifndef _CHARGE_RECORD_H_
#define _CHARGE_RECORD_H_
/******************************************************************************
-
- class ChargeRecord
-
- purpose: Keeps a record of calculated charges
- 
- Notes: Also used to record calculated commissions, maybe ChargeRecord is 
-        an innapropriate name?
- 
- Todo: 
-
*****************************************************************************/
#include <string>
#include <iostream>
#include "charge.h"
#include "numbers.h"

using namespace std;


class ChargeRecord
{
public:
  ChargeRecord(long=0, string="", double=0.0, ChargeAdjustment=ChargeAdjustment(), bool=false);

  void setId(long);
  void setDescrip(string);
  void increaseTotal(double);
  void setTotal(double);
  void setAdjustment(ChargeAdjustment);

  long getId();
  double getTotal();
  double getAdjustedTotal();
  double operator+(double);
  ChargeAdjustment getAdjustment();
void operator+=(ChargeRecord);
  bool operator==(ChargeRecord);
  bool operator ==(long);
  string getDescrip();
  bool isCommissionCharge();
  static bool compareIdsLT(ChargeRecord, ChargeRecord);

private:
  long id;
  string descrip;
  double total;
  bool commissionCharge;
  ChargeAdjustment adjustment;
};

#endif
