
#include "serialport.h"

SerialPort::SerialPort(string location, unsigned long baud, unsigned int dataBits, Parity parity, unsigned int stopBits)
{
  this->location = location;
  this->baud = baud;
  this->dataBits = dataBits;
  this->parity = parity;
  this->stopBits = stopBits;

  
  portDesc = -1;
  echoRecieved = false;
  echoSent = false;

  setReadWait(1, 0);


//  debug.open(stdout);
}


void SerialPort::operator=(SerialPort origin)
{
  this->location             = origin.location;
  this->baud                 = origin.baud;
  this->dataBits             = origin.dataBits;
  this->parity               = origin.parity;
  this->stopBits             = origin.stopBits;
  this->oldIos               = origin.oldIos;
  this->readWaitSeconds      = origin.readWaitSeconds;
  this->readWaitMicroSeconds = origin.readWaitMicroSeconds;
  this->echoRecieved         = origin.echoRecieved;
  this->echoSent             = origin.echoSent;
  this->portDesc             = origin.portDesc;
//  this->debug                = origin.debug;
}

SerialPort::~SerialPort()
{
  cout.unsetf(ios::hex);
  cout.unsetf(ios::showbase);
  cout.setf(ios::dec);
}

void SerialPort::setEchoRecieved(bool echoRecieved)
{
  this->echoRecieved = echoRecieved;
}

void SerialPort::setEchoSent(bool echoSent)
{
  this->echoSent = echoSent;
}

bool SerialPort::ready()
{
  if(/*portFile == NULL &&*/ portDesc == -1)
  {
    return false;
  }

  fd_set rfds;
  struct timeval tv;

  // setup for select(3) call
  FD_ZERO(&rfds);
  FD_SET(portDesc, &rfds);

  tv.tv_sec  = readWaitSeconds;
  tv.tv_usec = readWaitMicroSeconds;


  switch(select(portDesc + 1, &rfds, NULL, NULL, &tv))
  {
  case -1:	// error
	perror("select failed");
    // fall through (on purpose)

  case  0:	// nothing available
    return false;
    break;

  default:	// good to go - do nothing
    return true;
    break;
  }
}

void SerialPort::clear()
{
  tcflush(portDesc, TCIOFLUSH);
}


string SerialPort::receive(char stopChar, bool includeStop)
{
  char ch;
  char buf[2];
  string result = "";
  int count = 0;
  if(ready())
  {
    if(echoRecieved) cout << "Receiving: ";

    do
    {
      count = read(portDesc, buf, 1);
      ch = buf[0]; 

      if(echoRecieved)
      {
	cout.unsetf(ios::dec);
	cout.setf(ios::hex);
	cout.setf(ios::showbase);
	cout.setf(ios::uppercase);
        cout << "'" << ( ch < 20 ? string("CtrlChar") : string(1, ch)) << "' (" << int(ch) << "), ";
	cout.flush();
      }
      
      if(ch != stopChar)
      {
	result += ch;
      }

    }while(ch != stopChar);

    cout << endl;

    return result;
  }

  cerr << "error reading -- no data" << endl;
  return "";
}

string SerialPort::receive(long desiredLength)
{
  string result;
  char buf[255];
  int count = 0;
  char ch;

  if(ready())
  {
      while(result.length() < desiredLength)
      {
	count = read(portDesc, buf, (desiredLength < sizeof(buf) ? desiredLength : sizeof(buf)));
	buf[count] = '\0';
	result += buf;
      }

      for(unsigned int i = 0; i < result.length(); i++)
      {
	cout << result[i] << int(result[i]) << endl;
      }
  }
  else
  {
    cerr << "error reading -- no data" << endl;
    return string(result.length(), ' ');
  }

  return result;
}

void SerialPort::setReadWait(long seconds, long microSeconds)
{
  this->readWaitSeconds = seconds;
  this->readWaitMicroSeconds = microSeconds;
}

string SerialPort::receive(int length)
{
  return receive(long(length));
}

