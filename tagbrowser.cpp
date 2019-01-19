//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "tagbrowser.h"
#include "ui_tagbrowser.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <Q3Table>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

TagBrowser::TagBrowser( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::TagBrowser)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->sortCombo, SIGNAL( activated(int) ), this, SLOT( sortTagTransactionList() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
TagBrowser::~TagBrowser()
{
    delete ui;
}

#include <algorithm>

void TagBrowser::init()
{
    transactionDao.startBatchMode(true, false, false);
    AnimalCodeDAO::startBatchMode();
    ui->tagTable->setLeftMargin(0);
    populateTagList();
    showTagTable();
}

void TagBrowser::destroy()
{
    transactionDao.endBatchMode();
    AnimalCodeDAO::endBatchMode();
}

#include <qprogressdialog.h>

void TagBrowser::populateTagList()
{
    tagList = tagDao.getTagList();
    std::sort(tagList.begin(), tagList.end(), Tag::compareTagsLT);

    Transaction tempTrans;

    QProgressDialog progressDialog(this);
    progressDialog.setCaption("Loading Tags");
    progressDialog.setLabelText("Gathering Tag Data");

    progressDialog.setModal(true);
    progressDialog.show();
    progressDialog.setMaximum(tagList.size());
    for(unsigned int i = 0; i < tagList.size(); i++)
    {
        tempTrans = transactionDao.getTransactionById(tagList[i].getTransactionId());
        tempTrans.setTagList(vector<Tag>(1, tagList[i]));
        transactionList.push_back(tempTrans);
        progressDialog.setValue(i + 1);
    }
    progressDialog.hide();
}

bool compareTagsLT(Transaction a, Transaction b)
{
    return Tag::compareTagsLT(a.getTagList()[0], b.getTagList()[0]);
}

void TagBrowser::sortTagTransactionList()
{
    switch(ui->sortCombo->currentItem())
    {
    case 0:
        std::sort(transactionList.begin(), transactionList.end(), compareTagsLT);
        break;

    case 1:
        std::sort(transactionList.begin(), transactionList.end(), Transaction::compareIdsLT);
        break;

    case 2:
        std::sort(transactionList.begin(), transactionList.end(), Transaction::compareSellerIdsLT);
        break;

    case 3:
        std::sort(transactionList.begin(), transactionList.end(), Transaction::compareBuyerIdsLT);
        break;
    }

    showTagTable();
}

void TagBrowser::showTagTable()
{
    ui->tagTable->setNumRows(tagList.size());
    for(unsigned int i = 0; i < transactionList.size(); i++)
    {
        ui->tagTable->setText(i, 0, QString::fromStdString(transactionList[i].getTagList()[0].getTag()));
        ui->tagTable->setText(i, 1, QString::number(transactionList[i].getId()));
        ui->tagTable->setText(i, 2, QString::fromStdString(transactionList[i].getTagList()[0].getSellerId()));
        ui->tagTable->setText(i, 3, QString::fromStdString(transactionList[i].getBuyer().getNumber()));
        ui->tagTable->setText(i, 4, QString::fromStdString(transactionList[i].getBuyerPen()));
    }
}

