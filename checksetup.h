/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef CHECKSETUP_H
#define CHECKSETUP_H

#include <qvariant.h>
#include <qdialog.h>
#include <qpainter.h>
#include "reports/textcheck.h"
#include "dao/checkdao.h"
#include "checksetup_frame.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QButtonGroup;
class QRadioButton;
class QFrame;
class QLineEdit;
class QLabel;

#include "ui_checksetup.h"

class CheckSetup : public QDialog
{
    Q_OBJECT

public:
    CheckSetup( QWidget* parent = 0);
    ~CheckSetup();


public slots:
    void paintEvent( QPaintEvent * e );
    void drawFormat();
    void mouseMoveEvent( QMouseEvent * e );
    void save();
    void clearFormat( int buttonId );
    void setCoord( QString tag, CheckItemCoord coord );
    void browse();

protected:

protected slots:

private:
    CheckFormatData checkFormatData;
    CheckDAO dao;
    
    CheckSetupFrame *csf;

    void init();
    void initChecks();
    bool validateCoord(CheckItemCoord& coord);
    Ui::CheckSetup ui;
};

#endif // CHECKSETUP_H
