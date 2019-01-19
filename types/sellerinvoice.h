#ifndef SELLERINVOICE_H
#define SELLERINVOICE_H
#include "invoice.h"

class SellerInvoice : public Invoice
{
public:
    SellerInvoice(long id = 0, Date date = Date(), Customer seller= Customer(), Invoice::STATUS status = Invoice::UNPAID);
    virtual ~SellerInvoice();
    virtual double net();
};


#endif // SELLERINVOICE_H
