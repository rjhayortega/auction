#ifndef _OKI_2_PIXMAP_H_
#define _OKI_2_PIXMAP_H_

#include <qpixmap.h>
#include <qstringlist.h>
#include <qpainter.h>
#include "reports/textreport.h"
#include <deque>
#include <string>
#include <qsize.h>
#include <qpaintdevice.h>
#include <qimage.h>
#include "rational.h"

using namespace std;

class Oki2Pixmap 
{
public:
  Oki2Pixmap(TextReport =TextReport(), QPaintDevice* =NULL, QSize =QSize());
  QPixmap pixmap(int);

  QPixmap& operator[](int);
  unsigned int numPages();

  static QPixmap text2Pixmap(string);

private:
  vector<QPixmap> pixmapSource;
  TextReport reportSource;

  static void drawTextLine(string);
  void report2Pixmap();

  static int currentX;
  static int currentY;
  static QSize pageSize;

  static void initTextPainter();
  static const int pointSize;
  static QSize margins;
  static QPainter pagePainter;
  static Rational multiplier;
  static Rational pre12Multiplier;
  static QPixmap* pre12Page;

  static Rational pre17Multiplier;
  static QPixmap* pre17Page;

  static QPixmap* currentPage;
  static QPixmap* cpi10Page;
  static QPixmap* cpi12Page;
  static QPixmap* cpi17Page;
  static int columnWidth;
};

#endif
