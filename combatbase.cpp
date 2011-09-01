#include "combatbase.h"
#include <QPainter>
CombatBase::CombatBase(QPixmap* base):
      MapItem(base)
{

}

void CombatBase::attack(Tank* tank)
{

    emit this->attacked(tank);
}
