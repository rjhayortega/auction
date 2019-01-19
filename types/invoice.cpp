
#include "invoice.h"

#include <cstring>
#include <cstdio>

// [KLN] adds
#include "globals.h"

Invoice::Invoice(long number, Date date, Customer customer, STATUS status)
{
  setNumber(number);
  setCustomer(customer);
  setDate(date);
  setStatus(status);
  commissionAdjustment = 0.000000;
}

Invoice::~Invoice()
{}

void Invoice::setNumber(long number)
{
  this->number = number;
}

void Invoice::setChargeStubList(vector<Charge> stubList)
{
  chargeStubList = vector<Charge>(0, Charge());

  for(unsigned int i = 0; i < stubList.size(); i++)
  {
    if(stubList[i].getExpression() != "0")
    {
      stubList[i].setExpression("");
    }

    chargeStubList.push_back(stubList[i]);
  }
}

void Invoice::setDate(Date date)
{
  this->date = date;
}

void Invoice::setCommissionAdjustment(double commissionAdjust)
{
  this->commissionAdjustment = commissionAdjust;
}

void Invoice::setCustomer(Customer customer)
{
  this->customer = customer;
}

vector<ChargeRecord> Invoice::getChargeRecordList(bool includeCommission)
{
  vector<Transaction>::iterator currentTrans;

  vector<ChargeRecord> chargeRecordList;
  vector<ChargeRecord> transCRList;

  vector<ChargeRecord>::iterator curTransCR;
  vector<ChargeRecord>::iterator accessChargeRec;

  if(includeCommission)
  {
    chargeRecordList.push_back(ChargeRecord(0, "COMMISSION", getCommissionTotal(), getCommissionAdjustment()));
  }

  vector<Charge> multiplierChargeList;

  for(unsigned int i = 0; i < manualCharges.size(); i++)
  {
    if(manualCharges[i].needsMultiplier())
    {
      multiplierChargeList.push_back(manualCharges[i]);
    }
    else
    {
      chargeRecordList.push_back(ChargeRecord(manualCharges[i].getId(), manualCharges[i].getDescrip(), 0.0, manualCharges[i].getAdjustment()));
    }
  }

  vector<Charge> invoiceChargeList;
  vector<Charge> tempChargeList;

  vector<Charge>::iterator invoiceCharge;
  ChargeExpressionParser::VARIABLES values;

  for(currentTrans = transactionList.begin(); currentTrans != transactionList.end(); currentTrans++)
  {
    if(currentTrans->getMode() != Transaction::Invalid)
    {
      bool isPair = currentTrans->getAnimalCode().isPair();

      tempChargeList = currentTrans->invoiceChargeList();

      values.head = currentTrans->getHead(false, false, false);
      values.weight = currentTrans->getWeight(false);
      values.totalDollars = currentTrans->amount(false);

      bool isSwap = ((currentTrans->getMode() == Transaction::SwapCWT || currentTrans->getMode() == Transaction::SwapHead) && customer.getNumber() == currentTrans->getSeller().getNumber());

      for(unsigned int i = 0; i < tempChargeList.size(); i++)
      {
	if((invoiceCharge = find(invoiceChargeList.begin(), invoiceChargeList.end(), tempChargeList[i])) == invoiceChargeList.end())
	{
	  tempChargeList[i].resetValues();
	  tempChargeList[i].addValues(values, currentTrans->chargeMode(), isPair, isSwap);
	  invoiceChargeList.push_back(tempChargeList[i]);
	}
	else
	{
	  invoiceCharge->addValues(values, currentTrans->chargeMode(), isPair, isSwap);
	}
      }


      transCRList = currentTrans->itemizedChargeRecordList();

      for(curTransCR = transCRList.begin(); curTransCR != transCRList.end(); curTransCR++)
      {
	accessChargeRec = find(chargeRecordList.begin(), chargeRecordList.end(), *curTransCR);

	if(accessChargeRec == chargeRecordList.end())
	{
	  chargeRecordList.push_back(*curTransCR);
	}
	else
	{
	  accessChargeRec->increaseTotal(curTransCR->getTotal());
	}
      }
    }
  }

  for(unsigned int i = 0; i < invoiceChargeList.size(); i++)
  {
    ChargeRecord temp(invoiceChargeList[i].getId(),
		      invoiceChargeList[i].getDescrip(),
		      invoiceChargeList[i].calculate(),
                      invoiceChargeList[i].getAdjustment(), false); 
                      
    chargeRecordList.push_back(temp);
  }
 
  return chargeRecordList;
}

