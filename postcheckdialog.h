/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef POSTCHECKDIALOG_H
#define POSTCHECKDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "dao/checkdao.h"

#include <QMessageBox>
#include <QInputDialog>
#include "ui_postcheckdialog.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QPushButton;


class PostCheckDialog : public QDialog
{
    Q_OBJECT

public:
    PostCheckDialog( QWidget* parent = 0);
    ~PostCheckDialog();


    virtual Check getRealCheck( vector<Check> checkList );

public slots:
    void loadCheck();
    void proccessPost();
    void displayCheckInfo();

protected:

protected slots:

private:
    CheckDAO checkDao;
    Check check;

    void init();

    Ui::PostCheckDialog ui;
};

#endif // POSTCHECKDIALOG_H
