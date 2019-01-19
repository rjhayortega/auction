
#include "timer.h"


Timer::Timer()
{
  gettimeofday(&creationTime, NULL);
  previousTime = currentTime = creationTime;
}


unsigned long Timer::usecInterval()
{
  gettimeofday(&currentTime, NULL);
  unsigned long val = (unsigned long)(currentTime.tv_sec * 1000000 + currentTime.tv_usec) - (unsigned long)(previousTime.tv_sec * 1000000 + previousTime.tv_usec);
  previousTime = currentTime;
  return val;
}


unsigned long Timer::interval()
{
  gettimeofday(&currentTime, NULL);
  unsigned long val = currentTime.tv_sec - previousTime.tv_sec;
  previousTime = currentTime;
  return val;
}
