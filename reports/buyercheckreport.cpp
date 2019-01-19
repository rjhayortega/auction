
#include "buyercheckreport.h"

BuyerCheckReport::BuyerCheckReport(BuyerRecord record)
{
  this->check = record.getCheck();
  this->commissionList = record.getCommissionList();
}

string BuyerCheckReport::text()
{
  clearTables();
  addTable(checkTable());
  addTable(detailTable());
  return TextReport::text();
}

TextReportTable BuyerCheckReport::checkTable()
{
  TextReportTable table(3);

  table.insertRows(2);

  table.setColumnWidth(0, 13);
  table.setColumnWidth(1, 11);
  table.setColumnWidth(2, 56);

  table.setColumnAlignment(0, TextReportTable::LEFT);
  table.setColumnAlignment(1, TextReportTable::RIGHT);
  table.setColumnAlignment(2, TextReportTable::RIGHT);

  table.setText(0, 0, "CHECK NUMBER:");
  table.setText(0, 1, check.getNumber());
  table.setText(0, 2, check.getDate().toString("mm/dd/YYYY"));

  return table;
}


TextReportTable BuyerCheckReport::detailTable()
{
  TextReportTable table(3);

  table.setColumnWidth(0,27);
  table.setColumnWidth(1, 41);
  table.setColumnWidth(2, 12);

  table.setColumnAlignment(0, TextReportTable::LEFT);
  table.setColumnAlignment(1, TextReportTable::LEFT);
  table.setColumnAlignment(2, TextReportTable::RIGHT);

  table.insertRows(commissionList.size());

  table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::Continuous);
  table.setFooterStyle(TextReportTable::Continuous, TextReportTable::NoHeader);

  table.setHeader(0, "BUYER");
  table.setHeader(1, "COMPANY");
  table.setHeader(2, "COMMISSION");

  for(unsigned int i = 0; i < commissionList.size(); i++)
  {
    table.setText(i, 0, commissionList[i].name);
    table.setText(i, 1, commissionList[i].company);
    table.setText(i, 2, commissionList[i].commission);
  }

  table.setFooter(0, "TOTAL COMMISSIONS:");
  table.setFooter(2, check.getAmount());
  return table;
}
