
#include "timeclass.h"

#include <cstdio>
#include <cstdlib>

Time::Time(short hour, short minute, short second)
{
  this->hour = (hour > 23 ? 23 : hour);
  this->minute = (minute > 59 ? 59 : minute);
  this->second = (second > 59 ? 59 : second);
}

string Time::toString()
{
  char buf[20];
  sprintf(buf, "%02d:%02d:%02d", hour, minute, second);
  return buf;
}

Time Time::fromString(string timeString)
{
  string hourBuf, minuteBuf, secondBuf;
  short currentField = 0;

  for(unsigned int i = 0; i < timeString.length(); i++)
  {
    if(!isdigit(timeString[i]) && timeString[i] == ':')
    {
      currentField++;

      if(currentField > 2)
      {
	return Time();
      }
    }
    else if(isdigit(timeString[i]))
    {
      switch(currentField)
      {
      case 0:
	hourBuf += timeString[i];
	break;

      case 1:
	minuteBuf += timeString[i];
	break;

      case 2:
	secondBuf += timeString[i];
	break;
      default:
	return Time();
	break;
      }
    }
    else
    {
      return Time();
    }
  }
  short hour = atoi(hourBuf.c_str());
  short minute = atoi(minuteBuf.c_str());
  short second = atoi(secondBuf.c_str());

  return Time((hour > 23 ? 23 : hour), (minute > 59 ? 59 : minute),  (second > 59 ? 59 : second));
}

Time Time::currentTime()
{
  time_t currentTime;
  currentTime = time(&currentTime);

  struct tm *timeStruct;
  timeStruct = localtime(&currentTime);

  return Time(timeStruct->tm_hour, timeStruct->tm_min, timeStruct->tm_sec);
}

bool Time::operator==(Time that)
{
  return this->hour == that.hour && this->minute == that.minute && this->second == that.second;
}

double Time::hoursFrom(Time orig)
{
  long secondCount = (hour * 3600) + (minute * 60) + second;
  long origSecondCount = (orig.hour * 3600) + (orig.minute * 60) + orig.second;
  return double(secondCount - origSecondCount) / 3600;
}
