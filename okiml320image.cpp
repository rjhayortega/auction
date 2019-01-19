#include <math.h>
#include "okiml320image.h"

OkiML320Image::OkiML320Image(QString fileName)
{
    if(!QFile::exists(fileName))
    {
        dataLen = 0;
        numRows = 0;
        data = NULL;
    }
    else
    {
        QImage sourceImage(fileName);

        if(!sourceImage.isNull())
        {
            createImage(sourceImage);
        }
    }
}

OkiML320Image::OkiML320Image(QImage sourceImage)
{
    createImage(sourceImage);
}

OkiML320Image::~OkiML320Image()
{
    if(data != NULL)
    {
        delete [] data;
    }
}

int OkiML320Image::createImage(QImage sourceImage)
{
    returnDistance = 0;
    sourceImage = sourceImage.scaledToWidth(sourceImage.width() * 2);
    data = new unsigned char[sourceImage.width() * sourceImage.height() + (sourceImage.height() * 3)];
    dataLen = 0;
    width = sourceImage.width();
    height = sourceImage.height() / 8 + 1;
    QRect sliceRect(0, 0, 1, 8);
    unsigned char buf[8];

    for(int i = 0; i < sourceImage.height(); i+=8)
    {
        writeGraphicCommand(sourceImage.width());
        for(int j = 0; j < sourceImage.width(); j++)
        {
            sliceRect.setX(j);
            sliceRect.setY(i);
            sliceRect.setWidth(1);
            sliceRect.setHeight(8);

            imageSlice(buf, sliceRect, sourceImage);
            data[dataLen] = byteBufferToByte(buf);
            dataLen++;
        }
        writeFeedCommand();
    }
    writeReturnHeadCommand();
    return dataLen;
}


int OkiML320Image::imageSlice(unsigned char *buf, QRect sliceRect, QImage image)
{
    int bufLen = 0;
    QRgb currentColor;

    for(int i = 0; i < sliceRect.height(); i++)
    {
        for(int j = 0; j < sliceRect.width(); j++)
        {
            if(!image.valid(j + sliceRect.x(), i + sliceRect.y()))
            {
                currentColor = Qt::white;
            }
            else
            {
                currentColor = image.pixel(j + sliceRect.x(), i + sliceRect.y());
            }

            buf[bufLen] = qGray(qRed(currentColor), qGreen(currentColor), qBlue(currentColor));
            bufLen++;
        }
    }

    return bufLen;
}


unsigned char OkiML320Image::byteBufferToByte(unsigned char byteBuffer[8])
{
    unsigned char byte = 0;

    for(int i = 0; i < 8; i++)
    {
        byte += (byteBuffer[i] < 127 ? 1 : 0) * (unsigned char)pow(2.0, double(8 - i));
    }
    return byte;
}


void OkiML320Image::writeGraphicCommand(int numCols)
{
    data[dataLen + 0] = 27;   // ascii esc indicates start of command
    data[dataLen + 1] = 'L'; // 75;   // askii K indicates start single density graphics

    data[dataLen + 2] = numCols % 256;  //     numCols % 256
    data[dataLen + 3] = numCols / 256;  // +   numCols / 256
    // ------------------
    //   Num expected bytes
    dataLen += 4;
}

void OkiML320Image::writeReturnHeadCommand()
{
    long temp = returnDistance;
    unsigned char jump;

    while(temp > 0)
    {
        if(temp > 255)
        {
            jump = 255;
            temp -= 255;
        }
        else
        {
            jump = temp;
            temp = 0;
        }

        if(jump > 0)
        {
            data[dataLen + 0] = 27;
            data[dataLen + 1] = 'j'; // reverse feed
            data[dataLen + 2] = jump;
            data[dataLen + 3] = '\r';
            dataLen += 4;
        }
    }
}

void OkiML320Image::writeFeedCommand()
{
    data[dataLen + 0] = 27;    // ascii esc indicates command start
    data[dataLen + 1] = 'J';   // ascii J indicates feed Hn / 180 "
    data[dataLen + 2] = 21;    // set Hn
    data[dataLen + 3] = '\r';  // perform a carriage return
    returnDistance += 21;
    dataLen += 4;
}

int OkiML320Image::getImageSize()
{
    return dataLen;
}

int OkiML320Image::retrieveImage(unsigned char *imageBuf)
{
    for(int i = 0; i < dataLen; i++)
    {
        imageBuf[i] = data[i];
    }
    return dataLen;
}


void OkiML320Image::prependText(const char *textString, int lineLen, int numTextLines)
{
    //  dataLen = orig. image size, lineLen * numTextLines = size of text,
    //  height * lineLen = space for image spacers, numTextLines * 4 = space for text newlines
    int estimatedBufferSize = dataLen + (lineLen * numTextLines) + (height * lineLen) + (numTextLines * 4);
    unsigned char *buf = new unsigned char[estimatedBufferSize];
    unsigned char *textBuf = new unsigned char[lineLen * numTextLines];

    int jump;
    int bufLen = 0;
    int textDone = 0;
    int imageDone = 0;
    int currentPos = 0;
    int nextTextPos = 0;
    int nextImagePos = 0;
    int actualReturnDistance = 0;

    // fill out the text

    for(int i = 0; i < lineLen * numTextLines; i++)
    {
        if(textDone < strlen(textString))
        {
            textBuf[textDone] = textString[i];
        }
        else
        {
            textBuf[textDone] = ' ';
        }
        textDone++;
    }

    textDone = 0;


    while(textDone < numTextLines * lineLen || imageDone < dataLen)
    {
        // aligned for next text line
        if(currentPos == nextTextPos && textDone < numTextLines * lineLen)
        {
            for(int j = 0; j < lineLen; j++)
            {
                buf[bufLen] = textBuf[textDone];
                textDone++;
                bufLen++;
            }

            nextTextPos += 25;
        }
        else if(imageDone < dataLen) // aligned for next image line
        {
            for(int j = 0; j < width + 4; j++)
            {
                buf[bufLen] = data[imageDone];
                imageDone++;
                bufLen++;
            }

            imageDone += 4;  // ignore the embedded newline commands

            if(imageDone + (((returnDistance / 255) + 1) * 4) == dataLen)
            {
                imageDone = dataLen; // ignore the embedded return print head commands
            }

            nextImagePos += 21;
        }

        if(textDone >= numTextLines * lineLen)  // next line is for image, jump to the next image line
        {
            jump = nextImagePos - currentPos;
        }
        else if(imageDone >= dataLen)           // next line is for text, jump to the next text line
        {
            jump = nextTextPos - currentPos;
        }
        else
        {
            jump = (nextTextPos <= nextImagePos ? nextTextPos : nextImagePos) - currentPos;
        }

        buf[bufLen + 0] = 27;
        buf[bufLen + 1] = 'J';
        buf[bufLen + 2] = (unsigned char)jump;
        buf[bufLen + 3] = '\r';
        bufLen += 4;

        currentPos += jump;

        if(currentPos == nextImagePos && currentPos != nextTextPos && imageDone < dataLen)
        {
            for(int i = 0; i < lineLen; i++)
            {
                buf[bufLen] = ' ';
                bufLen++;
            }
        }
    }

    delete []data;
    data = new unsigned char[bufLen + (((returnDistance / 255) + 1) * 4)];
    dataLen = bufLen;

    for(int i = 0; i < bufLen; i++)
    {
        data[i] = buf[i];
    }

    returnDistance = currentPos;
    writeReturnHeadCommand();

    delete [] buf;
    delete [] textBuf;
}



int OkiML320Image::getHeight()
{
    return height;
}
