#ifndef MAPITEM_H
#define MAPITEM_H
#include "mapbase.h"
class MapItem : public MapBase
{
public:
    MapItem(QPixmap* base,unsigned int hindex = 0,unsigned int vindex = 0,
            unsigned int hnum = 1,unsigned int vnum = 1,QGraphicsItem* parent = 0);
    int crossType;
    int checkType;
    int breakType;
    int special;
    int mapX;
    int mapY;
    int mapZ;
};

#endif // MAPITEM_H
