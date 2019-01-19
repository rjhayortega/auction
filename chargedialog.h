/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef CHARGEDIALOG_H
#define CHARGEDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <list>
#include <string>
#include <vector>
#include "dao/chargedao.h"
#include "types/animalcode.h"
#include <QMessageBox>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QButtonGroup;
class QRadioButton;
class QGroupBox;
class QCheckBox;
class QLabel;
class QLineEdit;
class Q3Table;
class Q3ListBox;
class Q3ListBoxItem;
class QComboBox;

namespace Ui {
  class ChargeDialog;
}

class ChargeDialog : public QDialog
{
    Q_OBJECT

public:
    ChargeDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~ChargeDialog();

    int getSelectedChargeIndex();
    list<AnimalCode> getAnimalCodeList();

public slots:
    void populateChargeList();
    void moveChargeUp();
    void moveChargeDown();
    void saveCurrentCharge();
    void loadCurrentCharge( int currentRow );
    void resetCharge();
    void clearCodeTable();
    void checkCodeTableColumn( int col, bool check );
    void deleteCurrentCharge();
    void loadCodeTable( Charge charge );
    void checkColumns( const QString & text );

protected:

protected slots:

private:
    vector<Charge> chargeList;
    bool saveNew;
    ChargeDAO chargeDao;

    void init();
    Ui::ChargeDialog *ui;
};

#endif // CHARGEDIALOG_H
