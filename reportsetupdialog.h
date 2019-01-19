/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef REPORTSETUPDIALOG_H
#define REPORTSETUPDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "dao/setupdao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QSpinBox;
class QLabel;
class QTextEdit;
class QPushButton;

namespace Ui {
class ReportSetupDialog;
}


class ReportSetupDialog : public QDialog
{
    Q_OBJECT

public:
    ReportSetupDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~ReportSetupDialog();


public slots:
    void save();

protected:

protected slots:

private:
    SetupDAO setup;

    void init();
    Ui::ReportSetupDialog *ui;

};

#endif // REPORTSETUPDIALOG_H
