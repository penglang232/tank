#include "tankview.h"
#include "tank.h"
#include "mapitem.h"
#include "global.h"
#include <QKeyEvent>
#include <QDebug>
#include <QGLWidget>


extern Game* gGame;

TankView::TankView(QGraphicsView *parent)
    : QGraphicsView(parent)
{
    this->drawScene = new QGraphicsScene(this);

    this->game = new Game(this);
    gGame = this->game;
    this->setScene(this->drawScene);
    if(USING_OPENGL)this->setViewport(new QGLWidget());
    //this->setSceneRect(0,0,795,595);
    //this->setWindowFlags(Qt::FramelessWindowHint);

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

void TankView::setOrientation(ScreenOrientation orientation)
{
#if defined(Q_OS_SYMBIAN)
    // If the version of Qt on the device is < 4.7.2, that attribute won't work
    if (orientation != ScreenOrientationAuto) {
        const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
        if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
            qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
            return;
        }
    }
#endif // Q_OS_SYMBIAN

    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}
