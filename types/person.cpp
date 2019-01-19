
#include "person.h"

Person::Person(int id, Name name, Address address, ContactList contactList, string ssn, string cardNumber, string comment)
{
  setId(id);
  setName(name);
  setAddress(address);
  setContactList(contactList);
  setSocialSecurityNumber(ssn);
  setCreditCardNumber(cardNumber);
  setComment(comment);
}

void Person::setId(int id)
{
  this->id = id;
}

void Person::setName(Name name)
{
  this->name = name;
}


void Person::setAddress(Address address)
{
  this->address = address;
}

void Person::setContactList(ContactList contactList)
{
  this->contactList = contactList;
}

void Person::setSocialSecurityNumber(string ssn)
{
  this->ssn = ssn;
}

void Person::setCreditCardNumber(string cardNumber)
{
  this->creditCardNumber = cardNumber;
}

void Person::setComment(string comment)
{
  this->comment = comment;
}

int Person::getId()
{
  return id;
}

Name Person::getName()
{
  return name;
}

Address Person::getAddress()
{
  return address;
}

ContactList Person::getContactList()
{
  return contactList;
}

string Person::getSocialSecurityNumber()
{
  return ssn;
}

string Person::getCreditCardNumber()
{
  return creditCardNumber;
}

string Person::getComment()
{
  return comment;
}
