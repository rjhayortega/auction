
#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include "person.h"
#include "date.h"
#include <string>
#include <vector>
#include "tag.h"
#include <iostream>
#include <algorithm>
#include <ctype.h>

using namespace std;


class Customer : public Person
{
public:
  typedef enum{Seller=0, Buyer=1, Both = 10}Type; 

  bool isDigit(char) const;


  Customer(int=0, Name=Name(), Address=Address(), ContactList=ContactList(), 
           string="", string="", string="", string="",
           bool=false, bool=true, bool=false, string="", int rel= 0);
  string getNumber();
  bool operator<(const Customer&)const;
  bool operator<(const string&)const;

  void setNumber(string);
  string toString();
  bool operator==(string);
  bool operator==(Name);
  void setMadCowCertified(bool);
  void setBeefCouncil(bool);
  void setOnMailingList(bool);
  void setCompany(string);

  bool isMadCowCertified();
  bool isBeefCouncil();
  bool isOnMailingList();
  string getCompany();
  void setHead(long);
  long getHead();

  string getCustomerPartOfNumber();

  static bool compareCustomerNumbers(Customer, Customer);
  static bool compareCustomerNames(Customer, Customer);
  static bool compareCustomerNumbersLT(string, string);
  static bool compareNumbersLTEQ(string, string);
  static string customerPartOfNumber(string);
  static bool compareZipCodesLT(Customer, Customer);
  static bool sameCustomer(Customer, Customer);
  static bool comparePermanantCustomers(Customer, Customer);
  string formattedName();
  void setAltered(bool);
  bool isAltered();
  void setDocket(string);
  string getDocket();
  void setRelation(int rel);
  int getRelation();
  QString getPermNumber();
  void setPermNumber(QString permNum);
  QString getRelationString();


private:
 string number;
 bool madCowCertified;
 bool beefCouncil;
 bool onMailingList;
 string company;
 long head;
 bool altered;
 string docket;
 int m_relation;
 QString m_permNumber;  //Added to print disclaimer on invoice

};

class Buyer : public Customer
{
public:
  Buyer(int=0, Name=Name(), Address=Address(), ContactList=ContactList(), string="", string="", string="", string="", string="");
  Buyer(Customer);

  static bool sameBuyer(Buyer, Buyer);

private:
  string buyerNumber;

};

class Seller : public Customer
{
public:
  Seller(int=0, Name=Name(), Address=Address(), 
         ContactList=ContactList(), string="NOLOT", string="", 
         Date=Date(), long=0, string="", string="", 
         string="", vector<Tag> =vector<Tag>(), bool=true);

  Seller(Customer, long=0, vector<Tag> =vector<Tag>());
  string getMortgage();
  void setMortgage(string);
  vector<Tag> getTagList();
  void setTagList(vector<Tag>);
private:

  Date checkInDate;
  string sellerNumber;
  vector<Tag> tagList;
};


class PermanentCustomer : public Customer
{
public:
  PermanentCustomer(Name=Name(), Address=Address(), ContactList=ContactList());

private:

};
#endif
