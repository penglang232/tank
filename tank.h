#ifndef TANK_H
#define TANK_H
#include "abstractaction.h"
#include "sprite.h"
#include <QGraphicsItem>
#include <QList>

class TankGnu;
class Tank : public AbstractAction
{

public:
    Tank(unsigned int tankId,AbstractAction *parent = 0);

    enum TankVector{
        UP = 0,
        LEFT = 1,
        DOWN = 2,
        RIGHT = 3
    };

    qreal speed;
    unsigned int tankId;
    unsigned int gnuWidth;
    int actlevel;
    TankVector vector;

    int act();
    QRectF boundingRect() const;
    void action(const QMap<int,bool> &keyPressed);
    QPainterPath shape() const;
    void resize(qreal width, qreal height);
    void ackDone(TankGnu* gnu);
protected:
    bool paintBorder;
    QPainterPath* path;
    bool acking;

    QList<TankGnu*> gnus;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void initClipPath();
    void resetAck(TankGnu* gnu);
};

#endif // TANK_H
