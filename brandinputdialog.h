/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef BRANDINPUTDIALOG_H
#define BRANDINPUTDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <string>
#include "qpen.h"
#include "qpainter.h"
#include "dao/branddao.h"
#include "brandwidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLabel;
class QLineEdit;
class QFrame;

namespace Ui {
  class BrandInputDialog ;
}

class BrandInputDialog : public QDialog
{
    Q_OBJECT

public:
    BrandInputDialog( QWidget* parent = 0);
    ~BrandInputDialog();

public slots:
    void browseBrands();
    void clearBrand();
    void setPositionEdit();
    void setTransactionEdit();
    void setHeadEdit();
    void setTagEdit();
    void processEditItem();
    void clearPainting( QPainter * cur_painter );
    void drawNoBrandImage();
    void saveImage();

protected:

protected slots:

private:
    bool firstTouch;
    QPixmap *saverImage;
    QPainter *savePainter;
    QPainter *painter;
    QPen *defaultPen;
    typedef enum editItem{None, BrandPosition, TransactionNo, HeadCount, TagNo}EditItem;
    QPainter smallBrandPainter;
    long brandId;
    string brandPosition;
    long transactionNo;
    long headCount;
    string tag;
    BrandDAO brandDao;
    EditItem currentEdit;
    BrandWidget* brandWidget;
    BrandWidget* smallBrandWidget;

    void init();
    void destroy();
    
    Ui::BrandInputDialog *ui;

};

#endif // BRANDINPUTDIALOG_H
