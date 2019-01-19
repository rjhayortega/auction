//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end


#include "transactiondialog.h"
#include "ui_transactiondialog.h"

#include <qvariant.h>
#include <qlineedit.h>
#include <qspinbox.h>
#include <qlabel.h>
#include <Q3ListBox>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

#include "dao/transactiondao.h"
#include <QMessageBox>
#include "reports/transactionticket.h"
//#include "smplayer.h"
#include <string>

TransactionDialog::TransactionDialog( QWidget* parent )
    : QDialog( parent ), ui(new Ui::TransactionDialog) //,
//      m_smplayer(0),
//      m_transactionVideoDuration(0)
{

    ui->setupUi(this);
    // signals and slots connections
    connect( ui->cancelTransaction, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->buttSaveTransaction, SIGNAL( clicked() ), this, SLOT( saveButtonHandler() ) );
    connect( ui->transeditDesc, SIGNAL( textChanged(const QString&) ), this, SLOT( updateDescrip(const QString&) ) );
    connect( ui->transeditWeight, SIGNAL( textChanged(const QString&) ), this, SLOT( recalcAverageWeight(const QString&) ) );
    connect( ui->modeSpinBox, SIGNAL( valueChanged(int) ), this, SLOT( updateModeBox(int) ) );
    connect( ui->transeditMode, SIGNAL( activated(int) ), this, SLOT( updateMode(int) ) );
    connect( ui->transeditBid, SIGNAL( textChanged(const QString&) ), this, SLOT( formatToDollarString(const QString&) ) );
    connect( ui->printTicketButton, SIGNAL( clicked() ), this, SLOT( printButtonHandler() ) );
    connect( ui->tagEdit, SIGNAL( returnPressed() ), this, SLOT( addTag() ) );
    connect( ui->deleteTagButton, SIGNAL( clicked() ), this, SLOT( deleteTags() ) );
//    connect( ui->videoPushButton, SIGNAL( clicked() ), this, SLOT( playVideo() ) );

    init();
}

TransactionDialog::~TransactionDialog()
{
    delete ui;
    delete m_ticketPrinter;
//    if (m_smplayer) {
//        delete m_smplayer;
//    }
}

void TransactionDialog::init()
{
//    Q_INIT_RESOURCE(icons);
    block = false;
    ui->transeditBid->setText("000");
    m_ticketPrinter = PrinterDAO().getPrinter(PrinterDAO::Report);
    ui->manLabel->setText("MAN");

    if(!sale.currentSaleOpen())
    {
        ui->deleteTagButton->setEnabled(false);
        ui->buttSaveTransaction->setEnabled(false);
    }


}

///////////////////////////////////////////////////////////////////////////////
//
// name:    loadTransaction(long transId)
//
// purpose: loads a transaction from the database into the dialog
//
// calling params: long transId - the transaction id of the transaction to load
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void TransactionDialog::loadTransaction(long transId)
{
    transaction = TransactionDAO().getTransactionById(transId);
    ui->transeditNumber->setText(QString::number(transId));
    ui->transeditSeller->setText(QString::fromStdString(transaction.getSeller().getNumber()));
    ui->transeditBuyer->setText(QString::fromStdString(transaction.getBuyer().getNumber()));
    ui->transeditHead->setText(QString::number(transaction.getHead(false, false, true)));
    ui->transeditWeight->setText(QString::number(transaction.getWeight()));
    ui->transeditAvgWt->setText(QString::number(long(transaction.getAverageWeight())));
    AnimalCode code = transaction.getAnimalCode();
    ui->transeditDesc->setText(QString::number(code.getColor()) + QString::number(code.getType()) + QString::number(code.getFlaw()).rightJustify(2, '0'));
    ui->transedTextDesc->setText(QString::fromStdString(code.getDescrip()));
    ui->transeditBid->setText(QString::number(transaction.getPrice(), 'f', 2));
    weighMaster = QString::fromStdString(transaction.getWeighMaster());
    ui->transeditMode->setCurrentItem(Transaction::SALE_MODE(transaction.getMode()));
    ui->modeSpinBox->setValue(transaction.getMode());
    ui->transeditSPen->setText(QString::fromStdString(transaction.getSellerPen()));
    ui->transeditBPen->setText(QString::fromStdString(transaction.getBuyerPen()));
    ui->transeditComment->setText(QString::fromStdString(transaction.getComment()));
    ui->manLabel->setText(transaction.isManual() ? "MAN" : "");
    populateTagList();

    videoFileName();
    if (m_videoFileName.isEmpty()) {
        ui->videoPushButton->setEnabled(false);
    } else {
        ui->videoPushButton->setEnabled(true);
    }
}

