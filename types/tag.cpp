#include "tag.h"

#include <cstring>
#include <cstdlib>
#include <cstdio>

Tag::Tag(string tag, string seller, long transactionId, 
         AnimalCode code, string burcellosisTag, string breed, 
         char sex, int age, string vaccination, 
         string brucellosis, string monthsPreg, Date testDate, 
         string oldTag, string comment, long id, bool deleted,
	string rfid, Date tbInjDate)
{
  this->tag = tag;
  this->sellerId = seller;
  this->transactionId = transactionId;
  this->code = code;
  this->burcellosisTag = burcellosisTag;

  this->breed = breed;
  this->sex = sex;
  this->age = age;
  this->vaccination = vaccination;
  this->brucellosis = brucellosis;
  this->monthsPreg = monthsPreg;
  this->testDate = testDate;
  this->oldTag = oldTag;
  this->comment = comment;
  this->id = id;
  this->deleted = deleted;
  this->rfid = rfid;
  this->tbInjDate = tbInjDate;
}

void Tag::setSellerId(string sellerId)
{
  this->sellerId = sellerId;
}

void Tag::setTransactionId(long transId)
{
  this->transactionId = transId;
}

vector<Brand> Tag::getBrand()
{
  return brand;
}

void Tag::setTag(string tag)
{
  this->tag = tag;
}

void Tag::setAnimalCode(AnimalCode code)
{
  this->code = code;
}

void Tag::setBurcellosisTag(string bTag)
{
  this->burcellosisTag = bTag;

  for(unsigned int i = 0; i < brand.size(); i++)
  {
    brand[i].setBurcellosisTag(bTag);
  }
}

void Tag::setBrand(vector<Brand> brand)
{
  this->brand = brand;

  for(unsigned int i = 0; i < brand.size(); i++)
  {
    this->brand[i].setBurcellosisTag(burcellosisTag);
  }
}

// For the tags in tagVector, for each brand in brandVector, if the
// tags match in both tag and brand, then add the brand to a vector
// of brands, and at end of matching set the tag's brand(Vector)
// to the accumulated matching brands.
void Tag::mergeBrands(vector<Tag>& tagVector, vector<Brand>& brandVector)
{
  //cout << "    Tag::mergeBrands ..." << endl;

  for(unsigned i = 0; i < tagVector.size(); i++)
  {
    vector<Brand> tempBrandVector;	// brands to attach to tag object
    //cout << "    for tagVector " << i << endl;
    if(tagVector[i].getTag().length() <= 0 )	continue;

    string nakedtag = "";
    string slashtag = "";

    if ( tagVector[i].getTag()[0] == '/' )	{
      nakedtag = tagVector[i].getTag().substr(1);
      slashtag = tagVector[i].getTag();
      } else {
      nakedtag = tagVector[i].getTag();
      slashtag = "/" + tagVector[i].getTag();
      }

    for ( unsigned b = 0; b < brandVector.size(); b++ )
    {
      //cout << "    for brandVector " << b << endl;
      string brandtag = brandVector[b].getTag();
      if ( strcmp(brandtag.c_str(),nakedtag.c_str()) == 0 || strcmp(brandtag.c_str(),slashtag.c_str()) == 0 )	{
        tempBrandVector.push_back(brandVector[b]);
        //cout << "      added brand " << brandVector[b].getId() << " to tag brand vector" << endl;
      }
    }
    tagVector[i].setBrand(tempBrandVector);
  }

  //cout << "    ... Tag::mergeBrands" << endl;
}

void Tag::setId(long i)
{
  id = i;
}

void Tag::setDeleted(bool d)
{
  deleted = d;
}

void Tag::setRfid( string s )
{
  rfid = s;
}

void Tag::setTbInjDate( Date d )
{
  tbInjDate = d;
}

long Tag::getId()
{
  return id;
}

bool Tag::isDeleted()
{
  return deleted;
}

string Tag::getTag()
{
  return tag;
}

string Tag::getSellerId()
{
  return sellerId;
}

long Tag::getTransactionId()
{
  return transactionId;
}

AnimalCode Tag::getAnimalCode()
{
  return code;
}

string Tag::getBurcellosisTag()
{
  return burcellosisTag;
}

bool Tag::operator==(string thatTag)
{
  return this->tag == thatTag;
}

bool Tag::compareTagsLT(Tag a, Tag b)
{
  return a.digitPart() < b.digitPart();
}

long Tag::digitPart()
{
  string buf;

  bool foundSpace = false;

  for(unsigned int i = 0; i < tag.length() && !foundSpace; i++)
  {
    if(isdigit(tag[i]))
    {
      buf += tag[i];
    }
    else if(buf.length() > 0)
    {
      foundSpace = true;
    }
  }

  return (buf.length() > 0 ? atol(buf.c_str()) : 0);
}

vector<string> Tag::tagRange(string a, string b)
{
  vector<string> tagList;
  int digitPos = a.find_first_of("0123456789");
  string pre;
  string post;

  if(digitPos != string::npos)
  {
    if(digitPos != 0)
    {
      pre = a.substr(0, digitPos);
    }

    a = a.substr(digitPos);

    digitPos = a.find_last_of("0123456789");

    if(digitPos != a.length() - 1)
    {
      post = a.substr(digitPos + 1);
    }
  }
  else
  {
    a = "";
  }

  digitPos = b.find_first_of("0123456789");

  if(digitPos != string::npos)
  {
    b = b.substr(digitPos);
  }
  else
  {
    b = "";
  }

  if(a.length() > 0)
  {
    long first = atol(a.c_str());
    long last = atol(b.c_str());
    char buf[20];

    for(long i = first; i <= last; i++)
    {
      sprintf(buf, "%ld", i);
      tagList.push_back(pre + string(buf) + post);
    }
  }
  return tagList;
}

string Tag::getBreed()
{
  return breed;
}

char Tag::getSex()
{
  return sex;
}

int Tag::getAge()
{
  return age;
}

string Tag::getVaccination()
{
  return vaccination;
}

string Tag::getBrucellosis()
{
  return brucellosis;
}

string Tag::getMonthsPreg()
{
  return monthsPreg;
}

Date Tag::getTestDate()
{
  return testDate;
}

string Tag::getOldTag()
{
  return oldTag;
}

string Tag::getComment()
{
  return comment;
}

string Tag::getRfid()
{
  return rfid;
}

Date Tag::getTbInjDate()
{
  return tbInjDate;
}


void Tag::setBreed(string breed)
{
  this->breed = breed;
}

void Tag::setSex(char sex)
{
  this->sex = sex;
}

void Tag::setAge(int age)
{
  this->age = age;
}

void Tag::setVaccination(string vaccination)
{
  this->vaccination = vaccination;
}

void Tag::setBrucellosis(string brucellosis)
{
  this->brucellosis = brucellosis;
}

void Tag::setMonthsPreg(string monthsPreg)
{
  this->monthsPreg = monthsPreg;
}

void Tag::setTestDate(Date testDate)
{
  this->testDate = testDate;
}

void Tag::setOldTag(string oldTag)
{
  this->oldTag = oldTag;
}

void Tag::setComment(string comment)
{
  this->comment = comment;
}

