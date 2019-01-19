#include "oki2pixmap.h"
#include <qbitmap.h>
#include <Q3PaintDeviceMetrics>

int Oki2Pixmap::currentX = 0;
int Oki2Pixmap::currentY = 0;
const int Oki2Pixmap::pointSize = 10;
QSize Oki2Pixmap::margins(0,0);
QSize Oki2Pixmap::pageSize(612, 792);
QPainter Oki2Pixmap::pagePainter;
Rational Oki2Pixmap::multiplier(1, 0, 1);

Rational  Oki2Pixmap::pre12Multiplier = Oki2Pixmap::multiplier;
Rational  Oki2Pixmap::pre17Multiplier = Oki2Pixmap::multiplier;

QPixmap* Oki2Pixmap::pre12Page = NULL;
QPixmap* Oki2Pixmap::pre17Page = NULL;


QPixmap* Oki2Pixmap::currentPage = NULL;
QPixmap* Oki2Pixmap::cpi10Page = NULL;
QPixmap* Oki2Pixmap::cpi12Page = NULL;
QPixmap* Oki2Pixmap::cpi17Page = NULL;

int Oki2Pixmap::columnWidth = 7;

Oki2Pixmap::Oki2Pixmap(TextReport _reportSource, QPaintDevice* device, QSize _margins) : reportSource(_reportSource)
{
  Oki2Pixmap::margins = _margins;
  Q3PaintDeviceMetrics metrics(device);
  Oki2Pixmap::pageSize = QSize(metrics.width() - margins.width() * 2, metrics.height() - margins.height() * 2);
  columnWidth = pageSize.width() / 80;
  report2Pixmap();
}

QPixmap Oki2Pixmap::pixmap(int page)
{
  if(0 <= page && page < pixmapSource.size())
  {
    return pixmapSource[page];
  }

  return QPixmap();
}

void Oki2Pixmap::report2Pixmap()
{
  deque<string> reportPages = reportSource.paginatedText();

  pixmapSource.clear();
  pixmapSource = vector<QPixmap>(reportPages.size(), QPixmap());

  for(unsigned int i = 0; i < reportPages.size(); i++)
  {
    pixmapSource[i] = text2Pixmap(reportPages[i]);
  }
}

QPixmap Oki2Pixmap::text2Pixmap(string text)
{
  currentX = 0;
  currentY = 0;

  QStringList textLines = QStringList::split("\n", QString::fromStdString(text), true);

  QPixmap page(pageSize);
  page.fill();

  
  cpi10Page = new QPixmap(pageSize);
  cpi10Page->fill();
  cpi12Page = new QPixmap(QSize(round((Rational("1 1/6") * pageSize.width()).approx()), pageSize.height()));
  cpi12Page->fill();
  cpi17Page = new QPixmap(QSize(round((Rational("1 1/2") * pageSize.width()).approx()), pageSize.height()));
  cpi17Page->fill();


  pagePainter.begin(cpi10Page);  
  currentPage = cpi10Page;
  initTextPainter();

  for(unsigned int i = 0; i < textLines.size(); i++)
  {
    drawTextLine(textLines[i].toStdString());
  }

  pagePainter.end();   

  *cpi12Page = QPixmap(cpi12Page->convertToImage().smoothScale(pageSize, Qt::ScaleFree));
  *cpi17Page = QPixmap(cpi17Page->convertToImage().smoothScale(pageSize, Qt::ScaleFree));

  cpi10Page->setMask(cpi10Page->createHeuristicMask());
  cpi12Page->setMask(cpi12Page->createHeuristicMask());
  cpi17Page->setMask(cpi17Page->createHeuristicMask());  

/*
  pagePainter.begin(&page);   
  pagePainter.drawPixmap(0, 0, *cpi10Page);
  pagePainter.drawPixmap(0, 0, *cpi12Page);
  pagePainter.drawPixmap(0, 0, *cpi17Page);
  pagePainter.end();   
*/

  bitBlt(&page, 0, 0, cpi10Page, 0, 0, cpi10Page->width(), cpi10Page->height(), QPainter::CompositionMode_SourceOver);
  bitBlt(&page, 0, 0, cpi12Page, 0, 0, cpi12Page->width(), cpi10Page->height(), QPainter::CompositionMode_SourceOver);
  bitBlt(&page, 0, 0, cpi17Page, 0, 0, cpi10Page->width(), cpi10Page->height(), QPainter::CompositionMode_SourceOver);
  

  delete cpi12Page;
  delete cpi17Page;
  delete cpi10Page;

  cpi10Page = NULL;
  cpi12Page = NULL;
  cpi17Page = NULL;
  return page;
}

void Oki2Pixmap::drawTextLine(string textLine)
{  
  bool advance = false;

  for(unsigned int i = 0; i < textLine.size(); i++)
  {
    advance = false;
    switch(textLine[i])
    {
    default:
      advance = true;
/*
      {
      Rational result = multiplier * currentX;
      result = result.simplify();
      cout << "Multiplier * CurrentX = " << mutiplier << " * " << currentX << " = " << result << " ~= " << (multiplier * currentX).approx() << endl;
      }
*/
      pagePainter.drawText((multiplier * currentX).approx(), currentY, QString(1, textLine[i]));
      break;

    case 15:
      pre17Page = currentPage;
      pre17Multiplier = multiplier;

      pagePainter.end();   
      pagePainter.begin(cpi17Page);   
      currentPage = cpi17Page;
      initTextPainter();
      multiplier = "2 1/3"; 
//    cout << multiplier << " is approx: " << multiplier.approx() << endl;
      cout << multiplier << " set at line: " << __LINE__ << endl;
      break;

    case 18:
      pagePainter.end();   
      pagePainter.begin(pre17Page);  
      currentPage = pre17Page;
      multiplier = pre17Multiplier;
      cout << multiplier << " set at line: " << __LINE__ << endl;
      initTextPainter();
      break;

    case 27:
      if(i + 1 < textLine.length())
      {
	QPixmap *actualPage = NULL;

	i++;

	switch(textLine[i])
	{
	case 77:
	  pre12Page = currentPage;
	  pre12Multiplier = multiplier;
	  multiplier = "1 7/10";
	  cout << multiplier << " set at line: " << __LINE__ << endl;
	  currentPage = cpi12Page;
	  break;

	case 80:
	  currentPage = pre12Page;
	  multiplier = pre12Multiplier;
	  cout << multiplier << " set at line: " << __LINE__ << endl;
	  break;

	default:
	  cerr << "Unknown control code: " << int(textLine[i]) << endl;
	  break;
	}

	pagePainter.end();  
	pagePainter.begin(currentPage);   
	initTextPainter();
      }
      break;
    }

    if(advance)
    {
      if(multiplier.approx() == 0)
      {
//	cout << multiplier << endl;
      }
      else 
      {
        currentX += (Rational(columnWidth) / multiplier).approx();
      }
    }
  }

  currentX = 0;
  currentY += pointSize;
}


unsigned int Oki2Pixmap::numPages()
{
  return pixmapSource.size();
}

QPixmap& Oki2Pixmap::operator[](int index)
{
  return pixmapSource[index];
}

void Oki2Pixmap::initTextPainter()
{
  QFont textFont("Arial", pointSize);
  textFont.setBold("TRUE");
  pagePainter.setFont(QFont("Arial", pointSize));
  pagePainter.setPen(QColor(0,0,0));
  pagePainter.setBackgroundMode(Qt::TransparentMode);
}
