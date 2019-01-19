#ifndef _RADIO_TAG_DAO_H_
#define _RADIO_TAG_DAO_H_

#include "databasemanager.h"
#include "../types/customer.h"
#include "../types/radiotag.h"
#include "salemanager.h"

class RadioTagDAO
{
public:
  RadioTagDAO();
  void saveRadioTag(RadioTag);
  vector<RadioTag> getSellerRadioTagList(Seller);

private:
  SaleManager sale;
  RadioTag getRadioTagByCondition(string);
  vector<RadioTag> getRadioTagListByCondition(string);
};
#endif
