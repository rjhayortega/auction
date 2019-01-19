
#include "transaction.h"
#include "numbers.h"

#include <cstdio>

Transaction::Transaction(long id, Seller seller, Buyer buyer, long head,
                         long weight, double price, SALE_MODE mode, AnimalCode animalCode,
                         string descrip, string sellerPen, string buyerPen,
                         DateTime created, DateTime updated, string comment, Commission commission,
                         vector<Tag> tagList, string weighMaster, bool manual,DateTime videoStrt)
{
  this->id         = id;
  this->seller     = seller;
  this->buyer      = buyer;
  this->head       = head;
  this->weight     = weight;
  this->descrip    = descrip;
  this->animalCode = animalCode;
  this->price      = price;
  this->created    = created;
  this->updated    = updated;
  this->comment    = comment;
  this->sellerPen  = sellerPen;
  this->buyerPen   = buyerPen;
  this->commission = commission;
  this->tagList = tagList;
  setMode(mode);
  this->weighmaster = weighMaster;
  this->ownerNumber = "";
  this->manual = manual;
  this->draft = 0;
  this->videostart = videoStrt;
}

void Transaction::setDraft(long xdraft)
{
  this->draft = xdraft;
}

long Transaction::getDraft()
{
  return draft;
}
void Transaction::setOwnerNumber(string ownerNumber)
{
  this->ownerNumber = ownerNumber;
}

void Transaction::setId(long id)
{
  this->id = id;
}

void Transaction::setSeller(Seller seller)
{
  this->seller = seller;
}

void Transaction::setBuyer(Buyer buyer)
{
  this->buyer = buyer;
}

void Transaction::setDescription(string description)
{
  this->descrip = description;
}

void Transaction::setSellerPen(string sellerPen)
{
  this->sellerPen = sellerPen;
}

void Transaction::setBuyerPen(string buyerPen)
{
  this->buyerPen = buyerPen;
}

void Transaction::setCreated(DateTime created)
{
  this->created = created;
}

void Transaction::setUpdated(DateTime updated)
{
  this->updated = updated;
}

void Transaction::setVideoStart(DateTime videoStrt)
{
  this->videostart = videoStrt;
}

void Transaction::setComment(string comment)
{
  this->comment = comment;
}

void Transaction::setWeighmaster(string weighmaster)
{
  this->weighmaster = weighmaster;
}

bool Transaction::isManual()
{
  return manual;
}

void Transaction::setCommission(Commission commission)
{
  this->commission = commission;
}

void Transaction::setMode(SALE_MODE mode)
{
  this->mode = mode;
}

void Transaction::setHead(long head)
{
  this->head = head;
}

void Transaction::setTagList(vector<Tag> tagList)
{
  this->tagList = tagList;
}

void Transaction::setBrandList(vector<Brand> brandList)
{
  this->brandList = brandList;
}

vector<Brand> Transaction::getBrandList()
{
  return brandList;
}

void Transaction::setAnimalCode(AnimalCode animalCode)
{
  this->animalCode = animalCode;
}

string Transaction::getWeighMaster()
{
  return weighmaster;
}

void Transaction::setWeighMaster(string weighMaster)
{
  this->weighmaster = weighMaster;
}

void Transaction::setManual(bool manual)
{
  this->manual = manual;
}

double Transaction::amount(bool negateSwap)
{
  double amt = 0.0;
  switch(mode)
  {
  case SaleCWT:
  case ReSaleCWT:
  case SwapCWT:
    amt = getDollarAmount(getCWT() * getPrice());
    break;

  case SaleHead:
  case ReSaleHead:
  case SwapHead:
    amt = getDollarAmount(double(getHead()) * getPrice());
    break;

  case NoSaleHead:
  case NoSaleCWT:
  case Invalid:
  case NumModes:
    amt = 0.0;
    break;
  }

  if(swapped() && negateSwap)
  {
    amt = -amt;
  }

  return amt;
}


