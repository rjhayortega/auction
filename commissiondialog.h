/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef COMMISSIONDIALOG_H
#define COMMISSIONDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "dao/commissiondao.h"
#include "dao/animalcodedao.h"
#include "Q3ListView"
#include "breakeditdialog.h"
#include <QMessageBox>


class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLineEdit;
class QGroupBox;
class QLabel;
class QComboBox;
class QTable;
class Q3ListBox;
class Q3ListBoxItem;

namespace Ui {
  class CommissionDialog;
}

class CommissionDialog : public QDialog
{
    Q_OBJECT

public:
    CommissionDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~CommissionDialog();

  int selectedCommissionIndex();

public slots:
    void checkTable( const QString & text );
    void checkTableCol( int col, bool check );
    void populateCommissionListBox();
    void loadCommission( Q3ListBoxItem * item );
    void editBreakList( Q3ListBoxItem * item );
    void loadCodeList( long commId );
    void saveCommission();
    void clearCommCodeTable();
    void deleteItem();
    void clearForm();
    void showForm();
    void resetFields();
    void mouseMoveEvent( QMouseEvent * e );
    void showDescripAtCoord( int x, int y );

protected:

protected slots:

private:
    vector<Commission> commList;
    bool blockSignal;
    AnimalCodeDAO codeDao;

    void init();
    Ui::CommissionDialog *ui;
};

#endif // COMMISSIONDIALOG_H
