#include "brandwidget.h"
#include <QBuffer>

BrandWidget::BrandWidget(QWidget* parent) : QWidget(parent)
{
    if(parent != NULL)
    {
        setGeometry(0, 0, parent->width(), parent->height());
    }
    editable = true;
    m_isMousePressed = false;
    m_defaultPen = QPen(QColor(0,0,0), 20, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    m_saverImage = QImage(width(), height(),QImage::Format_RGB32);

}

BrandWidget::~BrandWidget()
{

}

void BrandWidget::setEditable(bool editable)
{
    this->editable = editable;
}

void BrandWidget::mouseMoveEvent(QMouseEvent* event)
{
    if(editable && m_isMousePressed)
    {
        m_mouseX = event->pos().x();
        m_mouseY = event->pos().y();
        update();
    }
}

void BrandWidget::paintEvent ( QPaintEvent * event )
{
    if( editable && m_isMousePressed ) {
        QPainter brandPainter(&m_saverImage);
        brandPainter.setPen(m_defaultPen);
        brandPainter.drawChord(m_mouseX, m_mouseY, 20, 20, 0, 5760);
    }
    QPainter brandImg(this);
    brandImg.drawImage(0, 0, m_saverImage);
    QWidget::paintEvent(event);
}

void BrandWidget::mousePressEvent(QMouseEvent* event)
{
      m_isMousePressed = true;
      m_mouseX = event->pos().x();
      m_mouseY = event->pos().y();
}
void BrandWidget::mouseReleaseEvent(QMouseEvent* event)
{
    m_isMousePressed = false;
}

void BrandWidget::clearPainting()
{
    QPainter savePainter(&m_saverImage);
    savePainter.eraseRect(0, 0, width(), height());
    repaint();
}

void BrandWidget::drawNoBrandImage()
{
    // it would probably be much easier to use the drawText()
    // function here, but I am trying to match the old program
    // as close as possible.

    clearPainting();
    QPainter* savePainter = new QPainter(&m_saverImage);
    // draw the 'N'
    savePainter->fillRect(10, 10, 72, 252, Qt::SolidPattern);
    savePainter->fillRect(82, 46, 36, 72, Qt::SolidPattern);
    savePainter->fillRect(118, 82, 36, 72, Qt::SolidPattern);
    savePainter->fillRect(154, 118, 36, 72, Qt::SolidPattern);
    savePainter->fillRect(190, 10, 72, 252, Qt::SolidPattern);

    // draw the 'B'
    savePainter->fillRect(290, 290, 216, 252, Qt::SolidPattern);
    savePainter->eraseRect(362, 326, 108, 72);
    savePainter->eraseRect(362, 434, 108, 72);
    savePainter->fillRect(506, 326, 36, 72, Qt::SolidPattern);
    savePainter->fillRect(506, 434, 36, 72, Qt::SolidPattern);
    //  savePainter->setPen(savePen);
    savePainter->end();
    delete savePainter;
    repaint();
}

std::string BrandWidget::getImageData()
{
    QImage brandImage = m_saverImage;
    //  smallBrandPainter.drawImage(0, 0, brandImage.scale(48, 48));
    brandImage = brandImage.scaled(48, 24);
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
 bool result =   brandImage.save(&buffer, "PNG"); // writes image into ba in PNG format

    QString imageDataStr(ba.toBase64());

//    unsigned char pixelArray;
    std::string imageData = imageDataStr.toStdString();


//    int bytesPerLine = brandImage.bytesPerLine();
//    int totalBytes = brandImage.byteCount();

//    int rowNumber = totalBytes/bytesPerLine;
//    for(unsigned int i = 0; i < rowNumber; i++) {
//        for(unsigned int j = 0; j < bytesPerLine; j++) {
//            pixelArray = 0;
//            // load the bit vector
//            for(unsigned int k = 0; k < 8; k++) {
//                if(QColor(brandImage.pixel(j, (i * 8) + k)) == QColor(0,0,0)) {
//                    //pixelArray |= (unsigned int)(pow(2.0, double(8 - k)));
//                    pixelArray |= (0x1 << (7-k));
//                }
//            }
//            imageData += pixelArray;
//        }
//    }
    return imageData;
}

QImage BrandWidget::getImage()
{
    return m_saverImage;
}

void BrandWidget::setImage(const QImage& image)
{
    m_saverImage = image;
    repaint();
}
