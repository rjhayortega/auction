
#include "customerreport.h"

#include <cstdio>

CustomerReport::CustomerReport(vector<Customer> custList)
{
  setCustomerList(custList);
}



CustomerReport::~CustomerReport()
{
}

string CustomerReport::headerString()
{
  string spacer (33, ' ');
  return spacer + "CUSTOMER LIST\n" + spacer + "-------------\n" + spacer +  Date::currentDate().toString("mm/dd/YYYY") + "\n";
}

void CustomerReport::initCustomerTable(TextReportTable& custTableRef)
{
}

string CustomerReport::unformattedText()
{
  string rptText;
  
  string number, name, company, address1, address2, cityStateZip;

  rptText += headerString();
  for(unsigned int i = 0; i < customerList.size(); i++)
  {
    number = customerList[i].getNumber();
    name = customerList[i].getName().getLast();
    address1 = customerList[i].getAddress().getAddress1();
    address2 = customerList[i].getAddress().getAddress2();
    company = customerList[i].getCompany();
    cityStateZip = customerList[i].getAddress().cityStateZipStr();

    rptText += 
      name + company + (number.length() > 0 ? "\t\tPerm #: " + number + "" : "") + "\n" +
      (company.length()      > 0 ? "\t" + company      + "\n" : "") + 
      (address1.length()     > 0 ? "\t" + address1     + "\n" : "") +
      (address2.length()     > 0 ? "\t" + address2     + "\n" : "") +
      (cityStateZip.length() > 0 ? "\t" + cityStateZip + "\n" : "") + 
      "\n";
  }

  return rptText;
}

TextReportTable CustomerReport::customerTable()
{
  TextReportTable custTable;
  initCustomerTable(custTable);
  custTable.insertRows(customerList.size());

  for(unsigned int i = 0; i < customerList.size(); i++)
  {
    setCustomerTableRow(i, custTable, customerList[i]);
  }

  setSummaryLines(custTable, customerList);

  return custTable;
}

void CustomerReport::setSummaryLines(TextReportTable& table, vector<Customer> customerList)
{
// default does nothing 
}

void SellerReport::setSummaryLines(TextReportTable& table, vector<Customer> customerList)
{
  table.insertRows(3);

  long totalHead = 0;
  for(unsigned int i = 0; i < customerList.size(); i++)
  {
    totalHead += customerList[i].getHead();
  }

  char buf[40];
  sprintf(buf, "Total Head: %ld", totalHead);

  table.setText(customerList.size() + 2, 0, buf, true);
}

void CustomerReport::setCustomerTableRow(unsigned int row, TextReportTable& table, Customer customer)
{
}

void CustomerReport::setCustomerList(vector<Customer> customerList)
{
  this->customerList = customerList;
}

string CustomerReport::text()
{
  clearTables();
  addTable(customerTable());
  return TextReport::text();
}

TextReportHeader CustomerReport::reportHeader()
{
  return TextReportHeader();
}

SellerReport::SellerReport(vector<Seller> sellerList, vector<string> checkNumberList)
{
  vector<Customer> customerList;
  this->checkNumberList = checkNumberList;
  for(unsigned int i = 0; i < sellerList.size(); i++)
  {
    customerList.push_back(sellerList[i]);
  }
  setCustomerList(customerList);
}

