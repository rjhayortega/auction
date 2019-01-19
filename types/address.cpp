#include "address.h"

///////////////////////////////////////////////////////////////////////////////
//
// name: Address(string, string, string, string, string, string)
//
// purpose: Constructor
//
// calling params: string address1 - the first address line
//                        address2 - the second address line
//                        city     - the city where the address is
//                        state    - the state of the address
//                        zip      - the zip code of the address
//                        unit     - the apartment number or unit
// 
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

Address::Address(string address1, string address2, string city, string state, string zip, string unit, string county)
{
  setAddress1(address1);
  setAddress2(address2);
  setCity(city);
  setState(state);
  setZip(zip);
  setUnit(unit);
  setCounty(county);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setAddress1(string)
//
// purpose: sets the first address line
//
// calling params: string address1 - the value to set the first address line to
// 
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void Address::setAddress1(string address1)
{
  this->address1 = address1;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setAddress2(string)
//
// purpose: sets the second address line
//
// calling params: string address2 - the value to set the second address line 
//                                   to
// 
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void Address::setAddress2(string address2)
{
  this->address2 = address2;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setCity(string)
//
// purpose: sets the value of the city string
//
// calling params: string city - the value to set the city string to
// 
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void Address::setCity(string city)
{
  this->city = city;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setState(string)
//
// purpose: sets the value of the state variable
//
// calling params: string state - the value to set the state string of the 
//                                object to
// 
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void Address::setState(string state)
{
  this->state = state;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setZip(string)
//
// purpose: sets the value of the zip data member
//
// calling params: string zip - the value to set the zip string of the object
// 
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void Address::setZip(string zip)
{
  this->zip = zip;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setUnit(string)
//
// purpose: sets the value of the unit data member of the object
//
// calling params: string unit - the value to set the unit data member to
// 
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void Address::setUnit(string unit)
{
  this->unit = unit;
}

void Address::setCounty(string county)
{
  this->county = county;
}

///////////////////////////////////////////////////////////////////////////////
//
// name: getAddress1()
//
// purpose: retrieves the first address line
//
// calling params: 
// 
// return params: string - the first address line of the address
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

string Address::getAddress1()
{
  return address1;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getAddress2()
//
// purpose: retrieves the second address line of the address
//
// calling params: 
// 
// return params: string - the second address line
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

string Address::getAddress2()
{
  return address2;
}

///////////////////////////////////////////////////////////////////////////////
//
// name: getCity()
//
// purpose: retrieves the city portion of the address
//
// calling params: 
// 
// return params: string - the city portion of the address
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

string Address::getCity()
{
  return city;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getState()
//
// purpose: retrieves the state portion of the address
//
// calling params: 
// 
// return params: string - the state portion of the address
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

string Address::getState()
{
  return state;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getZip()
//
// purpose: retrieves the zip code of the address
//
// calling params: 
//  
// return params: string - the zip code of the address
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

string Address::getZip()
{
  return zip;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getUnit()
//
// purpose: retrieves the unit number of the address
//
// calling params: 
// 
// return params: string - the unit number of the address
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

string Address::getUnit()
{
  return unit;
}

string Address::getCounty()
{
  return county;
}

///////////////////////////////////////////////////////////////////////////////
//
// name: cityStateZipStr()
//
// purpose: retrieves a formatted string of the city state and zip
//
// calling params: 
// 
// return params: string - the city state and zip in a nice format
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

string Address::cityStateZipStr()
{
  string temp = city + ", " + state + " " + zip;

  if(temp == ",  ")
  {
    temp = "";
  }

  return temp;
}
