
#include "customer.h"

#include <cstdio>

Customer::Customer(int id, Name name, Address address, ContactList contactList,
                   string number, string social, string creditCard, string comment,
                   bool madCowCertified, bool beefCouncil, bool onMailingList, string company, int rel) :
  Person  (id, name, address, contactList, social, creditCard, comment)
{
  setNumber(number);
  setMadCowCertified(madCowCertified);
  setBeefCouncil(beefCouncil);
  setOnMailingList(onMailingList);
  setCompany(company);
  altered = false;
  docket = "";
  m_relation = rel;
}

void Customer::setAltered(bool altered)
{
  this->altered = altered;
}

void Customer::setDocket(string docket)
{
  this->docket = docket;
}

string Customer::getDocket()
{
  return docket;
}

bool Customer::isAltered()
{
  return altered;
}
void Customer::setRelation(int rel)
{
    m_relation = rel;
}
int Customer::getRelation()
{
    return m_relation;
}

string Customer::formattedName()
{
  string nameStr = getName().getLast();
  int slashIndex = nameStr.find_first_of("/");

  if(slashIndex != string::npos)
  {
    string firstPart = nameStr.substr(0, slashIndex);
    string lastPart;

    if(slashIndex + 1 < nameStr.length())
    {
      lastPart = nameStr.substr(slashIndex + 1);
    }
    nameStr = lastPart + " " + firstPart;
  }

  return nameStr;
}

bool Customer::comparePermanantCustomers(Customer a, Customer b)
{
  if(a.getName().getLast() == b.getName().getLast())
  {
    return (a.getCompany() < b.getCompany());
  }
 
  return a.getName().getLast() < b.getName().getLast();
}

string Customer::getNumber()
{
  return number;

}

bool Customer::compareCustomerNumbers(Customer left, Customer right)
{
  return Customer::compareCustomerNumbersLT(left.getNumber(), right.getNumber());
}

bool Customer::compareCustomerNames(Customer left, Customer right)
{
  return left.getName().getLast() < right.getName().getLast();
}

bool Customer::compareCustomerNumbersLT(string left, string right)
{
  if(atol(left.c_str()) == atol(right.c_str()))
  {
    int leftStart = left.find_first_of("/-");
    int rightStart = right.find_first_of("/-");

    if(leftStart != string::npos && leftStart + 1 < left.length())
    {
      left = left.substr(leftStart + 1);
    }
    else
    {
      left = "-1";
    }

    if(rightStart != string::npos && rightStart + 1 < right.length())
    {
      right = right.substr(rightStart + 1);
    }
    else
    {
      right = "-1";
    }
  }

//   if(left.length() > 0 && !isdigit(left[0]) && right.length() > 0 && !isdigit(right[0]))
//   {
//     return left < right;
//   }

  return atol(left.c_str()) < atol(right.c_str());
}

bool Customer::compareNumbersLTEQ(string left, string right)
{
  return atol(left.c_str()) <= atol(right.c_str());
}

string Customer::customerPartOfNumber(string number)
{
  long customerPart = atol(number.c_str());
  char buf[20];
  sprintf(buf, "%ld", customerPart);

  return string(buf);
}

void Customer::setNumber(string number)
{
  string realNumber = number;

  // strip trailing and leading whitespace
  int index = realNumber.find_first_not_of(" ");

  if(index != string::npos)
  {
    realNumber = realNumber.substr(index);
  }
  else
  {
    return;
  }

  index = realNumber.find_first_of(" ");

  realNumber = realNumber.substr(0, index);

  if(realNumber.length() < 1)
  {
    realNumber = "NOLOT";
  }

  this->number = realNumber;
}

void Customer::setMadCowCertified(bool mcc)
{
  madCowCertified = mcc;
}

void Customer::setBeefCouncil(bool bc)
{
  beefCouncil = bc;
}

void Customer::setOnMailingList(bool ml)
{
  onMailingList = ml;
}

