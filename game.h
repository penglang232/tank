#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include <QTimer>
#include <QMap>
#include <QList>


class Sprite;
class TankView;
class Tank;
class AbstractAction;
class MapItem;
class MapManager;
class MapInfo;
class CombatBase;
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
    QList<AbstractAction*> actionItems; //不停动作的部件
    QList<MapItem*> mapItems;           //固有的部件
    QList<Sprite*> spriteItems;         //可以显示的部件
    CombatBase* combatBase;

    void onKeyPressed(int key);
    void onKeyRelease(int key);
    void addToScene(Sprite* s);
    void addMapItemToScene(MapItem* s);
    void addActionToScene(AbstractAction *s);
    void removeActionForScene(AbstractAction *s);
    void removeMapItemForScene(MapItem* s);
    void removeForScene(Sprite* s);
    bool hitTest(Sprite* s);
    QTimer timer;
protected:

    TankView* tankview;
    MapManager* mapManager;
    void resetKey();
private:
    MapInfo* map;
private slots:
    void paint();
    void createActionItems();
    void createMapItems();
    void initMap();
    void combatBaseDamage(Tank* tank);
};

#endif // STATEMANAGER_H
