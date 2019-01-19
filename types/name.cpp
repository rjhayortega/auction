#include "name.h"

#include <iostream>

using namespace std;

Name::Name(string last, string first, string middle, string salutation)
{
  setFirst(first);
  setLast(last);
  setMiddle(middle);
  setSalutation(salutation);
}

void Name::setInitials(string _initials)
{
  this->initials = _initials;
}

string Name::getInitials()
{
  return initials;
}

void Name::setFirst(string name)
{
  this->first = name;
}

void Name::setLast(string name)
{
  this->last = name;
}

void Name::setMiddle(string name)
{
  this->middle = name;
}

void Name::setSalutation(string salutation)
{
  this->salutation = salutation;
}


string Name::getFirst()
{
  return first;
}

string Name::getLast()
{
  return last;
}

string Name::getMiddle()
{
  return middle;
}

string Name::getSalutation()
{
  return salutation;
}

string Name::formal()
{
  return salutation + " " + first + " " + middle + " " +  last;
}


string Name::business()
{
  return last + ", " + first + " " + middle;
}


string Name::informal_long()
{
  return first + " " + middle + " " + last;
}


string Name::informal_midsize()
{
  return first + " " + last;
}

string Name::informal_short()
{
  return first;
}


bool Name::operator==(Name name)
{
  return (first == name.getFirst() && last == name.getLast() && middle == name.getMiddle());
}

string Name::storeString()
{
  return last + "/" + first;
}

Name Name::fromString(string nameString)
{
  string first="", last="";
  int splitIndex = nameString.find_first_of('/');

  if(splitIndex == string::npos)
  {
    splitIndex = nameString.find_first_of(' ');

    if(splitIndex == string::npos)
    {
      last = nameString;
    }
    else 
    {
      first = nameString.substr(0, splitIndex);
      if(splitIndex + 1 < nameString.length())
      {  last = nameString.substr(splitIndex + 1);}
    }
  }
  else
  {
      last = nameString.substr(0, splitIndex);
      if(splitIndex + 1 < nameString.length())
      { first = nameString.substr(splitIndex + 1); } // [KLN] added the "+ 1"
  }

  return Name(last, first);
}

string Name::autoInitials(string nameStr)
{
  string ai;

  if(nameStr.size() > 0)
  {
    ai += nameStr[0];

    int spacePos = 0;

    do
    {
      spacePos = nameStr.find_first_of(" ", spacePos + 1);

      if(spacePos != string::npos && spacePos + 1 < nameStr.length())
      {
	ai += nameStr[spacePos + 1];
      }

    }while(spacePos != string::npos);
  }

  return ai;
}
