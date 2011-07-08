#include "abstractaction.h"
//中文
AbstractAction::AbstractAction(Sprite* parent)
    : Place(PLACE_QUALITY_DEF,parent)
{

}
void AbstractAction::action(const QMap<int, bool> &keyPressed){}
