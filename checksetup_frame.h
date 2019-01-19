#ifndef CHECKSETUPFRAME_H
#define CHECKSETUPFRAME_H


#include <Q3Frame>

class CheckSetupFrame : public Q3Frame
{
Q_OBJECT

public:
    QStringList text;
    QFont formatFont;
  
    CheckSetupFrame( QWidget *parent=0);
    ~CheckSetupFrame();

protected:
    void paintEvent(QPaintEvent *);
};

#endif  // CHECKSETUPFRAME_H