#ifndef _TRANSACTION_TICKET_H_
#define _TRANSACTION_TICKET_H_

#include "textreport.h"
#include "../types/transaction.h"

class TransactionTicket : public TextReport
{
public:
  TransactionTicket(Transaction=Transaction(), string="");
  virtual string text();

private:
  Transaction transaction;
  TextReportTable transactionDataTable();
  TextReportTable transactionTable();
  string marketName;
};
#endif
