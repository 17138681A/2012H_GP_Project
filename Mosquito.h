//Day 4
#ifndef MOSQUITO_H
#define MOSQUITO_H
#include "Enemy.h"

class Mosquito: public Enemy{

    Q_OBJECT

public:

    Mosquito(QTimer* timer, QObject* parent);


public slots:
    void emitSpawnEnemyProjectileSignal();
    void move() override;

private:
    int randVer; //Spawn randomly whitin the vertical range
    int randHor; //To indicate how far it would go after spawning

};

#endif // MOSQUITO_H
