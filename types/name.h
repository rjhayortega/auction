
#ifndef _NAME_H_
#define _NAME_H_

#include <string>
using namespace std;

class Name
{
public:
  Name(string="", string="", string="", string="");

  void setFirst(string);
  void setLast(string);
  void setMiddle(string);
  void setSalutation(string);


  string getFirst();
  string getLast();
  string getMiddle();
  string getSalutation();

  string formal();
  string business();
  string informal_long();
  string informal_midsize();
  string informal_short();
  string storeString();

  bool operator==(Name);
  static Name fromString(string);
  void setInitials(string);
  string getInitials();
  static string autoInitials(string);
private:
  string first;
  string last;
  string middle;
  string salutation;
  string initials;
};
#endif
