
#ifndef _PRORATE_H_
#define _PRORATE_H_

#include <string>
#include <vector>
#include "invoice.h"
using namespace std;
class Prorate
{
public:
typedef struct prorateData
{
  long number;
  double amount;
}Data;

  Prorate(string, Data);
  Prorate(string, vector<Data>);
  void setAmount(double, unsigned int index=0);
  double getAmount(unsigned int index=0);
  double getValue(unsigned int index=0);
  string getPayee();
  vector<Data> getDataList();
  void setDataList(vector<Data>);
private:
  string payee;
  vector<Data> dataList;
};

#endif
