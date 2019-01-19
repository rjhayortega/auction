
#include "prorate.h"

Prorate::Prorate(string payee, Data data)
{
  this->payee = payee;
  dataList.push_back(data);
}

Prorate::Prorate(string payee, vector<Data> dataList)
{
  this->payee = payee;
  this->dataList = dataList;
}

double Prorate::getAmount(unsigned int index)
{
  if(index >= dataList.size())
  {
    return 0.00;
  }

  return dataList[index].amount;
}

void Prorate::setAmount(double amount, unsigned int index)
{
  if(index >= dataList.size())
  {
    return;
  }

  dataList[index].amount = amount;
}

double Prorate::getValue(unsigned int index)
{
  if(index >= dataList.size())
  {
    return 0.0;
  }

  return dataList[index].number;
}

string Prorate::getPayee()
{
  return payee;
}

vector<Prorate::Data> Prorate::getDataList()
{
  return dataList;
}

void Prorate::setDataList(vector<Data> dataList)
{
  this->dataList = dataList;
}
