#include "charge.h"

#include <algorithm>
#include <cstring>

ChargeAdjustment::ChargeAdjustment(double multiplier, double adjustment, bool needMultiplier, long chargeId)
{
  this->multiplier = multiplier;
  this->needMultiplier = needMultiplier;
  this->adjustment= adjustment;
  this->chargeId = chargeId;
}

double ChargeAdjustment::getMultiplier()
{
  return multiplier;
}

double ChargeAdjustment::getAdjustment()
{
  return adjustment;
}

long ChargeAdjustment::getChargeId()
{
  return chargeId;
}

void ChargeAdjustment::setChargeId(long chargeId)
{
  this->chargeId = chargeId;
}

bool ChargeAdjustment::needsMultiplier()
{
  return needMultiplier;
}

void ChargeAdjustment::setMultiplierNeed(bool need)
{
  this->needMultiplier = need;
}

ChargeExpressionParser Charge::calculator;

///////////////////////////////////////////////////////////////////////////////
//
// name: Charge(long=0,string="", string="", bool=false, bool=false, bool=false)
//
// purpose: Constructor
//
// calling params: long   id              - the id number of the charge
//                 string expression      - the mathematical expression the charge 
//                                          will perform to get a value
//                 bool   chargeOnNoSale  - determines if a no sale transaction
//                                          should be charged
//                        chargeOnReSale  - determines if a re-sale transaction
//                                          should be charged
//                        doubleOnPairs   - determines if pairs should double
//                                          the charge
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

Charge::Charge(long id, string descrip, string expression, 
               bool chargeOnNoSale, bool chargeOnReSale, bool doubleOnPairs, 
               bool needMultiplier, bool commCharge, bool beefCouncil)
{
  this->id             = id;
  this->descrip        = descrip;
  this->expression     = expression;
  this->chargeOnNoSale = chargeOnNoSale;
  this->chargeOnReSale = chargeOnReSale;
  this->doubleOnPairs  = doubleOnPairs;
  this->needMultiplier = needMultiplier;
  this->commissionCharge = commCharge;
  adjustment = ChargeAdjustment();
  this->beefCouncil = beefCouncil;
  this->breakType = ChargeBreak::None;
  this->breakList.clear();
  this->scope = Transaction;
}

void Charge::setScope(Scope scope)
{
  this->scope = scope;
}

Charge::Scope Charge::getScope()
{
  return scope;
}

bool Charge::isCommissionCharge()
{
  return commissionCharge;
}

void Charge::setBreakType(ChargeBreak::Type breakType)
{
  this->breakType = breakType;
}

///////////////////////////////////////////////////////////////////////////////
//
// name: calculate(ChargeExpressionParser::VARIABLES, CHARGE_MODE, bool)
//
// purpose: calculates the charge with the values in vals, by the mode 'mode'
//
// calling params: ChargeExpressionParser::VARIABLES vals - a structure the
//                                                          charge parser uses
//                                                          to initialize the
//                                                          variables of the 
//                                                          charge parser
//                 CHARGE_MODE mode  - determines if the transaction the 
//                                     charge is being applied to is Normal, 
//                                     a no-sale or a re-sale
//                 bool isPair       - determines if the charge is being 
//                                     applied to a pair type
// 
// return params: double - the amount of the charge
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

double Charge::calculate(ChargeExpressionParser::VARIABLES vals, CHARGE_MODE mode, bool isPair, string* expressionOverride)
{
  double result = 0.0;
  string actualExpression = expression;
  bool bestFound = false;

  if(chargeOnNoSale && mode == NoSale || chargeOnReSale && mode == ReSale || mode == Normal)
  {
    Charge::calculator.setValues(vals);
    if(expressionOverride == NULL || *expressionOverride == "")
    {
      double compareValue = 0.00000001;

      std::sort(breakList.begin(), breakList.end(), ChargeBreak::compareAmountLT);

      for(unsigned int i = 0; i < breakList.size() && breakType != ChargeBreak::None && !bestFound; i++)
      {
        compareValue = 0.00000001;

        switch(breakType)
        {
        default:
  	  break;
        case ChargeBreak::Head:
	  compareValue = vals.head;
	  break;

        case ChargeBreak::Weight:
        {
  	  compareValue = (vals.head != 0 ? vals.weight / vals.head : 0);
        }
        break;

        case ChargeBreak::Total:
	  compareValue = vals.totalDollars;
	  break;
        }

        if(compareValue >= breakList[i].getAmount())
        {
  	  actualExpression = breakList[i].getExpression();
        }
        else
        {
	  bestFound = true;
        }
      }

      if(expressionOverride != NULL)
      {
	*expressionOverride = actualExpression;
      }
    }
    else if(expressionOverride != NULL && *expressionOverride != "")
    {
      actualExpression = *expressionOverride;
    }

    result = Charge::calculator.parse(actualExpression);
  }

  if(isPair && doubleOnPairs)
  {
    result = result * 2;
  }

  return getDollarAmount(result);
}

