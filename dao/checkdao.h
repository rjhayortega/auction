
#ifndef _CHECK_DAO_H_
#define _CHECK_DAO_H_

#include "databasemanager.h"
#include "../types/check.h"
#include "../types/invoice.h"
#include "../reports/textcheck.h"
#include "setupdao.h"
#include <string>
#include <algorithm>
#include <vector>
#include "salemanager.h"


using namespace std;

class CheckDAO
{
public:
  CheckDAO();
  Check getCheckById(long);
  Check getCheckByNumber(long);
  vector<Check> getCheckListByNumber(long);
  Check getCheckByInvoice(Invoice, Check::STATUS=Check::Out);
  vector<string> getCustomerCheckNumberList(string);

  vector<Check> getInvoiceCheckList(long);

  vector<Check> getCheckList(Date, Date, bool=true, bool=true, bool=true, string="");
  vector<Check> getCheckList(Check::STATUS);
  vector<Check> getCheckList(long, long, bool=true, bool=true, bool=true, string="");
  vector<Deposit> getDepositList(Date fromDate, Date toDate, bool includeVoid, bool includeOut, bool includeCleared);

  Check saveCheck(Check);
  void voidChecksByInvoice(Invoice);
  void setCheckStatus(Check, Check::STATUS);

  Deposit getDepositByNumber(long);
  vector<Deposit> getDepositList();
  void setDepositStatus(Deposit, Deposit::STATUS);
  Deposit saveDeposit(Deposit);

  double getCheckTotal(Check::STATUS);
  double getDepositTotal(Deposit::STATUS);
  void setNextCheck(long);
  void deleteCheck(Check);

  CheckFormatData getCheckFormat(bool=false);
  void saveCheckFormat(CheckFormatData);
  bool checkExists(long);
  long getNextCheckNo(bool saveNextNo = true);
  long peekAtNextCheckNo();
  double invoiceAmount(long invoiceId);

private:
  Check getCheckByCondition(string);
  vector<Check> getCheckListByCondition(string);
  void voidChecksByCondition(string);
  void setCheckStatusByCondition(string, Check::STATUS);

  Deposit getDepositByCondition(string);
  vector<Deposit> getDepositListByCondition(string);
  void setDepositStatusByCondition(string, Deposit::STATUS);
  SetupDAO setup;
  SaleManager sale;
};
#endif
