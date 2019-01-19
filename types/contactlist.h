#ifndef _CONTACT_LIST_H_
#define _CONTACT_LIST_H_
/******************************************************************************
-
- class ContactList
-
- purpose: A list of contacts
- 
- Notes: Have not used this at all. May discard it before projects end 
-        If for some reason this stays in, may want to modify it to maike it morre
-        scalable
- Todo: 
-
*****************************************************************************/
#include <string>
#include <ctype.h>

using namespace std;

class ContactList
{

public:
  ContactList(string="", string="", string="", string="");


  void setFirstPhone(string);
  void setSecondPhone(string);
  void setFax(string);
  void setEmail(string);

  string getFirstPhone();
  string getSecondPhone();
  string getFax();
  string getEmail();
  string firstPhoneToString();


private:
  string stringToPhone(string);
  string phoneToString(string);

  string firstPhone;
  string secondPhone;
  string fax;
  string email;

};
#endif
