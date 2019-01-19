
#ifndef _OKIML320IMAGE_H_
#define _OKIML320IMAGE_H_

#include <qimage.h>
#include <qrect.h>
#include <qfile.h>
#include <qcolor.h>

#include <iostream>
using namespace std;

class OkiML320Image
{
public:
  OkiML320Image(QString="");
  OkiML320Image(QImage image);

  ~OkiML320Image();

  int createImage(QImage);
  int retrieveImage(unsigned char *);
  int getImageSize();
  int getHeight();
  void prependText(const char*, int, int textHeight);
protected:

private:
  unsigned char *data;
  int dataLen;
  int numRows;

  int width;
  int height;
  long returnDistance;

  int imageSlice(unsigned char *, QRect, QImage);
  unsigned char byteBufferToByte(unsigned char[8]);
  void writeGraphicCommand(int);
  void writeFeedCommand();
  void writeReturnHeadCommand();
};
#endif
