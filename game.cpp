#include "game.h"
#include "abstractaction.h"
#include "tankview.h"
#include "tankgnu.h"
#include "place.h"
#include <QDebug>


/*
     软键盘
     按键的时候通过预先初始化的SKey(QMap类型 key是qt按键值value是软键盘)
     查找软键盘相应按键，再使用Keypressed 按键状态机设置按键状态
 */

Game::Game(TankView* tankview)
{
    //软键盘初始化
    this->SKey.insert(Qt::Key_Up,Game::SK_UP);
    this->SKey.insert(Qt::Key_Down,Game::SK_DOWN);
    this->SKey.insert(Qt::Key_Left,Game::SK_LEFT);
    this->SKey.insert(Qt::Key_Right,Game::SK_RIGHT);
    this->SKey.insert(Qt::Key_Space,Game::SK_ACT);

    resetKey();

    this->createActionItems();
    this->createBlockItems();

    this->tankview = tankview;
    timer.setInterval(16);

    this->connect(&timer,SIGNAL(timeout()),this,SLOT(paint()));
    timer.start();

}

Game::~Game()
{
}

//初始化场景可动物体
void Game::createActionItems()
{
    Tank* tank1 = new Tank(1);
    actionItems.append(tank1);
}
//初始化场景不可动物体
void Game::createBlockItems()
{
    Place* p1 = new Place();
    Place* p2 = new Place();

    p1->setX(200);
    p1->setY(200);
    p1->resize(100,30);
    p2->setX(410);
    p2->setY(200);
    p2->resize(203,100);
    blockItems.append(p1);
    blockItems.append(p2);

}
/*
    重置按键状态
 */
void Game::resetKey()
{
    foreach(int value ,this->SKey.values()){
        this->keyPressed.insert(value,false);
    }
}
void Game::onKeyPressed(int key)
{
    if(this->SKey.keys().contains(key))
        this->keyPressed.insert(this->SKey.value(key),true);
}
void Game::onKeyRelease(int key)
{
    if(this->SKey.keys().contains(key))
        this->keyPressed.insert(this->SKey.value(key),false);
}

void Game::paint()
{
    for(int i=0;i< this->actionItems.size();i++)
    {
        AbstractAction* actionItem = this->actionItems.at(i);

        actionItem->action(this->keyPressed);
    }
}

void Game::addToScene(Place *s)
{
    this->tankview->drawScene->addItem(s);
    this->blockItems.append(s);
}
void Game::addActionToScene(AbstractAction *s)
{
    this->tankview->drawScene->addItem(s);
    this->actionItems.append(s);
}

void Game::removeActionForScene(AbstractAction *s)
{
    this->actionItems.removeAll(s);
    this->tankview->drawScene->removeItem(s);
}

void Game::removeBlockForScene(Place *s)
{
    this->blockItems.removeAll(s);
    this->tankview->drawScene->removeItem(s);
}

//碰撞检测
bool Game::hitTest(Place *s)
{
    return s->collidingItems().length() > 0;
}