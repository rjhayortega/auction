
#ifndef _TRUCKING_RECORD_H_
#define _TRUCKING_RECORD_H_

#include "date.h"
#include "customer.h"

class TruckingRecord
{
public:
typedef enum mode
{
  Flat,
  ByHundredWeight,
  ByHead,
  ByMile, 
  Other
}MODE;

TruckingRecord(long=0, string="",double=0.0, long=0, MODE=ByHundredWeight, Date=Date::currentDate(), long=0, string="", Customer::Type=Customer::Seller);

void setId(long);
void setTruckerName(string);
void setPrice(double);
void setQuantity(long);
void setMode(MODE);
void setCheckInDate(Date);
void setCheckNo(long);

long   getId();
string getTruckerName();
double getPrice();
long   getQuantity();
MODE   getMode();
Date   getCheckInDate();
long getCheckNo();

static bool compareTruckerNamesLT(TruckingRecord, TruckingRecord);

double amount();

void setConsignerName(string);
string getConsignerName();

string getConsignerNo();
Customer::Type getConsignerType();

private:
string consignerNo;
string consignerName;
Customer::Type consignerType;
  long id;
  string truckerName;
  double price;
  long quantity;
  MODE mode;
  Date checkInDate;
  long checkNo;
};

#endif
