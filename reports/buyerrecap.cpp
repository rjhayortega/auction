

#include "buyerrecap.h"

#include <cstdio>

BuyerRecap::BuyerRecap(vector<BuyerInvoice> invoiceList, string owner, Date date, vector<string> unprintedBuyerList, bool consolidateCharges, vector<ChargeRecord> recapCharges)
{
  this->invoiceList = invoiceList;
  this->owner = owner;
  this->date = date;
  this->unprintedBuyerList = unprintedBuyerList;
  this->consolidateCharges = consolidateCharges;
  this->recapCharges = recapCharges;
  chargeTotal = 0.00;
}

string BuyerRecap::text()
{
  clearTables();
  addTable(makeBuyerTable());
  addTable(makeRecapTable());

  if(!consolidateCharges || recapCharges.size() != 0)
  {
    addTable(makeSummaryTable());
  }

  addTable(makeTotalTable());
  return TextReport::text();
}


TextReportTable BuyerRecap::makeBuyerTable()
{
  TextReportTable buyerTable(3);
  buyerTable.insertRows(4);
  buyerTable.setColumnWidth(0, 35);
  buyerTable.setColumnWidth(1, 11);
  buyerTable.setColumnWidth(2, 34);

  buyerTable.setColumnAlignment(2, TextReportTable::RIGHT);

  buyerTable.setText(0, 1, "BUYER RECAP");
  buyerTable.setText(1, 0, owner);
  buyerTable.setText(1, 2, string("Date: ") + date.toString("mm/dd/YYYY"));
//  buyerTable.setText(2, 0, "Any buyer in this list that has an asterisk(*) next to it, has not been printed", true);
  buyerTable.setFooterSeperator(' ', ' ');
  buyerTable.setHeaderSeperator(' ', ' ');
  return buyerTable;
}



TextReportTable BuyerRecap::makeRecapTable()
{
  TextReportTable recapTable(6);
  recapTable.insertRows(invoiceList.size());

  recapTable.setColumnWidth(0, 10);
  recapTable.setColumnWidth(1, 10);
  recapTable.setColumnWidth(2, 15);
  recapTable.setColumnWidth(3, 15);
  recapTable.setColumnWidth(4, 15);
  recapTable.setColumnWidth(5, 15);

  recapTable.setColumnAlignment(0, TextReportTable::RIGHT);
  recapTable.setColumnAlignment(1, TextReportTable::RIGHT);
  recapTable.setColumnAlignment(2, TextReportTable::RIGHT);
  recapTable.setColumnAlignment(3, TextReportTable::RIGHT);
  recapTable.setColumnAlignment(4, TextReportTable::RIGHT);
  recapTable.setColumnAlignment(5, TextReportTable::RIGHT);

  recapTable.setHeader(0, "BUYER");
  recapTable.setHeader(1, "HEAD");
  recapTable.setHeader(2, "AVG. WT.");
  recapTable.setHeader(3, "TOTAL WEIGHT");
  recapTable.setHeader(4, "AVG. $/HW");
  recapTable.setHeader(5, "TOTAL PRICE");


  recapTable.setHeaderStyle(TextReportTable::Continuous, TextReportTable::Continuous);
  recapTable.setFooterStyle(TextReportTable::Continuous, TextReportTable::Broken);
  recapTable.setFooterSeperator('-', ' ');
  char buf[20];

  long totalHead = 0;
  long totalWeight = 0;
  double totalAvgDolPerCW = 0;
  double totalPrice = 0;

  recapTotal = 0;
  string alertChar;
  for(unsigned int i = 0; i < invoiceList.size(); i++)
  {
    alertChar = " ";
    if(find(unprintedBuyerList.begin(), unprintedBuyerList.end(), invoiceList[i].getCustomer().getNumber()) != unprintedBuyerList.end())
    {
      alertChar = "*";
    }

    recapTable.setText(i, 0, invoiceList[i].getCustomer().getNumber() + alertChar);

    sprintf(buf, "%ld", invoiceList[i].head(true));
    totalHead += invoiceList[i].head(true);
    recapTable.setText(i, 1, buf);

    sprintf(buf, "%0.f", invoiceList[i].averageWeight());
    recapTable.setText(i, 2, buf);

    sprintf(buf, "%0.f", invoiceList[i].weight());
    totalWeight += invoiceList[i].weight();
    recapTable.setText(i, 3, buf);

    if(!consolidateCharges)
    {
      sprintf(buf, "%0.2f", invoiceList[i].averageDolPerCW());
      totalAvgDolPerCW += invoiceList[i].averageDolPerCW();
    }
    else
    {
      sprintf(buf, "%0.2f", invoiceList[i].net() / invoiceList[i].cwt());
      totalAvgDolPerCW += invoiceList[i].net() / invoiceList[i].cwt();
    }

    recapTable.setText(i, 4, buf);

    sprintf(buf, "%0.2f", (consolidateCharges ? invoiceList[i].net() : invoiceList[i].gross()));
    totalPrice += (consolidateCharges ? invoiceList[i].net() : invoiceList[i].gross());
    recapTable.setText(i, 5, buf);
  }

  sprintf(buf, "%ld", totalHead);
  recapTable.setFooter(1, buf);

  sprintf(buf, "%0.f", double(totalWeight) / totalHead);
  recapTable.setFooter(2, buf);

  recapTable.setFooter(3, totalWeight);

  sprintf(buf, "%0.2f", getDollarAmount(totalPrice / (totalWeight / 100.0)));
  recapTable.setFooter(4, buf);

  sprintf(buf, "%0.2f", totalPrice);
  recapTable.setFooter(5, buf);
  recapTotal = totalPrice;
  return recapTable;
}


