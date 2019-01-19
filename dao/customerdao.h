
#ifndef _CUSTOMER_DAO_H_
#define _CUSTOMER_DAO_H_
#include "../types/dbug.h"
#include "../types/customer.h"
#include "databasemanager.h"
#include <string>
#include <vector>
#include <iostream>
#include "salemanager.h"
#include "setupdao.h"
#include <sstream>
#include <QSqlQuery>

// 04 Sep 09 rhw	Add method getCustomerListForCompany(string company).
// 19 Jun 09 rhw	Add method loadFromName(string name).
// 15 Jun 09 rhw	Add method sellerInDailyFile(string id).

using namespace std;

class CustomerDAO
{
public:
  static Customer loadFromId(int);
  static Customer loadFromName(string);
  static Customer loadFromPhone(string);
  static int saveCustomer(Customer, Customer::Type=Customer::Seller, bool=true, bool=false);
//  static bool customerExists(Customer);
  static void deleteCustomer(Customer);
  static void deleteByDocket(Customer);

  static void clearLienImports();
  static void clearPermNumber(string);
  static vector<Customer> getCustomerList(Customer::Type=Customer::Seller);
  static vector<Customer> getCustomerListThatBeginsWith(string, Customer::Type=Customer::Seller,bool=false);
  static vector<Customer> getCustomerListForCompany(string, Customer::Type=Customer::Buyer);
  static bool usedAsDaily(Customer);
  static bool nameExists(string);
  static bool previouslyAltered(long custId);

  static Customer loadFromPermNumber(string,bool=true);
  static void savePermNumber(Customer);
  static SetupDAO setup;
  static void updateChildCountryOfOrigin(Customer);
protected:
  static vector<Customer> getCustomerListByCondition(string, Customer::Type=Customer::Seller);
  static vector<Customer> getCustomerListByCondition(QSqlQuery &loadQuery);

private:
  static Customer loadByCondition(QSqlQuery &loadQuery);
  static Customer loadByCondition(string);
  static Customer loadFromBasePermNumber(string);

};

class SellerDAO 
{
public:
  typedef enum {iName, iCompany}Index;
  static Seller loadFromNumber(string);

  static vector<Seller>getCustomerList();
  static bool saveCustomer(Seller&);
  static bool sellerExists(Seller);
  static void deleteSeller(Seller);
  static long checkedInHead();
  static string idOfNextAlphabeticSeller(string, bool);
  static Seller nextSeller(Seller, Index, bool);
  static Seller findSeller(string, Index);
  static Seller getSeller(Tag);
  //vector<Customer> getCustomerList();

  static bool sellerInDailyFile(string);

  static void updateParentCountryOfOrigin(Seller);
private:
  static Seller loadByCondition(string);
  static const string fieldList;
  static Seller parseSellerFieldList(QSqlQuery &sellerQuery);


};

class BuyerDAO 
{
  public:
  static Buyer loadFromNumber(string);
  static Buyer loadFromBuyerByNumber(string);
  static vector<Buyer> getCustomerList();
  static bool saveCustomer(Buyer, bool=true);
  static bool buyerExists(Buyer);
  static void deleteBuyer(Buyer);
  //vector<Customer> getCustomerList();
private:
  static Buyer loadByCondition(string);
};

#endif