void Charge::resetValues()
{
  memset(&values,           0, sizeof(ChargeExpressionParser::VARIABLES));
  memset(&pairValues,       0, sizeof(ChargeExpressionParser::VARIABLES));
  memset(&nosaleValues,     0, sizeof(ChargeExpressionParser::VARIABLES));
  memset(&nosalePairValues, 0, sizeof(ChargeExpressionParser::VARIABLES));
  memset(&resaleValues,     0, sizeof(ChargeExpressionParser::VARIABLES));
  memset(&resalePairValues, 0, sizeof(ChargeExpressionParser::VARIABLES));
  memset(&swapValues,       0, sizeof(ChargeExpressionParser::VARIABLES));
  memset(&swapPairValues,   0, sizeof(ChargeExpressionParser::VARIABLES));
}

void Charge::addValues(ChargeExpressionParser::VARIABLES newValues, CHARGE_MODE mode, bool isPair, bool isSwap)
{
  if(isSwap)
  {
    if(isPair)
    {
      ChargeExpressionParser::addValues(&swapPairValues, newValues);
    }

    ChargeExpressionParser::addValues(&swapValues, newValues);
    
  }
  else 
  {
    switch(mode)
    {
    default:
      if(isPair)
      {
        ChargeExpressionParser::addValues(&pairValues, newValues);
      }

      ChargeExpressionParser::addValues(&values, newValues);
      
      break;
    
    case NoSale:
      if(isPair)
      {
        ChargeExpressionParser::addValues(&nosalePairValues, newValues);
      }

      ChargeExpressionParser::addValues(&nosaleValues, newValues);
      
      break;

    case ReSale:
      if(isPair)
      {
        ChargeExpressionParser::addValues(&resalePairValues, newValues);
      }
      ChargeExpressionParser::addValues(&resaleValues, newValues);
      break;
    }
  }
}

double Charge::calculate()
{
  ChargeExpressionParser::VARIABLES actualValues;
  ChargeExpressionParser::VARIABLES actualPairs;

  memset(&actualValues, 0, sizeof(ChargeExpressionParser::VARIABLES));
  memset(&actualPairs , 0, sizeof(ChargeExpressionParser::VARIABLES));

  ChargeExpressionParser::addValues(&actualValues, values);
//  ChargeExpressionParser::addValues(&actualValues, pairValues);

  if(doubleOnPairs)
  {
    ChargeExpressionParser::addValues(&actualPairs, pairValues);
  }

  if(chargeOnNoSale)
  {
    ChargeExpressionParser::addValues(&actualValues, nosaleValues);
//    ChargeExpressionParser::addValues(&actualValues, nosalePairValues);

    if(doubleOnPairs)
    {
      ChargeExpressionParser::addValues(&actualPairs, nosalePairValues);
    }
  }

  if(chargeOnReSale)
  {
    ChargeExpressionParser::addValues(&actualValues, resaleValues);
    //  ChargeExpressionParser::addValues(&actualValues, resalePairValues);

    if(doubleOnPairs)
    {
          ChargeExpressionParser::addValues(&actualPairs, resalePairValues);
    }
  }

  string actualExpression;
  return (calculate(actualValues, Charge::Normal, false, &actualExpression) + calculate(actualPairs, Charge::Normal, false, &actualExpression)) - (calculate(swapValues, Charge::Normal, false, &actualExpression) + calculate(swapPairValues, Charge::Normal, false, &actualExpression));
}

///////////////////////////////////////////////////////////////////////////////
//
// name: operator==(Charge)
//
// purpose: compares the 'this' object to the comparator object
//
// calling params: Charge comparator - the charge to compare the 'this' object 
//                                     to
// 
// return params: 
//
// Notes: returns true if the id's of the charges are identical
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

