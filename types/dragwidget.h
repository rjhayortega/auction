#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QWidget>
#include <QMap>
#include <QPair>

 class QDragEnterEvent;
 class QDropEvent;
 class DragLabel;

 class DragWidget : public QWidget
 {
     Q_OBJECT
 public:
     DragWidget(QWidget *parent = 0);
     QMap<QString, QPair<int,int>* > getLabelPositions();
     void setLabelPositions(QMap<QString, QPair<int,int>* >& labels);

 public slots:
     void checkedAddress1();
     void checkedAddress2();
     void checkedAmount();
     void checkedCity();
     void checkedDate();
     void checkedHead();
     void checkedMemo();
     void checkedNumber();
     void checkedPayee();
     void checkedSignature();
     void checkedTextAmount();

 protected:
     virtual void paintEvent(QPaintEvent * event);
     void dragEnterEvent(QDragEnterEvent *event);
     void dragMoveEvent(QDragMoveEvent *event);
     void dropEvent(QDropEvent *event);
     void mousePressEvent(QMouseEvent *event);
     void initLabels();
     void hideShowLabel(QString tag);

     QMap<QString, DragLabel*> m_labels;
 };

#endif // DRAGWIDGET_H
