#ifndef TANKGNU_H
#define TANKGNU_H
#include "abstractaction.h"
#include "tank.h"
#include <QLinearGradient>

class TankGnu : public AbstractAction
{
public:
    TankGnu(Tank* parent=0);
    QPainterPath shape() const;
    void action(const QMap<int, bool> &keyPressed);
    Tank* getTank();
    void setTank(Tank* tank);
    void setSpeed(int speed);
    int getSpeed();
protected:
    Tank* tank;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
private:
    int ackVector;
    int speed;
    QPainterPath path;
    QLinearGradient gnuGradient;
};

#endif // TANKGNU_H
