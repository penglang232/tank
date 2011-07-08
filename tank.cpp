#include "tank.h"
#include "spark.h"
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QTime>
#include "game.h"
#include "tankgnu.h"

#define TANK_DEF_WIDTH 36
#define TANK_DEF_HEIGHT 36
#define TANK_DEF_ACTLEVEL 1
#define TANK_DEF_SPEED 2
#define TANK_PADDING 0
#define TANK_GNU_WIDTH 3

extern Game* gGame;
QLinearGradient TankGradient;
static unsigned int paintTime;

Tank::Tank(unsigned int tankId,AbstractAction *parent) :
    AbstractAction(parent)
{
    paintTime = 0;
    acking = false;
    this->tankId = tankId;
    this->width = TANK_DEF_WIDTH;
    this->height = TANK_DEF_HEIGHT;
    this->actlevel = TANK_DEF_ACTLEVEL;
    this->speed = TANK_DEF_SPEED;
    this->gnuWidth = TANK_GNU_WIDTH;
    this->vector = Tank::UP;
    TankGradient.setColorAt(0,Qt::white);
    TankGradient.setColorAt(1,Qt::green);
    TankGradient.setStart(4,4);
    TankGradient.setFinalStop(40,40);
    paintBorder = false;
    path = 0;
    initClipPath();
    this->setTransformOriginPoint(this->width / 2 ,this->height /2);

}

void Tank::resize(qreal width, qreal height)
{
    Sprite::resize(width,height);
    this->initClipPath();
}

//剪切路径用于碰撞检测
void Tank::initClipPath()
{
    if(path == 0)path = new QPainterPath();
    else{
        delete path;
        path = new QPainterPath();
    }

    path->addRoundedRect(TANK_PADDING,TANK_PADDING,
                        this->width -TANK_PADDING *2 ,this->height - TANK_PADDING *2 ,5,5);
    path->setFillRule(Qt::WindingFill);
}

QRectF Tank::boundingRect() const
{
    qreal pw = 1.0;
    return QRectF(QPoint(0,0),QSizeF(this->width,this->height)).adjusted(-pw/2, -pw/2, pw/2, pw/2);
}

//绘制外观
void Tank::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    QTime point1;
    point1.start();

    if(paintBorder){
        painter->setPen(Qt::black);
        painter->setBrush(QBrush(Qt::white));
        painter->drawRect(0,0,this->width,this->height);
    }
    QVector<QPointF> points;
    points <<
        QPointF(this->width / 2 - gnuWidth * 2, 0) <<
        QPointF(this->width / 2 - gnuWidth, gnuWidth) <<
        QPointF(this->width / 2 - gnuWidth, this->height / 2) <<
        QPointF(this->width / 2 + gnuWidth, this->height / 2) <<
        QPointF(this->width / 2 + gnuWidth, gnuWidth) <<
        QPointF(this->width / 2 + gnuWidth * 2, 0);

    qreal drawWidth = this->width - TANK_PADDING*2;
    qreal drawHeight = this->height - TANK_PADDING*2;
    painter->setPen(QPen(Qt::black));
    painter->setBrush(QBrush(TankGradient));
    painter->drawChord(TANK_PADDING + 5,TANK_PADDING + 2,drawWidth - 10,15,0,16*180);
    painter->drawChord(TANK_PADDING + 5,drawHeight -16 - TANK_PADDING,drawWidth - 10,15,16*180,16*180);
    painter->drawRect(TANK_PADDING,TANK_PADDING + 10,drawWidth,drawHeight -12 - TANK_PADDING);
    painter->drawRoundedRect(TANK_PADDING,TANK_PADDING,
                             this->width /4 ,this->height - TANK_PADDING *2 ,2,2);
    for(int i=1;i<5;i++){
        painter->drawLine(TANK_PADDING,TANK_PADDING + i * 2,TANK_PADDING + this->width /4,TANK_PADDING + i * 2);
    }
    for(int i=4;i>0;i--){
        painter->drawLine(TANK_PADDING,drawHeight + TANK_PADDING - i * 2,TANK_PADDING + this->width /4,drawHeight + TANK_PADDING - i * 2);
    }
    painter->drawRoundedRect(drawWidth+TANK_PADDING - this->width /4,TANK_PADDING,
                             this->width /4 ,this->height - TANK_PADDING *2 ,2,2);
    for(int i=1;i<5;i++){
        painter->drawLine(drawWidth+TANK_PADDING - this->width /4,TANK_PADDING + i * 2,drawWidth+TANK_PADDING,TANK_PADDING + i * 2);
    }
    for(int i=4;i>0;i--){
        painter->drawLine(drawWidth+TANK_PADDING - this->width /4,drawHeight + TANK_PADDING - i * 2,drawWidth+TANK_PADDING,drawHeight + TANK_PADDING - i * 2);
    }

    painter->drawConvexPolygon(QPolygonF(points));
    painter->drawLine(points.at(1),points.at(4));

    painter->drawRoundedRect(this->width /2 - this->width / 6,this->height /2 , this->width / 3, this->height /3, 2.0 , 2.0);
    painter->drawEllipse(this->width /2 - this->width / 8,this->height /2 + 2, this->width / 4, this->height /4);

    switch(this->vector)
    {
        case Tank::UP:
            this->setRotation(0);
            break;
        case Tank::LEFT:
            this->setRotation(270);
            break;
        case Tank::DOWN:
            this->setRotation(180);
            break;
        case Tank::RIGHT:
            this->setRotation(90);
    }
    unsigned int time = point1.elapsed();
    if(paintTime < time){
        paintTime = time;
        qDebug() << paintTime;
    }
}

