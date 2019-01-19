/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef TAGEDITDIALOG_H
#define TAGEDITDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "dao/tagdao.h"
#include "types/customer.h"
#include "types/animalcode.h"
#include "types/transaction.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLabel;
class QLineEdit;
class Q3ListBox;
class Q3ListBoxItem;

namespace Ui {
  class TagEditDialog;
}

class TagEditDialog : public QDialog
{
    Q_OBJECT

public:
    TagEditDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~TagEditDialog();


    typedef enum {EditTransaction, EditSeller} Mode;

    AnimalCode getTagAnimalCode();
    void reset();

public slots:
    void init( Seller seller );
    void init( Transaction trans );
    void populateTagList();
    void loadTag( Q3ListBoxItem * item );
    void saveTag();
    void deleteTag();
    void updateDescrip( const QString & text );

protected:

protected slots:

private:
    vector<Tag> tagList;
    TagDAO dao;
    Seller seller;
    int currentRow;
    Mode mode;
    Transaction transaction;

    void init();
    Ui::TagEditDialog *ui;

};

#endif // TAGEDITDIALOG_H