bool Charge::operator==(Charge comparator)
{
  return this->id == comparator.getId();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setId(long)
//
// purpose: sets the id of the charge
//
// calling params: long id - the value to set the id to
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void Charge::setId(long id)
{
  this->id = id;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setDescrip(string)
//
// purpose: sets the value of the charge description variable
//
// calling params: string descrip - the value to set the description to
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void Charge::setDescrip(string descrip)
{
  this->descrip = descrip;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setExpression(string)
//
// purpose: sets the expression string
//
// calling params: 
// 
// return params: 
//
// Notes:
//
// Todo: check to ensure that the expression parses when it is being set
//
///////////////////////////////////////////////////////////////////////////////

void Charge::setExpression(string expression)
{
  this->expression = expression;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setChargesOnNoSale(bool)
//
// purpose: sets the chargeOnNoSale flag
//
// calling params: bool chargeOnNoSale - the new value of the chargeOnNoSale 
//                                       flag for the charge
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void Charge::setChargesOnNoSale(bool chargeOnNoSale)
{
  this->chargeOnNoSale = chargeOnNoSale;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setChargesOnReSale(bool)
//
// purpose: sets the chargeOnReSale flag
//
// calling params: bool chargeOnReSale - the new value of the chargeOnReSale 
//                                       flag for the charge
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void Charge::setChargesOnReSale(bool chargeOnReSale)
{
  this->chargeOnReSale = chargeOnReSale;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setDoublesOnPairs(bool)
//
// purpose: sets the doubleOnPairs flag
//
// calling params: bool doubleOnPairs - the new value of the doubleOnPairs
//                                      flag for the charge
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void Charge::setDoublesOnPairs(bool doubleOnPairs)
{
  this->doubleOnPairs = doubleOnPairs;
}

void Charge::setMultiplierNeed(bool needMultiplier)
{
  this->needMultiplier = needMultiplier;
}

void Charge::setAdjustment(ChargeAdjustment adj)
{
  adj.setMultiplierNeed(needMultiplier);
  this->adjustment = adj;
}

///////////////////////////////////////////////////////////////////////////////
//
// name: getId()
//
// purpose: retrieves the id number of the charge
//
// calling params: 
// 
// return params: long - the id number of the charge
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

long Charge::getId()
{
  return id;
}

bool Charge::isBeefCouncil()
{
  return beefCouncil;
}

void Charge::setBreakList(vector<ChargeBreak> breakList)
{
  this->breakList = breakList;
}

///////////////////////////////////////////////////////////////////////////////
//
// name: getDescrip()
//
// purpose: retrieves the description of the charge
//
// calling params: 
// 
// return params: string - the charge's description
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

string Charge::getDescrip()
{
  return descrip;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getExpression()
//
// purpose: retrieves the expression the charge uses to calculate the charge 
//          amount
//
// calling params: 
// 
// return params: string - an expression the charge uses to calculate the 
//                         charge amount
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

string Charge::getExpression()
{
  return expression;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: chargesOnNoSale()
//
// purpose: retrieves the value of the chargeOnNoSale flag
//
// calling params: 
// 
// return params: bool - the value of the chargeOnNoSale flag
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

bool Charge::chargesOnNoSale()
{
  return chargeOnNoSale;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: chargesOnReSale()
//
// purpose: retrieves the value of the chargeOnReSale flag
//
// calling params: 
// 
// return params: bool - the value of the chargeOnReSale flag
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

bool Charge::chargesOnReSale()
{
  return chargeOnReSale;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: doublesOnPairs()
//
// purpose: retrieves the value of the doublesOnPairs flag
//
// calling params: 
// 
// return params: bool - the value of the doublesOnPairs flag
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

bool Charge::doublesOnPairs()
{
  return doubleOnPairs;
}

bool Charge::needsMultiplier()
{
  return needMultiplier;
}

ChargeBreak::Type Charge::getBreakType()
{
  return breakType;
}

vector<ChargeBreak> Charge::getBreakList()
{
  return breakList;
}

bool Charge::compareIdsLT(Charge a, Charge b)
{
  return a.id < b.id;
}

ChargeAdjustment Charge::getAdjustment()
{
  return adjustment;
}
