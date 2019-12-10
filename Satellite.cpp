#include "Satellite.h"

Satellite::Satellite(QTimer* timer, QObject* parent):Enemy(timer, parent){

    randVer = 50 + rand()%300;
    randDir = -1 + 2*(rand()%2); //Satellite can either spawn from left or right
    health = 40;
    dropRate = 1;// 100% item droprate
    rotationDegree = 0;
    pix = QPixmap(":/image/spaceStation_022.png");

    if(randDir == -1)
        setPos(1280, randVer);
    else
        setPos(0 - pixmap().width()*scale(), randVer);

    setPixmap(pix);
    setStep(4);
    setScale(0.5);
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);

}

void Satellite::move(){


    rotationDegree += 3;
    setRotation(rotationDegree);

    setX(x() + step*randDir);

    if(x() > 1280 || x() + pixmap().width()*scale() < 0)
        delete this;

}
