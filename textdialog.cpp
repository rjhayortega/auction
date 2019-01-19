//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "textdialog.h"
#include "ui_textdialog.h"

#include <qvariant.h>
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

TextDialog::TextDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::TextDialog)
{
    ui->setupUi(this);

    // signals and slots connections
    connect( ui->okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( ui->cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
TextDialog::~TextDialog()
{
    delete ui;
}

void TextDialog::init()
{
}

void TextDialog::init(QString caption, QString text)
{
    this->setCaption(caption);
    ui->textEdit->setText(text);
    ui->textEdit->setFocus();
}

QString TextDialog::text()
{
    return ui->textEdit->text();
}

