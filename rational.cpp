#include "rational.h"
	
#include <cstdlib>


Rational::Rational(long _whole, long _num, long _den) : whole(_whole), num(_num), den(_den)
{
}

Rational::Rational(string str)
{
  *this = str;
}

double Rational::approx()
{
  if(den == 0)
  {
    cerr << *this << " is an undefined rational number" << endl;
    return 0.00000001;
  }

  return whole + double(num / den);
}

void Rational::setWholePart(long _whole)
{
  whole = _whole;
}

void Rational::setNumerator(long _num)
{
  num = _num;
}

void Rational::setDenominator(long _den)
{
  den = _den;
}

long Rational::wholePart()
{
  return whole;
}

long Rational::numerator()
{
  return num;
}

long Rational::denominator()
{
  return den;
}

Rational Rational::simplify()
{
  Rational temp = *this;
  temp.whole += temp.num / temp.den;
  temp.num = temp.num % temp.den;
  return temp;
}

Rational Rational::desimplify()
{
  Rational temp = *this;
  temp.whole *= temp.den;
  temp.num += temp.whole;
  temp.whole = 0;

  return temp;
}

Rational Rational::inverse()
{
  Rational value = *this;
  value.desimplify();
  long temp = value.den;
  value.den = value.num;
  value.num = temp;
  value.simplify();
  return value;
}

void Rational::reQuantify(Rational* a, Rational* b)
{
  if(a != NULL &&  b != NULL)
  { 
    if(a->den != b->den)
    {
      a->num = a->num * b->den;
      b->num = b->num * a->den;
      a->num = b->num = a->num * b->num;
    }
  }
}

Rational Rational::operator+(Rational b)
{
  Rational a = *this;
  a.whole += b.whole;
  reQuantify(&a, &b);

  a.num += b.num;
  return a;
}

Rational Rational::operator+=(Rational a)
{
  *this = *this + a;
  return *this;
}

Rational Rational::operator-(Rational b)
{
  Rational a = *this;
  a.whole -= b.whole;
  reQuantify(&a, &b);

  a.num -= b.num;
  return a;
}

Rational Rational::operator-=(Rational a)
{
  *this = *this - a;
  return *this;
}

Rational Rational::operator*(Rational b)
{
  Rational a = *this;
  a = a.desimplify();
  b = b.desimplify();

  a.den *= b.den;
  a.num *= b.num;

  simplify();
  return a;
}

Rational Rational::operator*=(Rational a)
{
  *this = *this * a;
   return *this;
}

Rational Rational::operator/(Rational b)
{
  Rational a = *this;
  a = a.desimplify();
  b = b.desimplify();
  a *= b.inverse();
  a.simplify();
  return a;
}

Rational Rational::operator/=(Rational a)
{
  *this = *this / a;
  return *this;
}

bool Rational::operator==(Rational b)
{
  Rational a = *this;

  a = a.desimplify();
  b = b.desimplify();

  reQuantify(&a, &b);

  return a.num ==  b.num;
}

bool Rational::operator<(Rational a)
{
  Rational temp = *this;

  temp = temp.desimplify();
  a = a.desimplify();

  reQuantify(&temp, &a);

  return temp.num < a.num;
}

bool Rational::operator<=(Rational b)
{
  return *this < b || *this == b;
}

bool Rational::operator>(Rational b)
{
  Rational a = *this;

  a = a.desimplify();
  b = b.desimplify();

  reQuantify(&a, &b);

  return a.num > b.num;
}

bool Rational::operator>=(Rational b)
{
  return *this > b || *this == b;
}


ostream& operator<<(ostream& stream, Rational& rational)
{
  stringstream wholePart;
  stringstream fractionPart;

  if(rational.whole != 0)
  {
    wholePart << rational.whole << " ";
  }

  if(rational.den == 0)
  {
    fractionPart << "undef";
  }
  else if(rational.num != 0)
  {
    fractionPart << rational.num << " / " << rational.den;
  }

  stream << wholePart.str() << fractionPart.str();

  return stream;
}

Rational Rational::operator=(string rationalStr)
{
  string wholeStr;
  string numStr;
  string denStr;

  string* dest = &wholeStr;
  denStr = "1";

  for(unsigned int i = 0; i < rationalStr.length(); i++)
  {
    switch(rationalStr[i])
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
      if(dest != NULL)
      {
        *dest += rationalStr[i];
      }
      break;

    case ' ':
      if(dest == &wholeStr)
      {
        dest = &numStr;
      }
      else
      {
        dest = NULL;
      }
      break;

    case '/':
      if(dest == &denStr)
      {
        return *this; // too many slashes
      }
      else if(dest == &numStr)
      {
        denStr = "";
        dest = &denStr;
      }
      else if(dest == &wholeStr)
      {
        denStr = "";
        numStr = wholeStr;
        wholeStr = "";
        dest = &denStr;
      }
      break;
    }
  }

  setWholePart(atol(wholeStr.c_str()));
  setNumerator(atol(numStr.c_str()));
  setDenominator(atol(denStr.c_str()));
  return *this;
}
