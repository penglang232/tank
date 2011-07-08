#include "place.h"
#include <QPainter>

Place::Place(unsigned int q ,Sprite* parent):
        Sprite(parent)
{
    quality =q;
}
QRectF Place::boundingRect() const
{
    qreal pw = 1.0;
    return QRectF(QPoint(0,0),QSizeF(this->width,this->height)).adjusted(-pw/2, -pw/2, pw/2, pw/2);
}

void Place::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    painter->setPen(Qt::white);
    painter->setBrush(QBrush(Qt::blue));
    painter->drawRect(0,0,this->width,this->height);
    //painter->drawRect(this->boundingRect());
}
