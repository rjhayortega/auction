#ifndef _BRAND_WIDGET_H_
#define _BRAND_WIDGET_H_

#include <qframe.h>
#include <qpixmap.h>
#include <qpainter.h>
#include <string> 
#include <qimage.h>
#include <math.h>
#include <iostream>
#include <qimage.h>

#include <QMouseEvent>


class BrandWidget : public QWidget
{
public:
  BrandWidget(QWidget* =NULL);
  std::string getImageData();
  void drawNoBrandImage();
  void clearPainting();
  ~BrandWidget();
  QImage getImage();
  void setImage(const QImage &image);
  void setEditable(bool);
protected:
  void mousePressEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent*);
  void mouseReleaseEvent(QMouseEvent*);
  virtual void paintEvent ( QPaintEvent * event );

private:
  QWidget* parent;
  QImage  m_saverImage;
  QPen m_defaultPen;
  bool editable;
  int m_mouseX;
  int m_mouseY;
  bool m_isMousePressed;
};

#endif