void Invoice::setTransactionList(vector<Transaction> newList)
{
  this->transactionList = newList;

  for(unsigned int i = 0; i < transactionList.size(); i++)
  {
    transactionList[i].setOwnerNumber(customer.getNumber());
  }
}

void Invoice::setTruckingList(vector<TruckingRecord> newList)
{
  this->truckingList = newList;
}

void Invoice::setStatus(STATUS status)
{
  this->status = status;
}



long Invoice::getNumber()
{
  return number;
}


Customer Invoice::getCustomer()
{
  return customer;
}


Date Invoice::getDate()
{
  return date;
}

Invoice::STATUS Invoice::getStatus()
{
  return status;
}

bool Invoice::codeMismatch()
{
  AnimalCode baseCode;

  for(unsigned int i = 0; i < transactionList.size(); i++)
  {
    if(i == 0)
    {
      baseCode = transactionList[i].getAnimalCode();
    }
    else 
    {
      if(!baseCode.compareGroup(transactionList[i].getAnimalCode()))
      {
	return true;
      }
    }
  }
    return false;
}

bool Invoice::compareInvoiceCustomerNamesLT(Invoice left, Invoice right)
{
  return left.getCustomer().getName().getLast() < right.getCustomer().getName().getLast();
}

void Invoice::sortTransactionList()
{
  sort(transactionList.begin(), transactionList.end(), Transaction::compareIdsLT);
}

double Invoice::truckingTotal()
{
  vector<TruckingRecord>::iterator current;
  double total = 0.000001;

  for(current = truckingList.begin(); current != truckingList.end(); current++)
  {
    total += current->amount();
  }

  return getDollarAmount(total);
}

unsigned int Invoice::transactionListLength()
{
  return transactionList.size();
}
// this should be working for mixed calc by transaction / calc by invoice commission

double Invoice::getCommissionTotal(bool adjust)
{
  vector<Transaction>::iterator currentTransaction;
  double totalCommission = 0.0;

  currentTransaction = transactionList.begin();
  Commission comm;

  list<Commission> commissionList;
  list<Commission>::iterator currentComm;
  CommissionExpressionParser::VARIABLES values;
  CommissionExpressionParser::VARIABLES noSaleValues;

  // go through each transaction

  for(currentTransaction = transactionList.begin(); currentTransaction != transactionList.end(); currentTransaction++)
  {
    if(currentTransaction->getMode() != Transaction::Invalid)
    {
      comm = currentTransaction->getCommission();

      // if the type is by Transaction add the transaction commission calculation to the total

      if(comm.getType() == Commission::ByTransaction)
      {
	totalCommission += currentTransaction->calculateCommission();
      }
      else if(comm.getType() == Commission::ByInvoice)  // save the data to calculate by invoice later
      {
	// save the values of the current transaction 

	memset(&values, 0, sizeof(CommissionExpressionParser::VARIABLES));
        memset(&noSaleValues, 0, sizeof(CommissionExpressionParser::VARIABLES));

	if(currentTransaction->getMode() != Transaction::NoSaleCWT && currentTransaction->getMode() != Transaction::NoSaleHead)
	{
	  values.head   = currentTransaction->getHead(false, true);
	  values.price  = currentTransaction->getPrice(true);
	  values.weight = currentTransaction->getWeight();
	  values.total  = currentTransaction->amount(true);
	}
	else
	{
	  noSaleValues.head = currentTransaction->getHead(false, true);
          noSaleValues.price = currentTransaction->getPrice(true);
          noSaleValues.weight = currentTransaction->getWeight();

	  Transaction::SALE_MODE oldMode = currentTransaction->getMode();

	  currentTransaction->setMode(Transaction::SALE_MODE(oldMode - 2));
          noSaleValues.total = currentTransaction->amount(true);
	  currentTransaction->setMode(oldMode);
	}

	  currentComm = find(commissionList.begin(), commissionList.end(), comm);

	  /*
	   * if no commissions of this type are currently in the list, add the commission to the end of the list
	   * and set the iterator to the last position
	   */

	  if(currentComm == commissionList.end())
	  {
	    commissionList.push_back(comm);
	    currentComm = commissionList.end();
	    currentComm--;
	  }

	  // add the values to the commission total for this type
	  currentComm->addValues(values);
	  currentComm->addNoSaleValues(noSaleValues);
	
      }
    }
  }

  // add the commissions stored in the invoice commission list to the total
  double tempCommission = 0.0;
  for(currentComm = commissionList.begin(); currentComm != commissionList.end(); currentComm++)
  {
      tempCommission = currentComm->calculate();
      // [KLN] debug end
//          cout << "tempCommission: " << tempCommission << endl;
      // [KLN] debug

//          totalCommission += currentComm->calculate();
          totalCommission += tempCommission;
  }

  // [KLN] debug
  if (commissionDebug) {
      cout << "totalCommission: " << totalCommission << endl;
  }
  // [KLN] debug end

  if(adjust)
  {
      // [KLN] debug
      if (commissionDebug) {
          cout << "  commissionAdjustment: " << commissionAdjustment << endl;
      }
      // [KLN] debug end
    totalCommission -= commissionAdjustment;
    // [KLN] debug
    if (commissionDebug) {
        cout << "  Adjusted totalCommission: " << totalCommission << endl;
    }
    // [KLN] debug end
  }

  return getDollarAmount(totalCommission);
}


