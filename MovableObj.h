///Day 1
#ifndef MOVABLEOBJ_H
#define MOVABLEOBJ_H


#include "QObject"
#include "QGraphicsPixmapItem"
#include "QTimer"
#include "QList"
#include "iostream"
using namespace std;

class Movable: public QObject{

Q_OBJECT

public:

    double getStep() const; //Get movement speed(distance per frame)
    void setStep(double s); //Set movement speed(distance per frame)

protected:

    double step; //Movement speed(distance per frame)

    QTimer* refreshTimer; //Object's status is updating in the same frequency with the game's refresh rate

public slots:

    virtual void move() = 0; //To be overrided so each child object has its distinct behaviour


};
#endif // MOVABLEOBJ_H
