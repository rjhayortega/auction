#ifndef _DATE_TIME_H_
#define _DATE_TIME_H_

#include "date.h"
#include "timeclass.h"

class DateTime 
{
public:
  DateTime(Date=Date(), Time=Time());
  static DateTime fromString(string, string="YYYY-mm-dd");
  static DateTime currentDateTime();
  string toString(string dateFormat);
  bool operator==(DateTime);
  double hoursFrom(DateTime);

private:
  Date date;
  Time time;
};
#endif
