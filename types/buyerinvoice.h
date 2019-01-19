#ifndef BUYERINVOICE_H
#define BUYERINVOICE_H
#include "invoice.h"
class BuyerInvoice : public Invoice
{
public:
  BuyerInvoice(long=0, Date=Date(), Customer=Customer(),Invoice::STATUS status= Invoice::UNPAID);
  virtual double net();
  virtual ~BuyerInvoice();

};

#endif // BUYERINVOICE_H
