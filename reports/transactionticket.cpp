#include "transactionticket.h"

#include <cstdio>

TransactionTicket::TransactionTicket(Transaction transaction, string marketName)
{
  this->transaction = transaction;
  this->marketName = marketName;
}

string TransactionTicket::text()
{
  clearTables();
  setHeader(TextReportHeader(marketName));
  addTable(transactionDataTable());
  addTable(transactionTable());
  return TextReport::text();
}

TextReportTable TransactionTicket::transactionDataTable()
{
  TextReportTable table(3);

  table.setColumnWidth(0, 26);
  table.setColumnWidth(1, 34);
  table.setColumnWidth(2, 20);

  table.setColumnAlignment(0, TextReportTable::LEFT);
  table.setColumnAlignment(1, TextReportTable::LEFT);
  table.setColumnAlignment(2, TextReportTable::RIGHT);

  table.insertRows(4);

  table.setText(2, 0, transaction.getCreated().toString("YYYY-mm-dd"));
  table.setText(2, 1, "SCALE TICKET AND BILL OF SALE");
  table.setText(2, 2, string("Weighmaster: ") + transaction.getWeighmaster());

  return table;
}

TextReportTable TransactionTicket::transactionTable()
{
  TextReportTable table(9);

  if(transaction.getDraft() == 0)
  {
    table.setColumnWidth(0, 4);
    table.setColumnWidth(1, 7);
    table.setColumnWidth(2, 16);
    table.setColumnWidth(3, 6);
    table.setColumnWidth(4, 9);
    table.setColumnWidth(5, 10);
    table.setColumnWidth(6, 11);
    table.setColumnWidth(7, 9);
    table.setColumnWidth(8, 8);

    table.setColumnAlignment(0, TextReportTable::LEFT);
    table.setColumnAlignment(1, TextReportTable::LEFT);
    table.setColumnAlignment(2, TextReportTable::LEFT);
    table.setColumnAlignment(3, TextReportTable::LEFT);
    table.setColumnAlignment(4, TextReportTable::LEFT);
    table.setColumnAlignment(5, TextReportTable::LEFT);
    table.setColumnAlignment(6, TextReportTable::LEFT);
    table.setColumnAlignment(7, TextReportTable::LEFT);
    table.setColumnAlignment(8, TextReportTable::LEFT);

    table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::Shadow);
    table.setHeader(0, "TRNS");
    table.setHeader(1, "  HD/CT");
    table.setHeader(2, "  DESC");
    table.setHeader(3, "  AVG.");
    table.setHeader(4, "  TOTAL");
    table.setHeader(5, "  BID");
    table.setHeader(6, "  COST");
    table.setHeader(7, "  SELLER");
    table.setHeader(8, " BUYER");
  }
  else
  {
    table = TextReportTable(4);
    
    table.setColumnWidth(0, 15);
    table.setColumnWidth(1, 15);
    table.setColumnWidth(2, 15);
    table.setColumnWidth(3, 15);

    table.setColumnAlignment(0, TextReportTable::LEFT);
    table.setColumnAlignment(1, TextReportTable::LEFT);
    table.setColumnAlignment(2, TextReportTable::LEFT);
    table.setColumnAlignment(3, TextReportTable::LEFT);
    
    table.setHeader(0, "Draft");
    table.setHeader(1, "Head");
    table.setHeader(2, "Weight");
    table.setHeader(3, "Avg. Weight");
  }

  table.insertRows(1);

  char buf[20];

  if(transaction.getDraft() != 0)
  {
    sprintf(buf, "%ld-%ld", transaction.getId(), transaction.getDraft());
    table.setText(0, 0, buf);
    table.setText(0, 1, transaction.getHead());
    table.setText(0, 2, transaction.getWeight());
    table.setText(0, 3, transaction.getAverageWeight()); 
  }
  else
  {
    sprintf(buf, "%ld", transaction.getId());
    table.setText(0, 0, buf);
    sprintf(buf, "  %ld", transaction.getHead());
    table.setText(0, 1, buf);
    table.setText(0, 2, string("  ") + transaction.getAnimalCode().getDescrip());
    sprintf(buf, "  %ld", transaction.getAverageWeight());
    table.setText(0, 3, buf);
    sprintf(buf, "  %ld", transaction.getWeight());
    table.setText(0, 4, buf);
    sprintf(buf, "  %0.2f", transaction.getPrice());
    table.setText(0, 5, buf);
    sprintf(buf, "  %0.2f", transaction.amount());
    table.setText(0, 6, buf);
    table.setText(0, 7, string("  ") + transaction.getSeller().getNumber());
    table.setText(0, 8, string(" ") + transaction.getBuyer().getNumber());
  }

  table.insertRows(1);
  table.setText(1, 0, "COMMENT: " + transaction.getComment(), true);

  vector<Tag> tagList = transaction.getTagList();
  string tagString = "BACKTAGS: ";

  for(unsigned int i = 0; i < tagList.size(); i++)
  {
    tagString += tagList[i].getTag() + (i < tagList.size() - 1 ? ", " : "");
  }

  unsigned int row = 2;

  string tmp = "";

   do
   {
     table.insertRows(1);
     tmp = tagString.substr(0, (tagString.length() > 80 ? 80 : tagString.length()));
     tagString = (tagString.length() > 80 ?  tagString.substr(80) : "");
     table.setText(row, 0, tmp, true);
     row++;
   }while(tagString.length() > 0);

  table.insertRows(1);

  table.setText(row, 0, string("BUYER PEN: ") + transaction.getBuyerPen(), true);
  return table;
}