double Invoice::bidTotal()
{
  double total = 0.0000;
  for(unsigned int i = 0; i < transactionList.size(); i++)
  {
    total += transactionList[i].getPrice();
  }

  return getDollarAmount(total);
}

double Invoice::gross()
{
  double amount = 0.00000001;

  for(unsigned int i = 0; i < transactionList.size(); i++)
  {
    amount += transactionList[i].amount();
  }

  return getDollarAmount(amount);
}


void Invoice::addTransaction(Transaction newTransaction)
{
  transactionList.push_back(newTransaction);
}


void Invoice::setManualCharges(vector<Charge> manualCharges)
{
  this->manualCharges = manualCharges;
}

void Invoice::operator+=(Transaction newTransaction)
{
  addTransaction(newTransaction);
}

void Invoice::removeTransaction(long transactionNumber)
{
  vector<Transaction>::iterator currentTransaction;
  currentTransaction = find(transactionList.begin(), transactionList.end(), transactionNumber);
}

vector<AnimalCode> Invoice::getUniqueSexList()
{
  vector<AnimalCode> codeList;
  bool found;

  for(unsigned int i = 0; i < transactionList.size(); i++)
  {
    found = false;
    long sex = long(transactionList[i].getAnimalCode().getType());

    for(unsigned int j = 0; j < codeList.size(); j++)
    {
      if(sex == codeList[j].getType())
      {
	found = true;
	break;
      }
    }

    if(!found)
    {
      codeList.push_back(transactionList[i].getAnimalCode());
    }
  }

  return codeList;
}

long Invoice::getSexAverageWeight(AnimalCode code)
{
  long result = 0;
  long headCount = 0;

  for(unsigned int i = 0; i < transactionList.size(); i++)
  {
    if(transactionList[i].getAnimalCode().getType() == code.getType())
    {
      switch(transactionList[i].getMode())
      {
      default:
	result += transactionList[i].getWeight();
	headCount += transactionList[i].getHead(true);
	break;

      case Transaction::NoSaleCWT:
      case Transaction::Invalid:
      case Transaction::NoSaleHead:
      case Transaction::SaleHead:
      case Transaction::ReSaleHead:
	break;
      };
    }
  }
  return getWeightAmount(headCount > 0 ? result / headCount : 0);
}

