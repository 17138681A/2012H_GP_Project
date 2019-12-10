#include "HorrorDisk.h"
#include "QThread"


HorrorDisk::HorrorDisk(QTimer* timer, QObject* parent):Enemy(timer, parent){

    randHor = 640;
    randDirOfX = -1 + 2*(rand()%2);
    randDirOfY = -1 + 2*(rand()%2);
    health = 1000;
    dropRate = 20;
    rotationDegree = 0;
    isArriving = true;

    pix = QPixmap(":/image/ufoBlue.png");

    setPixmap(pix);
    setStep(2);
    setPos(randHor, 0);
    setScale(1.5);
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);





}

void HorrorDisk::emitEnemyProjectileIsLaunchedSignal()
{
//    cout << "projectile is launched" << endl;


        for(double j = 0; j < 360; j+=22.5)
            emit enemyProjectileIsLaunched(j, x()+pixmap().width()/4, y());

}

void HorrorDisk::startBursting(){

    attackTimer->start(500);
    QTimer::singleShot(500, this, SLOT(stopBursting()));
}

void HorrorDisk::stopBursting(){

    attackTimer->stop();
    QTimer::singleShot(2000, this, SLOT(startBursting()));

}

void HorrorDisk::move(){

    setRotation(++rotationDegree);

    if(isArriving){

        setY(y()+step);

        if(y() >= 400){
            isArriving = false;

            attackTimer = new QTimer(this);
            connect(attackTimer, SIGNAL(timeout()), this, SLOT(emitEnemyProjectileIsLaunchedSignal()));
            startBursting();

        }
    }else {

        setStep(2);

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
