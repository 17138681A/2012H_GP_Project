#ifndef BEETLE_H
#define BEETLE_H
#include "Enemy.h"

class Beetle: public Enemy{

    Q_OBJECT

public:

    Beetle(QTimer* timer);


public slots:

    void emitSpawnEnemyProjectileSignal(); //This enemy can shoot projectile
    void startHovering(); //Start moving in either left or right direction
    void stopHovering(); //Stop moving, fire projectiles and prepare for the next horvering

    void move() override;


private:

    int randVer; //To indicate how far it would go after entering the game
    int randHor; //Spawn randomly whitin the horizontal range of [100, 1080)
    int randDir; //Random horizontal direction of movement during hovering

    bool isArriving; //Entering the game

};

#endif // BEETLE_H
