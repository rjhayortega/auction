
#include "historyreport.h"

HistoryReport::HistoryReport(vector<HistoryItem> historyList)
{
  setHistoryList(historyList);
}

void HistoryReport::setHistoryList(vector<HistoryItem> historyList)
{
  this->historyList = historyList;
}

TextReportTable HistoryReport::summaryTable()
{
  return TextReportTable();
}

string HistoryReport::text()
{
  addTable(historyTable());
  addTable(summaryTable());
  return TextReport::text();
}


SellerHistoryReport::SellerHistoryReport(vector<HistoryItem> historyList) : HistoryReport(historyList)
{
}

void SellerHistoryReport::initHistoryTable(TextReportTable& table)
{
  table.setColumnWidth(0, 12);
  table.setColumnWidth(1, 12);
  table.setColumnWidth(2, 4);
  table.setColumnWidth(3, 8);
  table.setColumnWidth(4, 21);
  table.setColumnWidth(5, 10);
  table.setColumnWidth(6, 12); 

  table.setColumnAlignment(0, TextReportTable::LEFT);
  table.setColumnAlignment(1, TextReportTable::RIGHT);
  table.setColumnAlignment(2, TextReportTable::RIGHT);
  table.setColumnAlignment(3, TextReportTable::RIGHT);
  table.setColumnAlignment(4, TextReportTable::CENTER);
  table.setColumnAlignment(5, TextReportTable::RIGHT);
  table.setColumnAlignment(6, TextReportTable::RIGHT);

  table.setHeader(0, "");
  table.setHeader(1, "Date");
  table.setHeader(2, "Hd");
  table.setHeader(3, "Wght");
  table.setHeader(4, "  Description");
  table.setHeader(5, "Bid");
  table.setHeader(6, "Gross");

  table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::Broken);
}

TextReportTable SellerHistoryReport::historyTable()
{
  TextReportTable table(7);
  initHistoryTable(table);

  sort(historyList.begin(), historyList.end(), HistoryItem::compareTypeDescrip);

 
  typeTotals = vector<Totals>();

  Transaction tempTrans;

  unsigned int row = 0;
  Totals tempTotals;

  if(historyList.size() > 0)
  {
    table.insertRows(1);
    tempTotals.typeDescrip = historyList[0].getCode().getTypeDescrip();
    tempTotals.head = 0;
    tempTotals.weight = 0;
    tempTotals.gross = 0.00000001;

    table.setText(0, 0, tempTotals.typeDescrip);
    row++;
  }

  for(unsigned int i = 0; i < historyList.size(); i++)
  {
    if(tempTotals.typeDescrip != historyList[i].getCode().getTypeDescrip())
    {
      table.insertRows(2);
      table.setText(row, 1, "SubTotal");
      table.setText(row, 2, tempTotals.head);
      table.setText(row, 3, tempTotals.weight);
      table.setText(row, 6, tempTotals.gross);
      typeTotals.push_back(tempTotals);

      tempTotals.typeDescrip = historyList[i].getCode().getTypeDescrip();
      tempTotals.head = 0;
      tempTotals.weight = 0;
      tempTotals.gross = 0.00000001;
      table.setText(row + 1, 0, tempTotals.typeDescrip);
      row += 2;
    }

    tempTrans.setPrice(historyList[i].getBid());
    tempTrans.setHead(historyList[i].getHead());
    tempTrans.setMode(historyList[i].getMode());
    tempTrans.setWeight(historyList[i].getWeight());

    table.insertRows(1);
    table.setText(row, 1, historyList[i].getDate().toString("mm/dd/YYYY"));
    table.setText(row, 2, historyList[i].getHead());
    table.setText(row, 3, tempTrans.getWeight());
    table.setText(row, 4, string("  ") + historyList[i].getCode().getDescrip());
    table.setText(row, 5, tempTrans.getPrice());

    if(historyList[i].getMode() == Transaction::NoSaleCWT || historyList[i].getMode() == Transaction::NoSaleHead)
    {
      table.setText(row, 6, "N/S");
    }
    else 
    {
      table.setText(row, 6, tempTrans.amount());
    }
    row++;

    tempTotals.head += tempTrans.getHead();
    tempTotals.weight += tempTrans.getWeight();
    tempTotals.gross += tempTrans.amount();

    if(i == historyList.size() - 1)
    {
      table.insertRows(1);
      table.setText(row, 1, "SubTotal");
      table.setText(row, 2, tempTotals.head);
      table.setText(row, 3, tempTotals.weight);
      table.setText(row, 6, tempTotals.gross);
      typeTotals.push_back(tempTotals);
      row++;
    }
  }

  table.insertRows(3);
  table.setText(row + 1, 0, string(27, ' ') + string("R E P O R T  S U M M A R Y"), true);

  return table;
}

