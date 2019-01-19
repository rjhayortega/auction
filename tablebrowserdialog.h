/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef TABLEBROWSERDIALOG_H
#define TABLEBROWSERDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <qstringlist.h>
#include <vector>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class Q3ListBox;
class Q3ListBoxItem;


namespace Ui {
  class TableBrowserDialog;
}

class TableBrowserDialog : public QDialog
{
    Q_OBJECT

public:
    TableBrowserDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~TableBrowserDialog();

  std::vector<int> selectedIndexVector();

public slots:
    void init( QStringList itemList );
    void setMulti( bool selectAll );
    void init( QStringList itemList, QString item );
    int selectedIndex();

protected:

protected slots:

private:
    void init();
    Ui::TableBrowserDialog *ui;
    
};

#endif // TABLEBROWSERDIALOG_H