void TransactionDialog::saveButtonHandler()
{
    saveTransaction();
    QDialog::accept();
}

void TransactionDialog::printButtonHandler()
{
    saveTransaction();
    printTicket();
    QDialog::accept();
}

void TransactionDialog::populateTagList()
{
    tagList = transaction.getTagList();
    sort(tagList.begin(), tagList.end(), Tag::compareTagsLT);
    QStringList tagStringList;
    for(unsigned int i = 0; i < tagList.size(); i++)
    {
        tagStringList += QString::fromStdString(tagList[i].getTag());
    }
    ui->tagListBox->clear();
    ui->tagListBox->insertStringList(tagStringList);
}

void TransactionDialog::addTag()
{
    QStringList tagStringList = QStringList::split("-", ui->tagEdit->text());
    Tag temp;
    string conflictingSeller;
    TagDAO tagDao;

    if(tagStringList.size() == 1)
    {
        QString tagString = tagStringList[0].stripWhiteSpace();
        if(tagString.length() > 0)
        {
            temp = Tag(tagString.toStdString(), transaction.getSeller().getNumber(), transaction.getId(), transaction.getAnimalCode());

            if(tagDao.conflict(temp, conflictingSeller))
            {
                if(QMessageBox::warning(this, "Caution!",
                                        "Tag: " + QString::fromStdString(temp.getTag()) + " already exists for seller: " + QString::fromStdString(conflictingSeller) + ", Overwrite?",
                                        QMessageBox::Yes, QMessageBox::No)
                        == QMessageBox::Yes)
                {
                    tagList.push_back(temp);
                }
            }
            else
            {
                tagDao.fillTag(temp);
                temp.setTransactionId(transaction.getId());
                temp.setAnimalCode(transaction.getAnimalCode());
                tagList.push_back(temp);
            }
        }
    }
    else if(tagStringList.size() == 2)
    {
        vector<string> tagRange = Tag::tagRange(tagStringList[0].toStdString(), tagStringList[1].toStdString());

        for(long i = 0; i < tagRange.size(); i++)
        {
            temp = Tag(tagRange[i], transaction.getSeller().getNumber(), transaction.getId(), transaction.getAnimalCode());

            if(tagDao.conflict(temp, conflictingSeller))
            {
                if(QMessageBox::warning(this, "Caution!",
                                        "Tag: " + QString::fromStdString(temp.getTag()) + " already exists for seller: " + QString::fromStdString(conflictingSeller) + ", Overwrite?",
                                        QMessageBox::Yes, QMessageBox::No)
                        == QMessageBox::Yes)
                {
                    tagList.push_back(temp);
                }
            }
            else
            {
                tagList.push_back(temp);
            }
        }
    }

    transaction.setTagList(tagList);

    populateTagList();
    ui->tagEdit->setText("");
    ui->tagEdit->setFocus();
}

void TransactionDialog::saveTagList()
{
    tagList = transaction.getTagList();
    TagDAO tagDao;
    tagDao.clearTransactionTags(transaction);
    for(unsigned int i = 0; i < tagList.size(); i++)
    {
        tagList[i].setTransactionId(transaction.getId());
        tagList[i].setSellerId(transaction.getSeller().getNumber());
        tagDao.saveTag(tagList[i]);
    }
}

void TransactionDialog::deleteTags()
{
    int opt = QMessageBox::question(this, "Disambiguation",
                                    "Which tags do you wish to delete?",
                                    "Selected", "All", "None");

    switch(opt)
    {
    case 0:
        deleteSelectedTag();
        break;

    case 1:
        transaction.setTagList(vector<Tag>());
        populateTagList();
        break;

    default:
        break;
    }
}

