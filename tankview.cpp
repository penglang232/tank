#include "tankview.h"
#include "tank.h"
#include "place.h"
#include "global.h"
#include <QKeyEvent>
#include <QDebug>

extern Game* gGame;

TankView::TankView(QGraphicsView *parent)
    : QGraphicsView(parent)
{
    this->drawScene = new QGraphicsScene(this);

    this->game = new Game(this);
    gGame = this->game;
    this->setScene(this->drawScene);
    this->setSceneRect(0,0,795,595);
    this->setWindowFlags(Qt::FramelessWindowHint);
    foreach(Sprite* s,this->game->actionItems)
    {
        this->drawScene->addItem(s);
    }
    foreach(Sprite* s,this->game->blockItems)
    {
        this->drawScene->addItem(s);
    }
}

TankView::~TankView()
{

}
void TankView::keyPressEvent ( QKeyEvent * event )
{
    game->onKeyPressed(event->key());
}
void TankView::keyReleaseEvent( QKeyEvent * event )
{
    game->onKeyRelease(event->key());
}

