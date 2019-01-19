
#ifndef _ADDRESS_H_
#define _ADDRESS_H_

/******************************************************************************
-
- class Address
-
- purpose: Encapsulates an address
- 
- Notes:
- 
- Todo:
-
*****************************************************************************/

#include <string>
using namespace std;

class Address
{
public:
  Address(string="",string="", string="", string="", string="", string="", string="");

  void setAddress1(string);
  void setAddress2(string);
  void setCity(string);
  void setState(string);
  void setZip(string);
  void setUnit(string);
  void setCounty(string);

  string getAddress1();
  string getAddress2();
  string getCity();
  string getState();
  string getZip();
  string getUnit();
  string getCounty();

  string cityStateZipStr();
private:
  string address1;
  string address2;
  string city;
  string state;
  string zip;
  string unit;
  string county;
};


#endif
