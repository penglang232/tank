#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include <QTimer>
#include <QMap>
#include <QList>



class TankView;
class AbstractAction;
class Place;
class Game : public QObject
{
    Q_OBJECT
public:
    Game(TankView* tankview);
    ~Game();

    enum SKey {
        SK_UP = 0,
        SK_LEFT ,
        SK_DOWN ,
        SK_RIGHT,
        SK_ACT
    };

    QMap<int,bool> keyPressed;
    QMap<int,int> SKey;
    QList<AbstractAction*> actionItems;
    QList<Place*> blockItems;

    void onKeyPressed(int key);
    void onKeyRelease(int key);
    void addToScene(Place* s);
    void addActionToScene(AbstractAction *s);
    void removeActionForScene(AbstractAction *s);
    void removeBlockForScene(Place* s);
    bool hitTest(Place* s);
    QTimer timer;
protected:

    TankView* tankview;
    void resetKey();
private slots:
    void paint();
    void createActionItems();
    void createBlockItems();
};

#endif // STATEMANAGER_H
