
#ifndef _ANIMAL_CODE_H_
#define _ANIMAL_CODE_H_

/******************************************************************************
-
- class AnimalCode
-
- purpose: Encapsulates an animal code
- 
- Notes: an animal code is a 3 part code that the auction markets use to
-        identify the types of animals. the 3 parts are the sex code,
-        the color code and the flaw code.
- 
- Todo:
-
*****************************************************************************/

#include <string>
using namespace std;

class AnimalCode
{

public:
  typedef enum {First, Second, Third, Fourth, Invalid}Group;

  AnimalCode(short=0,short=0,short=0, string="", string="", string="", bool=false);
  void setType(short);
  void setColor(short);
  void setFlaw(short);

  void setTypeDescrip(string);
  void setColorDescrip(string);
  void setFlawDescrip(string);

  void setDescrip(string);

  short getType();
  short getColor();
  short getFlaw();
  short chargeFlaw();

  string getTypeDescrip();
  string getColorDescrip();
  string getFlawDescrip();

  bool operator!=(AnimalCode);
  bool operator ==(AnimalCode);
  string getDescrip();
  bool isPair();
  void setIsPair(bool);
  bool compareGroup(AnimalCode);
  Group group();
  static AnimalCode fromString(string);
  static bool compareAnimalCodeEQ(AnimalCode, AnimalCode);

  string toString();
private:
  short type;
  short color;
  short flaw;

  string typeDescrip;
  string colorDescrip;
  string flawDescrip;
  bool pair;
};
#endif
