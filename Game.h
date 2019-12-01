#ifndef GAME_H
#define GAME_H


#include "Jet.h"
#include "PlayerProjectile.h"
#include "Guide.h"
#include "Spider.h"
#include "FrenzyPackDisplayBar.h"
#include "HealthBar.h"
#include "Equiment.h"
#include "Meteor.h"
#include "EnemyProjectile.h"
#include "enumList.h"
#include <QMainWindow>
#include "QDebug"
#include "QTime"
#include "QKeyEvent"
#include "QGraphicsView"
#include "iostream"
#include "QtMath"
#include "QList"
#include "QRandomGenerator"

class Game: public QGraphicsView{


public:

    Game(QObject* parent);

signals:

    void restart();

public slots:

    void fire();
    void stopFrenzyEffect();
    void screenEventHandler();
    void playerControlAvailable();
    void spawnEnemy();
    void spawnEquipment(double x, double y, int dropRate);
    void spawnEnemyPeojectile(double x, double y);
    void addEquipmentEffect(EquipmentName);/// Day 5
    void stopStormerEffect();
    void opening();



private:

    Q_OBJECT

    const int maxNumOfFrenzyPack = 3;
    const int maxHealthOfJet = 300;

    //Pointers to all objects that need to add to the graphic view
    QGraphicsScene* scene;
    Jet* jet;
    PlayerProjectile* projectile;
    Guide* guide;
    Equipment* equipment;
    Enemy* enemy;
    EnemyProjectile* enemyProjectile;
    FrenzyPackDisplayBar* frenzyPackDisplayBar;
    HealthBar* healthBar;

    //4 async event
    QTimer* refreshRate;
    QTimer* frenzy;
    QTimer* enemySpawningTimer;
    QTimer* openingTimer;


//    int fps;
//    int fireRate;


    //Readibility
    ProjectileType weapon;

    int numOfFrenzyPack;
    int stormerEffectStack;
    int killCount;

    bool goingUp = false;
    bool goingDown = false;
    bool goingLeft = false;
    bool goingRight = false;
    bool firing = false;
    bool frenzyMode = false;
    bool gameOver = false;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void addPlayerProjectile(Tilt tilt);
    void addEquipment(EquipmentName name, double x, double y);
    void addSpider();
    void addMeteor();

    void firePlasmaBeam();
    void fireFlakkerBeam();
    void fireUltraFlakkerBeam();

    void pause();
    //    void paintEvent(QPaintEvent* event) override;
    //    void timerEvent(QTimerEvent* event) override;

};

#endif // GAME_H
