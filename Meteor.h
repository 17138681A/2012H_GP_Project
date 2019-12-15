#ifndef METEOR_H
#define METEOR_H
#include "Enemy.h"

class Meteor: public Enemy{

    Q_OBJECT

public:

    Meteor(QTimer* timer, QObject* parent);

public slots:

    void move() override;

private:

    int rotationDegree; //To rotate the image of this object
    int rotationDir; //Rotate in either clockwise or anti-clockwise
    int randShape; //Spawn with random shape
    int randHor; //Spawn randomly whitin the horizontal range

};

#endif // METEOR_H
