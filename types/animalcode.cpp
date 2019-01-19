#include "animalcode.h"

#include <cstdio>
#include <cstdlib>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////////
//
// name: AnimalCode(short, short, short, string, string, string)
//
// purpose: Constructor
//
// calling params: short  type           - the sex code
//                        color          - the color code
//                        flaw           - the flaw code
//                 string typeDescrip    - the description of the sex code
//                        colorDescrip   - the description of the color code
//                        flawDescrip    - the description of the flaw code
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

AnimalCode::AnimalCode(short type, short color, short flaw, string typeDescrip, string colorDescrip, string flawDescrip, bool pair)
{
  this->type = type;
  this->flaw = flaw;
  this->color = color;
  setTypeDescrip(typeDescrip);
  setFlawDescrip(flawDescrip);
  setColorDescrip(colorDescrip);
  this->pair = pair;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setType(short)
//
// purpose: sets the value of the sex code for this animal code
//
// calling params: short type - the new value for the sex code
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void AnimalCode::setType(short type)
{
  this->type = type;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setColor(short)
//
// purpose: sets the value of the color code for the animal code
//
// calling params: short color - the new value for the color code
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void AnimalCode::setColor(short color)
{
  this->color = color;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setFlaw(short)
//
// purpose: sets the value of the flaw code for this animal code
//
// calling params: short flaw - the new value for the flaw code
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void AnimalCode::setFlaw(short)
{
  this->flaw = flaw;
}



///////////////////////////////////////////////////////////////////////////////
//
// name: setTypeDescrip(string)
//
// purpose: sets the textual description of the sex code
//
// calling params: string typeDescrip - the new description for the sex code
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void AnimalCode::setTypeDescrip(string descrip)
{
  typeDescrip = descrip;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setColorDescrip(string)
//
// purpose: sets the description of the color code
//
// calling params: string colorDescrip - the new value for the description of 
//                                       the color code
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void AnimalCode::setColorDescrip(string descrip)
{
  colorDescrip = descrip;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setFlawDescrip(string)
//
// purpose: sets the description for the flaw code for this animal code
//
// calling params: string flaw - the new description for the flaw code
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void AnimalCode::setFlawDescrip(string descrip)
{
  flawDescrip = descrip;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getType()
//
// purpose: retrieves the sex code for the animal code
//
// calling params: 
// 
// return params: short - the sex code of the animal code
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

short AnimalCode::getType()
{
  return type;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getColor()
//
// purpose: retrieves the color code of the animal code
//
// calling params: 
// 
// return params: short - the color code of the animal code
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

short AnimalCode::getColor()
{
  return color;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getFlaw()
//
// purpose: retrieves the flaw code of the animal code
//
// calling params: 
// 
// return params: short - the flaw code of the animal code
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

short AnimalCode::getFlaw()
{
  return flaw;
}

short AnimalCode::chargeFlaw()
{
  return (flaw < 10 ? flaw : 0);
}

///////////////////////////////////////////////////////////////////////////////
//
// name: getTypeDescrip()
//
// purpose: retrieves the textual description of the sex code of the animal 
//          code
//
// calling params: 
// 
// return params: string - the description of the sex code
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

string AnimalCode::getTypeDescrip()
{
  return typeDescrip;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getColorDescrip()
//
// purpose: retrieves the textual description of the color code of the animal
//          code
//
// calling params: 
// 
// return params: string - the desription of the color code
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

string AnimalCode::getColorDescrip()
{
  return colorDescrip;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getFlawDescrip()
//
// purpose: retrieves the textual description of the flaw code of the animal
//          code
//
// calling params: 
// 
// return params: string - the description of the flaw code 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

string AnimalCode::getFlawDescrip()
{
  return flawDescrip;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: operator!=(AnimalCode)
//
// purpose: compares 2 animal codes, returns true if the current object 
//          does not have the same color type and flaw codes
//
// calling params: 
// 
// return params: bool - AnimalCode != AnimalCode ==> true
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

bool AnimalCode::operator!=(AnimalCode comparator)
{
  return this->type != comparator.type && this->color != comparator.color && this->flaw != comparator.flaw;
}


//////////////////////////////////////////////
//
// bool operator==(AnimalCode)
//
// This determines if 2 animal codes will
// be equivelent as far as charges and 
// commissions are concerned
// keep this in mind if you decide you need 
// to alter this.
//
//////////////////////////////////////////////

bool AnimalCode::operator==(AnimalCode code)
{
  bool groupOk = false, flawOk = false;

  if((0 <= this->color && this->color < 70 && 0 <= code.color && code.color < 70)   ||
     (70 <= this->color && this->color < 80 && 70 <= code.color && code.color < 80) ||
     (80 <= this->color && this->color < 90 && 80 <= code.color && code.color < 90) ||
     (90 <= this->color && this->color < 100 && 90 <= code.color && code.color < 100))
  { groupOk = true; }

  if(this->flaw >= 10)
  {
    if(code.flaw == 0)
      flawOk = true;
  }
  else if(code.flaw >= 10)
  {
    if(this->flaw == 0)
      flawOk = true;
  }
  else if(this->flaw == code.flaw)
  { 
    flawOk = true;
  }
  else if(this->flaw >= 10 && code.flaw >= 10)
  {
    flawOk = true;
  }

  return (this->type == code.type && groupOk && flawOk);
}

bool AnimalCode::compareAnimalCodeEQ(AnimalCode a, AnimalCode b)
{
  return a.type == b.type && a.color == b.color && a.flaw == b.flaw;
}

string AnimalCode::toString()
{
  char buf[20];
  sprintf(buf, "%d%d%02d", color, type, flaw);
  return string(buf);
}

AnimalCode AnimalCode::fromString(string codeStr)
{
  short color, type, flaw;
  color = type = flaw = 0;

  if(codeStr.length() == 4)
  {
    color = atoi(codeStr.substr(0, 1).c_str());
    type = atoi(codeStr.substr(1, 1).c_str());
    flaw = atoi(codeStr.substr(2, 2).c_str());
  }
  else if(codeStr.length() == 5)
  {
    color = atoi(codeStr.substr(0, 2).c_str());
    type = atoi(codeStr.substr(2, 1).c_str());
    flaw = atoi(codeStr.substr(3, 2).c_str());
  }

  return AnimalCode(type, color, flaw);
}

///////////////////////////////////////////////////////////////////////////////
//
// name: getDescrip()
//
// purpose: retrieves a textual descripition of the AnimalCode object
//
// calling params: 
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

string AnimalCode::getDescrip()
{
  return  colorDescrip + "-" + typeDescrip + (flawDescrip.length() > 0 ? "-" :"") + flawDescrip;
}

bool AnimalCode::isPair()
{
  return pair;
}

void AnimalCode::setIsPair(bool pair)
{
  this->pair = pair;
}

AnimalCode::Group AnimalCode::group()
{
  if(0 <= color && color < 70)
  {
    return First;
  }
  else if(70 <= color && color < 80)
  {
    return Second;
  }
  else if(80 <= color && color < 90)
  {
    return Third;
  }
  else if(90 <= color && color < 100)
  {
    return Fourth;
  }
  
  return Invalid;
}

bool AnimalCode::compareGroup(AnimalCode code)
{
  return this->group() == code.group();
}

void AnimalCode::setDescrip(string descrip)
{
  int dashIndex = descrip.find_first_of("-");

  colorDescrip = typeDescrip = flawDescrip = "";

  if(dashIndex == string::npos)
  {
    colorDescrip = descrip;
  }
  else
  {
    colorDescrip = descrip.substr(0, dashIndex);

    if(dashIndex + 1 < descrip.length())
    {
      descrip = descrip.substr(dashIndex + 1);
    }
    else
    {
      descrip = "";
    }
  }

  dashIndex = descrip.find_first_of("-");

  if(dashIndex == string::npos)
  {
    typeDescrip = descrip;
  }
  else
  {
    typeDescrip = descrip.substr(0, dashIndex);

    if(dashIndex + 1 < descrip.length())
    {
      flawDescrip = descrip.substr(dashIndex + 1);
    }
  }
}

