
#include "discrepancyreport.h"

 DiscrepancyReport::DiscrepancyReport(vector<string> unprintedBuyers, vector<string> unprintedSellers, 
                                      vector<InvoiceDAO::DISCREPANCY> buyerDiscreps, vector<InvoiceDAO::DISCREPANCY> sellerDiscreps)
{
  unprintedSellerList = unprintedSellers;
  unprintedBuyerList = unprintedBuyers;
  sellerDiscrepancyList = sellerDiscreps;
  buyerDiscrepancyList = buyerDiscreps;
}


string DiscrepancyReport::text()
{
  clearTables();

  TextReportTable headerTable(1);
  headerTable.insertRows(1);

  headerTable.setText(0, 0, "Unprinted Sellers");
  addTable(headerTable);
  addTable(unprintedSellersTable());


  headerTable.setText(0,0,"Unprinted Buyers");
  addTable(headerTable);
  addTable(unprintedBuyersTable());

  headerTable.setText(0,0,"Seller Invoice Discrepancies");
  addTable(headerTable);
  addTable(sellerDiscrepancyTable());

  headerTable.setText(0,0,"Buyer Invoice Discrepancies");
  addTable(headerTable);
  addTable(buyerDiscrepancyTable());
  return TextReport::text();
}

TextReportTable DiscrepancyReport::unprintedSellersTable()
{
  TextReportTable table(7);
  table.insertRows(unprintedSellerList.size() / 7 + 2);

  unsigned int col = 0;
  unsigned int row = 0;
  for(unsigned int i = 0; i < unprintedSellerList.size(); i++)
  {
    table.setText(row, col, unprintedSellerList[i]);

    col++;

    if(col == 7)
    {
      row++;
      col = 0;
    }
  }
  return table;
}

TextReportTable DiscrepancyReport::unprintedBuyersTable()
{
  TextReportTable table(7);
  table.insertRows(unprintedBuyerList.size() / 7 + 2);

  unsigned int col = 0;
  unsigned int row = 0;
  for(unsigned int i = 0; i < unprintedBuyerList.size(); i++)
  {
    table.setText(row, col, unprintedBuyerList[i]);
    
    col++;

    if(col == 7)
    {
      row++;
      col = 0;
    }
  }
  return table;
}

TextReportTable DiscrepancyReport::sellerDiscrepancyTable()
{
  TextReportTable table = getDiscrepancyTable(sellerDiscrepancyList);
  return table;
}

TextReportTable DiscrepancyReport::buyerDiscrepancyTable()
{
  TextReportTable table = getDiscrepancyTable(buyerDiscrepancyList);
  return table;
}

TextReportTable DiscrepancyReport::getDiscrepancyTable(vector<InvoiceDAO::DISCREPANCY> list)
{
  TextReportTable table(4);
  table.insertRows(2);

  table.setHeader(0, "Customer ID");
  table.setHeader(1, "Original");
  table.setHeader(2, "Recalculated");
  table.setHeader(3, "Difference");

  table.setColumnAlignment(0, TextReportTable::RIGHT);
  table.setColumnAlignment(1, TextReportTable::RIGHT);
  table.setColumnAlignment(2, TextReportTable::RIGHT);
  table.setColumnAlignment(3, TextReportTable::RIGHT);

  table.setHeaderStyle(TextReportTable::Broken, TextReportTable::Broken);
  char orig[30], recalc[30], diff[30];
  char buf[80];
  unsigned int row = 0;
  for(unsigned int i = 0; i < list.size(); i++)
  {   
    if(list[i].checkDiscrep)
    {
      table.insertRows(1);
      sprintf(buf, "net invoice for seller #: %s differs from total of checks for seller", list[i].customer.c_str());
      table.setText(row, 0, buf, true);
      row++;
    }
    else
    {

      if(list[i].originalHead != list[i].recalculatedHead)
      {
	table.insertRows(1);
	char orig[20], recalc[20];
	sprintf(orig, "%ld", list[i].originalHead);
	sprintf(recalc, "%ld", list[i].recalculatedHead);

	table.setText(row, 0, string("Head mismatch, invoice: ") + list[i].customer + " printed with: " + string(orig) + " head, but now has: " + string(recalc) + " head", true); 
	row++;
      }

      double calcDiff = list[i].originalValue - list[i].recalculatedValue;

      if(calcDiff <= -0.0100000001 || calcDiff >= 0.0100000001)
      {
        table.insertRows(1);
        sprintf(orig,   "%0.2f", list[i].originalValue);
        sprintf(recalc, "%0.2f", list[i].recalculatedValue);
        sprintf(diff,   "%0.2f", list[i].originalValue - list[i].recalculatedValue);

        table.setText(row, 0, list[i].customer);
        table.setText(row, 1,         orig);
        table.setText(row, 2,         recalc);
        table.setText(row, 3,         diff);
        row++;
      }
    }
  }

  return table;
}

