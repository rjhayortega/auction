//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "tageditdialog.h"
#include "ui_tageditdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <Q3ListBox>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include <QMessageBox>

TagEditDialog::TagEditDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::TagEditDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->exitButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->tagListBox, SIGNAL( clicked(Q3ListBoxItem*) ), this, SLOT( loadTag(Q3ListBoxItem*) ) );
    connect( ui->tagDescrip, SIGNAL( textChanged(const QString&) ), this, SLOT( updateDescrip(const QString&) ) );
    connect( ui->tagEdit, SIGNAL( returnPressed() ), this, SLOT( saveTag() ) );
    connect( ui->tagDescrip, SIGNAL( returnPressed() ), this, SLOT( saveTag() ) );
    connect( ui->deleteButton, SIGNAL( clicked() ), this, SLOT( deleteTag() ) );
    connect( ui->burcellosisTagEdit, SIGNAL( returnPressed() ), this, SLOT( saveTag() ) );

    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
TagEditDialog::~TagEditDialog()
{
    delete ui;
}

void TagEditDialog::init()
{
}

void TagEditDialog::init(Seller seller)
{
    this->seller = seller;
    this->transaction = Transaction();
    mode = EditSeller;
    populateTagList();
}

void TagEditDialog::init(Transaction trans)
{
    this->transaction = trans;
    this->seller = trans.getSeller();
    mode = EditTransaction;
    populateTagList();
}

void TagEditDialog::populateTagList()
{
    reset();
    tagList = (mode == EditSeller ? dao.getTagList(seller) : dao.getTagList(transaction));
    sort(tagList.begin(), tagList.end(), Tag::compareTagsLT);
    QStringList stringList;

    for(unsigned int i = 0; i < tagList.size(); i++)
    {
        stringList += QString::fromStdString(tagList[i].getTag()).leftJustify(10, ' ', false) +  QString::fromStdString(tagList[i].getBurcellosisTag());
    }

    ui->tagListBox->clear();
    ui->tagListBox->insertStringList(stringList);
}

void TagEditDialog::loadTag(Q3ListBoxItem* item)
{
    int row = ui->tagListBox->index(item);

    if(0 <= row && row < tagList.size())
    {
        currentRow = row;
        ui->tagEdit->setText(QString::fromStdString(tagList[row].getTag()));
        ui->tagDescrip->setText(QString::number(tagList[row].getAnimalCode().getColor()) +
                                QString::number(tagList[row].getAnimalCode().getType()) +
                                QString::number(tagList[row].getAnimalCode().getFlaw()).rightJustify(2, '0'));
        ui->tagDescripText->setText(QString::fromStdString(tagList[row].getAnimalCode().getDescrip()));
        ui->burcellosisTagEdit->setText(QString::fromStdString(tagList[row].getBurcellosisTag()));
    }
}

void TagEditDialog::saveTag()
{
    if(ui->tagEdit->text().stripWhiteSpace().length() == 0)
    {
        return;
    }
    string conflictSellerId;
    if(0 <= currentRow && currentRow < tagList.size())
    {

        if(dao.conflict(tagList[currentRow], conflictSellerId))
        {
            if(QMessageBox::warning(this, "Caution!",
                                    "This tag already exists for seller: " + QString::fromStdString(conflictSellerId) + ", Overwrite?",
                                    QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
            {
                return;
            }
        }

        dao.deleteTag(tagList[currentRow]);
        tagList[currentRow].setTag(ui->tagEdit->text().toStdString());
        tagList[currentRow].setAnimalCode(getTagAnimalCode());
        tagList[currentRow].setBurcellosisTag(ui->burcellosisTagEdit->text().toStdString());
        dao.saveTag(tagList[currentRow]);
        ui->tagListBox->changeItem(ui->tagEdit->text(), currentRow);
        reset();
    }
    else
    {
        QStringList tagStringList = QStringList::split("-", ui->tagEdit->text());

        if(tagStringList.size() == 1)
        {
            Tag temp = Tag(tagStringList[0].stripWhiteSpace().toStdString(), seller.getNumber(), transaction.getId(), getTagAnimalCode(), ui->burcellosisTagEdit->text().toStdString());

            if(dao.conflict(temp, conflictSellerId))
            {
                if(QMessageBox::warning(this, "Caution!",
                                        "This tag already exists for seller: " + QString::fromStdString(conflictSellerId) + ", Overwrite?",
                                        QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
                {
                    return;
                }
            }

            dao.saveTag(temp);

        }
        else if(tagStringList.size() == 2)
        {
            long firstTag = atol(tagStringList[0].ascii());
            long lastTag = atol(tagStringList[1].ascii());

            vector<string> tagRange = Tag::tagRange(tagStringList[0].ascii(), tagStringList[1].ascii());

            for(long i = 0; i < tagRange.size(); i++)
            {
                cout << tagRange[i] << endl;
                Tag temp = Tag(tagRange[i], seller.getNumber(), transaction.getId(), getTagAnimalCode(), ui->burcellosisTagEdit->text().toStdString());

                if(dao.conflict(temp, conflictSellerId))
                {
                    if(QMessageBox::warning(this, "Caution!",
                                            "Tag: " + QString::fromStdString(temp.getTag()) + " already exists for seller: " + QString::fromStdString(conflictSellerId) + ", Overwrite?",
                                            QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
                    {
                        dao.saveTag(temp);
                    }
                }
                else
                {
                    dao.saveTag(temp);
                }


            }
        }

//        populateTagList();
    }
    populateTagList();

    ui->tagEdit->setFocus();
}


AnimalCode TagEditDialog::getTagAnimalCode()
{
    AnimalCode temp = AnimalCode::fromString(ui->tagDescrip->text().toStdString());
    return AnimalCodeDAO().fillAnimalCode(temp);
}

void TagEditDialog::reset()
{
    currentRow = -1;
    ui->tagEdit->setText("");
    ui->tagDescrip->setText("");
    ui->tagDescripText->setText("");
    ui->burcellosisTagEdit->setText("");
}

void TagEditDialog::deleteTag()
{
    int deleteOption = QMessageBox::warning(this, "Confirm delete",
                                            "You are about delete one or more tags.\n"
                                            "How do you wish to continue?",
                                            "Cancel", "Delete Selected", "Delete All");

    for(unsigned int i = 0; i < tagList.size(); i++)
    {
        switch(deleteOption)
        {
        case 0:
            return;
            break;

        case 1:
            if(ui->tagListBox->isSelected(i))
            {
                dao.deleteTag(tagList[i]);
            }
            break;

        case 2:
            dao.deleteTag(tagList[i]);
            break;
        }
    }

    populateTagList();
}

void TagEditDialog::updateDescrip(const QString& text)
{
    AnimalCode code = getTagAnimalCode();
    ui->tagDescripText->setText(QString::fromStdString(code.getDescrip()));
}
