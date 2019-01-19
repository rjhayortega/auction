
#include "expressionparser.h"

#include <cstdlib>

// Expression Grammar that is the basis of the design for this class
//
//     1.  <start>           -> <expression> eof
//     2.  <expression>      -> <term> <expression_tail>
//     3.  <expression_tail> -> + <term> <expression_tail>
//     4.  <expression_tail> -> - <term> <expression_tail>
//     5.  <expression_tail> -> l
//     6.  <term>            -> <factor> <term_tail>
//     7.  <term_tail>       -> * <factor> <term_tail>
//     8.  <term_tail>       -> / <factor> <term_tail>
//     9.  <term_tail>       -> l
//     10. <factor>          -> <primary> <factor_tail>
//     11. <factor_tail>     -> ^ <primary> <factor_tail>
//     12. <factor_tail>     -> l
//     13. <primary>         -> identifier
//     14. <primary>         -> integer_literal
//     15. <primary>         -> ( <expression> )

ExpressionParser::ExpressionParser()
{
  showParse = false;
}

ExpressionParser::~ExpressionParser()
{
}

void ExpressionParser::setShowParse(bool show)
{
  showParse = show;
}


// this is misnamed a little bit, its true name should be double evaluate(string, bool*) , but
// it does parse the expression in order to evaluate it, so this isn't too bad. If a user simply
// wishes to see if an expression will parse, he should set the values of the VARIABLES variable(values) to all 1's 
// (to prevent a division by 0 error from keeping a valid expression from parsing) and call this with a pointer to 
// bool as the second argument, which when de-referenced will contain the truth of the question 
// "Does this expression parse?"

double ExpressionParser::parse(string expression, bool *parsedOk)
{
  this->ok = parsedOk;
  bool okLocal = false;
  if(ok == NULL)
  {
    okLocal = true;
    this->ok = new bool;
  }

  if(showParse)
  {
    cout << "begin parse" << endl;
  }

  if(ok != NULL)
  {
    *ok = true;
  }

  if(!tokenize(expression))
  {
    if(ok != NULL)
    {
      *ok = false;
    }

    return 0.0;
  }

  if(showParse)
  {
    cout << "Token List " << endl;

    for(currentToken = tokenList.begin(); currentToken != tokenList.end(); currentToken++)
    {
      cout << *currentToken << endl;
    }
    currentToken = tokenList.begin();
  }

  if(tokenList.size() == 0)
  {
    return 0.00;
  }

  endOfExpression = false;
  parseExpression();

  double value = mathStack.top();
  mathStack.pop();

  if(!mathStack.empty())
  {
    cerr << "Error parsing expression";

    if(ok != NULL)
    {
      *ok = false;
    }
  }

  if(!(*ok))
  {
    value = 0.00;
  }

  if(okLocal)
  {
    delete ok;
  }

  return value;
}


bool ExpressionParser::tokenize(string expression)
{
  if(showParse) { cout << "Tokenizing" << endl;}

  string currentDouble = "";
  int dotCount = 0;
  bool nextTokenMustBeDigit = true;
  tokenList.clear();

  for(unsigned int i = 0; i < expression.length(); i++)
  {
    if(1)
    {
      switch(expression[i])
      {
      case '*':
	tokenList.push_back(string("*"));
	break;

      case '+':
	tokenList.push_back(string("+"));
	break;

      case '-':
	tokenList.push_back(string("-"));
	break;

      case '/':
	tokenList.push_back(string("/"));
	break;

      case '^':
	tokenList.push_back(string("^"));
	break;




      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '.':
	currentDouble += expression[i];
	dotCount += (expression[i] == '.' ? 1 : 0);

	if(dotCount > 1)
	{
	  cerr << "Error tokenizing expression, too many dots in a double literal" << endl;
	}

	if(i + 1 == expression.length() || !isDigit(expression[i + 1]))
	{
	  tokenList.push_back(currentDouble);
	  dotCount = 0;
	  currentDouble = "";
	}

        break;


      case '(':
	tokenList.push_back("(");
	break;

      case ')':
	tokenList.push_back(")");
	break;

      case ' ':     // ignore white space
      case '\n':
      case '\r':
	break;

      default:  // allow derived classes to define their own tokens
        if(!tokenizeVariable(expression[i])) 
	{
	   cerr << "Unknown token found in expression" << endl;
	   return false;
	}
      }
    }
  }

  currentToken = tokenList.begin();
  return true;
}


