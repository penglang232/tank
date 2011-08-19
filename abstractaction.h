#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H

#include "sprite.h"
#include <QMap>
#include <QPointF>

class AbstractAction : public Sprite
{
public:
    AbstractAction(Sprite* parent = 0);
    void virtual action(const QMap<int,bool> &keyPressed);
    QPointF prevPos;
};

#endif // ABSTRACTACTION_H
