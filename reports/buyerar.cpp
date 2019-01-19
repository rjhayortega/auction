
#include "buyerar.h"

BuyerAR::BuyerAR(vector<Record> recordList, bool detailed, SortOption sortOption)
{
  this->recordList = recordList;
  this->detailed = detailed;
  this->sortOption = sortOption;
}

string BuyerAR::text()
{
  clearTables();

  if(detailed)
  {
    addTable(detailedARTable());
  }
  else 
  {

    addTable(simpleARTable());
  }
  addTable(totalTable());
  return TextReport::text();
}

void BuyerAR::initTable(TextReportTable& table)
{
  table = TextReportTable(5);

  table.setColumnWidth(0,7);
  table.setColumnWidth(1, 37);
  table.setColumnWidth(2, 12);
  table.setColumnWidth(3, 12);
  table.setColumnWidth(4, 12);

  table.setColumnAlignment(0, TextReportTable::LEFT);
  table.setColumnAlignment(1, TextReportTable::LEFT);
  table.setColumnAlignment(2, TextReportTable::RIGHT);
  table.setColumnAlignment(3, TextReportTable::RIGHT);
  table.setColumnAlignment(4, TextReportTable::RIGHT);

  table.setHeader(0, "Number");
  table.setHeader(1, "Name");
  table.setHeader(2, "Paid");
  table.setHeader(3, "Company");
  table.setHeader(4, "Bal Due");

  table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::Broken);
  table.setFooterStyle(TextReportTable::NoHeader, TextReportTable::NoHeader);
}

TextReportTable BuyerAR::detailedARTable()
{
  switch(sortOption)
  {
  case NameSort:
  default:
    sort(recordList.begin(), recordList.end(), Record::compareName);
    break;

  case NumberSort:
    sort(recordList.begin(), recordList.end(), Record::compareId);
    break;
  }

  TextReportTable table;
  initTable(table);
  table.insertRows(recordList.size());

  paidTotal = 0.0;
  companyTotal = 0.0;
  unpaidTotal = 0.0;
  unprintedTotal = 0.00;

  unsigned int statusColumn = 0;

  for(unsigned int i = 0; i < recordList.size(); i++)
  {
    table.setText(i, 0, recordList[i].number + (recordList[i].printed ? "" : "*"));
    string nameString = recordList[i].name;

    if(nameString.length() > 20)
    {
      nameString = nameString.substr(0, 20);
    }

    nameString = nameString + string(21 - nameString.length(), ' ');

    table.setText(i, 1, nameString + recordList[i].company);
     unsigned int statusColumn;

    switch(recordList[i].status)
    {
    case Invoice::PAID:
      statusColumn = 2;
      paidTotal += recordList[i].amount;
      break;


    case Invoice::BILLED:
      statusColumn = 3;
      companyTotal += recordList[i].amount;
      break;

    case Invoice::UNPAID:
    default:
      statusColumn = 4;
      if(recordList[i].printed)
      {
	unpaidTotal += recordList[i].amount;
      }
      else 
      {
	unprintedTotal += recordList[i].amount;
      }
      break;
    }

    if(recordList[i].amount > 0.00)
    {
      table.setText(i, statusColumn, recordList[i].amount);
    }
    else
    {
      table.setText(i, statusColumn, "");
    }
  }


  return table;
}

TextReportTable BuyerAR::simpleARTable()
{
  sort(recordList.begin(), recordList.end(), Record::compareName);

  TextReportTable table;
  initTable(table);
//  table.insertRows(recordList.size());

  paidTotal = companyTotal = unpaidTotal = unprintedTotal = 0.00;
  double paidGross = 0.00, companyGross = 0.00, unpaidGross=0.00;

  unsigned int row = 0;

  for(unsigned int i = 0; i < recordList.size(); i++)
  {
    switch(recordList[i].status)
    {
    case Invoice::PAID:
      paidTotal += recordList[i].amount;
      paidGross += recordList[i].amount;
      break;

    case Invoice::BILLED:
      companyTotal += recordList[i].amount;
      companyGross += recordList[i].amount;
      break;

    case Invoice::UNPAID:

      if(recordList[i].printed)
      {
	unpaidTotal += recordList[i].amount;
      }
      else
      {
	unprintedTotal += recordList[i].amount;
      }
      unpaidGross += recordList[i].amount;
      break;
    }

    if(i == recordList.size() - 1 || !Record::compareNameEQ(recordList[i + 1], recordList[i]))
    {
      table.insertRows(1);
      table.setText(row, 0, (recordList[i].printed ? "" : "*"));
      table.setText(row, 1, recordList[i].name);

      if(paidGross != 0.00)
      {
          table.setText(row, 2, paidGross);
      }

      if(companyGross != 0.00)
      {
          table.setText(row, 3, companyGross);
      }

      if(unpaidGross != 0.00)
      {
	table.setText(row, 4, unpaidGross);
      }

      paidGross = companyGross = unpaidGross = 0.00;
      row++;
    }
  }

  return table;
}


TextReportTable BuyerAR::totalTable()
{
  TextReportTable table;
  initTable(table);

  table.setHeader(0, "");
  table.setHeader(1, "");
  table.setHeader(2, " ");
  table.setHeader(3, " ");
  table.setHeader(4, " ");

  table.setColumnAlignment(1, TextReportTable::RIGHT);
  table.insertRows(3);
 
  table.setText(0, 1, "Total Printed:");
  table.setText(0, 2, paidTotal);
  table.setText(0, 3, companyTotal);
  table.setText(0, 4, unpaidTotal);
  table.setText(1, 1, "Unprinted:");
  table.setText(1, 4, unprintedTotal);
  table.setText(2, 1, "Total: ");
  table.setText(2, 4, paidTotal + companyTotal + unpaidTotal + unprintedTotal);
  return table; 
}
