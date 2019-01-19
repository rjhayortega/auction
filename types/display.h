
#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <string>
#include "../serialport.h"
#include <vector>

class Display
{
public:
  class Row
  {
  public:

    private:
        long address;
  };

  
  typedef enum 
    {
      Current,				// display 'current' transaction
      Previous				// display previous (last) trans
    } WhichTrans;


  
  typedef enum
  {
      Null 	  =  0, // null display type
      TD3000  =  1, // TD3000 serial port (auct disp)
      TD3200  =  2, // TD3200 serial port (auct disp)
      TD3000u =  3, // TD3000 usb port (auct disp)
      LT9900u =  4, // LT9900 usb port (auct disp)
      P07303  =  5, // Touch Dynamics pole display
      unused8 = 98, // unused
      unused9 = 99  // unused
  }Type;

private:
  long id;
  Type rtti;
  std::string name;
  SerialPort port;
  long numRows;
  WhichTrans which;

  vector<Row> rowList;

};
#endif
