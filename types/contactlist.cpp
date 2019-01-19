
#include "contactlist.h"
///////////////////////////////////////////////////////////////////////////////
//
// name: ContactList(string="", string="", string="", string="")
//
// purpose: Constructor
//
// calling params: string firstPhone  - the first phone number of the contact
//                 string secondPhone - the second phone number of the contact
//                 string fax         - the contact's fax number
//                 string email       - the contact's email
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

ContactList::ContactList(string firstPhone, string secondPhone, string fax, string email)
{
  setFirstPhone(firstPhone);
  setSecondPhone(secondPhone);
  setFax(fax);
  setEmail(email);
}

///////////////////////////////////////////////////////////////////////////////
//
// name: setFirstPhone(string)
//
// purpose: sets the first phone number of the contact
//
// calling params: string - the first phone number of the contact
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void ContactList::setFirstPhone(string firstPhone)
{
  this->firstPhone = phoneToString(firstPhone);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: void setSecondPhone(string)
//
// purpose: sets the second phone number of the contact
//
// calling params: string secondPhone - the second phone number of the contact
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void ContactList::setSecondPhone(string secondPhone)
{
  this->secondPhone = phoneToString(secondPhone);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setFax(string)
//
// purpose: sets the fax number of the contact
//
// calling params: string fax - the fax number of the contact
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void ContactList::setFax(string fax)
{
  this->fax = phoneToString(fax);
}

///////////////////////////////////////////////////////////////////////////////
//
// name: setEmail(string)
//
// purpose: sets the email address of the contact
//
// calling params: string email - the email address of the contact
// 
// return params: 
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void ContactList::setEmail(string email)
{
  this->email = email;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getFirstPhone()
//
// purpose: retrieves the first phone number of the contact
//
// calling params: 
// 
// return params: string - the first phone number of the contact
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

string ContactList::getFirstPhone()
{
  return stringToPhone(firstPhone);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getSecondPhone()
//
// purpose: retrieves the second phone number of the contact
//
// calling params: 
// 
// return params: string - the second phone number of the contact
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

string ContactList::getSecondPhone()
{
  return stringToPhone(secondPhone);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getFax()
//
// purpose: retrieves the fax number of the contact
//
// calling params: 
// 
// return params: string - the fax number of the contact
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

string ContactList::getFax()
{
  return stringToPhone(fax);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getEmail()
//
// purpose: retrieves the email address of the contact
//
// calling params: 
// 
// return params: string - the email address of the contact
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

string ContactList::getEmail()
{
  return email;
}

string ContactList::stringToPhone(string phoneString)
{
  int group = 0;
  int groupSize = 4;

  string groupBuf;
  string phoneBuf;

  for(int i = phoneString.length() - 1; i >= 0; i--)
  {
    groupBuf = phoneString[i] + groupBuf;

    if(groupBuf.length() == groupSize || i == 0)
    {
      switch(group)
      {
      case 2:
	phoneBuf = " (" + groupBuf + ") " + phoneBuf;
	break;

      default:
	phoneBuf = groupBuf + (phoneBuf.length() > 0 ? "-" : "") + phoneBuf;
      }

      groupBuf = "";
      groupSize = 3;
      group++;
    }
  }

  return phoneBuf;
}

string ContactList::phoneToString(string phoneString)
{
  string phoneBuf;

  for(unsigned int i = 0; i < phoneString.size(); i++)
  {
    if(isdigit(phoneString[i]))
    {
      phoneBuf += phoneString[i];
    }
  }
  return phoneBuf;
}

string ContactList::firstPhoneToString()
{
  return phoneToString( firstPhone );
}

