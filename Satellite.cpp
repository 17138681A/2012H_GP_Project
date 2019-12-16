#include "Satellite.h"

Satellite::Satellite(QTimer* timer):Enemy(timer){

    randVer = 50 + rand()%300; //Spawn randomly whitin the vertical range of [50, 300)
    randDir = -1 + 2*(rand()%2); //Satellite can either spawn from left or right
    health = 40; //Set health
    dropRate = 1; //100% chance to spawn an equipment after getting destroyed

    rotationDegree = 0; //To rotate the iamge of this object

    pix = QPixmap(":/image/Satellite.png");


    if(randDir == -1)
        setPos(1280, randVer); //Spawn from right when randDir == -1
    else
        setPos(0 - pixmap().width()*scale(), randVer); //Spawn from left when randDir == 1

    setPixmap(pix);
    setStep(3); //Set movement speed
    setScale(0.5);
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2); //Set rotation point to center

}

void Satellite::move(){


    rotationDegree += 3; //Rotation speed is 3 degree per refreshTimer's interval
    setRotation(rotationDegree);

    setX(x() + step*randDir); //Move to left when randDir == -1, Move to right when randDir == 1

    if(x() > 1280 || x() + pixmap().width()*scale() < 0) //Delete this to save memory when going out of the screen
        delete this;

}
