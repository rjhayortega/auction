
#ifndef _HISTORY_ITEM_H_
#define _HISTORY_ITEM_H_

#include "transaction.h"
#include "customer.h"

class HistoryItem
{
public:
  HistoryItem(Date=Date(), long=0, string="", string="",
              string="", string="", long=0, long=0, AnimalCode=AnimalCode(), 
              double=0.00001, Transaction::SALE_MODE=Transaction::NoSaleCWT, string="");

  HistoryItem(Date, long, string, double);
  Date getDate();
  long getTransactionNo();
  string getSellerNo();
  string getSellerName();
  string getBuyerNo();
  string getBuyerName();
  long getHead();
  long getWeight();
  AnimalCode getCode();
  double getBid();
  string getWeighmaster();
  Transaction::SALE_MODE getMode();
  double getNet();
  void setAnimalCode(AnimalCode);

  static bool compareTypeDescrip(HistoryItem, HistoryItem);
  static bool compareSellerNamesLT(HistoryItem, HistoryItem);
  static bool compareBuyerNamesLT(HistoryItem, HistoryItem);
  static bool compareDatesLT(HistoryItem, HistoryItem);

private:
  Date date;
  long transNo;
  string sellerNo;
  string sellerName;
  string buyerNo;
  string buyerName;
  long head;
  long weight;
  AnimalCode code;
  double bid;
  Transaction::SALE_MODE mode;
  string weighmaster;
  double net;
};

#endif