string SerialPort::receiveLine()
{
  char buf[255];
  buf[0] = '\0';
  string result;

  if(ready())
  {
    return receive('\n');
  }
  else
  {
    cerr << "error reading -- no data" << endl;
  }

  if(echoRecieved) 
  { 
      cout << buf;

  }

  return string(buf);
}

void SerialPort::send(string data)
{
  write(portDesc, data.c_str(), data.length());
  if(echoSent)
  {
    cout << "Sent: ";

    for(unsigned int i = 0; i < data.length(); i++)
    {
      cout << int((unsigned char)(data[i])) << " ";
    }
    cout << endl;
  }
}

// useful for sending if there is a chance a null
// terminator('\0') is part of the data that needs
// to be sent to the port
void SerialPort::send(char *data, int len)
{
    write(portDesc, data, len);

    if(echoSent) cout << "Sent: ";

    for(int i = 0; i < len && echoSent; i++)
    {
      cout << "'" << (data[i] < 20 ? string("CtrlChar") : string(1, data[i])) << "'(" << int(data[i]) << ") ";
    }

    if(echoSent) cout << endl;
}

void SerialPort::openPort()
{
  portDesc = open(location.c_str(), (O_RDWR | O_NOCTTY));

  // open file
  if(portDesc == -1)
  {
    perror(string("could not open port: " + location).c_str());
    return;
  }

  if(tcgetattr(portDesc, &oldIos) != 0)
  {
    closePort();
    perror(string("opening port: " +  location + "(tcgetattr)").c_str());
    return;
  }


  struct termios tempIos;
  tcgetattr(portDesc, &tempIos);
  tempIos.c_cflag = 0;
  tempIos.c_iflag = IGNPAR;
  tempIos.c_oflag = 0;
  tempIos.c_lflag = (0 & ~ECHO);
   tempIos.c_cc[VMIN]=1;
   tempIos.c_cc[VTIME]=0;

  tcflush(portDesc, TCIFLUSH);

  if(tcsetattr(portDesc, TCSANOW, &tempIos) != 0)
  {
    perror("Setting flow control\n");
    closePort();
    return;
  }

  if(!(setPortBaud() && setPortDataBits() && setPortParity() && setPortStopBits()))
  {
    perror(string("setting paramaters for port: " + location).c_str());
    closePort();
    return;
  }


//  portFile = fdopen(portDesc,"r+");

  // set unbuffered I/O -- to prevent confusion in reading
//  setvbuf(portFile, NULL, _IONBF, 0);

}

void SerialPort::closePort()
{
  if(portDesc != -1)
  {
//    tcsetattr(portDesc, TCSANOW, &oldIos);
    close(portDesc);
    portDesc = -1;
  }
}

bool SerialPort::setPortBaud()
{
  struct termios tempIos;

  if(tcgetattr(portDesc, &tempIos) != 0)
  {
    perror("setting baudrate\n");
    return false;
  }

  // set port input & output speeds as requested
  if(cfsetispeed(&tempIos, baudMask()) != 0 || cfsetospeed(&tempIos, baudMask()) != 0)
  {
    perror("set baudrate (cfset_speed)");
    return false;
  }


  tempIos.c_cflag |= (CREAD|CLOCAL);
  tempIos.c_cflag &= ~CRTSCTS;

  // disable canonical processing
  tempIos.c_lflag &= ~ICANON;

  // turn off output processing
  tempIos.c_oflag &= ~OPOST;


   // set ios to keep changes
   if(tcsetattr(portDesc, TCSANOW, &tempIos) != 0)
   {
     perror("set baudrate (tcsetattr)");
     return false;
   }

  return true;
}

