#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H

#include "place.h"
#include <QMap>
#include <QPointF>

class AbstractAction : public Place
{
public:
    AbstractAction(Sprite* parent = 0);
    void virtual action(const QMap<int,bool> &keyPressed);
    QPointF prevPos;
};

#endif // ABSTRACTACTION_H
