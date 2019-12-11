#ifndef HORRORDISK_H
#define HORRORDISK_H

#include "Enemy.h"



class HorrorDisk: public Enemy{

Q_OBJECT

public:

    explicit HorrorDisk(QTimer* timer, QObject* parent);

public slots:
    void emitEnemyProjectileIsLaunchedSignal();
    void move() override;
    void startBursting();
//    void stopShooting();

private:

    int rotationDegree;
    int randDirOfX;
    int randDirOfY;
    int attackPeriod;
    int attackCounter;
    int numOfBurst;

    bool isArriving;
    bool isRaging;
//    bool bursting;

//    QTimer* attackTimer;
    QTimer* burstTimer;

};

#endif // HORRORDISK_H