long Transaction::getId()
{
  return id;
}


long Transaction::getHead(bool includePairs, bool negateSwap, bool includeInvalid)
{
  if(mode == Invalid && !includeInvalid)
  {
    return 0;
  }

  if(swapped() && negateSwap)
  {
    return -(head * (animalCode.isPair() && includePairs ? 2 : 1));
  }

  return (head * (animalCode.isPair() && includePairs ? 2 : 1));
}

Seller Transaction::getSeller()
{
  return seller;
}

Buyer Transaction::getBuyer()
{
  return buyer;
}

string Transaction::getDescription()
{
  return descrip;
}


long Transaction::getWeight(bool negateSwap)
{
  if(swapped() && negateSwap)
  {
    return -weight;
  }

  return weight;
}


double Transaction::getAverageWeight(bool negateSwap)
{
  double retVal = head == 0 ? 0.000 : double(weight) / head;
  if(negateSwap && swapped())
  {
    retVal = -retVal;
  }

  return getWeightAmount(retVal);
}

double Transaction::getPrice(bool negateSwap)
{
  if(swapped() && negateSwap)
  {
    return -price;
  }
  return price;
}

double Transaction::getCWT(bool negateSwap)
{
  if(negateSwap && swapped())
  {
    return -double(weight / 100.0);
  }

  return double(weight / 100.0);
}

double Transaction::calculateCommission()
{
  commission.resetValues();
  CommissionExpressionParser::VARIABLES values;

  values.head = head;
  values.price = price;
  values.weight = weight;
  values.total = amount(false);

  if(mode == Invalid || mode == NoSaleHead || mode == NoSaleCWT)
  {
    commission.addNoSaleValues(values);
    return commission.calculate();
  }


  commission.addValues(values);
  return commission.calculate();
}

Commission Transaction::getCommission()
{
  return commission;
}


bool Transaction::operator==(Transaction toCompare)
{
  return this->id == toCompare.id;
}


bool Transaction::compareIdsLT(Transaction a, Transaction b)
{
  return a.id < b.id;
}

bool Transaction::compareSellerIdsLT(Transaction a, Transaction b)
{
  return Customer::compareCustomerNumbersLT(a.seller.getNumber(), b.seller.getNumber());
}

bool Transaction::compareBuyerIdsLT(Transaction a, Transaction b)
{
  return Customer::compareCustomerNumbersLT(a.buyer.getNumber(), b.buyer.getNumber());
}

bool Transaction::compareHeadLT(Transaction a, Transaction b)
{
  return a.head < b.head;
}

bool Transaction::compareWeightLT(Transaction a, Transaction b)
{
  return a.weight < b.weight;
}

bool Transaction::compareAverageWeightLT(Transaction a, Transaction b)
{
  return a.getAverageWeight() < b.getAverageWeight();
}

bool Transaction::compareDescriptionLT(Transaction a, Transaction b)
{
  return a.animalCode.getDescrip() < b.animalCode.getDescrip();
}

bool Transaction::comparePriceLT(Transaction a, Transaction b)
{
  return a.price < b.price;
}

bool Transaction::compareAmountLT(Transaction a, Transaction b)
{
  return a.amount() < b.amount();
}

bool Transaction::compareBuyerPenLT(Transaction a, Transaction b)
{
      long digitPartA = atol(a.buyerPen.c_str());
      long digitPartB = atol(b.buyerPen.c_str());

      if(digitPartA != digitPartB)
      {
	return digitPartA < digitPartB;
      }

      int aIndex = a.buyerPen.find_first_not_of("0123456789");
      int bIndex = b.buyerPen.find_first_not_of("0123456789");

      string alphaPartA = (aIndex != string::npos ? a.buyerPen.substr(aIndex) : "");
      string alphaPartB = (bIndex != string::npos ? b.buyerPen.substr(bIndex) : "");

      return alphaPartA < alphaPartB;
}

