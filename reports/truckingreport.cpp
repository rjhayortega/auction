
#include "truckingreport.h"

TruckingReport::TruckingReport(vector<Invoice> sellerInvoiceList, vector<Invoice> buyerInvoiceList)
{
  this->sellerInvoiceList = sellerInvoiceList;
  this->buyerInvoiceList = buyerInvoiceList;

  invoiceList = NULL;
}

string TruckingReport::text()
{
  clearTables();

  invoiceList = NULL;
  if(sellerInvoiceList.size() > 0)
  {
    addTable(headerTable("Sellers"));
    invoiceList = &sellerInvoiceList;
    addTable(truckerTable());
  }

  invoiceList = NULL;
  if(buyerInvoiceList.size() > 0)
  {
    int size = 2;
    int firstRow = 0;

    if(sellerInvoiceList.size() > 0)
    {
      size = 4;
      firstRow = 2;
    }

    addTable(headerTable("Buyers", size, firstRow));
    invoiceList = &buyerInvoiceList;
    addTable(truckerTable());
  }

  return TextReport::text();
}

TextReportTable TruckingReport::truckerTable()
{
  TextReportTable table(3);
  table.setColumnWidth(0, 30);
  table.setColumnWidth(1, 10);
  table.setColumnWidth(2, 40);

  table.setColumnAlignment(0, TextReportTable::LEFT);
  table.setColumnAlignment(1, TextReportTable::RIGHT);
  table.setColumnAlignment(2, TextReportTable::CENTER);
  table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::Broken);
  table.setFooterStyle(TextReportTable::Broken, TextReportTable::NoHeader);

  table.setHeader(0, "Trucker");
  table.setHeader(1, "Amount");
  table.setHeader(2, "Consigner");
  double totalAmount = 0.00;
  vector<TruckingRecord> truckingList;
  vector<TruckingRecord> currentTruckingList;

  unsigned int row = 0;

  if(invoiceList == NULL)
  {
    return table;
  }

  for(unsigned int i = 0; i < invoiceList->size(); i++)
  {
      currentTruckingList = (*invoiceList)[i].getTruckingList();
      for(unsigned int j = 0; j < currentTruckingList.size(); j++)
      {
	currentTruckingList[j].setConsignerName((*invoiceList)[i].getCustomer().getName().getLast());
      }

      truckingList.insert(truckingList.end(), currentTruckingList.begin(), currentTruckingList.end());
  }

  sort(truckingList.begin(), truckingList.end(), TruckingRecord::compareTruckerNamesLT);
  table.insertRows(truckingList.size());

  for(unsigned int i = 0; i < truckingList.size(); i++)
  {
      table.setText(row, 0, truckingList[i].getTruckerName());
      table.setText(row, 1, truckingList[i].amount());
      totalAmount += truckingList[i].amount();
      table.setText(row, 2, truckingList[i].getConsignerName());
      row++;
  }     
  

  table.setFooter(0, "Total =");
  table.setFooter(1, totalAmount);
  return table;
}

TextReportTable TruckingReport::headerTable(string customerLabel, int size, int firstRow)
{
  TextReportTable table(1);

  table.insertRows(size);
  table.setColumnWidth(0, 79);
  table.setColumnAlignment(0, TextReportTable::CENTER);

  string headerString = string("Trucking Report For: " + customerLabel + " ");

  table.setText(firstRow, 0, headerString);
  table.setText(firstRow + 1, 0, string(headerString.size(), '-'));

  return table;
}
