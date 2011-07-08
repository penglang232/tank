#ifndef PLACE_H
#define PLACE_H
#include "sprite.h"
#define PLACE_QUALITY_DEF 1
class Place : public Sprite
{
public:
    Place(unsigned int q = PLACE_QUALITY_DEF,Sprite* parent=0);

    QRectF boundingRect() const;
    unsigned int quality;
protected:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
};

#endif // PLACE_H
