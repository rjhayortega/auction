#include "radiotag.h"

RadioTag::RadioTag(long id, string number, string sellerNumber, string buyerNumber, Date date, DateTime dateTime)
{
  this->id = id;
  this->number = number;
  this->sellerNumber = sellerNumber;
  this->buyerNumber = buyerNumber;
  this->date = date;
  this->dateTime = dateTime;
}

void RadioTag::setSellerNumber(string sellerNumber)
{
  this->sellerNumber = sellerNumber;
}

long RadioTag::getId()
{
  return id;
}

string RadioTag::getNumber()
{
  return number;
}

string RadioTag::getSellerNumber()
{
  return sellerNumber;
}

string RadioTag::getBuyerNumber()
{
  return buyerNumber;
}

Date RadioTag::getDate()
{
  return date;
}

DateTime RadioTag::getDateTime()
{
  return dateTime;
}
