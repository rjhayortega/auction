#ifndef _HISTORY_DAO_H_
#define _HISTORY_DAO_H_

/*
 *  WARNING: BREAKS ENCAPSULATION, DO NOT USE THIS CLASS TO SAVE DATA TO INAPPROPRIATE TABLES
 *  (i.e. any table other than the as yet unimplemented history table)
 *  in other words: only SELECT statements are allowed 
 */

#include "../types/historyitem.h"
#include "customerdao.h"
#include "transactiondao.h"
#include <vector>
#include <algorithm>

#include "animalcodedao.h"
class HistoryDAO
{
public:
  vector<HistoryItem> getBuyerHistoryList(string, Date, Date);
  vector<HistoryItem> getSellerHistoryList(string, Date, Date);
  vector<HistoryItem> getAnimalHistoryList(AnimalCode, Date, Date);
  vector<HistoryItem> getDateHistoryList(Date, Date);
  vector<HistoryItem> getSellerInvoiceHistoryList(Date, Date);
  vector<HistoryItem> getBuyerInvoiceHistoryList(Date, Date);
  string predictSeller(string);
  string predictBuyer(string);
private:
  TransactionDAO transactionDao;
  vector<HistoryItem> getHistoryListByCondition(string, string, Date, Date);
  vector<HistoryItem> getHistoryListByCondition(QSqlQuery &historyQuery);
  string getQueryString(string condStr, string altCondStr, Date startDate, Date endDate);

};

#endif
