#include <QtGui/QApplication>
#include "tankview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TankView w;
    //w.show();
    w.setOrientation(TankView::ScreenOrientationAuto);
    w.showFullScreen();
    //w.resize(800,600);

    return a.exec();
}
