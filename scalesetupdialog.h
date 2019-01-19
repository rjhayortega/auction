/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef SCALESETUPDIALOG_H
#define SCALESETUPDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "dao/setupdao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QComboBox;
class QPushButton;
class QLineEdit;
class QCheckBox;
class QButtonGroup;
class QRadioButton;

namespace Ui {
  class ScaleSetupDialog;
}


class ScaleSetupDialog : public QDialog
{
    Q_OBJECT

public:
    ScaleSetupDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~ScaleSetupDialog();


public slots:
void loadScale();
void save();
void browse();

protected:

protected slots:

private:
    QStringList charValueList;
    QStringList charNameList;
    SetupDAO setup;

    void init();
  Ui::ScaleSetupDialog *ui;
};

#endif // SCALESETUPDIALOG_H
