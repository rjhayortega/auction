#include "sellerinvoice.h"

SellerInvoice::SellerInvoice(long id, Date date, Customer seller,Invoice::STATUS status) :
    Invoice(id, date, seller,status)
{
}

double SellerInvoice::net()
{
    return gross() - (getCommissionTotal(true) + truckingTotal() + chargeTotal());
}
SellerInvoice::~SellerInvoice()
{}

