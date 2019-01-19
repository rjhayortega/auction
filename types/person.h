
#ifndef _PERSON_H_
#define _PERSON_H_

#include <string>
using namespace std;

#include "address.h"
#include "contactlist.h"
#include "name.h"

class Person
{
public:
  Person(int=0, Name=Name(), Address=Address(), ContactList=ContactList(), string="", string="", string="");

  void setId(int);
  void setName(Name);
  void setAddress(Address);
  void setContactList(ContactList);
  void setSocialSecurityNumber(string);
  void setCreditCardNumber(string);
  void setComment(string);

  int getId();
  Name getName();
  Address getAddress();
  ContactList getContactList();
  string getSocialSecurityNumber();
  string getCreditCardNumber();
  string getComment();
private:
  int id;
  Name name;
  Address address;
  ContactList contactList;
  string ssn;
  string comment;
  string creditCardNumber;
};
#endif