TextReportTable BuyerRecap::makeSummaryTable()
{
  vector<ChargeRecord> crList;
  vector<ChargeRecord> tempList;

  for(unsigned int i = 0; i < invoiceList.size() && !consolidateCharges; i++)
  {
    tempList = invoiceList[i].getChargeRecordList();
    tempList.insert(tempList.begin(), ChargeRecord(-1, "Trucking"   , invoiceList[i].truckingTotal()));
    tempList.insert(tempList.begin(), ChargeRecord(0, "Commissions", invoiceList[i].getCommissionTotal()));
    appendChargeRecordList(crList, tempList);
  }

  appendChargeRecordList(crList, recapCharges);
  sort(crList.begin(), crList.end(), ChargeRecord::compareIdsLT);

  // swap the trucking and commission

  if(crList.size() > 1)
  {
    ChargeRecord temp = crList[0];
    crList[0] = crList[1];
    crList[1] = temp;
  }

  double total = 0.0;

  TextReportTable summaryTable(3);
  summaryTable.insertRows(crList.size());

  summaryTable.setColumnWidth(0, 49);
  summaryTable.setColumnWidth(1, 20);
  summaryTable.setColumnWidth(2, 11);

  summaryTable.setColumnAlignment(2, TextReportTable::RIGHT);
  summaryTable.setHeaderSeperator(' ', ' ');
  summaryTable.setFooterStyle(TextReportTable::ContinuousBroken, TextReportTable::NoHeader);
  summaryTable.setFooterSeperator('=', ' ');

  for(unsigned int i = 0; i< crList.size(); i++)
  {
    summaryTable.setText(i, 1, crList[i].getDescrip());
    summaryTable.setText(i, 2, crList[i].getTotal());
    total += crList[i].getTotal();
  }

  chargeTotal = total;

  summaryTable.setFooter(1, "TOTAL FEES");
  summaryTable.setFooter(2, total);

  return summaryTable;
}

void BuyerRecap::appendChargeRecordList(vector<ChargeRecord>& dest, vector<ChargeRecord> src)
{
  bool found;
  for(unsigned int i = 0; i < src.size(); i++)
  {
    found = false;

    for(unsigned int j = 0; j < dest.size(); j++)
    {
      if(dest[j] == src[i])
      {
	found = true;
	dest[j].setTotal(dest[j].getTotal() + src[i].getAdjustedTotal());
      }
    }

    if(!found)
    {
      src[i].setTotal(src[i].getAdjustedTotal());
      dest.push_back(src[i]);
    }
  }
}

TextReportTable BuyerRecap::makeTotalTable()
{
  TextReportTable totalTable(3);
  totalTable.setHeaderStyle(TextReportTable::Broken, TextReportTable::Broken);
  totalTable.setColumnWidth(0, 49);
  totalTable.setColumnWidth(1, 20);
  totalTable.setColumnWidth(2, 11);

  totalTable.setColumnAlignment(2, TextReportTable::RIGHT);
  totalTable.insertRows(1);
  totalTable.setText(0, 1, "TOTAL COST");
  totalTable.setText(0, 2, recapTotal + chargeTotal);
  return totalTable;
}

double BuyerRecap::recapChargeTotal()
{
  double result = 0.000000001;

  for(unsigned int i = 0; i < recapCharges.size(); i++)
  {
    result += recapCharges[i].getTotal();
  }
  return result;
}