long Invoice::getSexHead(AnimalCode code)
{
  long headCount = 0;
  for(unsigned int i = 0; i < transactionList.size(); i++)
  {
    if(transactionList[i].getAnimalCode().getType() == code.getType())
    {
      switch(transactionList[i].getMode())
      {
      default:
	headCount += transactionList[i].getHead(true);
	break;

      case Transaction::NoSaleCWT:
      case Transaction::Invalid:
      case Transaction::NoSaleHead:
      case Transaction::SaleHead:
      case Transaction::ReSaleHead:
	break;
      };
    }
  }
  return headCount;
}

double Invoice::getSexAvgDolPerCWT(AnimalCode code)
{
  double result = 0.000001;
  long weight = 0;
  long headCount = 0;
  double amountCount = 0.0000001;

  for(unsigned int i = 0; i < transactionList.size(); i++)
  {
    if(transactionList[i].getAnimalCode().getType() == code.getType())
    {
      switch(transactionList[i].getMode())
      {
      default:
	headCount += transactionList[i].getHead(true);
	weight += transactionList[i].getWeight();
	amountCount += transactionList[i].amount();
	break;

      case Transaction::NoSaleCWT:
      case Transaction::Invalid:
      case Transaction::NoSaleHead:
      case Transaction::SaleHead:
      case Transaction::ReSaleHead:
	break;
      };
    }
  }


  result = amountCount / ((double(weight) / 100.00));

  return result;
}

vector<Charge> Invoice::getUniqueChargeList(bool includeCommission)
{
   vector<Charge> chargeList;
   vector<Charge> tempList;
   vector<Transaction>::iterator currentTrans;
   vector<Charge>::iterator currentCharge;

   if(includeCommission)
   {
     char buf[30];
     sprintf(buf, "%0.2f", getCommissionTotal());
     chargeList.push_back(Charge(0, "COMMISSION", buf));
     chargeList[chargeList.size() - 1].setAdjustment(ChargeAdjustment(0, commissionAdjustment, false));
   }

   chargeList.insert(chargeList.end(), manualCharges.begin(), manualCharges.end());

   for(currentTrans = transactionList.begin(); currentTrans != transactionList.end(); currentTrans++)
   {
     tempList = currentTrans->getChargeList();

     for(currentCharge = tempList.begin(); currentCharge != tempList.end(); currentCharge++)
     {  
	 if(find(chargeList.begin(), chargeList.end(), *currentCharge) == chargeList.end())
	 {
	   chargeList.push_back(*currentCharge);
	 }
     }
   }

   for(unsigned int i = 0; i < chargeStubList.size(); i++)
   {
     if(find(chargeList.begin(), chargeList.end(), chargeStubList[i]) == chargeList.end())
     {
       chargeList.push_back(chargeStubList[i]);
     }
   }

  return chargeList;
}

double Invoice::averageDolPerCW()
{
  return getDollarAmount((cwt() > 0 ? (gross() / cwt()) : 0));
}

double Invoice::averageNetPerCWT()
{
  return getDollarAmount((cwt() > 0 ? (net() / cwt()) : 0));
}

double Invoice::averageDolPerHead()
{
  return getDollarAmount((head() > 0 ? (gross() / head()) : 0));
}

void Invoice::initCommissions(Commission comm)
{
  for(unsigned int i = 0; i < transactionList.size(); i++)
  {
    transactionList[i].setCommission(comm);
  }
}

void Invoice::adjustCharges(vector<Charge> adjustmentList)
{
  vector<Transaction>::iterator currentTrans;
  vector<Charge>::iterator chargeLoc;

  chargeLoc = find(adjustmentList.begin(), adjustmentList.end(), 0);

  if(chargeLoc != adjustmentList.end()) // adjust commission
  {
    setCommissionAdjustment(chargeLoc->getAdjustment().getAdjustment());
  }

  for(unsigned int i = 0; i < manualCharges.size(); i++)
  {
    chargeLoc = find(adjustmentList.begin(), adjustmentList.end(), manualCharges[i]);

    if(chargeLoc != adjustmentList.end())
    {
      manualCharges[i].setAdjustment(chargeLoc->getAdjustment());
    }
  }

  for(currentTrans = transactionList.begin(); currentTrans != transactionList.end(); currentTrans++)
  {
    currentTrans->adjustCharges(adjustmentList);
  }

  for(unsigned int i = 0; i < chargeStubList.size(); i++)
  {
    chargeLoc = find(adjustmentList.begin(), adjustmentList.end(), chargeStubList[i]);

    if(chargeLoc != adjustmentList.end())
    {
      chargeStubList[i].setAdjustment(chargeLoc->getAdjustment());
    }
  }
}