TextReportTable SellerHistoryReport::summaryTable()
{
  TextReportTable table(4);

  table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::Broken);
  
  table.setColumnWidth(0, 30);
  table.setColumnWidth(1, 6);
  table.setColumnWidth(2, 9);
  table.setColumnWidth(3, 11);

  table.setColumnAlignment(0, TextReportTable::RIGHT); 
  table.setColumnAlignment(1, TextReportTable::RIGHT);
  table.setColumnAlignment(2, TextReportTable::RIGHT);
  table.setColumnAlignment(3, TextReportTable::RIGHT);

  table.setHeader(1, "Head");
  table.setHeader(2, "Weight");
  table.setHeader(3, "Gross");

  unsigned int row = 0;

  long headTotal = 0;
  long weightTotal = 0;
  double grossTotal = 0.00000001;

  for(unsigned int i = 0; i < typeTotals.size(); i++)
  {
    table.insertRows(2);
    table.setText(row, 0, typeTotals[i].typeDescrip + " Totals: ");
    table.setText(row, 1, typeTotals[i].head);
    table.setText(row, 2, typeTotals[i].weight);
    table.setText(row, 3, typeTotals[i].gross);

    headTotal += typeTotals[i].head;
    weightTotal += typeTotals[i].weight;
    grossTotal += typeTotals[i].gross;
    row += 2;
  }

  table.insertRows(2);

  table.setText(row, 1, string(4, '-'));
  table.setText(row, 2, string(7, '-'));
  table.setText(row, 3, string(9, '-'));
  row++;

  table.setText(row, 0, "Grand Totals: ");
  table.setText(row, 1, headTotal);
  table.setText(row, 2, weightTotal);
  table.setText(row, 3, grossTotal);
  return table;
}


BasicHistoryReport::BasicHistoryReport(vector<HistoryItem> historyList) : HistoryReport(historyList)
{
}

void BasicHistoryReport::initTable(TextReportTable& table)
{
  table = TextReportTable(6);

  table.setColumnWidth(0, 30);
  table.setColumnWidth(1, 10);
  table.setColumnWidth(2, 4);
  table.setColumnWidth(3, 8);
  table.setColumnWidth(4, 19);
  table.setColumnWidth(5, 8);

  table.setColumnAlignment(0, TextReportTable::LEFT);
  table.setColumnAlignment(1, TextReportTable::RIGHT);
  table.setColumnAlignment(2, TextReportTable::RIGHT);
  table.setColumnAlignment(3, TextReportTable::RIGHT);
  table.setColumnAlignment(4, TextReportTable::CENTER);
  table.setColumnAlignment(5, TextReportTable::RIGHT);

  table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::Broken);

  table.setHeader(0, "Seller");
  table.setHeader(1, "Date");
  table.setHeader(2, "Hd");
  table.setHeader(3, "Wght");
  table.setHeader(4, "Description");
  table.setHeader(5, "Bid");
}


TextReportTable BasicHistoryReport::historyTable()
{
  TextReportTable table;
  initTable(table);
  table.insertRows(historyList.size());

  for(unsigned int i = 0; i < historyList.size(); i++)
  {
    table.setText(i, 0, historyList[i].getSellerName());
    table.setText(i, 1, historyList[i].getDate().toString("mm/dd/YYYY"));
    table.setText(i, 2, historyList[i].getHead());
    table.setText(i, 3, historyList[i].getWeight());
    table.setText(i, 4, historyList[i].getCode().getDescrip());

    if(historyList[i].getMode() == Transaction::NoSaleCWT || historyList[i].getMode() == Transaction::NoSaleHead)
    {
      table.setText(i, 5, "N/S");
    }
    else
    {
      table.setText(i, 5, historyList[i].getBid());
    }
  }
  return table;
}

BuyerHistoryReport::BuyerHistoryReport(vector<HistoryItem> historyList) : BasicHistoryReport(historyList)
{
}

CodeHistoryReport::CodeHistoryReport(vector<HistoryItem> historyList) : BasicHistoryReport(historyList)
{
}

DateHistoryReport::DateHistoryReport(vector<HistoryItem> historyList) : HistoryReport(historyList)
{
}

void DateHistoryReport::initHistoryTable(TextReportTable& table)
{
  table = TextReportTable(4);

  table.setColumnWidth(0, 35);
  table.setColumnWidth(1, 13);
  table.setColumnWidth(2, 5);
  table.setColumnWidth(3, 24);

  table.setColumnAlignment(0, TextReportTable::LEFT);
  table.setColumnAlignment(1, TextReportTable::CENTER);
  table.setColumnAlignment(2, TextReportTable::RIGHT);
  table.setColumnAlignment(3, TextReportTable::RIGHT);

  table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::Broken);

  table.setHeader(0, customerTypeString());
  table.setHeader(1, "Date");
  table.setHeader(2, "Hd");
  table.setHeader(3, "Net");
}

TextReportTable DateHistoryReport::historyTable()
{
  TextReportTable table;
  initHistoryTable(table);
  table.insertRows(historyList.size());
  for(unsigned int i = 0; i < historyList.size(); i++)
  {
    table.setText(i, 0, customerNameString(i));
    table.setText(i, 1, historyList[i].getDate().toString("mm/dd/YYYY"));
    table.setText(i, 2, historyList[i].getHead());
    table.setText(i, 3, historyList[i].getNet());
  }

  return table;
}

SellerDateHistoryReport::SellerDateHistoryReport(vector<HistoryItem> historyList) : DateHistoryReport(historyList)
{
}

string SellerDateHistoryReport::customerTypeString()
{
  return "Seller";
}

string SellerDateHistoryReport::customerNameString(unsigned int index)
{
  if(0 <= index && index < historyList.size())
  {
    return historyList[index].getSellerName();
  }
  return "";
}



BuyerDateHistoryReport::BuyerDateHistoryReport(vector<HistoryItem> historyList) : DateHistoryReport(historyList)
{
}

string BuyerDateHistoryReport::customerTypeString()
{
  return "Buyer";
}

string BuyerDateHistoryReport::customerNameString(unsigned int index)
{
  if(0 <= index && index <historyList.size())
  {
    return historyList[index].getBuyerName();
  }

  return "";
}

