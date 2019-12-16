#include "Meteor.h"

Meteor::Meteor(QTimer* timer):Enemy(timer){

    randShape = rand()%4;
    randHor = 50 + rand()%900;

    rotationDegree = 0; //To rotate the image of this object
    rotationDir = -1 + 2*(rand()%2); //Rotate in either clockwise or anti-clockwise
    health = 60; //Set health
    dropRate = 0; //0% chance to spawn an equipment after getting destroyed

    if(randShape == 0)
        pix = QPixmap(":/image/meteorBrown_big1.png");

    else if(randShape == 1)
        pix = QPixmap(":/image/meteorBrown_big2.png");

    else if(randShape == 2)
        pix = QPixmap(":/image/meteorBrown_big3.png");

    else if(randShape == 3)
        pix = QPixmap(":/image/meteorBrown_big4.png");

    setPixmap(pix);
    setStep(1); //Set movement speed
    setPos(randHor, 0-pixmap().height());
    setScale(1);
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2); //Set rotation point to center

}

void Meteor::move(){

    setRotation(rotationDegree+=rotationDir); //Rotation speed is 1 degree per refreshTimer's interval

    setY(y()+step); //Moving forward


    if(y() - pixmap().height()*scale() >= 960) //Delete this object when going out of scene
        delete this;



}
