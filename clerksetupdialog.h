/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef CLERKSETUPDIALOG_H
#define CLERKSETUPDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "dao/setupdao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QGroupBox;
class Q3Table;
class QCheckBox;
class QLabel;
class QSpinBox;
class QButtonGroup;
class QPushButton;
class QLineEdit;

namespace Ui {
  class ClerkSetupDialog;
}

class ClerkSetupDialog : public QDialog
{
    Q_OBJECT

public:
    ClerkSetupDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~ClerkSetupDialog();


public slots:
    void loadClerkSetup();
    void enableAlternateTicketOption( bool enable );
    void enableZeroBalNotifyOption( bool enable );
    void loadPennerSetup();
    void accept();
    void saveClerkSetup();
    void savePennerSetup();

protected:

protected slots:

private slots:

    void on_zeroBalNotifycheckBox_toggled(bool checked);

private:
    QStringList keyList;
    SetupDAO setup;

    void init();
    Ui::ClerkSetupDialog *ui;
};

#endif // CLERKSETUPDIALOG_H
