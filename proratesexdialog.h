/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef PRORATESEXDIALOG_H
#define PRORATESEXDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <Q3Table>
#include "types/checkfactory.h"
#include "types/prorate.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class Q3Table;
class QPushButton;

namespace Ui {
  class ProrateSexDialog;
}

class ProrateSexDialog : public QDialog
{
    Q_OBJECT

public:
    ProrateSexDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~ProrateSexDialog();

  vector<Prorate::Data> getProrateData();

public slots:
    void init( vector<SexCheckFactory::CodeRecord> codeList, vector<Prorate> prorateList, unsigned int prorateRow );
    void removeProrateFromList( Prorate prorate, bool currentCustomer );
    void removeDataFromList( Prorate::Data data, bool currentCustomer );

protected:

protected slots:

private:
    vector<SexCheckFactory::CodeRecord> codeList;
    QString xChar;
    typedef enum {cKey=0, cHead=1, cTot=2, cChecked=3} CODE_FIELDS;

    void init();
    Ui::ProrateSexDialog *ui;
};

#endif // PRORATESEXDIALOG_H
