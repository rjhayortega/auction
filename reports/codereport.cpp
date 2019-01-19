
#include "codereport.h"

CodeReport::CodeReport(vector<AnimalCode> codeList, CodeType codeType)
{
  this->codeList = codeList;
  this->codeType = codeType;
}

string CodeReport::text()
{
  clearTables();
  addTable(codeTable());

  return TextReport::text();
}


TextReportTable CodeReport::codeTable()
{
  unsigned int maxCode;

  switch(codeType)
  {
  case Color:
  case Flaw:
    maxCode = 99;
    break;

  case Sex:
    maxCode = 9;
    break;
  }
  TextReportTable table(2);
  table.setColumnWidth(0, 7);
  table.setColumnWidth(1, 72);
  table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::Broken);
  table.setFooterStyle(TextReportTable::NoHeader, TextReportTable::NoHeader);

  short code;
  string descrip;

  unsigned int row = 0;
  for(unsigned int i = 0; i < codeList.size(); i++)
  {

    switch(codeType)
    {
    case Color:
    default:
      code = codeList[i].getColor();
      descrip = codeList[i].getColorDescrip();
      break;

    case Sex:
      code = codeList[i].getType();
      descrip = codeList[i].getTypeDescrip();
      break;

    case Flaw:
      code = codeList[i].getFlaw();
      descrip = codeList[i].getFlawDescrip();
      break;
    };    

    if(code <= maxCode && descrip.length() > 0)
    {
      table.insertRows(1);
      table.setText(row, 0, long(code));
      table.setText(row, 1, descrip);
      row++;
    }
  }

  return table;
}
