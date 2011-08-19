#include "game.h"
#include "abstractaction.h"
#include "tankview.h"
#include "tankgnu.h"
#include "mapitem.h"
#include "fps.h"
#include "mapmanager.h"
#include "mapinfo.h"
#include <QDebug>


/*
     软键盘
     按键的时候通过预先初始化的SKey(QMap类型 key是qt按键值value是软键盘)
     查找软键盘相应按键，再使用Keypressed 按键状态机设置按键状态
 */

static QString actionType("action");
static QString blockType("block");
static QString spriteType("sprite");
Game::Game(TankView* tankview)
{
    //软键盘初始化
    this->SKey.insert(Qt::Key_Up,Game::SK_UP);
    this->SKey.insert(Qt::Key_Down,Game::SK_DOWN);
    this->SKey.insert(Qt::Key_Left,Game::SK_LEFT);
    this->SKey.insert(Qt::Key_Right,Game::SK_RIGHT);
    this->SKey.insert(Qt::Key_Space,Game::SK_ACT);

    resetKey();

    this->tankview = tankview;
    mapManager = new MapManager(tankview->drawScene,this);

    this->initMap();

    foreach(Sprite* s,this->actionItems)
    {
        mapManager->addSprite(s,actionType);
    }
    foreach(Sprite* s,this->mapItems)
    {
        mapManager->addSprite(s,blockType);
    }

    timer.setInterval(DEF_FLUSH_TIMESTAMP);

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
    //tank1->setZValue(2);
    FPS* fps = new FPS();
    tank1->setPos(100,100);
    actionItems.append(tank1);
    actionItems.append(fps);
}
//初始化场景不可动物体
void Game::createMapItems()
{
    foreach( MapItem* item , this->map->getMapItemInfo())
    {
        this->mapItems.append(item); //将地图MapItem信息全部固有物件
    }
}

//初始化场景
void Game::initMap()
{
    QString mapbase(":/image/base/base1.png");
    QString mapdata("test2.mdt");
    this->map = new MapInfo(mapbase);
    this->map->readMap(mapdata);

    this->mapManager->initMap(map);
    this->createActionItems();
    this->createMapItems();
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
    this->tankview->drawScene->update();

}

void Game::addToScene(Sprite *s)
{
    this->tankview->drawScene->addItem(s);
    this->spriteItems.append(s);
}

void Game::addMapItemToScene(MapItem *s)
{
    this->tankview->drawScene->addItem(s);
    this->mapItems.append(s);
}


void Game::addActionToScene(AbstractAction *s)
{
    this->tankview->drawScene->addItem(s);
    this->actionItems.append(s);
}

void Game::removeActionForScene(AbstractAction *s)
{
    this->actionItems.removeAll(s);
    this->mapManager->removeSprite(s,actionType);
}

void Game::removeMapItemForScene(MapItem *s)
{
    this->mapItems.removeAll(s);
    this->mapManager->removeSprite(s,s->typeName);
}

void Game::removeForScene(Sprite *s)
{
    this->spriteItems.removeAll(s);
    this->mapManager->removeSprite(s,spriteType);
}

//碰撞检测
bool Game::hitTest(Sprite *s)
{
    return s->collidingItems().length() > 0;
}
