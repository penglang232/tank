#include "sprite.h"
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsSceneHoverEvent>

Sprite::Sprite(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    this->_pixmap = 0;
}

Sprite::~Sprite()
{
}

void Sprite::setPixmap(QPixmap *pixmap)
{
    this->width = pixmap->width();
    this->height = pixmap->height();
    this->_pixmap = pixmap;
    this->update();
}

QPixmap* Sprite::getPixmap(void)
{
    return this->_pixmap;
}

qreal Sprite::getWidth()
{
    return this->width;
}
qreal Sprite::getHeight()
{
    return this->height;
}

void Sprite::setHeight(qreal height)
{
    this->height = height;
}
void Sprite::setWidth(qreal width)
{
    this->width = width;
}

void Sprite::resize(qreal width, qreal height)
{
    this->width = width;
    this->height = height;
    this->update();
}

QRectF Sprite::boundingRect() const
{
    if (this->_pixmap)return QRectF();
    qreal pw = 1.0;
    return QRectF(QPoint(0,0),QSizeF(this->width,this->height)).adjusted(-pw/2, -pw/2, pw/2, pw/2);
}


void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->_pixmap)
        painter->drawPixmap(0,0,this->width,this->height,*this->_pixmap);
}

void Sprite::keyPressEvent(QKeyEvent *event)
{
    emit onKeyPress(event->key());
}
void Sprite::keyReleaseEvent(QKeyEvent *event)
{
    emit onKeyRelease(event->key());
}
void Sprite::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit onMousePress(event->pos().x(),event->pos().y(),event->buttons());
}
void Sprite::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit onMouseRelease(event->pos().x(),event->pos().y(),event->buttons());
}
void Sprite::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit onHover(event);
}
void Sprite::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
}
void Sprite::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
}
void Sprite::foucsInEvent(QFocusEvent *event)
{
    emit onFoucs(true);
}
void Sprite::foucsOutEvent(QFocusEvent *event)
{
    emit onFoucs(false);
}
