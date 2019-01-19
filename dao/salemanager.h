
#ifndef _SALE_MANAGER_H_
#define _SALE_MANAGER_H_

#include "../types/date.h"
#include "databasemanager.h"
#include <iostream>

#include <vector>
using namespace std;

class Sale
{
public:
  Sale(Date date=Date(), bool open=true)
  {
    this->date = date;
    this->open = open;
  }

  Date date;
  bool open;
};

class SaleManager
{
public:
  vector<Sale> getSaleList();
  void createSale(Date=Date());
  void setCurrentSale(Sale, bool=true);
  Date currentSaleDate();
  string currentSaleDateSQLString(); // convenience function

  bool currentSaleOpen();

  Sale mostRecentSale();
  void setDBCurrent(Sale);

  void closeSale(Sale&);
  // KLN add
  void openSale(Sale&);
  bool isSaleOpen(Sale&);
  bool isSaleActive(Sale&);
  // KLN add end

  Date maxNextNonSaleDay();
private:
  static Date saleDate;
  static bool saleOpen;
  static string saleDateSQLString;
};
#endif
