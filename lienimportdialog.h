/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef LIENIMPORTDIALOG_H
#define LIENIMPORTDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <vector>
#include <string>
#include <time.h>
#include <qprogressdialog.h>
#include <qfileinfo.h>
#include "lienrecord.h"
#include "dao/customerdao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QPushButton;
class QLineEdit;
class QComboBox;

namespace Ui {
  class LienImportDialog;
}

class LienImportDialog : public QDialog
{
    Q_OBJECT

public:
    LienImportDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~LienImportDialog();

    vector<LienRecord> getNebraskaLienList( QString fileName );
    vector<LienRecord> getSouthDakotaLienList( QString fileName );
    vector<LienRecord> getIdahoLienList( QString folderPath, bool & master );
    vector<LienRecord> getIdahoLienMasterList( QFileInfo * fileInfo );
    vector<LienRecord> getIdahoLienSupplementList( QFileInfo * fileInfo, vector<Customer> & deleteVector );
    vector<LienRecord> getNorthDakotaLienList( QString fileName );

public slots:
    void timerEvent( QTimerEvent * event );
    void browse();
    void importLiens();
    void insertLiens( vector<LienRecord> recordList );

protected:

protected slots:

private slots:
    void on_lienImportCancelButton_clicked();

private:
    QProgressDialog* progress;
    time_t start;
    time_t end;
    int progressCount;

    void init();
    
    Ui::LienImportDialog *ui;

};

#endif // LIENIMPORTDIALOG_H
