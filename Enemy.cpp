#include "Enemy.h"

Enemy::Enemy(QTimer* timer):Movable(timer){

    setZValue(1); //To prevent blocking by the health bar and display bar

}


//Get current health point
int Enemy::getHealth(){

    return health;

}


//Deduct certain health point
void Enemy::deductHealth(int hp){

    health -= hp;
    if(health <= 0){

        emit spawnEquipmentSignal(x(), y(), dropRate); //Spawn equipment after getting destroyed
        delete this;

    }

}

