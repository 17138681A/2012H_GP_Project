//Day 3
#ifndef ENEMY_H
#define ENEMY_H
#include "MovableObj.h"
#include "stdlib.h"
#include "QTimer"

class Enemy: public Movable, public QGraphicsPixmapItem{

    Q_OBJECT

public:

    Enemy(QTimer* timer, QObject* parent);
    int getHealth();
    virtual void deductHealth(int hp);

protected:


    int health;
    double dropRate;

    QPixmap pix;

signals:
    void spawnEquipmentSignal(double x, double y, double dropRate);
    void spawnEnemyProjectileSignal(double degree, double x, double y);



};


#endif // ENEMY_H
