#include "commission.h"

#include <cstdio>
#include "globals.h"

///////////////////////////////////////////////////////////////////////////////
//
// name: CommissionBreak(long=0, string="0.0", double=9999999999.99
//
// purpose: Constructor
//
// calling params: long    id          - the id of the commission break
//                 string  expression  - the expression which will be used to
//                                       calculate the value of the break
//                 double  breakValue  - the maximum value that this break
//                                       applies to 
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

CommissionBreak::CommissionBreak(long id, string expression, double breakValue, double noSaleCharge)
{
  setId(id);
  setExpression(expression);
  setBreakValue(breakValue);
  this->noSaleCharge = noSaleCharge;
  this->min = 0.00000001;
  this->max = 9999999999.99;
}

void CommissionBreak::setMin(double min)
{
  this->min = min;
}

void CommissionBreak::setMax(double max)
{
  this->max = max;
}

double CommissionBreak::getMin()
{
  return min;
}

double CommissionBreak::getMax()
{
  return max;
}

///////////////////////////////////////////////////////////////////////////////
//
// name: setId(long)
//
// purpose: sets the id of the Commission Break
//
// calling params: long id - the new value of the id
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CommissionBreak::setId(long id)
{
  this->id = id;
}



///////////////////////////////////////////////////////////////////////////////
//
// name: setExpression(string)
//
// purpose: sets the mathematical expression that the break holds for the 
//          commission
//
// calling params: string expression - a mathematical expression used 
//                                     to calculate the commission for this
//                                     break
// 
// return params: 
//
// Notes: See CommissionBreak class notes for notes on using expressions in 
//        the commissions
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CommissionBreak::setExpression(string expression)
{
  this->expression = expression;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setBreakValue(double)
//
// purpose: sets the maximum value at which this break will be used
//
// calling params: double breakVal - the maximum value at which this break will
//                                   be used
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CommissionBreak::setBreakValue(double breakVal)
{
  this->breakValue = breakVal;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getExpression()
//
// purpose: retrieves the mathematical expression of this break
//
// calling params: 
// 
// return params: string - a mathematical expression meant for use with the
//                         CommissionExpressionParser class
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

string CommissionBreak::getExpression()
{
  return expression;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getBreakValue()
//
// purpose: retrieves the maximum value that this break applies to 
//
// calling params: 
// 
// return params: double - the maximum value that this break applies to
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

double CommissionBreak::getBreakValue()
{
  return breakValue;
}

double CommissionBreak::getNoSaleCharge()
{
  return noSaleCharge;
}

///////////////////////////////////////////////////////////////////////////////
//
// name: getId()
//
// purpose: retrieves the id of the CommissionBreak
//
// calling params: 
// 
// return params: long - the id of the commission break
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

long CommissionBreak::getId()
{
  return id;
}

string CommissionBreak::buyerCommissionExpression(double amount, BuyerMode mode)
{
  char expression[255];
  switch(mode)
  {
  case Head:
  case CompanyHead:
  default:
    sprintf(expression, "%0.2f * H", amount); 
    break;

  case CWT:
  case CompanyCWT:
    sprintf(expression, "%0.2f * (W / 100)", amount);
    break;

  case Flat:
  case CompanyFlat:
    sprintf(expression, "%0.2f", amount);
    break;
  }

  return string(expression);
}

CommissionBreak CommissionBreak::buyerBreak(BuyerMode mode, double amount)
{
   return CommissionBreak(0, buyerCommissionExpression(amount, mode), 0);
}

///////////////////////////////////////////////////////////////////////////////
//
// name: Commission(long=0, TYPE=ByInvoice, BREAK_TYPE=AtWeight, vector<CommissionBreak> = vector<CommissionBreak>(), double=0.0, double=999999999.99)
//
// purpose: Constructor
//
// calling params: long                       id        - the id of the commission
//                 TYPE                       type      - the calculation mode of the commission
//                 BREAK_TYPE                 breakType - determines which value will cause 
//                                                        the commission to break
//                 vector<CommissionBreak>    breakList - the list of breaks the commission will use
//                 double                     min       - the minimum value that
//                                                        the commission can be
//                                            max       - the maximum value that
//                                                        the commission can be
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

Commission::Commission(long id, TYPE type, BREAK_TYPE breakType, vector<CommissionBreak> breakList, double min, double max, double noSaleCharge, string name)
{
  this->id = id;
  this->type = type;
  this->breakType = breakType;
  setBreakList(breakList);
  setMin(min);
  setMax(max);

  resetValues();

  this->noSaleCharge = noSaleCharge;
  this->name = name;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: ~Commission()
//
// purpose: destructor
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

Commission::~Commission()
{
}

Commission Commission::buyerCommission(CommissionBreak::BuyerMode buyerMode, double amount)
{
  return Commission(0, ByInvoice, AtHead, vector<CommissionBreak>(1,CommissionBreak::buyerBreak(buyerMode, amount)));
}

///////////////////////////////////////////////////////////////////////////////
//
// name: setType(TYPE type)
//
// purpose: Sets the calculation mode of the commission
//
// calling params: TYPE type - the new mode
// 
// return params: 
//
// Notes: 
//
// Todo: change the name of the TYPE type to MODE and the name of the type var
//       to mode
//
///////////////////////////////////////////////////////////////////////////////

void Commission::setType(TYPE type)
{
  this->type = type;
}

void Commission::setName(string name)
{
  this->name = name;
}

///////////////////////////////////////////////////////////////////////////////
//
// name: getType()
//
// purpose: retrieves the calculation mode of the commission
//
// calling params: 
// 
// return params: TYPE - the calulation mode of the commission
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

Commission::TYPE Commission::getType()
{
  return type;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setMin(double)
//
// purpose: sets the minimum value for a commission
//
// calling params: double min - the minumum value for the commission
// 
// return params: 
//
// Notes: If the value of the commission is below min after calculation,
//        then the calculate function returns min
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void Commission::setMin(double min)
{
  this->min = min;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setMax(double)
//
// purpose: sets the maximum possible value for a commission
//
// calling params: double max - the new maximum value for the commission
// 
// return params: 
//
// Notes: If the calculated value is greater than max in the calculation
//        function, then max is returned from the calculation function
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void Commission::setMax(double max)
{
  this->max = max;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getMin()
//
// purpose: retrieves the minimum possible value for the commission
//
// calling params: 
// 
// return params: double - the minimum possible value for the commission
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

double Commission::getMin()
{
  return min;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getMax()
//
// purpose: retrieves the largest possible value for the commission
//
// calling params: 
// 
// return params: double - the maximum commission value
//
// Notes: 
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

double Commission::getMax()
{
  return max;
}

double Commission::getNoSaleCharge()
{
  return noSaleCharge;
}

///////////////////////////////////////////////////////////////////////////////
//
// name: addValues(CommissionExpressionParser::VARIABLES)
//
// purpose: increases the values of the variables in the values variable  
//
// calling params: CommissionExpressionParser::VARIABLES vals - the commission Expression Parser values type
// 
// return params: 
//
// Notes: The values in the values variable are used to initialize the variables
//        in the expression parser. 
//
//        The initial values of all of the variables in the values variable
//        is 0, so to initialize the values just call this with the
//        vals variable set with your initializers
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void Commission::addValues(CommissionExpressionParser::VARIABLES vals)
{
  values.head += vals.head;
  values.price += vals.price;
  values.total += vals.total;
  values.weight += vals.weight;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: calculate()
//
// purpose: calculates the value of the commission
//
// calling params: 
// 
// return params: double - the value of the commission
//
// Notes: uses the CommissionExpressionParser to calculate the value from
//        the expression in the first commission break that is
//        valid.
//        return value will be no less than min and no greater than max
//
// Todo:
//
// All 'cout' statements in this function are '[KLN] debugs'
//
///////////////////////////////////////////////////////////////////////////////

double Commission::calculate()
{
  vector<CommissionBreak>::iterator currentBreak;
  double currentVal;

  if (commissionDebug) {
      cout << "Commission::calculate()" << endl; // [KLN] debug
  }

  switch(breakType)
  {
  case AtWeight:
  default:
    currentVal = getWeightAmount(values.weight / values.head);
    break;

  case AtHead:
    currentVal = double(values.head);
    break;

  case AtPrice:
    currentVal = (getDollarAmount(values.head == 0 ? 0 : values.total / values.head));//values.price;
    break;

  case AtTotal:
    currentVal = values.total;
    break;

  }
  if (commissionDebug) {
      cout << "  currentVal: " << currentVal << " "; // [KLN] debug
  }
  //sort(breakList.begin(), breakList.end());

  if(breakList.size() == 0)
  {
      if (commissionDebug) {
          cout << "  No break, returning only No Sale charges." << currentVal << endl;
      }
    cerr << "No break exists, returning only no sale charges" << endl;
    return noSaleCommission();
  }


  for(unsigned int i = breakList.size() - 1; i >= 0; i--)
  {
    if(breakList[i].getBreakValue() <= currentVal)
    {
      currentBreak = breakList.begin() + i;
      break;
    }

    if(i == 0)
    {
        if (commissionDebug) {
            cout << "  No valid breaks, returning only No Sale charges." << currentVal << endl;
        }
//      cerr << "no valid breaks, returning only no-sale charges" << endl;
      return noSaleCommission();
    }
  }

//   for(currentBreak = breakList.end(); currentBreak != breakList.begin(); currentBreak--)
//   {
//     if(currentBreak->getBreakValue() > currentVal)
//     {
//       break;
//     }
//   }

  calculator.setValues(values);

  if(currentBreak == breakList.end())
  {
    cerr << "Could not find appropriate break for this commission(" << currentVal << ")" << endl;
    return 0.0;
  }

  double result = calculator.parse(currentBreak->getExpression());

  double commPerHead = result / values.head;

  if(commPerHead < currentBreak->getMin() && currentBreak->getMin() > 0.009)
  {
    result = currentBreak->getMin() * values.head;
  }

  if(commPerHead < min && min > 0.009)
  {
   result = min * values.head;
  }


  if(commPerHead > currentBreak->getMax() && currentBreak->getMax() > 0.009)
  {
    result = currentBreak->getMax() * values.head;
  }

  if(commPerHead > max && max > 0.009)
  {
      result = max * values.head;
  }

  if (commissionDebug) {
      cout << " commission: " << result; // [KLN] debug
      if (noSaleCommission() > 0.10) cout << " (NoSale comm: " << noSaleCommission();
      cout << endl;

      cout << "End Commission::calculate()" << endl; // [KLN] debug
  }
  return getDollarAmount(result + (noSaleCommission()));
}

double Commission::noSaleCommission()
{
  if(noSaleCharge >= 1.00000001)
  {
    return noSaleValues.head * noSaleCharge;
  }
  
  if(noSaleCharge > 0.009)
  {
    Commission temp(0, type, breakType, breakList, min, max, 0.00000001);
    temp.resetValues();
    temp.addValues(noSaleValues);
    return temp.calculate() * noSaleCharge;
  }

  return 0.00000001;
}

/*
void Commission::addNoSaleHead(long noSaleHead)
{
  this->noSaleHead += noSaleHead;
}
*/

void Commission::addNoSaleValues(CommissionExpressionParser::VARIABLES vals)
{
  noSaleValues.head += vals.head;
  noSaleValues.price += vals.price;
  noSaleValues.total += vals.total;
  noSaleValues.weight += vals.weight;
}

void Commission::resetValues()
{
  values.head         = 0.0;
  values.price        = 0.0;
  values.total        = 0.0;
  values.weight       = 0.0;

  noSaleValues.head   = 0.00000001;
  noSaleValues.price  = 0.00000001;
  noSaleValues.total  = 0.00000001;
  noSaleValues.weight = 0.0000001;
}

///////////////////////////////////////////////////////////////////////////////
//
// name: setBreakList(vector<CommissionBrek> breakList)
//
// purpose: sets the list of breaks
//
// calling params: vector<CommissionBreak> breakList - a STL vector of commission
//                                                     breaks
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void Commission::setBreakList(vector<CommissionBreak> breakList)
{
  this->breakList = breakList;
}

void Commission::setBreakType(BREAK_TYPE breakType)
{
  this->breakType = breakType;
}

void Commission::setNoSaleCharge(double noSaleCharge)
{
  this->noSaleCharge = noSaleCharge;
}

///////////////////////////////////////////////////////////////////////////////
//
// name: getBreakList()
//
// purpose: retrieves the list of commission breaks
//
// calling params: 
// 
// return params: vector<CommissionBreak> - a STL vector of commission breaks
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

vector<CommissionBreak> Commission::getBreakList()
{
  return breakList;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getBreakType()
//
// purpose: shows on which of the variables the commission will break on
//
// calling params: 
// 
// return params: Commission::BREAK_TYPE - the break mode of the class
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

Commission::BREAK_TYPE Commission::getBreakType()
{
  return breakType;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getId()
//
// purpose: retrieves the id of the commission
//
// calling params: 
// 
// return params: long - the id of the commission
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

long Commission::getId()
{
  return id;
}

void Commission::setId(long id)
{
  this->id = id;
}

///////////////////////////////////////////////////////////////////////////////
//
// name: operator==(Commission)
//
// purpose: compares this object to the comparator object
//
// calling params: Commission comparator - the Commission to compare this to
// 
// return params: bool - the equality of this commission to the comparator Commission
//
// Notes: 2 Commissions are considered equivelent if thier id's are equivelent
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

bool Commission::operator==(Commission comparator)
{
  return id == comparator.id;
}

string Commission::getName()
{
  return name;
}