void TransactionDialog::deleteSelectedTag()
{
    vector<Tag> tempList;

    for(unsigned int i = 0; i < ui->tagListBox->numRows(); i++)
    {
        if(!ui->tagListBox->isSelected(i))
        {
            tempList.push_back(tagList[i]);
        }
    }
    transaction.setTagList(tempList);
    populateTagList();
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    saveTransaction()
//
// purpose: saves the current transaction to the database
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void TransactionDialog::saveTransaction()
{
    TransactionDAO dao;
    AnimalCode tempCode = AnimalCode::fromString(ui->transeditDesc->text().toStdString());
    AnimalCodeDAO codeDao;
    codeDao.fillAnimalCode(tempCode);

    QString bidStr = ui->transeditBid->text();
    bidStr.replace('$', ' ');
    double bid = bidStr.toDouble();
    DateTime created = transaction.getCreated();
    long transNo = ui->transeditNumber->text().toLong();

    bool manual = (ui->manLabel->text() == "MAN");

    // [KLN] mod to make sure Buyer Number is not blank if it's a manually entered NoSale!
    string buyerNum = ui->transeditBuyer->text().toStdString();
//    int modeInt = transaction.getMode();
    if ( buyerNum.empty() )
    {
        ui->transeditBuyer->setText("UNKNOWN");
    }
    // [KLN] end mod

    transaction = Transaction(ui->transeditNumber->text().toLong(), SellerDAO::loadFromNumber(ui->transeditSeller->text().toStdString()),
                              BuyerDAO::loadFromNumber(ui->transeditBuyer->text().toStdString()),
                              ui->transeditHead->text().toLong(), ui->transeditWeight->text().toLong(),
                              bid, Transaction::SALE_MODE(ui->transeditMode->currentItem()),
                              tempCode,
                              ui->transedTextDesc->text().toStdString(), ui->transeditSPen->text().toStdString(), ui->transeditBPen->text().toStdString(), created,
                              Date::currentDate(), ui->transeditComment->text().toStdString());

    transaction.setWeighMaster(weighMaster.toStdString());
    transaction.setManual(manual);

//    // [KLN] debug start
//std:cout << "=========================================" << endl;
//    cout << "trans Buyer: " << buyerNum << endl;
//    cout << "trans  Mode: " << modeInt << endl;
//    //    cout << "" <<  << endl;
//    //    cout << "" <<  << endl;
//    cout << "=========================================" << endl;
//    // [KLN] debug end

    long id = dao.saveTransaction(transaction);
    transaction.setId(id);
    transaction.setTagList(tagList);

    saveTagList();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    getTransaction()
//
// purpose: returns the transaction the dialog represents
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

Transaction TransactionDialog::getTransaction()
{
    return transaction;
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    updateDescrip(const QString& text)
//
// purpose: updates the descrip text label based on the code represented by
//          the string text
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void TransactionDialog::updateDescrip(const QString& text)
{
    AnimalCodeDAO dao;
    QStringList codeList = QStringList::split("-", text, TRUE);
    AnimalCode tempCode = AnimalCode::fromString(text.toStdString());

    ui->transedTextDesc->setText(QString::fromStdString(dao.fillAnimalCode(tempCode).getDescrip()));
    transaction.setAnimalCode(tempCode);
}


void TransactionDialog::recalcAverageWeight(const QString &totalWeightStr)
{
    if(ui->transeditHead->text().toLong() > 0)
    {
        ui->transeditAvgWt->setText(QString::number(getWeightAmount(ui->transeditWeight->text().toDouble() / ui->transeditHead->text().toLong())));
    }
}

//void TransactionDialog::startTagEditor()
//{
// TagEditDialog tagEditor(this);
//  tagEditor.init(transaction);
// tagEditor.exec();
//
// loadTransaction(transaction.getId());
//}

void TransactionDialog::updateModeBox(int item)
{
    if(!block)
    {
        block = true;
        ui->transeditMode->setCurrentItem(item);
        block = false;
    }
}

void TransactionDialog::updateMode(int item)
{
    if(!block)
    {
        block = true;
        ui->modeSpinBox->setValue(item);
        block = false;
    }
}

void TransactionDialog::formatToDollarString(const QString& text)
{
    int cursorPosition = ui->transeditBid->cursorPosition();
    string buf;
    bool foundStart = false;

    for(unsigned int i = 0; i < text.length(); i++)
    {
        if(!foundStart)
        {
            if(isdigit(text.ascii()[i]) && text.ascii()[i] != '0')
            {
                foundStart = true;
            }
        }

        if(isdigit(text.ascii()[i]) && foundStart)
        {
            buf += string(1, text.ascii()[i]);
        }
    }

    if(buf.size() < 3)
    {
        for(unsigned int i = 0; i < buf.size() - 3; i++)
        {
            buf = "0" + buf;
        }
    }

    buf.insert(buf.length() - 2, ".");
    buf = string("$") + buf;
    ui->transeditBid->setText(QString::fromStdString(buf));
}

void TransactionDialog::printTicket()
{
    TransactionTicket ticket(transaction, setup.get("genMktName"));
    string ticketText = ticket.text();
    m_ticketPrinter->print(ticketText,QTextDocument(), LinePrinter::Normal);
}


void TransactionDialog::playVideo()
{
//    if (! m_videoFileName.isEmpty()) {
//        if ( m_smplayer == 0 ) {
//            m_smplayer = new SMPlayer(QDir::tempPath(),this, ui->videoWidget );
//            connect(m_smplayer,SIGNAL(quitPlayer()), this, SLOT(quitPlayer()));
//        }
//        m_smplayer->start();

//        m_smplayer->gui()->returnCore()->setAMarker(m_videoOffset);
//        m_smplayer->gui()->returnCore()->setBMarker(m_transactionVideoDuration);

//        m_smplayer->gui()->returnCore()->open(m_videoFileName,m_videoOffset);
//    }
}

void TransactionDialog::videoFileName()
{
    m_videoFileName.clear();  // Clear video file name. If it is empty on exit, no video found.

    QDir dir(QDir::currentPath());
    DateTime transDate= transaction.getVideoStart();
    DateTime transEnd = transaction.getCreated();
    QString strDate;
    QString strTime;
    QString strEndTime;
    QString strDateTime = QString::fromStdString(transDate.toString("yyyy/mm/dd"));
    QString strEndDateTime = QString::fromStdString(transEnd.toString("yyyy/mm/dd"));

    int indexSpace = strDateTime.lastIndexOf(" ");
    int indexSpaceEndTime = strEndDateTime.lastIndexOf(" ");
    if ( (indexSpace != -1) && (indexSpaceEndTime != -1)) {
        strDate = strDateTime.left(indexSpace);
        strTime = strDateTime.right(strDateTime.size()-indexSpace-1);
        strEndTime = strEndDateTime.right(strDateTime.size()-indexSpaceEndTime-1);
    }
    else {
        qDebug() << "No recorded video found for this trans action creation date:" + strDate;
        return;
    }
    QString folderPath = "Videos/" + strDate;

    QStringList filters;
    filters << "*.avi";
    int durationTime = 0;

    if (! dir.cd(folderPath)) {
        qDebug() << "No recorded video found for this transaction creation date:" + strDate;
        return;
    } else {
        QStringList dirEntries = dir.entryList(filters);
        int dirEntriesSize = dirEntries.size();
        if ( dirEntriesSize > 0 ) {
            QString fileName = QString();
            int qMinOffset = 24*3600;
            for (int i = 0; i< dirEntriesSize; i++) {
                //make time format again from file name

                QString convertedFileName = dirEntries[i];
                convertedFileName = convertedFileName.replace(QString("_"),QString(":"));
                //remove extension
                convertedFileName = convertedFileName.left(convertedFileName.size()-4);
                QTime fileTime = QTime::fromString(convertedFileName,"hh:mm:ss");
                QTime transTime = QTime::fromString(strTime,"hh:mm:ss");
                QTime transEndTime = QTime::fromString(strEndTime,"hh:mm:ss");
                durationTime = transTime.secsTo(transEndTime);
                if (fileTime < transTime) {
                    int offset = fileTime.secsTo(transTime);
                    if (offset <= qMinOffset) {
                        qMinOffset = offset;
                        fileName =  dirEntries[i];
                    }
                }

            }
            if (!fileName.isEmpty()) {
                m_videoFileName = qApp->applicationDirPath()+"/"+folderPath+"/"+fileName;
                m_videoOffset = qMinOffset;
                m_transactionVideoDuration = durationTime;

            }

        }
    }
}


void TransactionDialog::quitPlayer()
{
//    if (m_smplayer) {
//        delete m_smplayer;
//        m_smplayer=0;
//    }
}
