#include "brand.h"
#include "tag.h"
#include <qmath.h>
#include <QColor>
#include <QList>

Brand::Brand(long id, string imageData, string brandPosition, long transactionNo, long headCount, string tag, string burcellosisTag)
{
  this->id = id;
  this->imageData = imageData;
  this->brandPosition = brandPosition;
  this->transactionNo = transactionNo;
  this->headCount = headCount;
  this->tag = tag;
  this->burcellosisTag = burcellosisTag;
}

long Brand::getId()
{
  return id;
}

string Brand::getImageData()
{
  return imageData;
}

string Brand::getBrandPosition()
{
  return brandPosition;
}

long Brand::getTransactionId()
{
  return transactionNo;
}

long Brand::getHead()
{
  return headCount;
}
string Brand::getTag()
{
  return tag;
}
string Brand::getBurcellosisTag()
{
  return burcellosisTag;
}

void Brand::setId(long id)
{
  this->id = id;
}

void Brand::setBrandPosition(string brandPosition)
{
  this->brandPosition = brandPosition;
}

void Brand::setTransactionId(long transactionId)
{
  this->transactionNo = transactionId;
}

void Brand::setHead(long head)
{
  this->headCount = head;
}

void Brand::setTag(string tag)
{
  this->tag = tag;
}

void Brand::setBurcellosisTag(string bTag)
{
  this->burcellosisTag = bTag;
}

bool Brand::operator==(Brand that)
{
  return this->id == that.id;
}

bool Brand::operator==(long thatId)
{
  return this->id == thatId;
}

bool Brand::operator==(string thatTag)
{
  return this->tag == thatTag;
}

bool Brand::compareTagsLT(Brand a, Brand b)
{
  return Tag::compareTagsLT(Tag(a.getTag()), Tag(b.getTag()));
}

QImage Brand::getBrandImage()
{

    string imageData = getImageData();
    QImage tempImage(48, 24, QImage::Format_RGB32);
    QString imageDataStr = QString::fromStdString(imageData);
    QByteArray ba = QByteArray::fromBase64(imageDataStr.toAscii());
    tempImage.loadFromData(ba,"PNG");
    return tempImage;
}

//This function convert brand image to string for matrix printer.
string Brand::brandImageToPrintMatrix()
{
    QImage brandImage = getBrandImage();
    unsigned char pixelArray;
    std::string imageData;

    int bytesPerLine = 48; //brandImage.bytesPerLine();
    int totalBytes = brandImage.byteCount();

    int rowNumber = 3; //totalBytes/(bytesPerLine*8); // 8 bit in the column, total 3 rows.
    for(unsigned int i = 0; i < rowNumber; i++) {
        for(unsigned int j = 0; j < bytesPerLine; j++) {
            pixelArray = 0;
            // load the bit vector
            for(unsigned int k = 0; k < 8; k++) {
               QRgb rgb =  brandImage.pixel(j, (i * 8) + k);
               if (QColor(rgb) != QColor(255,255,255)) {
                    pixelArray |= (0x1 << (7-k));
               }
            }
            imageData += pixelArray;
        }
    }

    //Debug only. Print  imageData as text ,black pixel is *, the rest is -.
#if 0
    QList < QList<char> > printRow;
    for(unsigned int i = 0; i < rowNumber; i++) {
        printRow.clear();
        for(unsigned int j = 0; j < bytesPerLine; j++) {
            QList <char> column;
            unsigned char byteToPrint = imageData[i*bytesPerLine + j];

            // load the bit vector

            for(unsigned int k = 0; k < 8; k++) {
                unsigned char mask = 0x1 << (7-k);
                if((byteToPrint & mask) == mask) {
                    column.push_back('*');
                }
                else {
                    column.push_back('-');
                }
            }
            printRow.push_back(column);
        }
        for (int dd = 0; dd< 8; dd++) {
             for (int kk = 0; kk <printRow.size(); kk++) {
                 QList<char> col = printRow[kk];
                 cout<< col.at(dd);

            }
            cout << endl;
        }
    }
#endif
    return imageData;
}
