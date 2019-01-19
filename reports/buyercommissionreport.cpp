
#include "buyercommissionreport.h"

BuyerCommissionReport::BuyerCommissionReport(vector<BuyerInvoice> invoiceList)
{
  this->invoiceList = invoiceList;
}

string BuyerCommissionReport::text()
{
  clearTables();
  addTable(buyerTable());
  return TextReport::text();
}

bool BuyerCommissionReport::compareInvoiceNamesLT(BuyerInvoice a, BuyerInvoice b)
{
  return a.getCustomer().getName().getLast() < b.getCustomer().getName().getLast();
}

TextReportTable BuyerCommissionReport::buyerTable()
{
  TextReportTable table(4);

  table.setColumnWidth(3, 15);
  table.setColumnWidth(2, 10);
  table.setColumnWidth(1, 30);
  table.setColumnWidth(0, 25);

  table.setColumnAlignment(0, TextReportTable::LEFT);
  table.setColumnAlignment(1, TextReportTable::LEFT);
  table.setColumnAlignment(2, TextReportTable::RIGHT);
  table.setColumnAlignment(3, TextReportTable::RIGHT);

  table.setHeader(0, "BUYER");
  table.setHeader(1, "COMPANY");
  table.setHeader(2, "WEIGHT");
  table.setHeader(3, "COMMISSION");

  double subTotal = 0.0000;
  double grandTotal = 0.0000;

  bool summarize = false;
  unsigned int row = 0;

  for(unsigned int i = 0; i < invoiceList.size(); i++)
  {
    if(i < invoiceList.size() - 1)
    {
      summarize = (invoiceList[i].getCustomer().getName().getLast() != invoiceList[i + 1].getCustomer().getName().getLast());
    }
    else 
    {
      summarize = true;
    }

    table.insertRows(2);

    table.setText(row, 0, invoiceList[i].getCustomer().getName().getLast());
    table.setText(row, 1, invoiceList[i].getCustomer().getCompany());
    table.setText(row, 2, invoiceList[i].weight());
    table.setText(row, 3, invoiceList[i].getCommissionTotal());
    table.setText(row + 1, 0, invoiceList[i].getCustomer().getAddress().cityStateZipStr(), true);
    row += 2;

    subTotal += invoiceList[i].getCommissionTotal();

    if(summarize)
    {
      table.insertRows(3);
      table.setText(row, 0, string(80, '-'), true);
      table.setText(row + 1, 0, "SUBTOTAL FOR " + invoiceList[i].getCustomer().getName().getLast(), true);
      table.setText(row + 1, 3, subTotal);
      grandTotal += subTotal;
      subTotal = 0.00000;
      row += 3;
    }
  }

  table.setFooter(0, "GRAND TOTAL BUYER COMMISSION", true);
  table.setFooter(3, grandTotal);
  return table;
}
