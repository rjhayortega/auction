#include "brucellosistestrecord.h"

#include <cstdio>
BrucellosisTestRecord::BrucellosisTestRecord(HealthRecord _record) : healthRecord(_record) {}

string BrucellosisTestRecord::text()
{
  addTable(header());
  addTable(body());
  setPageHeader(header());
  return TextReport::text();
}

TextReportTable BrucellosisTestRecord::header()
{
  TextReportTable table(4);

  table.setColumnWidth(0, 30);
  table.setColumnWidth(1, 18);
  table.setColumnWidth(2, 35);
  table.setColumnWidth(3, 20);

  table.insertRows(10);

  table.setText(0, 1, healthRecord.getMarketAddress().getUnit(), true);
  table.setText(3, 0, healthRecord.getMarketAddress().getAddress1(), true);
  table.setText(4, 0, healthRecord.getMarketAddress().cityStateZipStr(), true);

  char buf[36];
  sprintf(buf, "%s %d", healthRecord.getVet().getName().getLast().c_str(), healthRecord.getVet().getId());

  table.setText(5, 2, buf);
  table.setText(6, 2, healthRecord.getVet().getAddress().cityStateZipStr());

  return table;
}

TextReportTable BrucellosisTestRecord::body()
{
  TextReportTable table(9);
  table.setColumnWidth(0, 4);
  table.setColumnWidth(1, 18);
  table.setColumnWidth(2, 14);
  table.setColumnWidth(3, 4);
  table.setColumnWidth(4, 3);
  table.setColumnWidth(5, 14);
  table.setColumnWidth(6, 6);
  table.setColumnWidth(7, 27);
  table.setColumnWidth(8, 17);

  unsigned int row = 0;

  for(unsigned int i = 0; i < healthRecord.size(); i++)
  {
    table.insertRows(2);
    table.setText(row, 1, healthRecord[i].getTag());
    table.setText(row, 2, healthRecord[i].getBurcellosisTag());
    table.setText(row, 3, healthRecord[i].getAge());
    table.setText(row, 4, healthRecord[i].getBreed());
    table.setText(row, 5, healthRecord[i].getSex());
    table.setText(row, 6, healthRecord[i].getBrucellosis());
    table.setText(row, 7, healthRecord[i].getTestDate().toString("mm/dd/YYYY") + Name::autoInitials(healthRecord.getSeller().formattedName()));
    table.setText(row, 8, healthRecord.getSeller().getAddress().cityStateZipStr());
    row += 2;
  }

  return table;
}
