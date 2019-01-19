/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef BRANDBROWSERDIALOG_H
#define BRANDBROWSERDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <vector>
#include "dao/branddao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class Q3Table;

namespace Ui {
  class BrandBrowserDialog;
}

class BrandBrowserDialog : public QDialog
{
    Q_OBJECT

public:
    BrandBrowserDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~BrandBrowserDialog();


public slots:
    void loadBrandList();
    void nextGroup();
    void previousGroup();
    void lastGroup();
    void firstGroup();
    void clearBrandTable();
    void initBrandTable();
    void processColumn1();
    void processColumn2();
    void processColumn3();
    void processColumn4();
    void processItem( int col );
    void deleteColumn1();
    void deleteColumn2();
    void deleteColumn3();
    void deleteColumn4();
    void deleteBrand( int column );
    void copyColumn1();
    void copyColumn2();
    void copyColumn3();
    void copyColumn4();
    void copyColumn( int column );

protected:

protected slots:

private:
    BrandDAO brandDao;
    vector<Brand> brandList;
    vector<Brand> fullBrandList; // [KLN] add
    int offset;
    typedef enum editItem{None, BrandPosition, TransactionNo, HeadCount, TagNo}EditItem;
    EditItem editItem;
    long currentIndex;

    void init();
    
    Ui::BrandBrowserDialog *ui;

};

#endif // BRANDBROWSERDIALOG_H
