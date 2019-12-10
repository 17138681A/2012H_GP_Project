//Day 3
#ifndef ENEMY_H
#define ENEMY_H
#include "MovableObj.h"
#include "stdlib.h"
#include "QTimer"

class Enemy: public Movable, public QGraphicsPixmapItem{

    Q_OBJECT

public:

    explicit Enemy(QTimer* timer, QObject* parent);
    int getHealth();
    virtual void deductHealth(int hp);

protected:

    int randVer;
    int randHor;
    int health;
    double dropRate;

//    int tilt;
//    int randMovePeriod;
//    double spawnFactor;

    QTimer* refreshRate;
    QPixmap pix;

signals:
    void spawnEquipmentSignal(double x, double y, double dropRate);
    void enemyProjectileIsLaunched(double degree, double x, double y);



//    void fireSignal();

//public slots:
//    void move() override;
//    void emitFireSignal();

};


#endif // ENEMY_H