void ExpressionParser::parseExpression()
{
  if(showParse) {cout << "Parsing expression" << endl;}
  parseTerm();
  parseExpressionTail();
}


void ExpressionParser::parseExpressionTail()
{
  if(showParse)
  {  cout << "Parsing expression tail, current token: " << *currentToken << endl; }

  if(*currentToken == "+" || *currentToken == "-")
  {
    bool isPlus = *currentToken == "+";

    updateLookahead();

    if(endOfExpression)
    {
      *ok = false;
      cerr << "parse error" << endl;
      return;
    }

    parseTerm();
    parseExpressionTail();


    if(mathStack.size() < 2 || !(*ok))
    {
      *ok = false;
      return;
    }

    double right = mathStack.top();
    mathStack.pop();
    double left = mathStack.top();
    mathStack.pop();

    (isPlus ? mathStack.push(left + right) : mathStack.push(left - right));
  }
}


void ExpressionParser::parseTerm()
{
  if(showParse) { cout << "Parsing term" << endl;}
  parseFactor();
  parseTermTail();
}


void ExpressionParser::parseTermTail()
{
  if(showParse) { cout << "Parsing term tail, token is: " << *currentToken << endl; }

  if(*currentToken == "*" || *currentToken == "/")
  {
    bool isMul = *currentToken == "*";

    updateLookahead();

    if(endOfExpression)
    {
      *ok = false; 
      cerr << "Parse error" << endl;
      return;
    }

    parseFactor();
    parseTermTail();


    if(mathStack.size() < 2 || !(*ok))
    {
      *ok = false;
      return;
    }

    double right = mathStack.top();
    mathStack.pop();
    double left = mathStack.top();
    mathStack.pop();

    if(right == 0.0 && !isMul)
    {
      cerr << "warning expression attempted division by 0, result will not be accurate" << endl;
      mathStack.push(0.00000001);
    }
    else
    {
      (isMul ? mathStack.push(left * right) : mathStack.push(left / right));
    }
  }
}

void ExpressionParser::parseFactor()
{
  if(showParse) { cout << "Parsing factor" << endl; }
  parsePrimary();
  parseFactorTail();
}


void ExpressionParser::parseFactorTail()
{
  if(showParse) { cout << "Parsing factor tail, token is: " << *currentToken << endl; }

  if(*currentToken == "^")
  {
    updateLookahead();
    if(endOfExpression)
    {
      *ok = false;
      return;
    }

    parsePrimary();
    parseFactorTail();

    if(mathStack.size() < 2 || !(*ok))
    {
      *ok = false;
      return;
    }

    double right = mathStack.top();
    mathStack.pop();
    double left = mathStack.top();
    mathStack.pop();

    mathStack.push(pow(left, right));
  }
}


void ExpressionParser::parsePrimary()
{
  if(showParse) { cout << "Parsing primary, token is: " << *currentToken << endl; }

  switch((*currentToken)[0])
  {
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  case '.':
    if(showParse) { cout << "Double literal, pushing: " << atof(currentToken->c_str()) << " onto the stack"; }
    mathStack.push(atof(currentToken->c_str()));
    updateLookahead();
    break;

  case '(':
    updateLookahead();
    parseExpression();

    if(!((*currentToken)[0] == ')'))
    {
      cerr << "Mismatched parentheses" << endl;
    }
    updateLookahead();
    break;

  default:
    if(parseVariable(*currentToken))
    {
      updateLookahead();
    }
    else
    {
      cerr << "error -- unexpected token in expression - check the expression: " << " for errors" << endl;
      *ok = false;
      return;
    }
    break;
  }
}


bool ExpressionParser::isDigit(char exprElem)
{
  switch(exprElem)
  {
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  case '.':
    return true;
    break;
  } 

  return false;
}


