/****************************************************************************
** Updated to Qt4
**
**
****************************************************************************/
#ifndef BUYERCOMMISSIONDIALOG_H
#define BUYERCOMMISSIONDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "types/invoice.h"
#include "dao/commissiondao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class BuyerCommissionDialog : public QDialog
{
    Q_OBJECT

public:
    BuyerCommissionDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~BuyerCommissionDialog();


public slots:

protected:

protected slots:

private:
    Invoice invoice;

};

#endif // BUYERCOMMISSIONDIALOG_H
