#include "Beetle.h"

Beetle::Beetle(QTimer* timer, QObject* parent):Enemy(timer, parent){


    randHor = 100 + rand()%1080;
    randVer = 50 + rand()%300;

    health = 400;
    dropRate = 0.5; //5% item droprate

    isArriving = true;

    pix = QPixmap(":/image/enemyBlue4.png");

    setPixmap(pix);
    setStep(1.5);
    setPos(randHor, 0);
    setScale(1);



}


void Beetle::emitSpawnEnemyProjectileSignal()
{

    for(int i = 30; i >= -30; i -= 30)
        emit spawnEnemyProjectileSignal(i, x()+pixmap().width()/2, y()+pixmap().height());

}

void Beetle::startHovering(){


    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(move()));
    QTimer::singleShot(2000, this, SLOT(stopHovering()));

}

void Beetle::stopHovering(){

    emitSpawnEnemyProjectileSignal();
    randDir = -1 + 2*(rand()%2);

    disconnect(refreshTimer, SIGNAL(timeout()), this, SLOT(move()));
    QTimer::singleShot(1000, this, SLOT(startHovering()));
}



void Beetle::move(){

    if(isArriving){

        if(y()>=randVer){

            stopHovering();

            isArriving = false;

        }else setY(y()+step);

    }


    if(!isArriving){

        setX(x()+step*randDir);

        if(x() >= 1080 - pixmap().width()*scale())
            randDir = -1;

        if(x() <= 200)
            randDir = 1;

    }

}
