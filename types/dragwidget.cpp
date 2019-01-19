#include <QtGui>
#include <QPalette>
#include "dragwidget.h"
#include "draglabel.h"

DragWidget::DragWidget(QWidget *parent)
    : QWidget(parent)
{
    // setMinimumSize(400, qMax(200, y));
    QPalette p = palette();
    p.setColor(QPalette::Background, QColor(244,238,224));
    setPalette(p);

    setAcceptDrops(true);
    initLabels();
}

void DragWidget::paintEvent(QPaintEvent * event)
{
    QWidget::paintEvent(event);
    QPainter painter;
    painter.begin(this);
    painter.setBrush(Qt::black);
    int linePosition = 20;
    while(linePosition < height()){
        painter.drawLine(0, linePosition, width(), linePosition);
        linePosition += 20;
    }
    painter.end();
}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void DragWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void DragWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-auctioncheck")) {
        const QMimeData *mime = event->mimeData();
        QByteArray itemData = mime->data("application/x-auctioncheck");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString text;
        QPoint offset;
        dataStream >> text >> offset;
        DragLabel *newLabel = m_labels[text]; //new DragLabel(text, this);
        if (newLabel != 0){
            QPoint pos = event->pos() - offset;
            newLabel->move(pos.x(), ((pos.y() / 20) * 20) + 1);
            QPoint labPos = newLabel->pos();
            if(newLabel->pos().x() < 0){
                labPos.setX(0);
            }else if(newLabel->pos().x() + newLabel->width() > this->width()){
                labPos.setX(this->width() - newLabel->width());
            }
            newLabel->move(labPos);
            newLabel->show();
        }
        //newLabel->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->ignore();
            //event->acceptProposedAction();
        }
    }  else {
        event->ignore();
    }
}

void DragWidget::mousePressEvent(QMouseEvent *event)
{
    DragLabel *child = static_cast<DragLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPoint hotSpot = event->pos() - child->pos();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << child->labelText() << QPoint(hotSpot);

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-auctioncheck", itemData);
    mimeData->setText(child->labelText());

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(*child->pixmap());
    drag->setHotSpot(hotSpot);

 //   child->hide();

    if (drag->exec(Qt::MoveAction ) == Qt::MoveAction)
    {


    }
//        child->close();
//    else
//        child->show();
}

void DragWidget::checkedAddress1()
{
    hideShowLabel("Address 1");
}

void DragWidget::checkedAddress2()
{
    hideShowLabel("Address 2");
}

void DragWidget::checkedAmount()
{
    hideShowLabel("Amount");
}

void DragWidget::checkedCity()
{
    hideShowLabel("City, St Zip");
}

void DragWidget::checkedDate()
{
    hideShowLabel("Date");
}

void DragWidget::checkedHead()
{
    hideShowLabel("Head Count");
}

void DragWidget::checkedMemo()
{
    hideShowLabel("Memo");
}

void DragWidget::checkedNumber()
{
    hideShowLabel("Number");
}

void DragWidget::checkedPayee()
{
    hideShowLabel("Payee");
}

void DragWidget::checkedSignature()
{
    hideShowLabel("Signature");
}

void DragWidget::checkedTextAmount()
{
    hideShowLabel("Text Amount");
}

void DragWidget::initLabels()
{
    m_labels.insert("Address 1", NULL);
    m_labels.insert("Address 2", NULL);
    m_labels.insert("Amount", NULL);
    m_labels.insert("City, St Zip", NULL);
    m_labels.insert("Date", NULL);
    m_labels.insert("Head Count", NULL);
    m_labels.insert("Memo", NULL);
    m_labels.insert("Number", NULL);
    m_labels.insert("Payee", NULL);
    m_labels.insert("Signature", NULL);
    m_labels.insert("Text Amount", NULL);

    foreach(QString tag, m_labels.keys()){
        DragLabel* label = new DragLabel(tag, 100/*temp*/, this);
        label->setVisible(false);
        label->setAttribute(Qt::WA_DeleteOnClose);
        m_labels[tag] = label;
    }
}

void DragWidget::hideShowLabel(QString tag)
{
    DragLabel* label = m_labels.value(tag);
    if(label != NULL){
        if(label->isVisible()){
            label->setVisible(false);
        }else{
            label->setVisible(true);
        }
    }
}

QMap<QString, QPair<int, int> *> DragWidget::getLabelPositions()
{
    int rowHeight = 20;
    int colWidth = 10;

    QMap<QString, QPair<int,int>* > labels;

    foreach(QString tag, m_labels.keys()){
        DragLabel* label = m_labels.value(tag);
        if(label->isVisible()){
            QPoint position = label->pos();
            QPair<int, int>* cell = new QPair<int, int>(0, 0);
            cell->first = position.y() / rowHeight;
            cell->second = position.x() / colWidth;
            labels.insert(tag, cell);
        }else{
            QPair<int, int>* cell = new QPair<int, int>(0, 81);
            labels.insert(tag, cell);
        }
    }
    return labels;
}

void DragWidget::setLabelPositions(QMap<QString, QPair<int,int>* >& labels)
{
    int rowHeight = 20;
    int colWidth = 10;
    foreach(QString tag, labels.keys()){
        DragLabel* label = m_labels.value(tag);
        QPoint pos;
        pos.setX(labels.value(tag)->second * colWidth);
        pos.setY(labels.value(tag)->first * rowHeight + 1);
        label->move(pos);
    }
}




