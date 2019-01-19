

#include "date.h"
#include <cstdio>
#include <cmath>

Date::Date(int day, int month, int year)
{
  this->day = day;
  this->month = month;
  this->year = year;
}

short Date::getDay()
{
  return day;
}

short Date::getMonth()
{
  return month;
}

short Date::getYear()
{
  return year;
}

Date Date::fromString(string date, string format)
{
  char year_buf[5], day_buf[3], month_buf[3];
  int year_digit = 0, day_digit = 0, month_digit = 0;

  for(unsigned int i = 0; i < format.length(); i++)
  {
    if(i >= date.length())
    {
      return Date();
    }

    if(format[i] == 'y' || format[i] == 'Y' && year_digit < 4)
    {
      year_buf[year_digit] = date[i];
      year_digit++;
    }

    if(format[i] == 'm' && month_digit < 2)
    {
      month_buf[month_digit] = date[i];
      month_digit++;
    }

    if(format[i] == 'd' && day_digit < 2)
    {
      day_buf[day_digit] = date[i];
      day_digit++;
    }
  }

  year_buf[year_digit] = '\0';
  month_buf[month_digit] = '\0';
  day_buf[day_digit] = '\0';

  sscanf(day_buf, "%d", &day_digit);
  sscanf(month_buf, "%d", &month_digit);
  sscanf(year_buf, "%d", &year_digit);

  return Date(day_digit, month_digit, year_digit);
}



string Date::toString(string format)
{
  string temp;

  char year_buf[5], day_buf[3], month_buf[3];
  int year_digit = 0, day_digit = 0, month_digit = 0;

  sprintf(year_buf, "%.4d", year);
  sprintf(month_buf, "%.2d", month);
  sprintf(day_buf, "%.2d", day);


  for(unsigned int i = 0; i < format.length(); i++)
  {
    if(format[i] == 'y' || format[i] == 'Y' && year_digit < 4)
    {
      temp += year_buf[year_digit];
      year_digit++;
    }
    else if(format[i] == 'm' && month_digit < 2)
    {
      temp += month_buf[month_digit];
      month_digit++;
    }
    else if(format[i] == 'd' && day_digit < 2)
    {
      temp += day_buf[day_digit];
      day_digit++;
    }
    else
    {
      temp += format[i];
    }

  }

  return temp;
}


Date Date::currentDate()
{
  time_t cur_time;
  cur_time = time(&cur_time);
  tm *loc_time = localtime(&cur_time);

  return Date(loc_time->tm_mday, loc_time->tm_mon + 1, 1900 + loc_time->tm_year);
}

bool Date::operator==(Date comp)
{
  return (this->day == comp.day && this->month == comp.month && this->year == comp.year);
}

double Date::hoursFrom(Date orig)
{
 
  return (daysFrom(orig) * 24);
}

long Date::daysFrom(Date orig)
{
  long dayCount = 0;

  for(unsigned int i = 0; i < year - orig.year + 1; i++)
  {
    if(i == 0)
    {
      dayCount += orig.daysRemainingInYear();
    }
    else if(i == year - orig.year)
    {
      dayCount += dayOfYear();
    }
    else
    {
      dayCount += Date(0,0, orig.year + i).daysRemainingInYear();
    }
  }

  if(year == orig.year)
  {
    dayCount = dayOfYear() - orig.dayOfYear();
  }

  return dayCount;
}
long Date::daysRemainingInYear()
{
  return (isLeapYear() ? 366 : 365) - dayOfYear();
}

long Date::dayOfYear()
{
  long dayCount = 0;

  switch(month)
  {
  case 12:
    dayCount += 30;
  case 11:
    dayCount += 31;
  case 10:
    dayCount += 30;
  case 9:
    dayCount += 31;
  case 8:
    dayCount += 31;
  case 7:
    dayCount += 30;
  case 6:
    dayCount += 31;
  case 5:
    dayCount += 30;
  case 4:
    dayCount += 31;
  case 3:
    dayCount += (isLeapYear() ? 29 : 28);
  case 2:
    dayCount += 31;
  case 1:
    dayCount += 0;
  };

  return dayCount + day;
}

bool Date::isLeapYear()
{
  if(year % 4 == 0)
  {
    if(year % 100 == 0)
    {
      if(year % 400 == 0)
      {
	return true;
      }
    }
    else
    {
      return true;
    }
  }
  return false;
}

bool Date::operator<(Date that)
{
  if(this->year < that.year)
  {
    return true;
  }
  else if(this->year == that.year)
  {
    if(this->month < that.month)
    {
      return true;
    }
    else if(this->month == that.month && this->day < that.day)
    {
      return true;
    }
  }

  return false;
}


Date::WeekDay Date::dayOfWeek()
{
  // First sunday in 1980
  Date baseDate(6,1,1980);

  int offset = daysFrom(baseDate) % 7;

  cout << daysFrom(baseDate) << endl;

  cout << month << "/" << day << "/" << year << endl;
  return WeekDay(Sunday + offset);
}

string Date::dayOfWeekStr()
{
  switch(dayOfWeek())
  {
  case Sunday:
  default:
    return "Sun";

  case Monday:
    return "Mon";

  case Tuesday:
    return "Tue";

  case Wednesday:
    return "Wed";

  case Thursday:
    return "Thur";

  case Friday:
    return "Fri";

  case Saturday:
    return "Sat";
  }

  return "";
}

void Date::addDays(int daysToAdd)
{
  bool increase = (daysToAdd >= 0);

  daysToAdd = abs(daysToAdd);

  if(increase)
  {
    while(daysToAdd > daysRemainingInYear())
    {
      daysToAdd -= daysRemainingInYear();
      month = 1;
      day = 1;
      year++;
    }

    while(daysToAdd > daysRemainingInMonth())
    {
      day = 1; 
      month ++;
      daysToAdd -= daysRemainingInMonth();
    }

    day += daysToAdd;
  }
  else 
  {
    subtractDays(daysToAdd);
  }
}

void Date::subtractDays(int daysToSub)
{
  bool decrease = (daysToSub >= 0);
  daysToSub = abs(daysToSub);

  if(decrease)
  {
    while(daysToSub > dayOfYear())
    {
      daysToSub -= dayOfYear();
      day = 31;
      month = 12;
      year--;
    }


    while(daysToSub > monthLength())
    {
      daysToSub -= monthLength();
      month--;
      day = monthLength();
    }
    
    day -= daysToSub;
  }
  else
  {
    addDays(daysToSub);
  }
}

int Date::monthLength()
{
  switch(month)
  {
  default:
    return 31;
    break;

  case 4:
  case 6:
  case 9:
  case 11:
    return 30;
    break;

  case 2:
    if(isLeapYear())
    {
      return 29;
    }
    else
    {
      return 28;
    }
    break;
  }

  return 0;
}

int Date::daysRemainingInMonth()
{
  return monthLength() - day;
}