bool SerialPort::setPortDataBits()
{
  struct termios tempIos;
  unsigned long mask;

  // check port open && fetch ios
  if(tcgetattr(portDesc, &tempIos) )
  {
    perror("setting databits (tcgetattr)");
    return false;
  }

  switch(dataBits)
  {
  case 5:
    mask = CS5;
    break;

  case 6:
    mask = CS6;
    break;

  case 7:
    mask = CS7;
    break;

  case 8:
    mask = CS8;
    break;

  default:
    cerr << "invalid character width" << endl;
    return false;
  }

  tempIos.c_cflag &= ~CSIZE; 
  tempIos.c_cflag |= mask;  

  if(tcsetattr(portDesc, TCSANOW, &tempIos) != 0)
  {
    perror("setting databits (tcsetattr)");
    return false;
  }

  return true;
}

bool SerialPort::setPortParity()
{
  struct termios tempIos;

  // retrieve current parameters
  if(tcgetattr(portDesc, &tempIos) )
  {
    perror("setting parity (tcgetattr)");
    return false;
  }

  switch(parity)
  {
  case Space: // 'space' parity - parity bit always clear
  case None: // no parity
  default:
    tempIos.c_cflag &= ~PARENB;	// clear parity enable bit
    tempIos.c_iflag &= ~INPCK;	// clear input parity checking
    break;

  case Even:
    tempIos.c_cflag &= ~PARODD;	// clear odd-parity-check-and-generate bit
    tempIos.c_cflag |= PARENB;	// set parity enable bit
    // tempIos.c_iflag |= INPCK;	// set input parity checking
    tempIos.c_iflag &= ~INPCK;	// clear input parity checking
    break;

  case Odd:
    tempIos.c_cflag |= PARODD;	// set odd-parity bit
    tempIos.c_cflag |= PARENB;	// parity enable
    // tios.c_iflag |= INPCK;	// enable input parity checking
    tempIos.c_iflag &= ~INPCK;	// clear input parity checking
    break;

  case Mark:		// 'mark' parity - parity bit always set
    //  figure out how to set mark parity
    break;
  }

  if(tcsetattr(portDesc, TCSANOW, &tempIos) != 0)
  {
    perror("set_parityb (tcsetattr)");
    return false;
  }
  return true;  
}

bool SerialPort::setPortStopBits()
{
  struct termios tempIos;

  // fetch port attributes
  if(tcgetattr(portDesc, &tempIos) )
  {
    perror("setting stop bits (tcgetattr failed?)");
    return false;
  }

  // set bitmask
  switch(stopBits)
  {
  case 1:
    tempIos.c_cflag &= ~CSTOPB;	// clear flag => 1 stop bit
    break;
  case 2:
    tempIos.c_cflag |= CSTOPB;	// set flag => 2 stop bits
    break;
  default:
    cerr << "set_stopbits: invalid value (" << stopBits << ")" << endl;
    return(-1);
    break;
  }

  // set port attrib
  if(tcsetattr(portDesc, TCSANOW, &tempIos) != 0)
  {
    perror("setting stopbits (tcsetattr)");
    return false;
  }
  return true;  
}

unsigned long SerialPort::baudMask()
{
  switch(baud)
  {
  default:
  case 0:
    return B0;
  case 50:
    return B50;
  case 75:
    return B75;
  case 110:
    return B110;
  case 134:
    return B134;
  case 150:
    return B150;
  case 200:
    return B200;
  case 300:
    return B300;
  case 600:
    return B600;
  case 1200:
    return B1200;    
  case 1800:
    return B1800;    
  case 2400:
    return B2400;    
  case 4800:
    return B4800;    
  case 9600:
    return B9600;    
  case 19200:
    return B19200;    
  case 38400:
    return B38400;
  case 57600:
    return B57600;
  case 115200:
    return B115200;
  case 230400:
    return B230400;
  }

  return B0;
}

SerialPort::Parity SerialPort::getParity(char parityChar)
{
  switch(parityChar)
  {
  case 'N':
  case 'n':
  default:
    return SerialPort::None;

  case 'O':
  case 'o':
    return SerialPort::Odd;

  case 'E':
  case 'e':
    return SerialPort::Even;

  case 'M':
  case 'm':
    return SerialPort::Mark;

  case 'S':
  case 's':
    return SerialPort::Space;
  }

  return SerialPort::None;
}
