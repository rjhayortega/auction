#ifndef _RATIONAL_H_
#define _RATIONAL_H_

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Rational
{
public:
  Rational(long=0, long=0, long=1);
  Rational(string);
  double approx();

  void setWholePart(long);
  void setNumerator(long);
  void setDenominator(long);

  long wholePart();
  long numerator();
  long denominator();

  Rational simplify();
  Rational desimplify();
  Rational inverse();

  Rational operator+(Rational);
  Rational operator+=(Rational);
  Rational operator-(Rational);
  Rational operator-=(Rational);
  Rational operator*(Rational);
  Rational operator*=(Rational);
  Rational operator/(Rational);
  Rational operator/=(Rational);
  bool operator<(Rational);
  bool operator<=(Rational);
  bool operator>(Rational);
  bool operator>=(Rational);
  bool operator==(Rational);
  Rational operator=(string);

  friend ostream& operator<<(ostream&, Rational&);

  static void reQuantify(Rational*, Rational*);
private:
  long whole;
  long num;
  long den;
};
#endif
