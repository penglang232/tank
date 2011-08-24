#include "spark.h"
#include "sprite.h"
#include "game.h"
#include <QPainter>
#include <math.h>
QPainterPath starPath;
qreal Pi = 3.1415926;

extern Game* gGame;

Spark::Spark(Sprite* p)
    :Sprite(p)
{
    this->width = 100;
    this->height = 100;
    starPath.moveTo(90, 50);
    for (int i = 1; i < 5; ++i) {
        starPath.lineTo(50 + 40 * cos(0.8 * i * Pi),
                        50 + 40 * sin(0.8 * i * Pi));
    }
    starPath.closeSubpath();
    timer = new QTimer(this);
    this->connect(timer,SIGNAL(timeout()),this,SLOT(clear()));
    timer->start(1500);
}

void Spark::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPath(starPath);
}

void Spark::clear()
{
    gGame->removeForScene(this);
    delete timer;
    delete this;
}
