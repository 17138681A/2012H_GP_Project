#include "HorrorDisk.h"
#include "QThread"


HorrorDisk::HorrorDisk(QTimer* timer):Enemy(timer){


    randDirOfX = -1 + 2*(rand()%2); //Randomize initial horizontal direction of movement after finishing the arrival
    randDirOfY = -1 + 2*(rand()%2); //Randomize initial vertical direction of movement after finishing the arrival

    health = 2400; //Set health
    dropRate = 20; //100% chance to spawn an ultra spray pack
    rotationDegree = 0; //To rotate the iamge of this object

    shotCounter = 0; //To count how many shot was made in each wave of attack
    maxNumOfShot = 1; //To indicate how many shot should made in each wave of attack

    isArriving = true; //Entering the game
    rage = false; //Special attack and behavior after getting rage

    pix = QPixmap(":/image/ufoBlue.png");
    setPixmap(pix);

    setStep(1); //Set movement speed
    setPos(640-pixmap().width()/2, 0-pixmap().height());
    setScale(1.5);
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2); //Set rotation point to center

}

void HorrorDisk::emitSpawnEnemyProjectileSignal()
{

        //Shoot 16 projectiles in all direction
        for(double j = 0; j < 360; j+=22.5)
            emit spawnEnemyProjectileSignal(j, x()+pixmap().width()*scale()/2, y()+pixmap().height()*scale()/2);

        shotCounter++;

        //Shoot 1 time when maxNumOfShot == 1, shoot 2 times when maxNumOfShot == 2
        if(shotCounter%maxNumOfShot == 0){

            disconnect(fireRateTimer, SIGNAL(timeout()), this, SLOT(emitSpawnEnemyProjectileSignal())); //Stop shooting
            QTimer::singleShot(2000, this, SLOT(startShooting())); //2 seconds delay between each attack wave

        }
}

void HorrorDisk::startShooting(){

    connect(fireRateTimer, SIGNAL(timeout()), this, SLOT(emitSpawnEnemyProjectileSignal()));

}

void HorrorDisk::move(){

    setRotation(++rotationDegree); //Rotation speed is 1 degree per refreshTimer's interval

    if(isArriving){

        setY(y()+step); //Entering the game

        if(y() >= 400){ //Entering combat mode after reaching a certain postion

            isArriving = false;

            fireRateTimer = new QTimer(this);
            fireRateTimer->start(100);
            connect(fireRateTimer, SIGNAL(timeout()), this, SLOT(emitSpawnEnemyProjectileSignal()));

            setStep(2); //Move faster during combat mode

        }

    }else {

        if(health < 800 && !rage){

            rage = true;

            maxNumOfShot++; //Make 2 shot in each attack wave after getting rage
            setStep(3); //Move faster after getting rage

            pix = QPixmap(":/image/ufoRed.png");
            setPixmap(pix);
        }

        //Bounce back upon reaching the border of the window
        if(y() <= 0)
            randDirOfY = 1;

        if(x() <= 0)
            randDirOfX = 1;

        if(y() >= 960 - pixmap().height()*scale())
            randDirOfY = -1;

        if(x() >= 1280 - pixmap().width()*scale())
            randDirOfX = -1;

        //Always moving with 45 degree inclination
        setPos(x()+step*randDirOfX, y()+step*randDirOfY);

    }

}
