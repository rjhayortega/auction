#include "southdakotahealthcertificate.h"

SouthDakotaHealthCertificate::SouthDakotaHealthCertificate(HealthRecord _record) : healthRecord(_record) {}

string SouthDakotaHealthCertificate::text()
{
  addTable(headerTable());
  addTable(body());
  addTable(footer());
  return TextReport::text();
}


TextReportTable SouthDakotaHealthCertificate::headerTable()
{
  TextReportTable table(4);
  table.setColumnWidth(0, 9);
  table.setColumnWidth(1, 40);
  table.setColumnWidth(2, 44);
  table.setColumnWidth(3, 15);

  table.insertRows(16);

  string sellerAddressString;

  sellerAddressString = 
    "" + healthRecord.getSeller().getAddress().getAddress1() + "-"
    "" + healthRecord.getSeller().getAddress().getCity() + ","
    "" + healthRecord.getSeller().getAddress().getCounty() + "";

  table.setText(0, 1, healthRecord.getSeller().formattedName(), true);
  table.setText(1, 1, sellerAddressString, true);

  string buyerAddressString = 
    "" + healthRecord.getBuyer().getAddress().getAddress1() + "-"
    "" + healthRecord.getBuyer().getAddress().getCity() + ","
    "" + healthRecord.getBuyer().getAddress().getState() + "";

  table.setText(0, 2, healthRecord.getBuyer().formattedName());
  table.setText(1, 2, buyerAddressString);

  table.setText(0, 3, "OFFICE");
  table.setText(1, 3, Date::currentDate().toString("mm-dd-YYYY"));

  return table;
}

TextReportTable SouthDakotaHealthCertificate::body()
{
  TextReportTable table(8);
  table.setColumnWidth(0, 9);
  table.setColumnWidth(1, 22);
  table.setColumnWidth(2, 17);
  table.setColumnWidth(3, 4);
  table.setColumnWidth(4, 2);
  table.setColumnWidth(5, 17);
  table.setColumnWidth(6, 20);
  table.setColumnWidth(7, 10);

  table.insertRows(20);

  for(unsigned int i = 0; i < healthRecord.size() && i < 20; i++)
  {
    table.setText(i, 1, healthRecord[i].getTag());
    table.setText(i, 2, healthRecord[i].getBurcellosisTag());
    table.setText(i, 3, healthRecord[i].getAge());
    table.setText(i, 4, string(1, healthRecord[i].getSex()));
    table.setText(i, 5, healthRecord[i].getBreed());
    table.setText(i, 6, "NO TEST REQUIRED");
    table.setText(i, 7, healthRecord[i].getVaccination());
  }

  return table;
}

TextReportTable SouthDakotaHealthCertificate::footer()
{
  TextReportTable table(3);

  table.setColumnWidth(0, 75);
  table.setColumnWidth(1, 20);
  table.setColumnWidth(2, 10);

  table.insertRows(6);

  table.setText(3, 1, vet.getAddress().getAddress1());
  table.setText(4, 1, vet.getAddress().cityStateZipStr());
  table.setText(5, 1, vet.getContactList().getFirstPhone());
  table.setText(1, 2, Date::currentDate().toString("mm-dd-YYYY"));

  return table;
}
