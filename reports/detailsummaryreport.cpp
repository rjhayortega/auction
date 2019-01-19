
#include "detailsummaryreport.h"

#include <cstdio>

DetailSummaryReport::DetailSummaryReport(vector<InvoiceSummaryRecord> recordList, bool isSeller)
{
  this->recordList = recordList;
  this->isSeller = isSeller;
}

string DetailSummaryReport::text()
{
  clearTables();
  addTable(extraHeaderTable());
  addTable(summaryTable());
  return TextReport::text();
}

TextReportTable DetailSummaryReport::extraHeaderTable()
{
  TextReportTable table(1);

  table.insertRows(1);
  table.setColumnWidth(0, 80);
  table.setText(0, 0, "NUMBER    NAME");

  return table;
}

TextReportTable DetailSummaryReport::summaryTable()
{
  char lineBuf[15];

  createTableMap();
  unsigned int numCols = tableMap.size() + 3 + (isSeller ? 1 : 0);
  TextReportTable table(numCols);

  table.setColumnWidth(0, 5);
  table.setColumnWidth(1, 10);
  table.setColumnWidth(2, 10);

  table.setHeader(0, "HEAD");
  table.setHeader(1, "NET");
  table.setHeader(2, "GROSS");

  if(numCols > 3)
  {
    table.setHeader(3, "COMM");
    table.setHeader(4, "TRKNG");
  }

  table.setColumnAlignment(0, TextReportTable::RIGHT);
  table.setColumnAlignment(1, TextReportTable::RIGHT);
  table.setColumnAlignment(2, TextReportTable::RIGHT);

  table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::Broken);

  vector<ChargeSummaryRecord> chargeList;
  char buf[20];

  for(unsigned int i = 3; i < numCols - (isSeller ? 1 : 0); i++)
  {
    table.setColumnWidth(i, 8);
    table.setColumnAlignment(i, TextReportTable::RIGHT);

    if(i > 4)
    {
      sprintf(buf, "%d", i -2);
      table.setHeader(i, tableMap[i - 3].getChargeDescription().substr(0, 6));
    }
  }
 
  if(isSeller)
  {
    table.setColumnWidth(numCols - 1, 8);
    table.setColumnAlignment(numCols - 1, TextReportTable::RIGHT);
    table.setHeader(numCols - 1, "Check#");
  }

  unsigned int row = 0;

  for(unsigned int i = 0; i < recordList.size(); i++)
  {
    table.insertRows(2);
    table.setText(row, 0, recordList[i].getCustomerNumber() + string(10 - recordList[i].getCustomerNumber().length(), ' ') + recordList[i].getCustomerName(), true);

    table.setText(row + 1, 0, recordList[i].getHead());
    table.setText(row + 1, 1, recordList[i].getNet(isSeller));
    table.setText(row + 1, 2, recordList[i].getGross());

    chargeList = recordList[i].getChargeSummaryList();

    for(unsigned int j = 0; j < chargeList.size(); j++)
    {
      table.setText(row + 1, getChargeColumn(chargeList[j]), chargeList[j].getChargeTotal());
    }

    if(isSeller)
    {
      string checkNoStr;
      vector<string> checkNoList = recordList[i].getCheckNumberList();
      switch(checkNoList.size())
      {
      case 0:
	checkNoStr = "";
	break;

      case 1:
	checkNoStr = checkNoList[0];
	break;

      default:
	checkNoStr = string("*") + checkNoList[0];
	break;
      }

      table.setText(row + 1, numCols -1, checkNoStr);
    }

    row += 2;
  }

  return table;
}

void DetailSummaryReport::createTableMap()
{
  vector<ChargeSummaryRecord> tempList;

  for(unsigned int i = 0; i < recordList.size(); i++)
  {
    tempList = recordList[i].getChargeSummaryList();

    for(unsigned int j = 0; j < tempList.size(); j++)
    {
      if(find(tableMap.begin(), tableMap.end(), tempList[j]) == tableMap.end())
      {
	tableMap.push_back(tempList[j]);
      }
    }
  }

  sort(tableMap.begin(), tableMap.end(), ChargeSummaryRecord::compareIdsLT);
}

unsigned int DetailSummaryReport::getChargeColumn(ChargeSummaryRecord record)
{
  if(record.getChargeId() == 0)
  {
    return 3;
  }

  if(record.getChargeId() == -1)
  {
    return 4;
  }

  for(unsigned int i = 0; i < tableMap.size(); i++)
  {
    if(tableMap[i] == record)
    {
      return i + 3;
    }
  }
}
