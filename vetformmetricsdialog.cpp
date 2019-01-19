//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "vetformmetricsdialog.h"
#include "ui_vetformmetricsdialog.h"

#include <qvariant.h>
#include <Q3Table>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

VetFormMetricsDialog::VetFormMetricsDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::VetFormMetricsDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->okButton, SIGNAL( clicked() ), this, SLOT( saveMetrics() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
VetFormMetricsDialog::~VetFormMetricsDialog()
{
    delete ui;
}

void VetFormMetricsDialog:: init()
{
    loadMetrics();
}

void VetFormMetricsDialog::loadMetrics()
{
    QString vetFormMetrics = QString::fromStdString(setup.get("vetFormMetrics"));

    QStringList metricsList = QStringList::split(";", vetFormMetrics, true);
    QStringList metric;
    bool metricOk;

    for(int i = 0; i < ui->metricsTable->numRows(); i++)
    {
        metricOk = false;

        if(i < metricsList.size())
        {
            metric = QStringList::split(":", metricsList[i], true);

            if(metric.size() == 2)
            {
                metricOk = true;
                bool conversionOk;

                metric[0].toLong(&conversionOk);

                if(conversionOk)
                {
                    ui->metricsTable->setText(i, 0, metric[0]);
                }
                else
                {
                    ui->metricsTable->setText(i, 0, defaultTOFStr(i));
                }

                metric[1].toLong(&conversionOk);

                if(conversionOk)
                {
                    ui->metricsTable->setText(i, 1, metric[1]);
                }
                else
                {
                    ui->metricsTable->setText(i, 1, defaultHeightStr(i));
                }
            }
        }

        if(!metricOk)
        {
            ui->metricsTable->setText(i, 0, defaultTOFStr(i));
            ui->metricsTable->setText(i, 1, defaultHeightStr(i));
        }
    }
}


QString VetFormMetricsDialog::defaultTOFStr(int formId)
{
    QString result;
    switch(formId)
    {
    default:
        result = "0";
        break;
    }

    return result;
}

QString VetFormMetricsDialog::defaultHeightStr(int formId)
{
    QString result;

    switch(formId)
    {
    default:
        result = "64";
        break;
    }

    return result;
}

void VetFormMetricsDialog::saveMetrics()
{
    QStringList resultList;

    for(int i = 0; i < ui->metricsTable->numRows(); i++)
    {
        resultList += QString::number(ui->metricsTable->text(i, 0).toLong()) + ":" + QString::number(ui->metricsTable->text(i, 1).toLong());
    }


    setup.set("vetFormMetrics",  resultList.join(";").toStdString());

    QDialog::accept();
}
