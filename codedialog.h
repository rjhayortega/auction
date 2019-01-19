/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef CODEDIALOG_H
#define CODEDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <vector>
#include "types/animalcode.h"
#include "dao/animalcodedao.h"
#include "dao/commissiondao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class Q3ListBox;
class Q3ListBoxItem;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QComboBox;
class QCheckBox;
class QButtonGroup;
class QRadioButton;

namespace Ui {
  class CodeDialog;
}

class CodeDialog : public QDialog
{
    Q_OBJECT

public:
    CodeDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~CodeDialog();

public slots:
    void populateCodeList();
    void loadCurrentCode( int row );
    void saveCurrentCode();
    void deleteCurrentCode();
    void resetFields();
    void printCodeList();

protected:

protected slots:

private:
    vector<AnimalCode> codeList;
    CommissionDAO::COLOR_GROUP colorGroup;

    void init();
    Ui::CodeDialog *ui;
};

#endif // CODEDIALOG_H
