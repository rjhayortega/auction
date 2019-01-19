/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "types/transaction.h"
#include "dao/setupdao.h"
#include "dao/printerdao.h"
#include "dao/salemanager.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLineEdit;
class QSpinBox;
class QLabel;
class QListBox;
class QListBoxItem;
class QComboBox;
class QPushButton;
class SMPlayer;

namespace Ui { 
  class TransactionDialog;
}

class TransactionDialog : public QDialog
{
    Q_OBJECT

public:
    TransactionDialog(QWidget* parent = 0);
    ~TransactionDialog();

    virtual Transaction getTransaction();

public slots:
    void loadTransaction( long transId );
    void saveButtonHandler();
    void printButtonHandler();
    void populateTagList();
    void addTag();
    void saveTagList();
    void deleteTags();
    void deleteSelectedTag();
    void saveTransaction();
    void updateDescrip( const QString & text );
    void recalcAverageWeight( const QString & totalWeightStr );
    void updateModeBox( int item );
    void updateMode( int item );
    void formatToDollarString( const QString & text );
    void printTicket();
    void playVideo();
    void quitPlayer();

protected:

protected slots:

private:
    Transaction transaction;
    bool block;
    SetupDAO setup;
    vector<Tag> tagList;
    PrinterBase * m_ticketPrinter;
    QString weighMaster;
    SaleManager sale;
    SMPlayer* m_smplayer;

    QString m_videoFileName;
    int  m_videoOffset;
    int  m_transactionVideoDuration;

    void init();
    void videoFileName();
    
    Ui::TransactionDialog *ui;
};

#endif // TRANSACTIONDIALOG_H
