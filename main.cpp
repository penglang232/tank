#include <QtGui/QApplication>
#include <QTextCodec>
#include "tankview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec* utf8 = QTextCodec::codecForName("UTF8");
    QTextCodec::setCodecForCStrings(utf8);
    QTextCodec::setCodecForLocale(utf8);
    QTextCodec::setCodecForTr(utf8);

    TankView w;
    //w.show();
    w.setOrientation(TankView::ScreenOrientationAuto);
    w.showFullScreen();
    //w.resize(800,600);

    return a.exec();
}