void Invoice::setTransactionChargeList(unsigned int index, vector<Charge> chargeList)
{
  if(0 <= index && index < transactionList.size())
  {
    transactionList[index].setChargeList(chargeList);
  }
}

// for testing only, should not really be used for anything, especially if
// there is a ui in place for the invoice

string Invoice::toString()
{
  string temp;
  char buf[15];

  temp = customer.toString() + "\n" + date.toString() + "\n";

  vector<Transaction>::iterator currentTransaction;

  for(currentTransaction = transactionList.begin(); currentTransaction != transactionList.end(); currentTransaction++)
  {
    temp += currentTransaction->toString() + "\n";
  }

  sprintf(buf, "%0.2f", gross());
  temp += string(buf) + "\n";
  sprintf(buf, "%0.2f", net());
  temp += string(buf) + "\n";

  vector<ChargeRecord> chgSumm = getChargeRecordList();

  for(unsigned int i = 0; i < chgSumm.size(); i++)
  {
    sprintf(buf, "\t%0.2f", chgSumm[i].getAdjustedTotal());
    temp += chgSumm[i].getDescrip() + buf + "\n";
  }

  return temp;
}

double Invoice::net()
{
  return 0.0;
}

double Invoice::cwt()
{
  return weight() / 100;
}

double Invoice::chargeTotal()
{
  vector<ChargeRecord> chgSumm = getChargeRecordList();
  vector<ChargeRecord>::iterator current;
  double total = 0.0;

  for(current = chgSumm.begin(); current != chgSumm.end(); current++)
  {
    total += current->getAdjustedTotal();
  }

  return getDollarAmount(total);
}

vector<TruckingRecord> Invoice::getTruckingList()
{
  return truckingList;
}

long Invoice::head(bool includePairs, bool includeNoSale)
{
  long totHead = 0;

  for(unsigned int i = 0; i < transactionList.size(); i++)
  {
      if((!includeNoSale && !(transactionList[i].getMode() == Transaction::NoSaleHead || transactionList[i].getMode() == Transaction::NoSaleCWT)) ||
          includeNoSale)
      {
	  totHead += transactionList[i].getHead(includePairs);
      }
  }

  return totHead;
}

long Invoice::noSaleHead(bool includePairs)
{
  long total = 0;

  for(unsigned int i = 0; i < transactionList.size(); i++)
  {
    if(transactionList[i].getMode() == Transaction::NoSaleCWT || transactionList[i].getMode() == Transaction::NoSaleHead)
    {
      total += transactionList[i].getHead(includePairs);
    }
  }
  return total;
}

long Invoice::noSaleWeight()
{
  long total = 0;

  for(unsigned int i = 0; i < transactionList.size(); i++)
  {
    if(transactionList[i].getMode() == Transaction::NoSaleCWT || transactionList[i].getMode() == Transaction::NoSaleHead)
    {
      total += transactionList[i].getWeight();
    }
  }
  return total;
}

double Invoice::weight(bool includeNoSale)
{
  vector<Transaction>::iterator current;
  double totWeight = 0.000;

  for(current = transactionList.begin(); current != transactionList.end(); current++)
  {
    if(includeNoSale || !(current->getMode() == Transaction::NoSaleHead || current->getMode() == Transaction::NoSaleCWT))
    {
      totWeight += current->getWeight();
    }
  }

  return round(totWeight);
}

double Invoice::averageWeight(bool includeNoSale)
{
  long totalHead = head(false, includeNoSale);
  return getWeightAmount(totalHead != 0 ? weight(includeNoSale) / totalHead: 0);
}

ChargeAdjustment Invoice::getCommissionAdjustment()
{
  return ChargeAdjustment(1, commissionAdjustment, false);
}




vector<Transaction>Invoice::getTransactionList()
{
  return transactionList;
}

