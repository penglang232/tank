#ifndef SPARK_H
#define SPARK_H
#include "sprite.h"

#include <QTimer>
class Spark : public Sprite
{
    Q_OBJECT
public:
    Spark(Sprite* p = 0);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QTimer* timer;

protected slots:
    void clear();
};

#endif // SPARK_H
