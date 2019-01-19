
#include "summaryreport.h"

SummaryReport::SummaryReport(InvoiceDAO::SUMMARY buyerSummary,  vector<ChargeDAO::SUMMARY_ITEM> buyerChargeSummary, bool groupBuyerCharges, 
                             InvoiceDAO::SUMMARY sellerSummary, vector<ChargeDAO::SUMMARY_ITEM> sellerChargeSummary, bool groupSellerCharges)
{
  setHeader(TextReportHeader("Summary Report"));
  setBuyerSummary(buyerSummary);
  setBuyerChargeSummary(buyerChargeSummary);
  setSellerSummary(sellerSummary);
  setSellerChargeSummary(sellerChargeSummary);

  this->groupBuyerCharges = groupBuyerCharges;
  this->groupSellerCharges = groupSellerCharges;
}

void SummaryReport::setBuyerSummary(InvoiceDAO::SUMMARY summary)
{
  buyerSummary.head = summary.head;
  buyerSummary.total = summary.total;
  buyerSummary.noSaleHead = summary.noSaleHead;

//  // [KLN] debug
//  cout << "BuyerSummary --" << endl;
//  cout << "        head: " << summary.head << endl;
//  cout << "       total: " << summary.total << endl;
//  cout << "  noSaleHead: " << summary.noSaleHead << endl << endl;
//  // [KLN] debug end
}

void SummaryReport::setBuyerChargeSummary(vector<ChargeDAO::SUMMARY_ITEM> buyerChargeSummary)
{
  this->buyerChargeSummary = buyerChargeSummary;
}

void SummaryReport::setSellerChargeSummary(vector<ChargeDAO::SUMMARY_ITEM> sellerChargeSummary)
{
  this->sellerChargeSummary = sellerChargeSummary;
}

void SummaryReport::setSellerSummary(InvoiceDAO::SUMMARY summary)
{
  sellerSummary.head = summary.head;
  sellerSummary.total = summary.total;
  sellerSummary.noSaleHead = summary.noSaleHead;
//  // [KLN] debug
//  cout << "sellerSummary --" << endl;
//  cout << "        head: " << summary.head << endl;
//  cout << "       total: " << summary.total << endl;
//  cout << "  noSaleHead: " << summary.noSaleHead << endl << endl;
//  // [KLN] debug end
}

