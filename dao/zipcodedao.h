#ifndef _ZIP_CODE_H_
#define _ZIP_CODE_H_

#include "../types/address.h"
#include "databasemanager.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class ZipCodeDAO
{
public:
  ZipCodeDAO();
  vector<Address> getZipCodeListByCity(string);
  vector<Address> getZipCodeListByZip(string);

private:
  vector<Address> getZipCodeListByCondition(QSqlQuery& zipCodeListQuery);

};

#endif
