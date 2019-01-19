
#include "minnesotavetcertificate.h"

MinnesotaVetCertificate::MinnesotaVetCertificate(HealthRecord _healthRecord) : healthRecord(_healthRecord) {}

string MinnesotaVetCertificate::text()
{
  TextReportTable customerTable = generateCustomerTable();
  addTable(customerTable);
  addTable(generateTagTable());
  setPageHeader(customerTable);

  return TextReport::text();
}


TextReportTable MinnesotaVetCertificate::generateCustomerTable()
{
  TextReportTable table(3);
  table.setColumnWidth(0, 40);
  table.setColumnWidth(1, 40);
  table.setColumnWidth(2, 40);

  table.insertRows(9);

  Seller seller = healthRecord.getSeller();
  Buyer buyer = healthRecord.getBuyer();

  table.setText(0, 0, seller.formattedName());
  table.setText(1, 0, seller.getAddress().getAddress1());
  table.setText(2, 0, seller.getAddress().cityStateZipStr());


  table.setText(0, 1, buyer.formattedName());
  table.setText(1, 1, buyer.getAddress().getAddress1());
  table.setText(2, 1, buyer.getAddress().cityStateZipStr());

  return table;
}

TextReportTable MinnesotaVetCertificate::generateTagTable()
{
  TextReportTable table(14);

  table.setColumnWidth(0, 15);
  table.setColumnWidth(1, 15);
  table.setColumnWidth(2, 4);
  table.setColumnWidth(3, 3);
  table.setColumnWidth(4, 4);
  table.setColumnWidth(5, 7);
  table.setColumnWidth(6, 6);
  table.setColumnWidth(7, 6);
  table.setColumnWidth(8, 6);
  table.setColumnWidth(9, 6);
  table.setColumnWidth(10, 6);
  table.setColumnWidth(11, 6);
  table.setColumnWidth(12, 6);

  table.insertRows(healthRecord.size());

  for(unsigned int i = 0; i < healthRecord.size(); i++)
  {
    table.setText(i, 0, healthRecord[i].getTag());
    table.setText(i, 1, healthRecord[i].getBurcellosisTag());
    table.setText(i, 2, long(healthRecord[i].getAge()));
    table.setText(i, 3, string(1, healthRecord[i].getSex()));
    table.setText(i, 4, healthRecord[i].getBreed());
    table.setText(i, 5, healthRecord[i].getVaccination());
    table.setText(i, 6, healthRecord[i].getBrucellosis());
    table.setText(i, 9, healthRecord[i].getTestDate().toString("mm/dd/YYYY"), true);
  }
  return table;
}
