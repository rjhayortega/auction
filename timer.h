#ifndef _TIMER_H_
#define _TIMER_H_

#include <time.h>
#include <sys/time.h>

class Timer
{
public:
  Timer();

  unsigned long interval();
  unsigned long usecInterval();

private:
  struct timeval creationTime;
  struct timeval previousTime;
  struct timeval  currentTime;
};

#endif