string SummaryReport::reportText()
{
  TextReportTable summaryTable(5);

  char head[20];
  char total[30];

  sprintf(total, "%0.2f", buyerSummary.total);


  summaryTable.setColumnWidth(0, 25);
  summaryTable.setColumnWidth(1, 10);
  summaryTable.setColumnWidth(2, 10);
  summaryTable.setColumnWidth(3, 25);
  summaryTable.setColumnWidth(4, 10);

  summaryTable.setHeader(0, "Buyer");
  summaryTable.setHeader(1, " ");
  summaryTable.setHeader(3, "Seller");
  summaryTable.setHeader(4, " ");

  summaryTable.setHeaderStyle(TextReportTable::ContinuousBroken, TextReportTable::ContinuousBroken);
  summaryTable.setColumnAlignment(0, TextReportTable::RIGHT);
  summaryTable.setColumnAlignment(1, TextReportTable::RIGHT);
  summaryTable.setColumnAlignment(2, TextReportTable::RIGHT);
  summaryTable.setColumnAlignment(3, TextReportTable::RIGHT);
  summaryTable.setColumnAlignment(4, TextReportTable::RIGHT);


  sort(buyerChargeSummary.begin(), buyerChargeSummary.end(), compareChargeIdsLT);
  sort(sellerChargeSummary.begin(), sellerChargeSummary.end(), compareChargeIdsLT);

  if(groupSellerCharges)
  {
    shrinkChargeSummary(sellerChargeSummary);
  }

  if(groupBuyerCharges)
  {
    shrinkChargeSummary(buyerChargeSummary);
  }

  unsigned int chgSummLen = (buyerChargeSummary.size() > sellerChargeSummary.size() ? buyerChargeSummary.size() : sellerChargeSummary.size());

  summaryTable.insertRows(9 + chgSummLen);
  sprintf(head, "%ld", buyerSummary.head);
  summaryTable.setText(0, 0, "Total Head Count: " + string(25 - strlen("Total Head Count: "), '.'));
  summaryTable.setText(0, 1, head);

  sprintf(head, "%d", sellerSummary.head);
  summaryTable.setText(0, 3,  "Total Head Count: " + string(25 - strlen("Total Head Count: "), '.'));
  summaryTable.setText(0, 4, head);

// no such thing as buyer no sale
//   summaryTable.setText(1, 0,  "Total No Sale Hd: " + string(25 - strlen("Total No Sale Hd: "), '.'));
//   summaryTable.setText(1, 1, buyerSummary.noSaleHead);


  summaryTable.setText(1, 3,  "Total No Sale Hd: " + string(25 - strlen("Total No Sale Hd: "), '.'));
  summaryTable.setText(1, 4, sellerSummary.noSaleHead);

  sprintf(total, "%0.2f", buyerSummary.total);
  summaryTable.setText(2, 0, "Total Bought: " + string(25 - strlen("Total Bought: "), '.'));
  summaryTable.setText(2, 1, total);

  sprintf(total, "%0.2f", sellerSummary.total);
  summaryTable.setText(2, 3, "Total Sales: " + string(25 - strlen("Total Sales: "), '.'));
  summaryTable.setText(2, 4, total);

  char buf[30];
  double buyerChargeTotal = 0.0;
  double sellerChargeTotal = 0.0;

  for(unsigned int i = 0; i < chgSummLen; i++)
  {
    if(i < buyerChargeSummary.size())
    {
      sprintf(buf, "%0.2f", buyerChargeSummary[i].total);
      summaryTable.setText(3 + i, 0, buyerChargeSummary[i].descrip);
      summaryTable.setText(3 + i, 1, buf);
      buyerChargeTotal += buyerChargeSummary[i].total;
    }

    if(i < sellerChargeSummary.size())
    {
      sprintf(buf, "%0.2f", sellerChargeSummary[i].total);
      summaryTable.setText(3 + i, 3, sellerChargeSummary[i].descrip);
      summaryTable.setText(3 + i, 4, buf);
      sellerChargeTotal += sellerChargeSummary[i].total;
    }
  }

  sprintf(buf, "%0.2f", buyerChargeTotal);
  summaryTable.setText(4 + chgSummLen, 0, "Charges Sub-Total: " + string(25 - strlen("Charges Sub-Total: "), '.'));
  summaryTable.setText(4 + chgSummLen, 1, buf);

  sprintf(buf, "%0.2f", sellerChargeTotal);
  summaryTable.setText(4 + chgSummLen, 3, "Charges Sub-Total: " + string(25 - strlen("Charges Sub-Total: "), '.'));
  summaryTable.setText(4 + chgSummLen, 4, buf);

  sprintf(buf, "%0.2f", buyerSummary.total + buyerChargeTotal);
  summaryTable.setText(5 + chgSummLen, 0, "Total Reciepts" + string(25 - strlen("Total Reciepts"), '.'));
  summaryTable.setText(5 + chgSummLen, 1, buf);

  sprintf(buf, "%0.2f", sellerSummary.total - sellerChargeTotal);
  summaryTable.setText(5 + chgSummLen, 3, "Total Paid Out" + string(25 - strlen("Total Paid Out"), '.'));
  summaryTable.setText(5 + chgSummLen, 4, buf);

  clearTables();
  addTable(summaryTable);
  return text();
}

void SummaryReport::shrinkChargeSummary(vector<ChargeDAO::SUMMARY_ITEM>& chargeSummary)
{
  vector<ChargeDAO::SUMMARY_ITEM> tempSummary = chargeSummary;

  chargeSummary.clear();

  for(unsigned int i = 0; i < tempSummary.size(); i++)
  {
    if(i == 0)
    {
      chargeSummary.push_back(tempSummary[i]);
    }
    else
    {
      if(chargeSummary.back().descrip == tempSummary[i].descrip)
      {
	chargeSummary.back().total += tempSummary[i].total;
      }
      else 
      {
	chargeSummary.push_back(tempSummary[i]);
      }
    }
  }
}

bool SummaryReport::compareChargeIdsLT(ChargeDAO::SUMMARY_ITEM a, ChargeDAO::SUMMARY_ITEM b)
{
  return a.id < b.id;
}
