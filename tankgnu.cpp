#include "tankgnu.h"
#include <QPainter>
#define GNU_DEF_WIDTH 6
#define GNU_DEF_HEIGHT 20
#define GNU_DEF_SPEED 4

static QLinearGradient GnuGradient;
static QPainterPath path;

TankGnu::TankGnu(Tank* tank)
{
    this->width = GNU_DEF_WIDTH;
    this->height = GNU_DEF_HEIGHT;
    this->tank = tank;
    this->ackVector = tank->vector;
    this->speed = GNU_DEF_SPEED;

    GnuGradient.setColorAt(0,Qt::white);
    GnuGradient.setColorAt(1,Qt::green);
    GnuGradient.setStart(1,0);
    GnuGradient.setFinalStop(10,10);

    path.moveTo(0,5);
    path.lineTo(3,0);
    path.lineTo(6,5);
    path.lineTo(6,12);
    path.lineTo(0,12);
    path.closeSubpath();
}

QPainterPath TankGnu::shape() const
{
    return path;
}

void TankGnu::action(const QMap<int, bool> &keyPressed)
{
    this->prevPos = this->pos();
    switch(this->ackVector)
    {
    case Tank::UP:
        this->moveBy(0,-this->speed);
        break;
    case Tank::LEFT:
        this->moveBy(-this->speed,0);
        break;
    case Tank::DOWN:
        this->moveBy(0,this->speed);
        break;
    case Tank::RIGHT:
        this->moveBy(this->speed,0);
        break;
    }
    if(this->collidingItems().length() > 0){
        this->tank->ackDone(this);
    }

}

void TankGnu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(QBrush(GnuGradient));
    painter->drawPath(path);
    //painter->drawRect(0,0,this->width,this->height);

}
void TankGnu::setTank(Tank *tank)
{
    this->tank = tank;
}
Tank* TankGnu::getTank()
{
    return this->tank;
}
int TankGnu::getSpeed()
{
    return this->speed;
}
void TankGnu::setSpeed(int speed)
{
    this->speed = speed;
}