void ExpressionParser::updateLookahead()
{
  if(!endOfExpression)
  {
    currentToken++;
  }

  if(currentToken == tokenList.end())
  {
    endOfExpression = true;
    currentToken--;
  }
}

bool ExpressionParser::showsParse()
{
  return showParse;
}

void ExpressionParser::appendTokenList(string token)
{
  tokenList.push_back(token);
}

bool ExpressionParser::tokenizeVariable(char tokenChar)
{
  cerr << "unkown variable: " << tokenChar << endl;
  return false;
}

bool ExpressionParser::parseVariable(string token)
{
  cerr << "unknown token: " << token << endl;
  return false;
}

void ExpressionParser::appendStack(double val)
{
  mathStack.push(val);
}

CommissionExpressionParser::CommissionExpressionParser() : ExpressionParser()
{
  values.total = 0; 
  values.head = 0; 
  values.price = 0;
  values.weight = 0;
}

CommissionExpressionParser::CommissionExpressionParser(VARIABLES vars) : ExpressionParser()
{
  setValues(vars);
}

CommissionExpressionParser::~CommissionExpressionParser()
{}

void CommissionExpressionParser::setValues(VARIABLES vals)
{
  values.total = vals.total;
  values.head = vals.head;
  values.price = vals.price;
  values.weight = vals.weight;
}


bool CommissionExpressionParser::tokenizeVariable(char tokenChar)
{
  switch(tokenChar)
  {
  case 'H':  // token represents the head variable
  case 'h':
    appendTokenList(string("H"));
    break;

  case 'P':  // token represents the price variable
  case 'p':
    appendTokenList(string("P"));
    break;

  case 'T': // token represents the transaction total variable
  case 't':
    appendTokenList(string("T"));
    break;

  case 'W': // token represents total weight 
  case 'w':
    appendTokenList(string("W"));
    break;

  default:
    return false;
    break;
  }

  return true;
}


bool CommissionExpressionParser::parseVariable(string token)
{
  switch(token[0])
  {
  case 'T':
    appendStack(values.total);
    break;

  case 'H':
    appendStack(values.head);
    break;

  case 'P':
    appendStack(values.price);
    break;

  case 'W':
    appendStack(values.weight);
    break;

  default:
    return false;
    break;
  }

  return true;
}



ChargeExpressionParser::ChargeExpressionParser() : ExpressionParser()
{
  values.head = 0;
  values.weight = 0;
  values.totalDollars = 0.0;
}

ChargeExpressionParser::ChargeExpressionParser(VARIABLES vals) : ExpressionParser()
{
  setValues(vals);
}

ChargeExpressionParser::~ChargeExpressionParser()
{}

void ChargeExpressionParser::setValues(VARIABLES vals)
{
  values.head = vals.head;
  values.weight = vals.weight;
  values.totalDollars = vals.totalDollars;
}

void ChargeExpressionParser::addValues(VARIABLES* dest, VARIABLES src)
{
  dest->head += src.head;
  dest->weight += src.weight;
  dest->totalDollars += src.totalDollars;
}

bool ChargeExpressionParser::tokenizeVariable(char lexeme)
{
  switch(lexeme)
  {
  case 'H':
  case 'h':
    appendTokenList("H");
    break;

  case 'W':
  case 'w':
    appendTokenList("W");
    break;

  case 'T':
  case 't':
    appendTokenList("T");
    break;

  default:
    return false;
    break;
  }

  return true;
}


bool ChargeExpressionParser::parseVariable(string token)
{
  switch(token[0])
  {
  case 'H':
    if(showsParse()) { cout << "Head variable, pushing: " << values.head << " on the stack" << endl; }
    appendStack(values.head);
    break;

  case 'W':
    if(showsParse()) { cout << "Weight variable, pushing: " << values.weight << " on the stack" << endl; }
    appendStack(values.weight);
    break;

  case 'T':
    appendStack(values.totalDollars);
    if(showsParse()) { cout << "Total variable, pushing: " << values.totalDollars << " on the stack" << endl; }
    break;

  default:
    return false;
    break;
  }

  return true;
}
