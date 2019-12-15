#include "Mosquito.h"

Mosquito::Mosquito(QTimer* timer, QObject* parent):Enemy(timer, parent){


    health = 60;     //Set health
    dropRate = 0.05; //5% item droprate

    randHor = 100 + rand()%1080; //Spawn randomly whitin the horizontal range of [100, 1080)
    randVer = 50 + rand()%300;   //To indicate how far it would go after spawning

    pix = QPixmap(":/image/enemyBlack1.png"); //Set object's image
    setPixmap(pix);

    setStep(2);    //Set movement speed
    setScale(0.6);

    setPos(randHor, 0-pixmap().height());


}


void Mosquito::emitSpawnEnemyProjectileSignal()
{

    //Sporadically fire projectile
    int randNum = rand()%250;

    if(randNum == 1)
        emit spawnEnemyProjectileSignal(0, x()+pixmap().width()*scale()/2, y()+pixmap().height()*scale());

}



void Mosquito::move(){

    if(y()>=randVer){

        emitSpawnEnemyProjectileSignal(); //Sporadically fire projectile after reaching a certain postion

    }else

        setPos(x(), y()+step); //Moving forward until reaching a certain position

}
