#include "HorrorDisk.h"
#include "QThread"


HorrorDisk::HorrorDisk(QTimer* timer, QObject* parent):Enemy(timer, parent){


    randDirOfX = -1 + 2*(rand()%2);
    randDirOfY = -1 + 2*(rand()%2);
    health = 2400;
    dropRate = 21;
    rotationDegree = 0;
    attackCounter = 0;
    numOfBurst = 1;
    isArriving = true;
    isRaging = false;

    pix = QPixmap(":/image/ufoBlue.png");

    setPixmap(pix);
    setStep(1);
    setPos(640-pixmap().width()*scale()/2, 0);
    setScale(1.5);
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);

}

void HorrorDisk::emitEnemyProjectileIsLaunchedSignal()
{
//    cout << "projectile is launched" << endl;




        attackCounter++;

        if(attackCounter%numOfBurst == 0){
            disconnect(burstTimer, SIGNAL(timeout()), this, SLOT(emitEnemyProjectileIsLaunchedSignal()));
            QTimer::singleShot(2000, this, SLOT(startBursting()));
        }

        for(double j = 0; j < 360; j+=22.5)
            emit enemyProjectileIsLaunched(j, x()+pixmap().width()/2, y()+pixmap().height()/2);






}

void HorrorDisk::startBursting(){


    connect(burstTimer, SIGNAL(timeout()), this, SLOT(emitEnemyProjectileIsLaunchedSignal()));

}

//void HorrorDisk::stopShooting(){

//    QTimer::singleShot(2000, this, SLOT(startBursting()));
//    disconnect(attackTimer, SIGNAL(timeout()), this, SLOT(emitEnemyProjectileIsLaunchedSignal()));


//}

void HorrorDisk::move(){

    setRotation(++rotationDegree);

    if(isArriving){

        setY(y()+step);

        if(y() >= 400){

            isArriving = false;

            burstTimer = new QTimer(this);
            burstTimer->start(200);
            connect(burstTimer, SIGNAL(timeout()), this, SLOT(emitEnemyProjectileIsLaunchedSignal()));

//            attackTimer = new QTimer(this);
//            attackTimer->start(2000);
//            connect(attackTimer, SIGNAL(timeout()), this, SLOT(emitEnemyProjectileIsLaunchedSignal()));

//            emitEnemyProjectileIsLaunchedSignal();

            setStep(2);

        }

    }else {

        if(health < 800 && !isRaging){

            isRaging = true;

            numOfBurst++;
            setStep(3);

            pix = QPixmap(":/image/ufoRed.png");
            setPixmap(pix);
        }

        if(y() <= 0)
            randDirOfY = 1;

        if(x() <= 0)
            randDirOfX = 1;

        if(y() >= 960 - pixmap().height()*scale())
            randDirOfY = -1;

        if(x() >= 1280 - pixmap().width()*scale())
            randDirOfX = -1;

        setPos(x()+step*randDirOfX, y()+step*randDirOfY);

    }

}