bool Transaction::compareSellerNamesLT(Transaction a, Transaction b)
{
  return (a.getSeller().getName().getLast() < b.getSeller().getName().getLast());
}

bool Transaction::comparePricePerCWTLT(Transaction a, Transaction b)
{
  return( a.getPricePerCWT() < b.getPricePerCWT());
}

bool Transaction::comparePricePerHeadLT(Transaction a, Transaction b)
{
  return (a.getPricePerHead() < b.getPricePerHead());
}

bool Transaction::operator==(long number)
{
  return this->id == number;
}

// used only for testing
string Transaction::toString()
{
  char buf[15];
  string temp;

  sprintf(buf, "%ld", id);
  temp += string(buf) + " ";
  temp += seller.toString() + " ";

  temp += buyer.toString() + " ";

  sprintf(buf, "%ld", getHead());
  temp += string(buf) + " ";
  sprintf(buf, "%ld", getWeight());
  temp += string(buf) + " ";
  sprintf(buf, "%0.2f", getPrice());
  temp += string(buf) + " ";
  sprintf(buf, "%0.2f", amount());
  temp += string(buf) + " ";
  return temp;
}


AnimalCode Transaction::getAnimalCode()
{
  return animalCode;
}

Transaction::SALE_MODE Transaction::getMode()
{
  return mode;
}

string Transaction::getSellerPen()
{
  return sellerPen;
}

string Transaction::getBuyerPen()
{
  return buyerPen;
}

string Transaction::getComment()
{
  return comment;
}

DateTime Transaction::getUpdated()
{
  return updated;
}

DateTime Transaction::getCreated()
{
  return created;
}

DateTime Transaction::getVideoStart()
{
  return videostart;
}

string Transaction::getWeighmaster()
{
  return weighmaster;
}

vector<Tag> Transaction::getTagList()
{
  return tagList;
}

double Transaction::getPricePerCWT(bool negateSwap)
{
  double cwt = getCWT(false);
  double retVal = getDollarAmount(cwt == 0 ? 0.000 : amount(false) / cwt);

  if(negateSwap && swapped())
  {
    retVal = -retVal;
  }

  return retVal;
}

double Transaction::getPricePerHead(bool negateSwap)
{
  double retVal = getDollarAmount(head == 0 ? 0 : amount(false) / head);

  if(negateSwap && swapped())
  {
    retVal = -retVal;
  }

  return retVal;
}

void Transaction::setChargeList(vector<Charge> chargeList)
{
  this->chargeList = chargeList;
}

bool Transaction::swapped()
{
  return ((mode == Transaction::SwapCWT || mode == Transaction::SwapHead) && ownerNumber == seller.getNumber() && ownerNumber.length() > 0);
}

double Transaction::calculateCharges()
{
  vector<Charge>::iterator current;
  ChargeExpressionParser::VARIABLES values;
  values.head = head;
  values.weight = weight;
  values.totalDollars = amount(false);
  double totalCharges = 0.0;

  if(mode == Invalid)
  {
    return 0.00000;
  }

  for(current = chargeList.begin(); current != chargeList.end(); current++)
  {
    Charge::CHARGE_MODE _chargeMode = chargeMode();

    totalCharges += current->calculate(values, _chargeMode, animalCode.isPair());
  }

  if(swapped())
  {
    totalCharges = -totalCharges;
  }

  return totalCharges;
}

Charge::CHARGE_MODE Transaction::chargeMode()
{
    Charge::CHARGE_MODE _chargeMode = Charge::Normal;

    switch(mode)
    {
    case NoSaleCWT:
    case NoSaleHead:
      _chargeMode = Charge::NoSale;
      break;

    case ReSaleCWT:
    case ReSaleHead:
      _chargeMode = Charge::ReSale;
      break;

    default:
      _chargeMode = Charge::Normal;
      break;
    }

    return _chargeMode;
}

void Transaction::addCharge(Charge charge)
{
  if(find(chargeList.begin(), chargeList.end(), charge) == chargeList.end())
  {
    chargeList.push_back(charge);
  }
}

