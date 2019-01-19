
#ifndef _SERIAL_PORT_H_
#define _SERIAL_PORT_H_

#include <iostream>
#include <string>

#include <unistd.h>
#include <termios.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/select.h>
#include <fstream>

using namespace std;

class SerialPort
{
public:
typedef enum
{
  None=0,
  Odd=1,
  Even=2,
  Mark=3,
  Space=4
}Parity;

SerialPort(string="/dev/ttyS0", unsigned long=9600, unsigned int=8, Parity=None, unsigned int=1);
~SerialPort();
void openPort();
void closePort();

bool ready();
void clear();
void send(string);
void send(char*, int);

string receive(char, bool=true);
string receive(long);
string receive(int);
string receiveLine();

void setReadWait(long, long);
void setEchoRecieved(bool);
void setEchoSent(bool);
void operator=(SerialPort);
static Parity getParity(char);
private:
  string location;
  unsigned long baud;
  unsigned int dataBits;
  Parity parity;
  unsigned int stopBits;

  struct termios oldIos;

  long readWaitSeconds;
  long readWaitMicroSeconds;

  bool setPortBaud();
  bool setPortDataBits();
  bool setPortParity();
  bool setPortStopBits();

  bool echoRecieved;
  bool echoSent;

  unsigned long baudMask();
  int portDesc;
//  FILE *portFile;
//  ofstream debug;
};

#endif
