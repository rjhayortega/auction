#ifndef _MARKET_REPORT_H_
#define _MARKET_REPORT_H_

#include "../types/transaction.h"
#include "textreport.h"
#include <sstream>

using namespace std;
class MarketReport : public TextReport
{
public:
  typedef enum
  {
    Sex, 
    Seller,
    Head,
    Weight,
    Price,
    TransId,
    None
  }SortItem;

  typedef struct sortRecord
  {
    SortItem sort;
    bool reverse;
  }SortRecord;

  typedef vector<Transaction> TransactionGroup;

  MarketReport(vector<Transaction> =vector<Transaction>(), bool=true, bool=false);
  string text();
  string exportText();
  void setSortOrder(SortRecord, SortRecord, SortRecord, SortRecord, SortRecord, SortRecord);
  void setCommentList(vector<string>);

  static bool compareSex(Transaction, Transaction);
  static bool compareHead(Transaction, Transaction);
  static bool compareSeller(Transaction, Transaction);
  static bool compareWeight(Transaction, Transaction);
  static bool comparePrice(Transaction, Transaction);

  static bool compareSexRev(Transaction, Transaction);
  static bool compareHeadRev(Transaction, Transaction);
  static bool compareSellerRev(Transaction, Transaction);
  static bool compareWeightRev(Transaction, Transaction);
  static bool comparePriceRev(Transaction, Transaction);
  static bool compareIdsRev(Transaction, Transaction);

  void setWegthRanges(int minW, int maxW, int stepW, bool isGroupEnabled);
  vector<string> getUniqueSexList();
private:
  TextReportTable headerTable();
  TextReportTable tableTemplate();
  TextReportTable sexTable(short);
  TextReportTable commentTable(string comment);

  TextReportTable transactionTable();
  void fillTableRow(TextReportTable&, unsigned int, Transaction, bool emptyRow=false);

  vector<Transaction> getSexList(short);
  void sortList();
  vector<Transaction> transactionList;
  vector<TransactionGroup> splitGroup(TransactionGroup, SortRecord);
  vector<short> usedSexes;
  bool splitSexes;
  void sortGroup(TransactionGroup&, SortRecord);
  vector<TransactionGroup> groupList;
  vector<string> commentList;
  SortRecord sortOrder[6];
  bool listSorted;
  bool hideSeller;

  int m_minWegth;
  int m_maxWegth;
  int m_step;
  bool m_isGroup;
};
#endif
