#ifndef BEETLE_H
#define BEETLE_H
#include "Enemy.h"

class Beetle: public Enemy{

    Q_OBJECT

public:

    Beetle(QTimer* timer, QObject* parent);

public slots:

    void emitSpawnEnemyProjectileSignal();
    void move() override;
    void startHovering();
    void stopHovering();

private:
    int randVer;
    int randHor;
    int randDir;
    bool isArriving;

    QTimer* hoverTimer;



};

#endif // BEETLE_H
