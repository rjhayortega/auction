
#ifndef _DISPLAY_DAO_H_
#define _DISPLAY_DAO_H_

#include "databasemanager.h"

class DisplayDAO 
{
public:
  class Display
    {
    };
  vector<Display> getDisplayList();
private:
  vector<Display> getDisplayByCondition();
  vector<Display> getDisplayListByCondition(string);
}
#endif
