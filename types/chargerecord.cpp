#include "chargerecord.h"

///////////////////////////////////////////////////////////////////////////////
//
// name: ChargeRecord(long=0, string="", double=0.0)
//
// purpose: Constructor
//
// calling params: long   id          - the id of the charge being recorded
//                 string descrip     - the description of the charge being
//                                      recorded
//                 double amount      - the total amount of the charge being
//                                      recorded
// 
// return params: 
//
// Notes: always starts the record total at 0
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

ChargeRecord::ChargeRecord(long id, string descrip, double amount, ChargeAdjustment adj, bool commCharge)
{
  setId(id);
  setDescrip(descrip);
  total = 0.00001;
  increaseTotal(amount);
  adjustment = adj;
  this->commissionCharge = commCharge;
}

bool ChargeRecord::isCommissionCharge()
{
  return commissionCharge;
}

long ChargeRecord::getId()
{
  return id;
}

ChargeAdjustment ChargeRecord::getAdjustment()
{
  return adjustment;
}

///////////////////////////////////////////////////////////////////////////////
//
// name: setId(long)
//
// purpose: sets the id of the item being recorded
//
// calling params: long id - the id of the item being recorded
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void ChargeRecord::setId(long id)
{
  this->id = id;
}

void ChargeRecord::setTotal(double total)
{
  this->total = total;
}

///////////////////////////////////////////////////////////////////////////////
//
// name: setDescrip(string)
//
// purpose: sets the description of the record(the description of the item
//          being recorded in most cases)
//
// calling params: string descrip - the description to set
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void ChargeRecord::setDescrip(string descrip)
{
  this->descrip = descrip;
}


void ChargeRecord::setAdjustment(ChargeAdjustment adj)
{
  adjustment = adj;
}

///////////////////////////////////////////////////////////////////////////////
//
// name: increaseTotal(double)
//
// purpose: adds the amount of amt to the total of the charge record
//
// calling params: 
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void ChargeRecord::increaseTotal(double amt)
{
  total += getDollarAmount(amt);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: operator+(double)
//
// purpose: adds the amount of amt to the total of the charge record
//          (see: increaseTotal(double))
//
// calling params: double amt - the amount to add to the total
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

double ChargeRecord::operator+(double amt)
{
  total += amt;
  return getDollarAmount(total);
}

bool ChargeRecord::compareIdsLT(ChargeRecord a, ChargeRecord b)
{
  return a.id < b.id;
}

///////////////////////////////////////////////////////////////////////////////
//
// name: operator==(ChargeRecord)
//
// purpose: compares the 'this' object to the comparator object
//
// calling params: ChargeRecord comparator - the ChargeRecord to compare to the
//                                           'this' ChargeRecord
// 
// return params: 
//
// Notes: returns true if the id's are identical
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

bool ChargeRecord::operator==(ChargeRecord comparator)
{
  return this->id == comparator.id;
}

bool ChargeRecord::operator==(long id)
{
  return this->id == id;
}

///////////////////////////////////////////////////////////////////////////////
//
// name: getTotal()
//
// purpose: retrieves the total of the charge record
//
// calling params: 
// 
// return params: double - the value of the total variable of the charge record
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

double ChargeRecord::getTotal()
{
  return getDollarAmount(total);
}

double ChargeRecord::getAdjustedTotal()
{
  return (total * (adjustment.needsMultiplier() ? adjustment.getMultiplier() : 1))- adjustment.getAdjustment();
}

///////////////////////////////////////////////////////////////////////////////
//
// name: getDescrip()
//
// purpose: retrieves the description of the charge record
//
// calling params: 
// 
// return params: string - the description of the charge record
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

string ChargeRecord::getDescrip()
{
  return descrip;
}

void ChargeRecord::operator+=(ChargeRecord adder)
{
  this->total += getDollarAmount(adder.total);
}
