#ifndef TANKVIEW_H
#define TANKVIEW_H

#include <QtGui/QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "tank.h"
#include "game.h"
#include "abstractaction.h"
#define USING_OPENGL true
class Place;
class TankView : public QGraphicsView
{
    Q_OBJECT

public:
    TankView(QGraphicsView *parent = 0);
    ~TankView();
    QGraphicsScene* drawScene;
    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };
    void setOrientation(ScreenOrientation orientation);
protected:
    void keyPressEvent ( QKeyEvent * event );
    void keyReleaseEvent ( QKeyEvent * event );
private:
    Game* game;
};

#endif // TANKVIEW_H
