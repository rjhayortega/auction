

#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

#include "customer.h"
#include "animalcode.h"
#include "datetime.h"
#include "commission.h"
#include "charge.h"
#include "chargerecord.h"
#include "tag.h"
#include "brand.h"

#include <list>
#include <vector>
#include <string>
#include <math.h>
#include <iostream>
#include "math.h"
#include <QString>

using namespace std;


class Transaction
{
public:
typedef enum
{
 Invalid,	// 0 - Invalid Transaction
 SaleCWT,	// 1 - Sale by CWT
 SaleHead,	// 2 - Sale by Head
 NoSaleCWT,	// 3 - Nosale, bid per head
 NoSaleHead,	// 4 - Nosale, bid per cwt
 ReSaleCWT,	// 5 - Resale, per cwt
 ReSaleHead,	// 6 - Resale, per head
 SwapCWT,  	// 7 - Swap per cwt
 SwapHead,  	// 8 - Swap per head
 NumModes	// Also invalid .. 
}SALE_MODE;

  Transaction(long=0, Seller=Seller(), Buyer=Buyer(), long=0,
              long=0, double=0, SALE_MODE=Invalid, AnimalCode=AnimalCode(),
              string="",string="",string="",DateTime=DateTime(),
              DateTime=DateTime(),string="", Commission=Commission(), vector<Tag> =vector<Tag>(), string="",
              bool=false,DateTime videoStrt = DateTime());

  void setId(long);

  void setSeller(Seller);
  void setBuyer(Buyer);
  void setDescription(string);
  void setSellerPen(string);
  void setBuyerPen(string);
  void setCreated(DateTime);
  void setUpdated(DateTime);
  void setVideoStart(DateTime);
  void setComment(string);
  void setWeighmaster(string);

  double amount(bool=true);
  void setMode(SALE_MODE);
  void setCommission(Commission);
  void setHead(long);
  void setAnimalCode(AnimalCode);

  long getId();
  long getHead(bool=false, bool=true, bool=false);
  Seller getSeller();
  Buyer getBuyer();
  string getDescription();
  long getWeight(bool=true);
  double getAverageWeight(bool=true);
  double getPrice(bool=true);
  double getCWT(bool=true);
  double calculateCommission();
  Commission getCommission();
  AnimalCode getAnimalCode();
  bool operator==(Transaction);
  bool operator==(long);
  SALE_MODE getMode();
  string getSellerPen();
  string getBuyerPen();
  string getComment();
  string toString();
  DateTime getCreated();
  DateTime getUpdated();
  DateTime getVideoStart();
  string getWeighmaster();
  void setChargeList(vector<Charge>);
  double calculateCharges();
  void setTagList(vector<Tag>);
  void setBrandList(vector<Brand>);
  vector<ChargeRecord> itemizedChargeRecordList();
  vector<Charge> getChargeList();
  vector<Tag> getTagList();
  vector<Brand> getBrandList();
  void addCharge(Charge);
  double getPricePerCWT(bool=true);
  double getPricePerHead(bool = true);
  bool swapped();
  void setOwnerNumber(string);
  void adjustCharges(vector<Charge>);
  void setPrice(double);
  static bool compareIdsLT(Transaction, Transaction);
  static bool compareSellerIdsLT(Transaction, Transaction);
  static bool compareBuyerIdsLT(Transaction, Transaction);
  static bool compareHeadLT(Transaction, Transaction);
  static bool compareWeightLT(Transaction, Transaction);
  static bool compareAverageWeightLT(Transaction, Transaction);
  static bool compareDescriptionLT(Transaction, Transaction);
  static bool comparePriceLT(Transaction, Transaction);
  static bool compareAmountLT(Transaction, Transaction);
  static bool compareBuyerPenLT(Transaction, Transaction);
  static bool compareSellerNamesLT(Transaction, Transaction);
  static bool comparePricePerCWTLT(Transaction, Transaction);
  static bool comparePricePerHeadLT(Transaction, Transaction);
  string ownerNumber;
  bool isManual();
  void setWeighMaster(string);
  void setManual(bool);
  string getWeighMaster();
  void setWeight(long weight);
  void increaseChargeValues(ChargeExpressionParser::VARIABLES&);
  vector<Charge> invoiceChargeList();

  Charge::CHARGE_MODE chargeMode();
  void setDraft(long draft);
  long getDraft();
  // Interface functions for print transaction info on invoice.
  QString transactionNumber();
  QString headStr();


private:
  long id;
  Seller seller;
  Buyer buyer;
  long head;
  long weight;
  string descrip;
  AnimalCode animalCode;
  double price;
  DateTime created;
  DateTime updated;
  string comment;
  string sellerPen;
  string buyerPen;
  SALE_MODE mode;
  Commission commission;
  string weighmaster;
  vector<Charge> chargeList;
  vector<Tag> tagList;
  vector<Brand> brandList;
  bool manual;
  long draft;
  DateTime videostart;
};

#endif
