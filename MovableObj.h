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

    int getStep() const;
    void setStep(int s);
    virtual ~Movable() {}


//    double getX() const;
//    double getY() const;
//    int getHeight() const;
//    int getWidth() const;


//    void setptX(double x);
//    void setptY(double y);
//    void setHeight(int h);
//    void setWidth(int w);



protected:

    int step;//Movement speed

//    double ptX;
//    double ptY;
//    int objHeight;
//    int objWidth;


public slots:
    virtual void move() = 0;






//    virtual void move(Direction) = 0;
};
#endif // MOVABLEOBJ_H
