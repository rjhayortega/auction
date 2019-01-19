
#include "datetime.h"

DateTime::DateTime(Date date, Time time)
{
  this->date = date;
  this->time = time;
}

string DateTime::toString(string dateFormat)
{
  return date.toString(dateFormat) + " " + time.toString();
}


DateTime DateTime::fromString(string dateTime, string dateFormat)
{
  int splitPos = dateTime.find_first_of(' ');

  if(splitPos == string::npos)
  {
    return DateTime();
  }

  string dateString = dateTime.substr(0, splitPos);
  string timeString = (dateTime.length() > splitPos + 1 ? dateTime.substr(splitPos + 1) : "");
  return DateTime(Date::fromString(dateString, dateFormat), Time::fromString(timeString));
}

double DateTime::hoursFrom(DateTime orig)
{
  return date.hoursFrom(orig.date) + time.hoursFrom(orig.time);
}

DateTime DateTime::currentDateTime()
{
  return DateTime(Date::currentDate(), Time::currentTime());
}

bool DateTime::operator==(DateTime that)
{
  return this->date == that.date && this->time == that.time;
}
