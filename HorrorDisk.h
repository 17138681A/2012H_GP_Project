#ifndef HORRORDISK_H
#define HORRORDISK_H

#include "Enemy.h"
#include "QTimer"
#include "QObject"

class HorrorDisk: public Enemy{

Q_OBJECT

public:

    explicit HorrorDisk(QTimer* timer, QObject* parent);

public slots:
    void emitEnemyProjectileIsLaunchedSignal();
    void move() override;
    void startBursting();
    void stopBursting();

private:

    int rotationDegree;
    int randDirOfX;
    int randDirOfY;
    bool isArriving;

    QTimer* attackTimer;

};

#endif // HORRORDISK_H
