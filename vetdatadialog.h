/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef VETDATADIALOG_H
#define VETDATADIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "dao/setupdao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QGroupBox;
class QTextEdit;
class QLabel;

namespace Ui {
  class VetDataDialog;
}

class VetDataDialog : public QDialog
{
    Q_OBJECT

public:
    VetDataDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~VetDataDialog();

public slots:
    void accept();
    void loadVetData();
    void saveVetData();

protected:
    QGridLayout* VetDataDialogLayout;
    QSpacerItem* spacer2;
    QGridLayout* vetDataGroupLayout;

protected slots:

private:
    SetupDAO setup;

    void init();
    Ui::VetDataDialog *ui;
    
};

#endif // VETDATADIALOG_H
