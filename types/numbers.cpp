
#include "numbers.h"
#include <iostream>
using namespace std;

// JAL->NTS:
//     what the hell was I thinking. this is ugly
//     it works good for now, but when I have time
//     lets incorparate a little OOP into the design
//     of this module

double getDollarAmount(double amount)
{
  double dollars;
  double cents = modf(amount, &dollars);
  cents = cents * 100;
  
  double error = modf(cents, &cents);

  if(error < -0.00000001)
  {
    cents -= (error > -0.499999 ? 0.00000001 : 1.00000001);
  }
  else 
  {
    cents += (error < .499999 ? 0.00000001 : 1.00000001);
  }

  return dollars + (cents / 100);
}

long getWeightAmount(double weight)
{
  double result;
  double error = modf(weight, &result);
  result += (error < .499999 ? 0.00000001 : 1.00000001);
  return long(result) ;
}
