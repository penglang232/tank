#include "abstractaction.h"
//中文
AbstractAction::AbstractAction(Sprite* parent)
    :Sprite(parent)
{

}
void AbstractAction::action(const QMap<int, bool> &keyPressed){}
