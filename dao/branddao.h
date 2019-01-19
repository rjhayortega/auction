#ifndef _BRAND_DAO_H_
#define _BRAND_DAO_H_

#include "databasemanager.h"
#include "../types/brand.h"
#include "salemanager.h"
#include "../types/transaction.h"
#include "../types/tag.h"
#include <vector>
#include <sstream>

using namespace std;

class BrandDAO
{
public:
  BrandDAO();

  bool saveBrand(Brand);
  vector<Brand> getTransactionBrandList(Transaction);
  vector<Brand> getLimitedBrandList(int, int);
  vector<Brand> getTagBrand(Tag);
  vector<Brand> getTagBrandVector(vector<Tag>&);
  void deleteBrand(Brand);

  vector<Brand> getBrandList();
  void removeCompetingBrands(Brand brand);

  vector<Brand> getInvoiceBrandList(string);
  long getBrandListSize();// [KLN] add

private:
  vector<Brand> getBrandListByCondition(string);

  SaleManager sale;
};
#endif
