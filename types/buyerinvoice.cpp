#include "buyerinvoice.h"

BuyerInvoice::BuyerInvoice(long id, Date date, Customer seller, STATUS status) :
  Invoice(id, date, seller,status)
{
}

double BuyerInvoice::net()
{
  return gross() + (getCommissionTotal(true)) + truckingTotal() + chargeTotal();
}

BuyerInvoice::~BuyerInvoice()
{


}
