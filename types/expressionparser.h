
#ifndef _EXPRESSION_PARSER_H_
#define _EXPRESSION_PARSER_H_

#include <list>
#include <stack>
#include <string>
#include <iostream>
#include <math.h>
using namespace std;

class ExpressionParser
{
public:
  ExpressionParser();
  virtual ~ExpressionParser();
  double parse(string, bool* = NULL);
  void setShowParse(bool);


protected:
  virtual bool tokenizeVariable(char);
  virtual bool parseVariable(string);
  void appendTokenList(string token);
  void appendStack(double value);
  void updateLookahead();
  bool showsParse();
private:
  bool *ok;
  bool showParse;
  bool endOfExpression;

  list<string> tokenList;
  list<string>::iterator currentToken;

  stack<double> mathStack;

  bool tokenize(string);

  void parseExpression();
  void parseExpressionTail();
  void parseTerm();
  void parseTermTail();
  void parseFactor();
  void parseFactorTail();
  void parsePrimary();

  bool isDigit(char);

};

class CommissionExpressionParser : public ExpressionParser
{
public:
  typedef struct
  {
    double total;
    double head;
    double price;
    double weight;
  }VARIABLES;


  CommissionExpressionParser();
  CommissionExpressionParser(VARIABLES);
  virtual ~CommissionExpressionParser();
  void setValues(VARIABLES);

protected:
  virtual bool tokenizeVariable(char);
  virtual bool parseVariable(string);
private:
  VARIABLES values;
};

class ChargeExpressionParser : public ExpressionParser
{
public:
  typedef struct variables
  {
    double head;
    double weight;
    double totalDollars;
  }VARIABLES;

  ChargeExpressionParser();
  ChargeExpressionParser(VARIABLES);
  virtual ~ChargeExpressionParser();
  void setValues(VARIABLES);
  static void addValues(VARIABLES*, VARIABLES);
protected:
  virtual bool tokenizeVariable(char);
  virtual bool parseVariable(string);

private:
  VARIABLES values;

};
#endif
