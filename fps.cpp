#include "fps.h"
#include <QDateTime>
#include <QPainter>
#include <QMap>
#include <QDebug>

static unsigned long prevtime;
static int flushCount;
static QString prevFPS;

FPS::FPS(AbstractAction* parent):
    AbstractAction(parent)
{
    prevtime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    _FPS=tr("30");
    prevFPS = _FPS;
    flushCount = 0;
    this->setWidth(100);
    this->setHeight(24);
    this->update();
}

void FPS::action(const QMap<int, bool> &keyPressed)
{
    unsigned long c;
    c=  QDateTime::currentDateTime().toMSecsSinceEpoch();

    qreal timestamp = c - prevtime + 1; //真实时间间隔

    if(timestamp < DEF_FLUSH_TIMESTAMP)timestamp = DEF_FLUSH_TIMESTAMP;

    int t  = 1000/timestamp;

    _FPS = QVariant(t).toString();

    //if(timestamp > 20 )qDebug() << "_FPS:" <<_FPS; //延时偏大

    flushCount++;
    if(flushCount > 10)
    {
        if(prevFPS != _FPS)
        {
            prevFPS = _FPS;
            this->update();
        }
        flushCount =0;
    }
    prevtime = c;
}

void FPS::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black));
    painter->setBrush(QBrush(Qt::yellow));
    painter->drawText(20,20,_FPS);
}
