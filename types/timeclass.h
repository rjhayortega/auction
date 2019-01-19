#ifndef _TIME_CLASS_H_
#define _TIME_CLASS_H_

#include <time.h>
#include <string>
#include <iostream>

using namespace std;

class Time
{
public:
  Time(short=0, short=0, short=0);
  string toString();
  static Time fromString(string);
  static Time currentTime();
  bool operator==(Time);
  double hoursFrom(Time);
private:
  short hour;
  short minute;
  short second;
};

#endif