QPainterPath Tank::shape() const
{
    return *path;
}

int Tank::act()
{
    return actlevel;
}

void Tank::action(const QMap<int,bool> &keyPressed)
{
    Tank* t = this;
    t->prevPos = t->pos();
    if(keyPressed.value(Game::SK_UP,false)){
        t->moveBy(0,-speed);
        t->vector = Tank::UP;
    }
    if(keyPressed.value(Game::SK_LEFT,false)){
        t->moveBy(-speed,0);
        t->vector = Tank::LEFT;
    }
    if(keyPressed.value(Game::SK_DOWN,false)){
        t->moveBy(0,speed);
        t->vector = Tank::DOWN;
    }
    if(keyPressed.value(Game::SK_RIGHT,false)){
        t->moveBy(speed,0);
        t->vector = Tank::RIGHT;
    }
    if(keyPressed.value(Game::SK_ACT,false))
    {
        if(!acking){
            acking = true;
            qDebug()<< "tank:"+QVariant(this->tankId).toString()+" -ack-";
            TankGnu* gnu = new TankGnu(this);
            gnu->setTransformOriginPoint(3,6);
            Tank* tank = this;
            qreal dWidth = tank->getWidth();
            qreal dHeight = tank->getHeight();

            switch(tank->vector)
            {
            case Tank::UP:
                gnu->setPos(tank->x() + dWidth / 2 - gnu->getWidth() /2,tank->y() - TANK_GNU_WIDTH);
                break;
            case Tank::LEFT:
                gnu->setPos(tank->x() - TANK_GNU_WIDTH ,tank->y()+dHeight / 2 - gnu->getHeight()/2 );
                gnu->setRotation(270);
                break;
            case Tank::DOWN:
                gnu->setPos(tank->x() + dWidth / 2 - gnu->getWidth() / 2,tank->y() + tank->getHeight() +TANK_GNU_WIDTH);
                gnu->setRotation(180);
                break;
            case Tank::RIGHT:
                gnu->setPos(tank->x()+tank->getWidth() + TANK_GNU_WIDTH,tank->y() + dHeight / 2 - gnu->getHeight() / 2);
                gnu->setRotation(90);
                break;
            }

            gnus.append(gnu);
            gGame->addActionToScene(gnu);
        //keyPressed.insert(Game::SK_ACT,false);
        }
    }
    foreach(Sprite* item , gGame->blockItems) //检测阻隔对象
    {
        if(item->collidesWithItem(this))
        {
            this->setPos(this->prevPos);
            item->collidingItems().removeAt(item->collidingItems().indexOf(this));
            this->collidingItems().removeAll(this);
            break;
        }
    }
}

void Tank::ackDone(TankGnu* gnu)
{
    qDebug() << this->tankId<< " ack Done";
    gGame->removeActionForScene(gnu);

    foreach(Place* p ,gGame->blockItems)
    {
        if(p->collidesWithItem(gnu)){
            if(p->quality <= this->actlevel){
                gGame->removeBlockForScene(p);

                Spark* spark = new Spark();
                spark->setX(p->x());
                spark->setY(p->y());
                gGame->addToScene(spark);

                delete p;
            }
        }
    }

    this->acking = false;
    this->gnus.removeAll(gnu);

    delete gnu;

}
