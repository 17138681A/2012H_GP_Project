#ifndef SATELLITE_H
#define SATELLITE_H
#include "Enemy.h"

class Satellite: public Enemy{

    Q_OBJECT

public:
    Satellite(QTimer* timer, QObject* parent);

public slots:
    void move() override;

private:
    int rotationDegree; //To rotate the image of this object
    int randDir; //Satellite can either spawn from left or right
    int randVer; //Spawn randomly whitin the vertical range

};

#endif // SATELLITE_H
