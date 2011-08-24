#ifndef COMBATBASE_H
#define COMBATBASE_H
#include "abstractaction.h"
#include "mapitem.h"
class QPainterPath;
class Tank;
class CombatBase : public MapItem
{
        Q_OBJECT
public:
    CombatBase(QPixmap* base);
    int health;
public slots:
    void attack(Tank* tank);
signals:
    void attacked(Tank* tank);
    void warning(int Level);

};

#endif // COMBATBASE_H
