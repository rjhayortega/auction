//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "scalesetupdialog.h"
#include "ui_scalesetupdialog.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include <QFileDialog>

ScaleSetupDialog::ScaleSetupDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::ScaleSetupDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->saveButton, SIGNAL( clicked() ), this, SLOT( save() ) );
    connect( ui->saveButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( ui->browseButton, SIGNAL( clicked() ), this, SLOT( browse() ) );
    connect( ui->teleWeightCheckBox, SIGNAL( clicked() ), this, SLOT( loadScale() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
ScaleSetupDialog::~ScaleSetupDialog()
{
    qDebug("ScaleSetupDialog::~ScaleSetupDialog()");
    delete ui;
}

void ScaleSetupDialog::init()
{
    charValueList << "0x05" << "0x0A" << "0x0D" << "0x02";
    charNameList  << "ENQ"  << "LF"   << "CR"   << "STX";

    QStringList charList;

    for(int i = 0; i < (charNameList.size() < charValueList.size() ? charNameList.size() : charValueList.size()); i++)
    {
        charList += charValueList[i] + " (" + charNameList[i] + ") ";
    }

    ui->startCharCombo->clear();
    ui->endCharCombo->clear();

    QString motion = QString::fromStdString(setup.get("genScaleMotion"));
    if ( motion.isNull() || motion.isEmpty() ) {
        motion = "M";
    }

    ui->startCharCombo->insertStringList(charList);
    ui->endCharCombo->insertStringList(charList);
    ui->teleWeightCheckBox->setChecked(setup.getBoolean("useTeleweight"));
    ui->lineEditMotionChar->setText(motion.trimmed());
    loadScale();
}

void ScaleSetupDialog::loadScale()
{
    string portKey = "genScalePort";

    QStringList deviceList = QStringList::split(",", QString::fromStdString(setup.get(portKey)), true);

    // On the deviceList and formatList switches
    // falls through on purpose, prevents odd configurations from
    // causing this to crash. Really, this shouldn't be neccessary, but I
    // feel more comfortable including this because I am not sure
    // how previous versions have been configured. This should keep
    // it safe
    int index;

    switch(deviceList.size())
    {
    default:
    case 5:
        ui->stopBitCombo->setCurrentText(deviceList[4]);
    case 4:
        switch(deviceList[3].upper().ascii()[0])
        {
        case 'N':
        default:
            index = 0;
            break;

        case 'O':
            index = 1;
            break;
        case 'E':
            index = 2;
            break;
        }
        ui->parityCombo->setCurrentItem(index);
    case 3:
        ui->dataBitCombo->setCurrentText(deviceList[2]);
    case 2:
        ui->baudCombo->setCurrentText(deviceList[1]);
    case 1:
        ui->devicePathEdit->setText(deviceList[0]);
    case 0:
        break;
    }

    if(ui->teleWeightCheckBox->isChecked())
    {
        ui->retrievalModeGroup->setEnabled(false);
        ui->startCharCombo->setEnabled(false);
        ui->formatStringEdit->setEnabled(false);
        ui->endCharCombo->setEnabled(false);
    }
    else
    {
        ui->retrievalModeGroup->setEnabled(true);
        ui->startCharCombo->setEnabled(true);
        ui->formatStringEdit->setEnabled(true);
        ui->endCharCombo->setEnabled(true);

        QStringList formatList = QStringList::split(',', QString::fromStdString(setup.get("genScaleFormat")));

// falls through on purpose to
        switch(formatList.size())
        {
        case 4:
            index = charValueList.findIndex(formatList[3]);

            if(index != -1)
            {
                ui->endCharCombo->setCurrentItem(index);
            }

        case 3:
            ui->formatStringEdit->setText(formatList[2]);
        case 2:
            index = charValueList.findIndex(formatList[1]);
            if(index != -1)
            {
                ui->startCharCombo->setCurrentItem(index);
            }
        case 1:
            if(formatList[0].upper() == "C")
            {
                ui->continuousRadio->setChecked(true);
            }
            else
            {
                ui->demandRadio->setChecked(true);
            }
        case 0:
            break;
        }
    }
}

void ScaleSetupDialog::save()
{
    setup.setBoolean("useTeleWeight", ui->teleWeightCheckBox->isChecked());
    setup.set("genScaleLoc", "1");    // as far as I can tell, these serve no useful purpose, but if
    setup.set("genScaleType", "1");  // they are not set, the clerk program crashes.
    setup.set("genScaleMotion", ui->lineEditMotionChar->text().toStdString());

    string portKey = "genScalePort";

    QString portString;
    QString parityChar;

    switch(ui->parityCombo->currentItem())
    {
    case 0:
        parityChar = "N";
        break;

    case 1:
        parityChar = "O";
        break;
    case 2:
        parityChar = "E";
        break;
    }
    portString = ui->devicePathEdit->text() + "," + ui->baudCombo->currentText() + "," + ui->dataBitCombo->currentText() + "," + parityChar + "," + ui->stopBitCombo->currentText();

    setup.set(portKey, portString.toStdString());

    if(!ui->teleWeightCheckBox->isChecked())
    {
        QString modeChar;

        if(ui->continuousRadio->isChecked())
        {
            modeChar = "C";
        }
        else
        {
            modeChar = "D";
        }

        QStringList  formatStringList;
        formatStringList << modeChar << charValueList[ui->startCharCombo->currentItem()] << ui->formatStringEdit->text() << charValueList[ui->endCharCombo->currentItem()];
        setup.set("genScaleFormat", formatStringList.join(",").toStdString());
    }
}

void ScaleSetupDialog::browse()
{
    QString path = QFileDialog::getOpenFileName("/dev/", "Serial Ports (ttyS0 ttyS1 ttyS2 ttyS3 ttyS4 ttyUSB0 ttyUSB1 ttyUSB2 ttyUSB3 ttyUSB4)");
    if(path != QString::null)
    {
        ui->devicePathEdit->setText(path);
    }
}
