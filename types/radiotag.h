#ifndef _RADIO_TAG_H_
#define _RADIO_TAG_H_

#include <string> 
#include "date.h"
#include "datetime.h"

using namespace std;
class RadioTag
{
public:
  RadioTag(long=0, string="", string="", string="", Date=Date(), DateTime=DateTime::currentDateTime());

  void setSellerNumber(string);

  long getId();
  string getNumber();
  string getSellerNumber();
  string getBuyerNumber();
  Date getDate();
  DateTime getDateTime();

private:
  long id;
  string number;
  string sellerNumber;
  string buyerNumber;
  Date date;
  DateTime dateTime;
};
#endif
