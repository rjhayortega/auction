
#include "transactionlist.h"

#include <cstdio>

TransactionList::TransactionList(vector<Transaction> transList)
{
  this->transactionList = transList;
}

string TransactionList::text()
{
  clearTables();
  addTable(transactionTable());
  return TextReport::text();
}

TextReportTable TransactionList::transactionTable()
{
  TextReportTable transTable(9);
  transTable.insertRows(transactionList.size());

  transTable.setColumnWidth(0, 6);
  transTable.setColumnWidth(1, 8);
  transTable.setColumnWidth(2, 8);
  transTable.setColumnWidth(3, 5);
  transTable.setColumnWidth(4, 7);
  transTable.setColumnWidth(5, 21);
  transTable.setColumnWidth(6, 7);
  transTable.setColumnWidth(7, 11);
  transTable.setColumnWidth(8, 7);

  transTable.setColumnAlignment(0, TextReportTable::RIGHT);
  transTable.setColumnAlignment(1, TextReportTable::RIGHT);
  transTable.setColumnAlignment(2, TextReportTable::RIGHT);
  transTable.setColumnAlignment(3, TextReportTable::RIGHT);
  transTable.setColumnAlignment(4, TextReportTable::RIGHT);
  transTable.setColumnAlignment(5, TextReportTable::CENTER);
  transTable.setColumnAlignment(6, TextReportTable::RIGHT);
  transTable.setColumnAlignment(7, TextReportTable::RIGHT);
  transTable.setColumnAlignment(8, TextReportTable::CENTER);

  transTable.setHeader(0, "Trans.");
  transTable.setHeader(1, "Seller");
  transTable.setHeader(2, "Buyer");
  transTable.setHeader(3, "Head");
  transTable.setHeader(4, "Weight");
  transTable.setHeader(5, "Description");
  transTable.setHeader(6, "Price");
  transTable.setHeader(7, "Amount");
  transTable.setHeader(8, "Mode");

  transTable.setHeaderStyle(TextReportTable::Broken, TextReportTable::Broken);
  transTable.setHeaderSeperator(' ', '-');

  char buf[30];

  for(unsigned int i = 0; i < transactionList.size(); i++)
  {
    sprintf(buf, "%ld", transactionList[i].getId());
    transTable.setText(i, 0, buf);
    transTable.setText(i, 1, transactionList[i].getSeller().getNumber());
    transTable.setText(i, 2, transactionList[i].getBuyer().getNumber());
    sprintf(buf, "%ld", transactionList[i].getHead());
    transTable.setText(i, 3, buf);
    sprintf(buf, "%ld", transactionList[i].getWeight());
    transTable.setText(i, 4, buf);
    transTable.setText(i, 5, transactionList[i].getAnimalCode().getDescrip());
    sprintf(buf, "%0.2f", transactionList[i].getPrice());
    transTable.setText(i, 6, buf);
    sprintf(buf, "%0.2f", transactionList[i].amount());
    transTable.setText(i, 7, buf);
    sprintf(buf, "%d", transactionList[i].getMode());
    transTable.setText(i, 8, buf);
  }

  return transTable;
}
