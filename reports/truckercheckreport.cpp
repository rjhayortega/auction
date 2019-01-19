
#include "truckercheckreport.h"

#include <cstdio>

TruckerCheckReport::TruckerCheckReport(TruckerRecord record)
{
  this->check = record.getCheck();
  this->truckerList = record.getRecordList();
}

string TruckerCheckReport::text()
{
  clearTables();
  addTable(checkTable());
  addTable(detailTable());
  return TextReport::text();
}

TextReportTable TruckerCheckReport::checkTable()
{
  TextReportTable table(6);
  table.insertRows(2);
  table.setColumnWidth(0, 6);
  table.setColumnWidth(1, 13);
  table.setColumnWidth(2, 9);
  table.setColumnWidth(3, 10);
  table.setColumnWidth(4, 9);
  table.setColumnWidth(5, 33);


  table.setText(0, 0, "Date:");
  table.setText(0, 1, check.getDate().toString("mm/dd/YYYY"));
  table.setText(0, 2, "Check #:");
  table.setText(0, 3, check.getNumber());
  table.setText(0, 4, "Trucker: ");
  table.setText(0, 5, check.getPayee());

  return table;
}


TextReportTable TruckerCheckReport::detailTable()
{
  TextReportTable table(7);

  table.setColumnWidth(0, 23);
  table.setColumnWidth(1, 4);
  table.setColumnWidth(2, 10);
  table.setColumnWidth(3, 10);
  table.setColumnWidth(4, 11);
  table.setColumnWidth(5, 1);
  table.setColumnWidth(6, 1);

  table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::Broken);
  table.setFooterStyle(TextReportTable::Continuous, TextReportTable::NoHeader);

  table.setHeader(0, "Customer #/Name");
  table.setHeader(1, "Type");
  table.setHeader(2, "Qty");
  table.setHeader(3, "Charge");
  table.setHeader(4, "Subtotal");

  table.setColumnAlignment(0, TextReportTable::LEFT);
  table.setColumnAlignment(1, TextReportTable::LEFT);
  table.setColumnAlignment(2, TextReportTable::RIGHT);
  table.setColumnAlignment(3, TextReportTable::RIGHT);
  table.setColumnAlignment(4, TextReportTable::RIGHT);
  table.setColumnAlignment(5, TextReportTable::RIGHT);
  table.setColumnAlignment(6, TextReportTable::RIGHT);

  string modeStr;
  double amount, amountTotal = 0.000, cwtTotal = 0.000;
  long headTotal = 0;
  table.insertRows(truckerList.size());
  for(unsigned int i = 0; i < truckerList.size(); i++)
  {
    table.setText(i, 0, truckerList[i].customerId + "/" + truckerList[i].customerName);
    switch(truckerList[i].record.getMode())
    {
    case TruckingRecord::Flat:
      modeStr = "Flat";
      break;

    case TruckingRecord::ByHundredWeight:
      modeStr = "CWT";
      cwtTotal += truckerList[i].cwt;
      break;

    case TruckingRecord::ByHead:
      modeStr = "Head";
      headTotal += truckerList[i].record.getQuantity();
      break;

    case TruckingRecord::ByMile:
      modeStr = "Mile";
      break;

    case TruckingRecord::Other:
      modeStr = "MISC";
      break;
    }

    table.setText(i, 1, modeStr);
    table.setText(i, 2, truckerList[i].record.getQuantity());
    table.setText(i, 3, truckerList[i].record.getPrice());
    amount = truckerList[i].record.amount();
    amountTotal += amount;
    table.setText(i, 4, amount);
  }

  char buf[9];
  sprintf(buf, "%8d", headTotal);

  table.setFooter(0, string("Head:") +  string(buf) + string("  CWT:"));
  table.setFooter(1, cwtTotal, true);
  table.setFooter(3, "Amount: ");
  table.setFooter(4, amountTotal);
  return table;
}
