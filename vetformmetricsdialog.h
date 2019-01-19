/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef VETFORMMETRICSDIALOG_H
#define VETFORMMETRICSDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "dao/setupdao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTable;
class QPushButton;

namespace Ui {
  class VetFormMetricsDialog;
}

class VetFormMetricsDialog : public QDialog
{
    Q_OBJECT

public:
    VetFormMetricsDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~VetFormMetricsDialog();

    QString defaultTOFStr( int formId );
    QString defaultHeightStr( int formId );

public slots:
    void loadMetrics();
    void saveMetrics();

protected:

protected slots:

private:
    SetupDAO setup;

    void init();
    Ui::VetFormMetricsDialog *ui;
};

#endif // VETFORMMETRICSDIALOG_H
