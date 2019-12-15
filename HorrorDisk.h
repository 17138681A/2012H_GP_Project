#ifndef HORRORDISK_H
#define HORRORDISK_H

#include "Enemy.h"



class HorrorDisk: public Enemy{

Q_OBJECT

public:

    HorrorDisk(QTimer* timer, QObject* parent);

public slots:
    void emitSpawnEnemyProjectileSignal();
    void move() override;
    void startShooting();


private:

    int rotationDegree; //To rotate the image of this object
    int randDirOfX; //Randomize initial horizontal direction of movement after entering the game
    int randDirOfY; //Randomize initial vertical direction of movement after entering the game
    int shotCounter; //To count how many shot was made in each wave of attack
    int maxNumOfShot; //To indicate how many shot should made in each wave of attack

    bool isArriving; //Entering the game
    bool rage; //Special attack and behavior after getting rage


    QTimer* fireRateTimer; //To detemine the fire rate in each attack wave

};

#endif // HORRORDISK_H