void Customer::setCompany(string company)
{
  this->company = company;
}

string Customer::toString()
{
  return getName().getLast();
}

bool Customer::operator<(const Customer& cust)const
{
  return this->number < cust.number;
}

bool Customer::operator<(const string& custNum)const
{
  return this->number < custNum;
}

bool Customer::operator==(string custNumber)
{
  return this->number == custNumber;
}

bool Customer::operator==(Name custName)
{
  return getName() == custName;
}

bool Customer::isMadCowCertified()
{
  return madCowCertified;
}

bool Customer::isBeefCouncil()
{
  return beefCouncil;
}

bool Customer::isOnMailingList()
{
  return onMailingList;
}

bool Customer::compareZipCodesLT(Customer a, Customer b)
{
  return atol(a.getAddress().getZip().c_str()) < atol(b.getAddress().getZip().c_str());
}

string Customer::getCompany()
{
  return company;
}

Buyer::Buyer(int id, Name name, Address address, ContactList contactList,
             string number, string company, string social, string creditCard, string comment) :
  Customer(id, name, address, contactList, number, social, creditCard, comment, false, false, false, company)
{

}

Buyer::Buyer(Customer customer) : Customer(customer)
{
//  this->company = company;
}

// string Buyer::getCompany()
// {
//   return company;
// }


Seller::Seller(int id, Name name, Address address, ContactList contactList, 
               string number, string mortgage, Date checkInDate, long head,
               string social, string creditCard, string comment, vector<Tag> tagList, bool beefCouncil) : 
  Customer(id, name, address, contactList, number, social, creditCard, comment, false, beefCouncil, false, mortgage)
{
  setHead(head);
  this->checkInDate = checkInDate;
  this->tagList = tagList;
//  this->mortgage = mortgage;
}

Seller::Seller(Customer customer, long head, vector<Tag> tagList) : Customer(customer)
{
  setHead(head);
  this->tagList = tagList;
  //this->mortgage = mortgage;
}

void Seller::setTagList(vector<Tag> tagList)
{
  this->tagList = tagList;
}

void Seller::setMortgage(string mortgage)
{
  setCompany(mortgage);
}

vector<Tag> Seller::getTagList()
{
  return tagList;
}

long Customer::getHead()
{
  return head;
}

string Customer::getCustomerPartOfNumber()
{
  return Customer::customerPartOfNumber(number);
}

void Customer::setHead(long head)
{
  this->head = head;
}

string Seller::getMortgage()
{
  return getCompany();
}

bool Buyer::sameBuyer(Buyer a, Buyer b)
{
  string aNum = a.getNumber();
  string bNum = b.getNumber();
  string aBuf = "", bBuf = "";

  for(unsigned int i = 0; i < aNum.length() && isdigit(aNum[i]); i++)
  {
    aBuf += aNum[i];
  }

  for(unsigned int i = 0; i < bNum.length() && isdigit(bNum[i]); i++)
  {
    bBuf += bNum[i];
  }

  return atoi(aBuf.c_str()) == atoi(bBuf.c_str());
}

bool Customer::sameCustomer(Customer a, Customer b)
{
  return (a.getName() == b.getName() &&
          a.getAddress().getAddress1() == b.getAddress().getAddress1() &&
          a.getAddress().getAddress2() == b.getAddress().getAddress2() &&
          a.getAddress().cityStateZipStr() == b.getAddress().cityStateZipStr());
}


QString Customer::getPermNumber()
{
    return m_permNumber;

}
void Customer::setPermNumber(QString permNum)
{
    m_permNumber = permNum;
}

QString Customer::getRelationString()
{
    QString result = "";
    switch (m_relation){
    case 1:
        result = "Owner";
        break;
    case 2:
        result = "Officer";
        break;
    case 3:
        result = "Agent";
        break;
    case 4:
        result = "Employee";
        break;
    }
    return result;
}
