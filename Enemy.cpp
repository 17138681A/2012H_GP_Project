#include "Enemy.h"
#include "Jet.h"

Enemy::Enemy(QTimer* timer, QObject* parent){


    refreshTimer = timer;
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(move()));
    setZValue(1);


}

int Enemy::getHealth(){

    return health;

}


void Enemy::deductHealth(int hp){

    health -= hp;
    if(health <= 0){
        emit spawnEquipmentSignal(x(), y(), dropRate);
        delete this;
    }

}

