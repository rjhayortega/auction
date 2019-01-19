//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "brandinputdialog.h"
#include "ui_brandinputdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qframe.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

BrandInputDialog::BrandInputDialog( QWidget* parent)
    : QDialog( parent ), ui(new Ui::BrandInputDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->clearButton, SIGNAL( clicked() ), this, SLOT( clearBrand() ) );
    connect( ui->noBrandButton, SIGNAL( clicked() ), this, SLOT( drawNoBrandImage() ) );
    connect( ui->exitButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( ui->saveButton, SIGNAL( clicked() ), this, SLOT( saveImage() ) );
    connect( ui->positionButton, SIGNAL( clicked() ), this, SLOT( setPositionEdit() ) );
    connect( ui->transactionButton, SIGNAL( clicked() ), this, SLOT( setTransactionEdit() ) );
    connect( ui->headButton, SIGNAL( clicked() ), this, SLOT( setHeadEdit() ) );
    connect( ui->tagButton, SIGNAL( clicked() ), this, SLOT( setTagEdit() ) );
    connect( ui->inputEdit, SIGNAL( returnPressed() ), this, SLOT( processEditItem() ) );
    connect( ui->viewButton, SIGNAL( clicked() ), this, SLOT( browseBrands() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
BrandInputDialog::~BrandInputDialog()
{
    delete ui;
}

#include <qpainter.h>
#include <qpicture.h>
#include <QMessageBox>
#include <iostream>
#include "dao/printerdao.h"
#include "math.h"
#include "types/brand.h"
#include <string>
#include "brandbrowserdialog.h"


using namespace std;

////////////////////////////////////////////////////////////////////////
//
// name: BrandInputDialog::init()
//
// purpose:  constructor like function, initialized drawing area
//
// calling parms:
//
// return parms:
//
// TODO:
//
////////////////////////////////////////////////////////////////////////
void BrandInputDialog::init()
{
    // initialize the widget painter (used for writing to the  frame on a paintEvent())
    //  painter = new QPainter(BrandInputFrame);
    //  defaultPen = new QPen(QColor(0,0,0), 20, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // this is the actual image that is being drawn on.
    //  saverImage = new QPixmap(BrandInputFrame->width(), BrandInputFrame->height());
    //  saverImage->fill();
    //  savePainter = new QPainter(saverImage);
    //  savePainter->setPen(*defaultPen);

    //  smallBrandPainter.begin(smallBrand);

    ui->inputLabel->setText("");
    ui->inputEdit->setEnabled(false);
    brandWidget = new BrandWidget(ui->BrandInputFrame);
    smallBrandWidget = new BrandWidget(ui->smallBrandFrame);
    smallBrandWidget->setEditable(false);
    clearBrand();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: browseBrands()
// 
// purpose: starts the brand browser dialog
//
// calling params: void
// 
// return params: void
//
// Notes: 
//        
// Todo: 
//
///////////////////////////////////////////////////////////////////////////////
void BrandInputDialog::browseBrands()
{
    BrandBrowserDialog(this).exec();
    // repaint();
}

////////////////////////////////////////////////////////////////////////
//
// name: BrandInputDialog::destroy()
//
// purpose:  constructor like function, initialized drawing area
//
// calling parms:
//
// return parms:
//
// TODO: defaultPen = new QPen(QColor(0,0,0), 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
//
////////////////////////////////////////////////////////////////////////
void BrandInputDialog::destroy()
{
    //painter->end();

    // delete painter;
    // delete defaultPen;

    //savePainter->end();
    //smallBrandPainter.end();

    // delete saverImage;
    // delete savePainter;
    delete brandWidget;
    delete smallBrandWidget;
}


////////////////////////////////////////////////////////////////////////
//
// name: BrandInputDialog::mouseMoveEvent() <signal handler>
//
// purpose:  if the mouse is moved while a button is pressed (on the drawing area, this
//                         draws a filled circle at the point where the mouse has
//                         moved to.
//
// calling parms: QMouseEvent *event  - the mouse move event
//
// return parms:
//
// TODO:
//
////////////////////////////////////////////////////////////////////////
/*
void BrandInputDialog::mouseMoveEvent(QMouseEvent *event)
{
  // test to see if saving should be allowed for a new image


  int x = event->x() - BrandInputFrame->x();
  int y = event->y() - BrandInputFrame->y();


  int width = BrandInputFrame->width();
  int height = BrandInputFrame->height();

  if(x < 0 || x > width)
  {
      return;
  }

  if(y < 0 || y > height)
  {
      return;
  }

  savePainter->drawChord(x, y, 20, 20, 0, 5760);

  repaint();
}
*/

////////////////////////////////////////////////////////////////////////
//
// name: BrandInputDialog::clearBrand() <signal handler>
//
// purpose: Clears the drawing area and cust id input field
//
// calling parms:
//
// return parms:
//
// TODO:
//
////////////////////////////////////////////////////////////////////////
void BrandInputDialog::clearBrand()
{
    brandId = 0;
    ui->currentPositionDisplay->setText("");
    ui->currentTransactionDisplay->setText("0");
    ui->currentHeadDisplay->setText("0");
    ui->currentTagDisplay->setText("");

    currentEdit = None;
    ui->inputLabel->setText("");
    ui->inputEdit->setEnabled(false);
    brandWidget->clearPainting();
    smallBrandWidget->clearPainting();
    //clearPainting(savePainter);
    // clearPainting(&smallBrandPainter);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setPositionEdit()
// 
// purpose: sets up the main input to be used for the brand position
//
// calling params: void
// 
// return params: void
//
// Notes: 
//        
// Todo: 
//
///////////////////////////////////////////////////////////////////////////////
void BrandInputDialog::setPositionEdit()
{
    ui->inputLabel->setText("Brand Position On Animal:");
    ui->inputEdit->setEnabled(true);
    ui->inputEdit->setText("");
    ui->inputEdit->setFocus();
    currentEdit = BrandPosition;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setTransactionEdit()
// 
// purpose: sets up the main input to be used for the transaction id
//
// calling params: void
// 
// return params: void
//
// Notes: 
//        
// Todo: 

//
///////////////////////////////////////////////////////////////////////////////
void BrandInputDialog::setTransactionEdit()
{
    ui->inputLabel->setText("Transaction #:");
    ui->inputEdit->setEnabled(true);
    ui->inputEdit->setText("");
    ui->inputEdit->setFocus();
    currentEdit = TransactionNo;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setHeadEdit()
// 
// purpose: sets up the main input to be used to enter the head count
//
// calling params: void
// 
// return params: void
//
// Notes: 
//        
// Todo: 
//
///////////////////////////////////////////////////////////////////////////////
void BrandInputDialog::setHeadEdit()
{
    ui->inputLabel->setText("Head Count:");
    ui->inputEdit->setEnabled(true);
    ui->inputEdit->setText("");
    ui->inputEdit->setFocus();
    currentEdit = HeadCount;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setTagEdit()
// 
// purpose: sets the main input to be used for the tag number of the brand
//
// calling params: void
// 
// return params: void
//
// Notes: 
//        
// Todo: 
//
///////////////////////////////////////////////////////////////////////////////
void BrandInputDialog::setTagEdit()
{
    ui->inputLabel->setText("Tag #:");
    ui->inputEdit->setEnabled(true);
    ui->inputEdit->setText("");
    ui->inputEdit->setFocus();
    currentEdit = TagNo;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: processEditItem()
// 
// purpose: Processes the main input
//
// calling params: void
// 
// return params: void
//
// Notes: The main input is polymorphic in that it can be used to input
//        several different types of data
//        
// Todo: 
//
///////////////////////////////////////////////////////////////////////////////
void BrandInputDialog::processEditItem()
{
    switch(currentEdit)
    {
    case None:
    default:
        return;
        break;

    case BrandPosition:
        ui->currentPositionDisplay->setText(ui->inputEdit->text());
        break;

    case TransactionNo:
        ui->currentTransactionDisplay->setText(QString::number(ui->inputEdit->text().toLong()));
        break;

    case HeadCount:
        ui->currentHeadDisplay->setText(QString::number(ui->inputEdit->text().toLong()));
        break;

    case TagNo:
        ui->currentTagDisplay->setText(ui->inputEdit->text());
        saveImage();
        break;
    }

    ui->inputEdit->setText("");
}

////////////////////////////////////////////////////////////////////////
//
// name: BrandInputDialog::clearPainting()
//
// purpose: clears a drawing area
//
// calling parms:
//
// return parms:
//
// TODO:
//
////////////////////////////////////////////////////////////////////////
void BrandInputDialog::clearPainting(QPainter *cur_painter)
{
    /*
  cur_painter->eraseRect(0, 0, BrandInputFrame->width(), BrandInputFrame->height());

  //redraw the frame borders
  cur_painter->setPen(QColor(255, 255, 255));
  cur_painter->drawLine(0, 0, BrandInputFrame->width(), 0);
  cur_painter->drawLine(0, 0, 0, BrandInputFrame->height());

  cur_painter->setPen(QColor(150, 150, 150));
  cur_painter->drawLine(BrandInputFrame->width() - 1, 0,
            BrandInputFrame->width() -1, BrandInputFrame->height());
  cur_painter->drawLine(0, BrandInputFrame->height() - 1,
            BrandInputFrame->width(), BrandInputFrame->height() -1);

  //reset the pen to the default
  cur_painter->setPen(*defaultPen);

  repaint();
  */
    brandWidget->clearPainting();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: drawNoBrandImage()
// 
// purpose: draws the 'No Brand' Image in the drawing area
//
// calling params: void
// 
// return params: void
//
// Notes: 
//        
// Todo: 
//
///////////////////////////////////////////////////////////////////////////////

void BrandInputDialog::drawNoBrandImage()
{
    // it would probably be much easier to use the drawText()
    // function here, but I am trying to match the old program
    // as close as possible.
    
    /*
  clearPainting(savePainter);
  QPen savePen = savePainter->pen();
  QPen linePen = savePen;
  linePen.setWidth(1);
  linePen.setCapStyle(Qt::SquareCap);
  savePainter->setPen(linePen);

  // draw the 'N'
  savePainter->fillRect(10, 10, 72, 252, QBrush::SolidPattern);
  savePainter->fillRect(82, 46, 36, 72, QBrush::SolidPattern);
  savePainter->fillRect(118, 82, 36, 72, QBrush::SolidPattern);
  savePainter->fillRect(154, 118, 36, 72, QBrush::SolidPattern);
  savePainter->fillRect(190, 10, 72, 252, QBrush::SolidPattern);

  // draw the 'B'
  savePainter->fillRect(290, 290, 216, 252, QBrush::SolidPattern);
  savePainter->eraseRect(362, 326, 108, 72);
  savePainter->eraseRect(362, 434, 108, 72);
  savePainter->fillRect(506, 326, 36, 72, QBrush::SolidPattern);
  savePainter->fillRect(506, 434, 36, 72, QBrush::SolidPattern);
  savePainter->setPen(savePen);
  repaint();
  */
    brandWidget->drawNoBrandImage();
}


////////////////////////////////////////////////////////////////////////
//
// name: BrandInputDialog::saveImage()
//
// purpose:  uses the BrandDAO class to save the image data 
//                 stored in savePainter. Image is stored in the mysql database
//                 as type "JPEG"
//
// calling parms:
//
// return parms:
//
// TODO:
//
////////////////////////////////////////////////////////////////////////
void BrandInputDialog::saveImage()
{
    /*
  QImage brandImage = saverImage->convertToImage();
  smallBrandPainter.drawImage(0, 0, brandImage.scale(48, 48));
  brandImage = brandImage.scale(48, 24);
  char pixelArray;
  string imageData;
  
  for(unsigned int i = 0; i < 3; i++)
  {
    for(unsigned int j = 0; j < brandImage.width(); j++)
    {
      pixelArray = 0;

      // load the bit vector

      for(unsigned int k = 0; k < 8; k++)
      {
    if(QColor(brandImage.pixel(j, (i * 8) + k)) == QColor(0,0,0))
    {
      pixelArray |= (unsigned int)(pow(2.0, double(8 - k)));
    }
      }
      imageData += pixelArray;
    }
  }
  */
    string imageData = brandWidget->getImageData();

    QImage brandSmallImage = brandWidget->getImage().scaled(48,48);
    smallBrandWidget->setImage(brandSmallImage);

    Brand currentBrand(brandId, imageData,
                       ui->currentPositionDisplay->text().toStdString(),
                       ui->currentTransactionDisplay->text().toLong(),
                       ui->currentHeadDisplay->text().toLong(),
                       ui->currentTagDisplay->text().toStdString());

    brandDao.saveBrand(currentBrand);

    // test printing

    /*
  string buf;
  
  for(unsigned int i = 0; i < 3; i++)
  {
   buf += string(1, char(27)) + string(1, 'L') + string(1, char(48)) + string(1, char(0));
   buf += imageData.substr(i * 48, 48);
   buf += string(1, char(27)) + string(1, 'J') + string(1, char(21)) + string(1, '\r'); // feed
  }
  
  
  LinePrinter testPrinter(PrinterDAO().getPrinter(PrinterDAO::Report));
  testPrinter.print(buf);
  */
}

////////////////////////////////////////////////////////////////////////
//
// name: BrandInputDialog::paintEvent(QPaintEvent *)
//
// purpose:  overloaded, paints the savedImage to the 
//                      display area;
//
// calling parms: QPaintEvent *the paint event
//
// return parms:
//
// TODO:
//
////////////////////////////////////////////////////////////////////////
/*
void BrandInputDialog::paintEvent(QPaintEvent *)
{

  painter->drawPixmap(0, 0, *saverImage);

//  smallBrandPainter.drawPixmap(0, 0, saverImage->convertToImage().scale(48, 48));
}


*/

