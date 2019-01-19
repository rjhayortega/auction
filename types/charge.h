
#ifndef _CHARGE_H_
#define _CHARGE_H_
/******************************************************************************
-
- class Charge
-
- purpose: Encapsulates a charge
- 
- Notes: a charge in the auction program is an extra cost that is associated 
         with a transaction. 
- 
- Todo: Add multiplier functionality
-
*****************************************************************************/

#include "expressionparser.h"
#include <string>
#include "numbers.h"
#include <vector>

using namespace std;

class ChargeBreak 
{
public:
  typedef enum {None, Head, Weight, Total}Type;

  ChargeBreak(long _id=0, double _amount=0.00000001, string _expression="") : id(_id), amount(_amount), expression(_expression) {}

  void setId(long _id) { id=_id;}
  void setAmount(double _amount) {amount=_amount;}
  void setExpression(string _expression) {expression=_expression;}

  long getId() {return id;}
  double getAmount() {return amount;}
  string getExpression() {return expression;}
  static bool compareAmountLT(ChargeBreak a, ChargeBreak b) { return a.amount < b.amount; }
private:
  long id;
  double amount;
  string expression;
};

class ChargeAdjustment
{
public:
  ChargeAdjustment(double=0.00001, double=0.00001, bool=false, long=0);
  double getMultiplier();
  double getAdjustment();
  bool needsMultiplier();

  void setMultiplier(double _mul) { multiplier=_mul; }
  void setAdjustment(double _adj) { adjustment=_adj; } 
  void setMultiplierNeed(bool);
  long getChargeId();
  void setChargeId(long);

private:
  long chargeId;
  double multiplier;
  double adjustment;
  bool needMultiplier;
};

class Charge
{
public:
typedef enum chargeMode
{
  Normal,
  NoSale,
  ReSale
}CHARGE_MODE;
  typedef enum{Transaction, Invoice}Scope;

  Charge(long=0, string="UNDEF", string="0", bool=false, bool=false, bool=false, bool=false, bool=false, bool=false);
  double calculate(ChargeExpressionParser::VARIABLES, CHARGE_MODE=Normal, bool=false, string* =NULL);

  double calculate();

  void setId(long);
  void setDescrip(string);
  void setExpression(string);
  void setChargesOnNoSale(bool);
  void setChargesOnReSale(bool);
  void setDoublesOnPairs(bool);
  void setMultiplierNeed(bool);
  void setAdjustment(ChargeAdjustment);
  bool operator==(Charge);

  long getId();
  string getDescrip();
  string getExpression();
  bool chargesOnNoSale();
  bool chargesOnReSale();
  bool doublesOnPairs();
  bool needsMultiplier();
  bool isCommissionCharge();
  ChargeAdjustment getAdjustment();
  static bool compareIdsLT(Charge, Charge);
  bool isBeefCouncil();
  vector<ChargeBreak> getBreakList();
  ChargeBreak::Type getBreakType();
  void setBreakList(vector<ChargeBreak>);
  void setBreakType(ChargeBreak::Type);
  void setScope(Scope);
  Scope getScope();
  void resetValues();
  void addValues(ChargeExpressionParser::VARIABLES, CHARGE_MODE, bool, bool);

  static bool compareIdsEQ(Charge a, Charge b) { return a.id == b.id; }


private:
  long id;
  string descrip;
  string expression;
  bool chargeOnNoSale;
  bool chargeOnReSale;
  bool doubleOnPairs;
  bool needMultiplier;
  ChargeAdjustment adjustment;
  static ChargeExpressionParser calculator;
  bool commissionCharge;
  bool beefCouncil;
  vector<ChargeBreak> breakList;
  ChargeBreak::Type breakType;
  Scope scope;

  ChargeExpressionParser::VARIABLES values;
  ChargeExpressionParser::VARIABLES pairValues;
  ChargeExpressionParser::VARIABLES nosaleValues;
  ChargeExpressionParser::VARIABLES nosalePairValues;
  ChargeExpressionParser::VARIABLES resaleValues;
  ChargeExpressionParser::VARIABLES resalePairValues;
  ChargeExpressionParser::VARIABLES swapValues;
  ChargeExpressionParser::VARIABLES swapPairValues;
};
#endif
