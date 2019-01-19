
#ifndef _COMMISSION_H_
#define _COMMISSION_H_
/******************************************************************************
-
- class CommissionBreak
-
- purpose: encapsulates a particular range to apply to a commission
- 
- Notes: A break is the part of the commission that contains the expression
-       that the commission will use to calculate the commission's value. 
-       The reason that the breaks are used to store the expressions is
-       so that different expressions can be used for a commission if
-       the commission will be different after a user defined amount for
-       the various break modes (see: breakType property of commissions)
-       A commission can have zero or more breaks. If a commission has no 
-       breaks or the break value is out of range of all existing breaks, a 
-       value of zero will be the result when the commission is calculated
- 
-       There are several variables that can be used in the expression 
-       portion of the break, but for them to have any meaning in the
-       commission, the values variable must be initialized with the values
-       that represent the variables. The values are set by adding
-       a CommissionExpressionParser::VARIABLES type struct to the current 
-       values with the addValues(CommissionExpressionParser::VARIABLES)
-       function of the Commission class. The values are all initially set to
-       zero. An important thing to be aware of when using division is that
-       in the commission parser, division by 0 is NOT UNDEFINED but instead 
-       always causes to have that part of the expression as being evaluted to
-       zero. The reason for this is that for most (if not all) user-defined 
-       commissions, this will be semantically correct (e.g. when the user wants
-       use the price-per-head (P / H) in the calculation, when there are 0 head
-       obviously there is no price for those head thus the p-p-h will be 0.
-       Unless a likely situation comes to my attention where division by 0 should
-       be undefined for these expressions, I am going to leave this as-is
-
-       The expression variables and the corresponding values variables are as follows.
-        __________________________________
-       | Expr Var. | values var to be set |
-       |----------------------------------|
-       |  h or H   |     values.head      |
-       |  t or T   |     values.total     |
-       |  p or P   |     values.price     |
-       |  w or W   |     values.weight    |
-        ----------------------------------
- 
- Todo: 
-
*****************************************************************************/

/******************************************************************************
-
- class Commission
-
- purpose: encapsulates a commission
- 
- Notes: The breaks are what hold the math expressions for the commission
-        calculations. For a commission to mean anything relevent, the 
-        commission must have at least one break. However this break may have 
-        a value of the system maximum so that it will be used for all values
-        if no break exists for the current breakType and breakValue, then
-        the resulting commission calculation will be 0.0. 
- 
- Todo: Write this up a little more clearly
-
*****************************************************************************/

#include "expressionparser.h"
#include "animalcode.h"
#include "numbers.h"
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

class CommissionBreak
{
public:
typedef enum buyermode
{
  CWT=0,
  Head=1,
  Flat=2,
  CompanyCWT=3,
  CompanyHead=4,
  CompanyFlat=5
}BuyerMode;

  CommissionBreak(long, string="0.0", double=0.0000, double=0.0000);
  void setId(long);
  void setExpression(string);
  void setBreakValue(double);
  void setMin(double);
  void setMax(double);

  double getMin();
  double getMax();

  long getId();
  string getExpression();
  double getBreakValue();
  double getNoSaleCharge();
  static string buyerCommissionExpression(double, BuyerMode);
  static CommissionBreak buyerBreak(BuyerMode, double);
private:
  long id;
  string expression;
  double breakValue;
  double noSaleCharge;
  double min;
  double max;
};

class Commission
{
public:
  typedef enum {ByTransaction=0, ByInvoice=1}   TYPE;
  typedef enum {AtWeight, AtHead, AtPrice, AtTotal} BREAK_TYPE;

  Commission(long=0, TYPE=ByInvoice, BREAK_TYPE=AtWeight, vector<CommissionBreak> = vector<CommissionBreak>(),double=0.0, double=9999999999.99, double=0.0000, string="");
  void setName(string);
  double calculate();
  double noSaleCommission();
  ~Commission();

  void resetValues();

  void setType(TYPE);
  TYPE getType();
  void setMin(double);
  void setMax(double);
  void setBreakType(BREAK_TYPE);
  void setNoSaleCharge(double);
  double getMin();
  double getMax();
  double getNoSaleCharge();
  
  //void addNoSaleHead(long);

  BREAK_TYPE getBreakType();

  long getId();
  void setId(long);

  void setBreakList(vector<CommissionBreak>);
  vector<CommissionBreak> getBreakList();

  bool operator==(Commission);
  void addValues(CommissionExpressionParser::VARIABLES);
  void addNoSaleValues(CommissionExpressionParser::VARIABLES);

  static Commission buyerCommission(CommissionBreak::BuyerMode, double);
  string getName();
private:
  long id;
  TYPE type;
  BREAK_TYPE breakType;
  double min;
  double max; 
  double noSaleCharge;
  CommissionExpressionParser calculator;
  CommissionExpressionParser::VARIABLES values;
  CommissionExpressionParser::VARIABLES noSaleValues;

  vector<CommissionBreak> breakList;
  string name;
/*
  double noSaleHead;
  double noSalePrice;
  double noSaleTotal;
  double noSaleWeight;
*/

};
#endif
