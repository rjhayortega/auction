#include "summaryrecord.h"

ChargeSummaryRecord::ChargeSummaryRecord(long chargeId, string chargeDescription, double chargeTotal)
{
  this->chargeId = chargeId;
  this->chargeDescription = chargeDescription;
  this->chargeTotal = chargeTotal;
}

long ChargeSummaryRecord::getChargeId()
{
  return chargeId;
}

string ChargeSummaryRecord::getChargeDescription()
{
  return chargeDescription;
}

double ChargeSummaryRecord::getChargeTotal()
{
  return chargeTotal;
}

bool ChargeSummaryRecord::operator==(ChargeSummaryRecord comparator)
{
  return this->chargeId == comparator.chargeId;
}

bool ChargeSummaryRecord::compareIdsLT(ChargeSummaryRecord a, ChargeSummaryRecord b)
{
  return a.chargeId < b.chargeId;
}

InvoiceSummaryRecord::InvoiceSummaryRecord(string number, string name, long head, double gross, vector<ChargeSummaryRecord> chargeList, vector<string> checkNumberList)
{
  this->customerNumber = number;
  this->customerName = name;
  this->head = head;
  this->gross = gross;
  this->chargeSummaryList = chargeList;
  this->checkNumberList = checkNumberList;
}

string InvoiceSummaryRecord::getCustomerNumber()
{
  return customerNumber;
}

string InvoiceSummaryRecord::getCustomerName()
{
  return customerName;
}

long InvoiceSummaryRecord::getHead()
{
  return head;
}

double InvoiceSummaryRecord::getNet(bool seller)
{
  if(seller)
  {
    return getGross() - getChargeTotal();
  }
  else
  {
    return getGross() + getChargeTotal();
  }
}

double InvoiceSummaryRecord::getGross()
{
  return gross;
}

vector<ChargeSummaryRecord> InvoiceSummaryRecord::getChargeSummaryList()
{
  return chargeSummaryList;
}

double InvoiceSummaryRecord::getChargeTotal()
{
  double total = 0.00000;

  for(unsigned int i = 0; i < chargeSummaryList.size(); i++)
  {
    total += chargeSummaryList[i].getChargeTotal();
  }
  return total;
}

unsigned int InvoiceSummaryRecord::chargeListLength()
{
  return chargeSummaryList.size();
}

vector<string> InvoiceSummaryRecord::getCheckNumberList()
{
  return checkNumberList;
}

bool InvoiceSummaryRecord::compareCustomerNumbersLT(InvoiceSummaryRecord a, InvoiceSummaryRecord b)
{
  return Customer::compareCustomerNumbersLT(a.customerNumber, b.customerNumber);
}
