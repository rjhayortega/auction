/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef TAGBROWSER_H
#define TAGBROWSER_H

#include <qvariant.h>
#include <qdialog.h>
#include <vector>
#include "dao/tagdao.h"
#include "dao/transactiondao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QComboBox;
class Q3Table;

namespace Ui {
  class TagBrowser;
}

class TagBrowser : public QDialog
{
    Q_OBJECT

public:
    TagBrowser( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~TagBrowser();

public slots:
    void populateTagList();
    void sortTagTransactionList();
    void showTagTable();
    void destroy();

protected:

protected slots:

private:
    TagDAO tagDao;
    vector<Tag> tagList;
    TransactionDAO transactionDao;
    vector<Transaction> transactionList;

    void init();
    Ui::TagBrowser *ui;
    
};

#endif // TAGBROWSER_H
