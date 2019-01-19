//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "reportsetupdialog.h"
#include "ui_reportsetupdialog.h"

#include <qvariant.h>
#include <qspinbox.h>
#include <qlabel.h>
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

ReportSetupDialog::ReportSetupDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::ReportSetupDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->okButton, SIGNAL( clicked() ), this, SLOT( save() ) );
    connect( ui->okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
ReportSetupDialog::~ReportSetupDialog()
{
    delete ui;
}

void ReportSetupDialog::init()
{
    ui->firstLineSpinBox->setValue(atoi(setup.get("reportFirstLine").c_str()));
    ui->pageLengthSpinBox->setValue(atoi(setup.get("reportPageLength").c_str()));;
    ui->marketReportComment->setText(QString::fromStdString(setup.get("genMktComment")));
}

void ReportSetupDialog::save()
{
    setup.set("reportFirstLine", QString::number(ui->firstLineSpinBox->value()).toStdString());
    setup.set("reportPageLength", QString::number(ui->pageLengthSpinBox->value()).toStdString());
    setup.set("genMktComment", ui->marketReportComment->text().toStdString());
}
