#ifndef _LIEN_RECORD_H_
#define _LIEN_RECORD_H_
#include <string>

// TODO: Hide the data members

using namespace std;

class LienRecord
{
public:
  string docket;
  string id;
  string name;
  string address1;
  string address2;
  string city;
  string state;
  string zip;
  string mortgage;
  string county;

public:
  LienRecord(string docket="", string id="", string name="", string address1="", string address2="", string city="", string state="", string zip="", string county="")
  {
    this->docket = docket;
    this->id = id;
    this->name = name;
    this->address1 = address1;
    this->address2 = address2;
    this->city = city;
    this->state = state;
    this->zip = zip;
    this->county = county;
  }


  bool operator==(LienRecord record)
  {
    return record.docket == this->docket;
  }

  bool operator<(const LienRecord& record) const
  {
    return this->docket < record.docket;
  }

  string getName()
  {
    return name;
  }

  static bool compareLT(LienRecord a, LienRecord b)
  {
    if(a.name < b.name)
    {
      return true;
    }

    if(a.name == b.name)
    {
      return a.mortgage < b.mortgage;
    }

    return false;
  }

  static bool compareEQ(LienRecord a, LienRecord b)
  {
    return a.name == b.name && a.mortgage == b.mortgage;
  }

};
#endif
