#ifndef TANKVIEW_H
#define TANKVIEW_H

#include <QtGui/QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "tank.h"
#include "game.h"
#include "abstractaction.h"

class Place;
class TankView : public QGraphicsView
{
    Q_OBJECT

public:
    TankView(QGraphicsView *parent = 0);
    ~TankView();
    QGraphicsScene* drawScene;
protected:
    void keyPressEvent ( QKeyEvent * event );
    void keyReleaseEvent ( QKeyEvent * event );
private:
    Game* game;
};

#endif // TANKVIEW_H
