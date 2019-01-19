
#ifndef _TAG_H_
#define _TAG_H_

#include <iostream>
#include <string>
#include <vector>

#include "brand.h"
#include "date.h"
#include "animalcode.h"

using namespace std;
class Tag
{
public:
  Tag(string="", string="", long=0, AnimalCode=AnimalCode(), string="",
      string="HO", char='F', int=0, string="", string="", string="", 
      Date=Date(), string="", string="",long=0, bool=false,
	string="", Date=Date());
		// extended last 2 fields 2/1/10

  void setTag(string);
  void setSellerId(string);
  void setTransactionId(long);
  void setAnimalCode(AnimalCode);
  void setBurcellosisTag(string);
  void setBrand(vector<Brand>);
  void setId(long);
  void setDeleted(bool);

  vector<Brand> getBrand();
  string getTag();
  string getSellerId();
  long getTransactionId();
  AnimalCode getAnimalCode();
  string getBurcellosisTag();
  bool operator==(string);
  static bool compareTagsLT(Tag, Tag);
  long digitPart();
  static vector<string> tagRange(string, string);

  string getBreed();
  char getSex();
  int getAge();
  string getVaccination();
  string getBrucellosis();
  string getMonthsPreg();
  Date getTestDate();
  string getOldTag();
  string getComment();
  long getId();
  bool isDeleted();
  string getRfid();		// new 2/1/10
  Date getTbInjDate();		// new 2/1/10

  void setBreed(string);
  void setSex(char);
  void setAge(int);
  void setVaccination(string);
  void setBrucellosis(string);
  void setMonthsPreg(string);
  void setTestDate(Date);
  void setOldTag(string);
  void setComment(string);
  static void mergeBrands(vector<Tag>&, vector<Brand>&);
  void setRfid(string);		// new 2/1/10
  void setTbInjDate(Date);	// new 2/1/10

private:
  string tag;
  string sellerId;
  long transactionId;
  AnimalCode code;
  string burcellosisTag;
  vector<Brand> brand;

  string breed;
  char sex;
  int age;
  string vaccination;
  string brucellosis;
  string monthsPreg;
  Date testDate;
  string oldTag;
  string comment;
  long id;
  bool deleted;
  string rfid;		// new 2/1/10
  Date tbInjDate;	// new 2/1/10
};
#endif
