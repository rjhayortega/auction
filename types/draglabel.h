#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QLabel>

 class QDragEnterEvent;
 class QDragMoveEvent;
 class QFrame;

 class DragLabel : public QLabel
 {
     Q_OBJECT
 public:
     DragLabel(const QString &text, int width, QWidget *parent);
     QString labelText() const;

 private:
     QString m_labelText;
 };


#endif // DRAGLABEL_H
