#include "Spider.h"

Spider::Spider(QTimer* timer, QObject* parent):Enemy(timer, parent){



    randHor = 100 + rand()%1080;
    randVer = 50 + rand()%300;
    health = 50;
    dropRate = 0.05;// 21% item droprate

    pix = QPixmap(":/image/enemyBlack1.png");

    setPixmap(pix);
    setStep(2);
    setPos(randHor, 0);
    setScale(0.5);



}


void Spider::emitEnemyProjectileIsLaunchedSignal()
{
//    cout << "projectile is launched" << endl;
    int randNum = rand()%200;

    if(randNum == 1)
        emit enemyProjectileIsLaunched(0, x()+pixmap().width()*scale()/2, y());

}



void Spider::move(){

    if(y()>=randVer){

//        disconnect(refreshRate, SIGNAL(timeout()), this, SLOT(move()));
////        refreshRate = new QTimer(this);
////        refreshRate->start(2000);
//        connect(refreshRate, SIGNAL(timeout()), this, SLOT(emitEnemyProjectileIsLaunchedSignal()));

        emitEnemyProjectileIsLaunchedSignal();

    }else


        setPos(x(), y()+step);

}