vector<ChargeRecord> Transaction::itemizedChargeRecordList()
{
  vector<Charge>::iterator current;
  ChargeExpressionParser::VARIABLES values;
  values.head = head;
  values.weight = weight;
  values.totalDollars = amount(false);

  vector<ChargeRecord> itemizedChargeList;

  if(mode == Invalid)
  {
    return vector<ChargeRecord>();
  }
  double chargeAmount = 0.00000;
  for(current = chargeList.begin(); current != chargeList.end(); current++)
  {
    if(current->getScope() == Charge::Transaction)
    {
      Charge::CHARGE_MODE chargeMode = Charge::Normal;

      switch(mode)
      {
      case NoSaleCWT:
      case NoSaleHead:
        chargeMode = Charge::NoSale;
        break;

      case ReSaleCWT:
      case ReSaleHead:
        chargeMode = Charge::ReSale;
        break;

      default:
        chargeMode = Charge::Normal;
        break;
      }

      chargeAmount = current->calculate(values, chargeMode, animalCode.isPair());

      if(swapped())
      {
        chargeAmount = 0.0000000001 - chargeAmount - 0.02;
      }

      itemizedChargeList.push_back(ChargeRecord(current->getId(), current->getDescrip(), chargeAmount, current->getAdjustment(), current->isCommissionCharge()));
    }
  }
  return itemizedChargeList;
}

void Transaction::setPrice(double price)
{
  this->price = price;
}

void Transaction::setWeight(long weight)
{
  this->weight = weight;
}

vector<Charge> Transaction::getChargeList()
{

  if(mode == Invalid)
  {
    return vector<Charge>();
  }

  return chargeList;
}

void Transaction::adjustCharges(vector<Charge> adjustmentList)
{
  vector<Charge>::iterator charge;
  vector<Charge>::iterator adjustedCharge;

  pair<vector<Charge>::iterator, vector<Charge>::iterator> range;

  sort(chargeList.begin(), chargeList.end(), Charge::compareIdsLT);

  for(unsigned int i = 0; i < adjustmentList.size(); i++)
  {
    range = equal_range(chargeList.begin(), chargeList.end(), adjustmentList[i], Charge::compareIdsLT);

    for(charge = range.first; charge != range.second; charge++)
    {
      charge->setAdjustment(adjustmentList[i].getAdjustment());
    }
  }

/*
  for(charge = chargeList.begin(); charge != chargeList.end(); charge++)
  {
    for(adjustedCharge = adjustmentList.begin(); adjustedCharge != adjustmentList.end(); adjustedCharge++)
    {
      if(*charge == *adjustedCharge)
      {
	charge->setAdjustment(adjustedCharge->getAdjustment());
      }
    }
  }
*/
}

vector<Charge> Transaction::invoiceChargeList()
{
  vector<Charge> resultVector;

  for(unsigned int i = 0; i < chargeList.size(); i++)
  {
    if(chargeList[i].getScope() == Charge::Invoice)
    {
      resultVector.push_back(chargeList[i]);
    }
  }

  return resultVector;
}

void Transaction::increaseChargeValues(ChargeExpressionParser::VARIABLES& values)
{
  values.head         += head;
  values.weight       += weight;
  values.totalDollars += amount(false);
}

// Interface functions for print transaction info.
QString Transaction::transactionNumber()
{
    QString result;
    QString formatString = QString("%1%2");
    if(swapped()) {
        formatString = QString("%1-%2S");
    }
    result = QString(formatString).arg(getId()).arg((isManual() ? "M" : " "));
    return result;
}

QString Transaction::headStr()
{
    QString result;
    if( getAnimalCode().isPair()) {
       result= QString("%1/%2").arg(getHead(false, false)).arg(getHead(false, false));
    }
    else {
        result= QString("%1").arg(getHead(false, false));
    }
    return result;
}
