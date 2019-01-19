#include "checksetup_frame.h"

#include <QPainter>
#include <QPoint>

CheckSetupFrame::CheckSetupFrame( QWidget *parent) : Q3Frame(parent)
{
    setBackgroundMode(Qt::NoBackground);
}

CheckSetupFrame::~CheckSetupFrame()
{
}

void CheckSetupFrame::paintEvent(QPaintEvent *)
{
    //qDebug("CheckSetupFrame::paintEvent(QPaintEvent *)");
    QPainter painter(this);
    
    painter.setFont(formatFont);
    
    painter.eraseRect(this->rect());

    for(int i = 0; i < 13; i++)
    {
        painter.drawText(QPoint(10, 20 * (i + 1)), text[i]);
    }
}