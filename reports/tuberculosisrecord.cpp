
#include "tuberculosisrecord.h"

#include <iostream>
using namespace std;

TuberculosisRecord::TuberculosisRecord(HealthRecord _record, Person _vet) : record(_record), vet(_vet)
{}

string TuberculosisRecord::text()
{
  addTable(recordHeader());
  addTable(recordBody());
  setPageHeader(recordHeader());
  return TextReport::text();
}

TextReportTable TuberculosisRecord::recordHeader()
{
  TextReportTable table(5);
  table.setColumnWidth(0, 12);
  table.setColumnWidth(1, 3);
  table.setColumnWidth(2, 32);
  table.setColumnWidth(3, 20);
  table.setColumnWidth(4, 9);

  table.setColumnAlignment(4, TextReportTable::RIGHT);
  table.insertRows(20);

  string phoneStr = vet.getContactList().getFirstPhone();

  if(phoneStr.length() > 29)
  {
    phoneStr = phoneStr.substr(0, 29);
  }

  if(phoneStr.length() < 29)
  {
    phoneStr = string(29 - phoneStr.length(), ' ') + phoneStr;
  }

  table.setText(0, 1, record.getSeller().getName().getLast(), true);
  table.setText(1, 1, record.getSeller().getAddress().getAddress1(), true);
  table.setText(2, 1, record.getSeller().getAddress().getAddress2(), true);
  table.setText(3, 1, record.getSeller().getAddress().cityStateZipStr(), true);
  table.setText(4, 0, record.getSeller().getAddress().getCounty());
  table.setText(5, 2, record.getSeller().getAddress().getCity());
  table.setText(6, 3, phoneStr, true);
  table.setText(7, 4, long(vet.getId()));
  table.setText(8, 3 , vet.getName().getLast());

  return table;
}

TextReportTable TuberculosisRecord::recordBody()
{
  TextReportTable table(6);

  table.setColumnWidth(0, 3);
  table.setColumnWidth(1, 15);
  table.setColumnWidth(2, 3);
  table.setColumnWidth(3, 4);
  table.setColumnWidth(4, 3);
  table.setColumnWidth(5, 20);

  table.insertRows(record.size() * 2);

  for(unsigned int i = 0; i < record.size(); i+=2)
  {
    table.setText(i, 1, record[i].getBurcellosisTag());
    table.setText(i, 2, long(record[i].getAge()));
    table.setText(i, 3, record[i].getBreed());
    table.setText(i, 4, string(1, record[i].getSex()));
    table.setText(i, 5, "NEG");
  }

  return table;
}
