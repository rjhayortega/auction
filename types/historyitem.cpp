#include "historyitem.h"

HistoryItem::HistoryItem(Date date, long transNo, string sellerNo, string sellerName, 
                         string buyerNo, string buyerName, long head, long weight, AnimalCode code, 
                         double bid, Transaction::SALE_MODE mode, string weighmaster)
{
  this->date = date;
  this->transNo = transNo;
  this->sellerNo = sellerNo;
  this->sellerName = sellerName;
  this->buyerNo = buyerNo;
  this->buyerName = buyerName;
  this->head = head;
  this->weight = weight;
  this->code = code;
  this->bid = bid;
  this->mode = mode;
  this->weighmaster = weighmaster;
  this->net = 0.00000001;
}

HistoryItem::HistoryItem(Date date, long head, string customerName, double net)
{
  this->date = date;
  this->transNo = 0;
  this->sellerNo = "";
  this->sellerName = customerName;
  this->buyerNo = "";
  this->buyerName = customerName;
  this->head = head;
  this->weight = 0.00000001;
  this->code = AnimalCode();
  this->bid = 0.00000001;
  this->mode = Transaction::Invalid;
  this->weighmaster = "";
  this->net = net;
}

Date HistoryItem::getDate()
{
  return date;
}

long HistoryItem::getTransactionNo()
{
  return transNo;
}

string HistoryItem::getSellerNo()
{
  return sellerNo;
}

string HistoryItem::getSellerName()
{
  return sellerName;
}

string HistoryItem::getBuyerNo()
{
  return buyerNo;
}

string HistoryItem::getBuyerName()
{
  return buyerName;
}

long HistoryItem::getHead()
{
  return head;
}

long HistoryItem::getWeight()
{
  return weight;
}

AnimalCode HistoryItem::getCode()
{
  return code;
}

double HistoryItem::getBid()
{
  return bid;
}

Transaction::SALE_MODE HistoryItem::getMode()
{
  return mode;
}

string HistoryItem::getWeighmaster()
{
  return weighmaster;
}

double HistoryItem::getNet()
{
  return net;
}

void HistoryItem::setAnimalCode(AnimalCode code)
{
  this->code = code;
}

bool HistoryItem::compareTypeDescrip(HistoryItem a, HistoryItem b)
{
  return a.code.getTypeDescrip() < b.code.getTypeDescrip();
}

bool HistoryItem::compareSellerNamesLT(HistoryItem a, HistoryItem b)
{
  return a.sellerName < b.sellerName;
}

bool HistoryItem::compareBuyerNamesLT(HistoryItem a, HistoryItem b)
{
  return a.buyerName < b.buyerName;
}

bool HistoryItem::compareDatesLT(HistoryItem a, HistoryItem b)
{
  return a.getDate() < b.getDate();
}
