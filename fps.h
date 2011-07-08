#ifndef FPS_H
#define FPS_H
#include "abstractaction.h"
#include <QMap>
#define TMP_TIME 1000 //1秒钟

#define DEF_MAX_FRAME_RATE 60 //最大帧率
#define DEF_FLUSH_TIMESTAMP TMP_TIME / DEF_MAX_FRAME_RATE
class FPS : public AbstractAction
{
public:
    FPS(AbstractAction *parent = 0);
    void action(const QMap<int,bool> &keyPressed);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    QString _FPS;

};

#endif // FPS_H
