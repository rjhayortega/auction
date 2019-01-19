/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef BREAKEDITDIALOG_H
#define BREAKEDITDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "dao/commissiondao.h"
#include "dao/animalcodedao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QPushButton;
class QTextEdit;
class Q3Table;

namespace Ui {
  class BreakEditDialog;
}

class BreakEditDialog : public QDialog
{
    Q_OBJECT

public:
    BreakEditDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~BreakEditDialog();

public slots:
    void init( Commission commission );
    void showCodeAssociation( list<AnimalCode> codeList );
    void populateBreakTable();
    void accept();
    void saveBreakList();

protected:

protected slots:

private:
    vector<CommissionBreak> breakList;
    string unitString;
    Commission commission;

    void init();
    Ui::BreakEditDialog *ui;
};

#endif // BREAKEDITDIALOG_H
