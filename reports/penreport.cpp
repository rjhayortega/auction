
#include "penreport.h"

PenReport::PenReport(vector<PenReport::Item> penItemList, SortOption sortOption)
{
  this->penItemList = penItemList;
  this->sortOption = sortOption;
}

string PenReport::text()
{
  clearTables();
  addTable(penTable());
  return TextReport::text();
}

TextReportTable PenReport::penTable()
{
  switch(sortOption)
  {
  case SortByPen:
  default:
    sort(penItemList.begin(), penItemList.end(), Item::comparePenLT);
    break;
  
  case SortByNumber:
    sort(penItemList.begin(), penItemList.end(), Item::compareBuyerNumberLT);
    break;
  }

  int baseRow = 0;

//  for(unsigned int i = 1; i < penItemList.size(); i++)
//  {

//     if(penItemList[baseRow].pen == penItemList[i].pen)
//     {
//       penItemList[baseRow].head += penItemList[i].head;
//       penItemList[i].head = 0;
//       penItemList[i].pen = "";
//     }
//     else
//     {
//       if(penItemList[i].pen == "")
//       {
// 	penItemList[i].pen == "NO PEN";
//       }

//       baseRow = i;
//     }
//  }

  TextReportTable table(7);

  table.setColumnWidth(0, 14);
  table.setColumnWidth(1, 24);
  table.setColumnWidth(2, 8);
  table.setColumnWidth(3, 8);
  table.setColumnWidth(4, 8);
  table.setColumnWidth(5, 9);
  table.setColumnWidth(6, 8);

  table.setColumnAlignment(0, TextReportTable::LEFT);
  table.setColumnAlignment(1, TextReportTable::LEFT);
  table.setColumnAlignment(2, TextReportTable::RIGHT);
  table.setColumnAlignment(3, TextReportTable::RIGHT);
  table.setColumnAlignment(4, TextReportTable::RIGHT);
  table.setColumnAlignment(5, TextReportTable::RIGHT);
  table.setColumnAlignment(6, TextReportTable::RIGHT);

  table.setHeader(0, "Buyer Number");
  table.setHeader(1, "Buyer");
  table.setHeader(2, "Pen");
  table.setHeader(3, "Head");
//  table.setHeader(4, "No Sale");
  table.setHeader(5, "Weight");
  table.setHeader(6, "Avg Wgt");

  table.insertRows(penItemList.size());

  table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::Broken);

  for(unsigned int i = 0; i < penItemList.size(); i++)
  {
    table.setText(i, 0, penItemList[i].buyerId);
    table.setText(i, 1, penItemList[i].buyerName);
    table.setText(i, 2, penItemList[i].pen);
    table.setText(i, 3, penItemList[i].head);
//    table.setText(i, 4, penItemList[i].noSaleCount);
    table.setText(i, 5, penItemList[i].weight);
    table.setText(i, 6, long((penItemList[i].head > 0 ? getWeightAmount(penItemList[i].weight / penItemList[i].head) : 0)));
  }

  return table;
}