void SellerReport::initCustomerTable(TextReportTable &custTableRef)
{
  custTableRef = TextReportTable(6);

  custTableRef.setColumnWidth(0, 9);
  custTableRef.setColumnWidth(1, 25);
  custTableRef.setColumnWidth(2, 22);
  custTableRef.setColumnWidth(3, 22);
  custTableRef.setColumnWidth(4, 8);
  custTableRef.setColumnWidth(5, 10);

  custTableRef.setColumnAlignment(0, TextReportTable::LEFT);
  custTableRef.setColumnAlignment(1, TextReportTable::LEFT);
  custTableRef.setColumnAlignment(2, TextReportTable::LEFT);
  custTableRef.setColumnAlignment(3, TextReportTable::LEFT);
  custTableRef.setColumnAlignment(4, TextReportTable::CENTER);
  custTableRef.setColumnAlignment(5, TextReportTable::RIGHT);

  custTableRef.setHeaderStyle(TextReportTable::Broken, TextReportTable::Broken);
  custTableRef.setHeaderSeperator(' ', '-');

  custTableRef.setHeader(0, "Number");
  custTableRef.setHeader(1, "Seller");
  custTableRef.setHeader(2, "Address");
  custTableRef.setHeader(3, "City/State/Zip");
  custTableRef.setHeader(4, "Hd Cnt");
  custTableRef.setHeader(5, "Check #");
  custTableRef.setSurroundingText(string(1, char(27)) + string(1, char(77)), string(1, char(27)) + string(1, char(80)));
}

void SellerReport::setCustomerTableRow(unsigned int row, TextReportTable& tableRef, Customer customer)
{
  char buf[20];
  sprintf(buf, "%ld",   customer.getHead());
  tableRef.setText(row, 0, customer.getNumber());
  tableRef.setText(row, 1, string(" ") + customer.getName().getLast());
  tableRef.setText(row, 2, string(" ") + customer.getAddress().getAddress1());
  tableRef.setText(row, 3, string(" ") + customer.getAddress().cityStateZipStr());
  tableRef.setText(row, 4, string(" ") + buf);
  tableRef.setText(row, 5, (row < checkNumberList.size() ? checkNumberList[row] : ""));
}

string SellerReport::headerString()
{
  return "Seller List";
}

string BuyerReport::headerString()
{
  return "Buyer List";
}

TextReportHeader SellerReport::reportHeader()
{
  TextReportHeader header("Seller List");
  header.addHeaderLine   ("-----------");
  header.addHeaderLine(" ");

  return header;
}

TextReportHeader BuyerReport::reportHeader()
{
  TextReportHeader header("Buyer List");
  header.addHeaderLine   ("----------");
  header.addHeaderLine(" ");
  return header;
}

BuyerReport::BuyerReport(vector<Buyer> buyerList)
{
  vector<Customer> customerList;

  for(unsigned int i = 0; i < buyerList.size();i++)
  {
    customerList.push_back(buyerList[i]);
  }
  setCustomerList(customerList);
}

void BuyerReport::initCustomerTable(TextReportTable &custTableRef)
{
  custTableRef = TextReportTable(5);

  custTableRef.setColumnWidth(0, 8);
  custTableRef.setColumnWidth(1, 20);
  custTableRef.setColumnWidth(2, 20);
  custTableRef.setColumnWidth(3, 16);
  custTableRef.setColumnWidth(4, 16);

  custTableRef.setColumnAlignment(0, TextReportTable::LEFT);
  custTableRef.setColumnAlignment(1, TextReportTable::LEFT);
  custTableRef.setColumnAlignment(2, TextReportTable::LEFT);


  custTableRef.setHeaderStyle(TextReportTable::Broken, TextReportTable::Broken);
  custTableRef.setHeaderSeperator(' ', '-');

  custTableRef.setHeader(0, "Number");
  custTableRef.setHeader(1, "Name");
  custTableRef.setHeader(2, "Company");
  custTableRef.setHeader(3, "Address");
  custTableRef.setHeader(4, "City/State/Zip");

}

void BuyerReport::setCustomerTableRow(unsigned int row, TextReportTable& tableRef, Customer customer)
{
  tableRef.setText(row, 0,               customer.getNumber());
  tableRef.setText(row, 1, string(" ") + customer.getName().getLast());
  tableRef.setText(row, 2, string(" ") + customer.getCompany());
  tableRef.setText(row, 3, string(" ") + customer.getAddress().getAddress1());
  tableRef.setText(row, 4, string(" ") + customer.getAddress().cityStateZipStr());
}

