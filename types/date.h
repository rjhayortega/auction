

#ifndef _DATE_H_
#define _DATE_H_

#include "time.h"
#include <string>
#include <iostream>

using namespace std;

class Date
{
public:  typedef enum {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday} WeekDay;

  Date(int=0,int=0,int=0);
  short getDay();
  short getMonth();
  short getYear();

  void addDays(int);
  void subtractDays(int);
  static Date fromString(string, string);
  static Date currentDate();
  string toString(string="m-d-y");
  bool operator==(Date);
  double hoursFrom(Date);
  long dayOfYear();
  long daysFrom(Date);
  long daysRemainingInYear();
  int daysRemainingInMonth();
  bool isLeapYear();
  bool operator<(Date);

  WeekDay dayOfWeek();
  string dayOfWeekStr();


private:

  int monthLength();

  int day;
  int month;
  int year;

};
#endif
