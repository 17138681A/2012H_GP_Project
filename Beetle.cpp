#include "Beetle.h"

Beetle::Beetle(QTimer* timer):Enemy(timer){


    randHor = 100 + rand()%1080; //Spawn randomly whitin the horizontal range of [100, 1080)
    randVer = 50 + rand()%300; //To indicate how far it would go after entering the game

    health = 300; //Set health
    dropRate = 0.5; //50% chance to spawn an equipment after getting destroyed

    isArriving = true;

    pix = QPixmap(":/image/enemyBlue4.png");
    setPixmap(pix);

    setStep(1.5); //Set movement speed
    setPos(randHor, 0);
    setScale(1);

}


void Beetle::emitSpawnEnemyProjectileSignal()
{

    //Fan out 3 projectiles infront of it
    for(int i = 30; i >= -30; i -= 30)
        emit spawnEnemyProjectileSignal(i, x()+pixmap().width()/2, y()+pixmap().height());

}


//Start moving in either left or right direction
void Beetle::startHovering(){


    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(move()));
    QTimer::singleShot(2000, this, SLOT(stopHovering()));

}


//Stop moving, fire projectiles and prepare for the next horvering
void Beetle::stopHovering(){

    disconnect(refreshTimer, SIGNAL(timeout()), this, SLOT(move()));

    emitSpawnEnemyProjectileSignal();

    randDir = -1 + 2*(rand()%2); //Decide the direction of next hovering

    QTimer::singleShot(1000, this, SLOT(startHovering())); //Start hovering again after staying 1 second
}



void Beetle::move(){

    if(isArriving){

        if(y()>=randVer){

            stopHovering(); //Prepare for hovering after reaching a certain position

            isArriving = false;

        }else setY(y()+step); //Moving forward until reaching a certain position

    }

    if(!isArriving){

        setX(x()+step*randDir); //Moving either left or right during the hovering

        //Hovering in restricted area
        if(x() >= 1080 - pixmap().width()*scale())
            randDir = -1;

        if(x() <= 200)
            randDir = 1;

    }

}
