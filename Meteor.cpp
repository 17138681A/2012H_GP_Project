#include "Meteor.h"

Meteor::Meteor(QTimer* timer, QObject* parent):Enemy(timer, parent){

    randMeteor = rand()%4;

    randHor = randHor = 50 + rand()%900;
    rotationDegree = 0;
    health = 100;
    dropRate = -1;

    if(randMeteor == 0)
        pix = QPixmap(":/image/meteorBrown_big1.png");

    else if(randMeteor == 1)
        pix = QPixmap(":/image/meteorBrown_big2.png");

    else if(randMeteor == 2)
        pix = QPixmap(":/image/meteorBrown_big3.png");

    else if(randMeteor == 3)
        pix = QPixmap(":/image/meteorBrown_big4.png");

    setPixmap(pix);
    setStep(1);
    setPos(randHor, 0);
    setScale(1);
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);



}

void Meteor::move(){

    setRotation(++rotationDegree);
    //set before delete
    setY(y()+step);


    if(y() - pixmap().height()*scale() >= 960)
        delete this;



}
