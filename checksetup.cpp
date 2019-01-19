//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Addui.setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "checksetup.h"
#include "ui_checksetup.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qframe.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include <QMouseEvent>
#include <QFileDialog>

CheckSetup::CheckSetup( QWidget* parent): QDialog( parent)
{
    ui.setupUi(this);
    //csf = new CheckSetupFrame();
    //csf =ui.checkFormat;
    //csf->formatFont = QFont("Bitstream Vera Sans Mono");
    //csf->formatFont.setPixelSize(13);


    // signals and slots connections
    connect(ui.saveButton, SIGNAL( clicked() ), this, SLOT( save() ) );
    //connect(ui.checkItemGroup, SIGNAL( clicked(int) ), this, SLOT( clearFormat(int) ) );
    connect(ui.showAddress1, SIGNAL(stateChanged(int)), ui.checkSetupWidget, SLOT(checkedAddress1()));
    connect(ui.showAddress2, SIGNAL(stateChanged(int)), ui.checkSetupWidget, SLOT(checkedAddress2()));
    connect(ui.showAmount, SIGNAL(stateChanged(int)), ui.checkSetupWidget, SLOT(checkedAmount()));
    connect(ui.showCity, SIGNAL(stateChanged(int)), ui.checkSetupWidget, SLOT(checkedCity()));
    connect(ui.showDate, SIGNAL(stateChanged(int)), ui.checkSetupWidget, SLOT(checkedDate()));
    connect(ui.showHead, SIGNAL(stateChanged(int)), ui.checkSetupWidget, SLOT(checkedHead()));
    connect(ui.showMemo, SIGNAL(stateChanged(int)), ui.checkSetupWidget, SLOT(checkedMemo()));
    connect(ui.showNumber, SIGNAL(stateChanged(int)), ui.checkSetupWidget, SLOT(checkedNumber()));
    connect(ui.showPayee, SIGNAL(stateChanged(int)), ui.checkSetupWidget, SLOT(checkedPayee()));
    connect(ui.showSignature, SIGNAL(stateChanged(int)), ui.checkSetupWidget, SLOT(checkedSignature()));
    connect(ui.showTextAmount, SIGNAL(stateChanged(int)), ui.checkSetupWidget, SLOT(checkedTextAmount()));
    connect(ui.browseButton, SIGNAL( clicked() ), this, SLOT( browse() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CheckSetup::~CheckSetup()
{

}

void CheckSetup::init()
{
    qDebug("CheckSetup::init()");
    checkFormatData = dao.getCheckFormat(true);
    ui.sigFilePathEdit->setText(QString::fromStdString(checkFormatData.getSignaturePath()));
    initChecks();
    SetupDAO setup;
    ui.preSpace->setText(QString::fromStdString(setup.get("chkPreSpaceLines")));
    qDebug("CheckSetup::init()   exit!");
}

void CheckSetup::initChecks()
{
    QMap<QString, QPair<int,int>* > labels;
    CheckItemCoord coord;
    coord = checkFormatData.getDateCoord();
    if(validateCoord(coord)){
        ui.showDate->setCheckState(Qt::Checked);
        labels.insert("Date", new QPair<int, int>(coord.getRow(), coord.getCol()));
    }
    coord = checkFormatData.getAddress1Coord();
    if(validateCoord(coord)){
        ui.showAddress1->setCheckState(Qt::Checked);
        labels.insert("Address 1", new QPair<int, int>(coord.getRow(), coord.getCol()));
    }
    coord = checkFormatData.getAddress2Coord();
    if(validateCoord(coord)){
        ui.showAddress2->setCheckState(Qt::Checked);
        labels.insert("Address 2", new QPair<int, int>(coord.getRow(), coord.getCol()));
    }
    coord = checkFormatData.getAmountCoord();
    if(validateCoord(coord)){
        ui.showAmount->setCheckState(Qt::Checked);
        labels.insert("Amount", new QPair<int, int>(coord.getRow(), coord.getCol()));
    }
    coord = checkFormatData.getCityStZipCoord();
    if(validateCoord(coord)){
        ui.showCity->setCheckState(Qt::Checked);
        labels.insert("City, St Zip", new QPair<int, int>(coord.getRow(), coord.getCol()));
    }
    coord = checkFormatData.getCommentCoord();
    if(validateCoord(coord)){
        ui.showMemo->setCheckState(Qt::Checked);
        labels.insert("Memo", new QPair<int, int>(coord.getRow(), coord.getCol()));
    }
    coord = checkFormatData.getHeadCoord();
    if(validateCoord(coord)){
        ui.showHead->setCheckState(Qt::Checked);
        labels.insert("Head Count", new QPair<int, int>(coord.getRow(), coord.getCol()));
    }
    coord = checkFormatData.getNumberCoord();
    if(validateCoord(coord)){
        ui.showNumber->setCheckState(Qt::Checked);
        labels.insert("Number", new QPair<int, int>(coord.getRow(), coord.getCol()));
    }
    coord = checkFormatData.getPayeeCoord();
    if(validateCoord(coord)){
        ui.showPayee->setCheckState(Qt::Checked);
        labels.insert("Payee", new QPair<int, int>(coord.getRow(), coord.getCol()));
    }
    coord = checkFormatData.getSignatureCoord();
    if(validateCoord(coord)){
        ui.showSignature->setCheckState(Qt::Checked);
        labels.insert("Signature", new QPair<int, int>(coord.getRow(), coord.getCol()));
    }
    coord = checkFormatData.getTextAmountCoord();
    if(validateCoord(coord)){
        ui.showTextAmount->setCheckState(Qt::Checked);
        labels.insert("Text Amount", new QPair<int, int>(coord.getRow(), coord.getCol()));
    }

    ui.checkSetupWidget->setLabelPositions(labels);
    qDeleteAll(labels);
    labels.clear();
}

bool CheckSetup::validateCoord(CheckItemCoord& coord)
{
    if(coord.getRow() < 0 || coord.getRow() > 12){
        return false;
    }
    if(coord.getCol() < 0 || coord.getCol() > 80){
        return false;
    }
    return true;
}

void CheckSetup::paintEvent(QPaintEvent *)
{
    //qDebug("CheckSetup::paintEvent(QPaintEvent *)");
    //drawFormat();
}

void CheckSetup::drawFormat()
{
    //qDebug("CheckSetup::drawFormat()");
    

    //qDebug("CheckSetup::drawFormat()  before painter");
    //QPainter painter(ui->checkFormat);
    //qDebug("CheckSetup::drawFormat()  after painter");

    //formatFont = QFont("Bitstream Vera Sans Mono");
    //formatFont.setPixelSize(13);
    //painter.setFont(formatFont);




    //QStringList text;
    csf->text.clear();
    for(unsigned int i = 0; i < 13; i++)
    {
        csf->text += QString(100, ' ');
    }

    CheckItemCoord coord;

    coord = checkFormatData.getDateCoord();
    csf->text[coord.getRow()].replace(coord.getCol(), QString("Date").length(), "Date");

    coord = checkFormatData.getAmountCoord();
    csf->text[coord.getRow()].replace(coord.getCol(), QString("Amount").length(),  "Amount");

    coord = checkFormatData.getTextAmountCoord();
    csf->text[coord.getRow()].replace(coord.getCol(), QString("Text Amount").length(), "Text Amount");

    coord = checkFormatData.getCommentCoord();
    csf->text[coord.getRow()].replace(coord.getCol(), QString("Memo").length(), "Memo");
    coord = checkFormatData.getSignatureCoord();

    coord = checkFormatData.getSignatureCoord();
    csf->text[coord.getRow()].replace(coord.getCol(), QString("Signature").length(), "Signature");

    coord = checkFormatData.getPayeeCoord();
    csf->text[coord.getRow()].replace(coord.getCol(), QString("Payee").length(), "Payee");

    coord = checkFormatData.getAddress1Coord();
    csf->text[coord.getRow()].replace(coord.getCol(), QString("Address1").length(), "Address1");

    coord = checkFormatData.getAddress2Coord();
    csf->text[coord.getRow()].replace(coord.getCol(), QString("Address2").length(), "Address2");

    coord = checkFormatData.getCityStZipCoord();
    csf->text[coord.getRow()].replace(coord.getCol(), QString("City, St Zip").length(), "City, St Zip");

    coord = checkFormatData.getHeadCoord();
    csf->text[coord.getRow()].replace(coord.getCol(), QString("Head Cnt").length(), "Head Cnt");

    coord = checkFormatData.getNumberCoord();
    csf->text[coord.getRow()].replace(coord.getCol(), QString("Number").length(), "Number");

    //painter.eraseRect(ui->checkFormat->rect());

    //for(int i = 0; i < 13; i++)
    //{
    //    painter.drawText(QPoint(10, 20 * (i + 1)), text[i]);
    //}
    
    csf->update();
}

void CheckSetup::mouseMoveEvent(QMouseEvent *e)
{
    int col = 80;
    int row = 0;

    int x, y;
#if 0
    if(e->x() >ui.checkFormat->x() && e->x() <ui.checkFormat->x() +ui.checkFormat->width() &&
            e->y() >ui.checkFormat->y() && e->y() <ui.checkFormat->y() +ui.checkFormat->height() &&
            e->state() == Qt::LeftButton)
    {
        x = e->x() -ui.checkFormat->x();
        y = e->y() -ui.checkFormat->y();

        col = double(x) /ui.checkFormat->width() * 80;
        row = double(y) /ui.checkFormat->height() * 13;
        CheckItemCoord coord(row, col);
        setCoord(ui->checkItemGroup->selectedId(), coord);
        drawFormat();
    }
#endif
}

void CheckSetup::save()
{
    QMap<QString, QPair<int,int>* > labels = ui.checkSetupWidget->getLabelPositions();
    foreach(QString tag, labels.keys()){
        CheckItemCoord cord(labels.value(tag)->first, labels.value(tag)->second);
        setCoord(tag, cord);
    }
    qDeleteAll(labels);
    labels.clear();
    checkFormatData.setSignaturePath(ui.sigFilePathEdit->text().toStdString());
    dao.saveCheckFormat(checkFormatData);
    QDialog::accept();
    SetupDAO setup;
    setup.set("chkPreSpaceLines",ui.preSpace->text().toStdString());
}

void CheckSetup::clearFormat(int buttonId)
{
    /*
    CheckItemCoord coord(0, 85);
    setCoord(buttonId, coord);
    drawFormat();
    */
}

void CheckSetup::setCoord(QString tag, CheckItemCoord coord)
{ 
    if(tag == "Date"){
        checkFormatData.setDateCoord(coord);
    }else if(tag == "Memo"){
        checkFormatData.setCommentCoord(coord);
    }else if(tag == "Text Amount"){
        checkFormatData.setTextAmountCoord(coord);
    }else if(tag == "Signature" ){
        checkFormatData.setSignatureCoord(coord);
    }else if(tag == "Payee"){
        checkFormatData.setPayeeCoord(coord);
    }else if(tag == "Amount"){
        checkFormatData.setAmountCoord(coord);
    }else if(tag == "Address 1"){
        checkFormatData.setAddress1Coord(coord);
    }else if(tag == "Address 2"){
        checkFormatData.setAddress2Coord(coord);
    }else if(tag == "City, St Zip"){
        checkFormatData.setCityStZipCoord(coord);
    }else if(tag == "Head Count"){
        checkFormatData.setHeadCoord(coord);
    }else if(tag == "Number"){
        checkFormatData.setNumberCoord(coord);
    }
}

void CheckSetup::browse()
{
   ui.sigFilePathEdit->setText(QFileDialog:: getOpenFileName ("",  "Jpeg Files (*.jpg *.jpeg)"));
}
