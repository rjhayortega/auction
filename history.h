/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef HISTORY_H
#define HISTORY_H

#include <qvariant.h>
#include <qdialog.h>
#include "types/historyitem.h"
#include "dao/historydao.h"
#include "dao/salemanager.h"
#include "dao/animalcodedao.h"
#include "autofilledit.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QComboBox;
class QLabel;
class QDateEdit;
class QPushButton;
class QLineEdit;

namespace Ui {
  class History;
}

class History : public QDialog
{
    Q_OBJECT

public:
    History( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~History();


    void loadHistoryList();

public slots:
    void init();
    void initIndex( int indexNo );
    void populateHistory();
    void printHistory();
    void predictParamater( const QString & parameter );
    void clear();

protected:

protected slots:
    
private:
    QString lastParameter;
    AnimalCodeDAO codeDao;
    HistoryDAO historyDao;
    vector<HistoryItem> historyList;
    AutoFillEdit* historyParamaterEdit;

    void destroy();
    
    Ui::History *ui;

};

#endif // HISTORY_H
