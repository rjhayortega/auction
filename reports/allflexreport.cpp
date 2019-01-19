
#include "allflexreport.h"

AllFlexReport::AllFlexReport(vector<Seller> _sellerList) : sellerList(_sellerList) {}

string AllFlexReport::text()
{
  addTable(tagTable());

  return TextReport::text();
}

TextReportTable AllFlexReport::tagTable()
{
  TextReportTable table(14);

  table.setColumnWidth(0, 8);
  table.setColumnWidth(1, 10);
  table.setColumnWidth(2, 4);
  table.setColumnWidth(3, 6);
  table.setColumnWidth(4, 4);
  table.setColumnWidth(5, 4);
  table.setColumnWidth(6, 6);
  table.setColumnWidth(7, 12);
  table.setColumnWidth(8, 20);
  table.setColumnWidth(9, 20);
  table.setColumnWidth(10, 4);
  table.setColumnWidth(11, 8);
  table.setColumnWidth(12, 15);
  table.setColumnWidth(13, 12);

  table.setSurroundingText(string(1, char(15)), string(1, (18)));
  table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::Broken);

  table.setHeader(0, "ALLFLEX");
  table.setHeader(1, "RTMETAL");
  table.setHeader(2, "AGE");
  table.setHeader(3, "BREED");
  table.setHeader(4, "CHV");
  table.setHeader(5, "SX");
  table.setHeader(6, "BRUC");
  table.setHeader(7, "TESTDATE");
  table.setHeader(8, "OWNER");
  table.setHeader(9, "ADDRESS");
  table.setHeader(10, "ST");
  table.setHeader(11, "MOPG");
  table.setHeader(12, "COMMENTS");
  table.setHeader(13, "OLDTAG");

  vector<Tag> sellerTagList;

  int row = 0;

  for(unsigned int i = 0; i < sellerList.size(); i++)
  {
    sellerTagList = sellerList[i].getTagList();

    for(unsigned int j = 0; j < sellerTagList.size(); j++)
    {
      table.insertRows(1);
      table.setText(row, 0, sellerTagList[j].getTag());
      table.setText(row, 1, sellerTagList[j].getBurcellosisTag());
      table.setText(row, 2, long(sellerTagList[j].getAge()));
      table.setText(row, 3, sellerTagList[j].getBreed());
      table.setText(row, 4, sellerTagList[j].getVaccination());
      table.setText(row, 5, string(1, sellerTagList[j].getSex()));
      table.setText(row, 6, sellerTagList[j].getBrucellosis());
      table.setText(row, 7, sellerTagList[j].getTestDate().toString("mm/dd/YYYY"));
      table.setText(row, 8, sellerList[i].getName().getLast());
      table.setText(row, 9, sellerList[i].getAddress().getAddress1());
      table.setText(row, 10, sellerList[i].getAddress().getState());
      table.setText(row, 11, sellerTagList[j].getMonthsPreg());
      table.setText(row, 12, sellerTagList[j].getComment()); 
      table.setText(row, 13, sellerTagList[j].getOldTag());
      row++;
    }
  }

  return table;
}
