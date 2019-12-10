#include "Enemy.h"
#include "Jet.h"

Enemy::Enemy(QTimer* timer, QObject* parent){


    refreshRate = timer;
    connect(refreshRate, SIGNAL(timeout()), this, SLOT(move()));
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


//void Enemy::move(){

////    if(y()>=randVer){
////        disconnect(refreshRate, SIGNAL(timeout()), this, SLOT(move()));
//////        refreshRate = new QTimer(this);
//////        refreshRate->start(3000);
//////        connect(refreshRate, SIGNAL(timeout()), this, SLOT(emitFireSignal()));
////    }else

////    setPos(x(), y()+step);

//}

//void Enemy::emitFireSignal(){

//    emit fireSignal();
//}
