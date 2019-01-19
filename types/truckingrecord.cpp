
#include "truckingrecord.h"

TruckingRecord::TruckingRecord(long id, string truckerName, double price, long quantity, MODE mode, Date date, long checkNo, string consignerNo, Customer::Type consignerType)
{
  setId(id);
  setTruckerName(truckerName);
  setPrice(price);
  setQuantity(quantity);
  setMode(mode);
  setCheckInDate(date);
  this->consignerNo = consignerNo;
  this->consignerType = consignerType;
  this->checkNo = checkNo;
}

void TruckingRecord::setCheckNo(long checkNo)
{
  this->checkNo = checkNo;
}

long TruckingRecord::getCheckNo()
{
  return checkNo;
}

string TruckingRecord::getConsignerNo()
{
  return consignerNo;
}

Customer::Type TruckingRecord::getConsignerType()
{
  return consignerType;
}

bool TruckingRecord::compareTruckerNamesLT(TruckingRecord left, TruckingRecord right)
{
  return left.truckerName < right.truckerName;
}

void TruckingRecord::setId(long id)
{
  this->id = id;
}

void TruckingRecord::setTruckerName(string truckerName)
{
  this->truckerName = truckerName;
}

void TruckingRecord::setPrice(double price)
{
  this->price = price;
}

void TruckingRecord::setQuantity(long quantity)
{
  this->quantity = quantity;
}

void TruckingRecord::setMode(MODE mode)
{
  this->mode = mode;
}

void TruckingRecord::setCheckInDate(Date date)
{
  this->checkInDate = date;
}

long TruckingRecord::getId()
{
  return id;
}

string TruckingRecord::getTruckerName()
{
  return truckerName;
}

double TruckingRecord::getPrice()
{
  return price;
}

long TruckingRecord::getQuantity()
{
  return quantity;
}

TruckingRecord::MODE TruckingRecord::getMode()
{
  return mode;
}

Date TruckingRecord::getCheckInDate()
{
  return checkInDate;
}

double TruckingRecord::amount()
{
  switch(mode)
  {
  case ByHead:
  case ByMile:
  case Other:
  case Flat:
  default:
    return price * double(quantity);
    break;

  case ByHundredWeight:
    return price * (double(quantity) / 100.00);
    break;

//  case ByHundredWeight:
//     return price * cwt * double(quantity);
//     break;

//    return price;
    break;
  }

  return 0.0;
}


void TruckingRecord::setConsignerName(string name)
{
  consignerName = name;
}

string TruckingRecord::getConsignerName()
{
  return consignerName;
}
