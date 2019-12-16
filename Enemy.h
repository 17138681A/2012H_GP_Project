//Day 3
#ifndef ENEMY_H
#define ENEMY_H
#include "MovableObj.h"
#include "stdlib.h"
#include "QTimer"
#include "QTimer"
#include "QtMath"

class Enemy: public Movable, public QGraphicsPixmapItem{

    Q_OBJECT

public:

    Enemy(QTimer* timer);

    int getHealth(); //Get current health point

    virtual void deductHealth(int hp); //Deduct certain health point

protected:

    int health;
    double dropRate; //The possibility of droppping an equipment after getting detroyed

    QPixmap pix;

signals:

    void spawnEquipmentSignal(double x, double y, double dropRate); //Informing the game to spawn equipment
    void spawnEnemyProjectileSignal(double degree, double x, double y); //Informing the game to spawn enemy projectile


};


#endif // ENEMY_H
