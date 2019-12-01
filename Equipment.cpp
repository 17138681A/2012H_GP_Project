//Day 4
#include "Equiment.h"
#include "Jet.h"

Equipment::Equipment(EquipmentName equipment, double x, double y, QTimer* timer, QObject* parent)
{

    randNum = rand()%4;
    name = equipment;
    refreshRate = timer;


    if(randNum == 0){
        xBounceDirection = 1;
        yBounceDirection = 1;

    }else if(randNum == 1){
        xBounceDirection = 1;
        yBounceDirection = -1;

    }else if(randNum == 2){
        xBounceDirection = -1;
        yBounceDirection = 1;

    }else if(randNum == 3){
        xBounceDirection = -1;
        yBounceDirection = -1;
    }


    if(name == STORMER_PACK)
        pix = QPixmap(":/image/flakker.png");

    else if(name == ULTRA_STORMER_PACK)
        pix = QPixmap(":/image/ultra_flakker.png");

    else if(name == HEALTH_PACK)
        pix = QPixmap(":/image/healthpack.png");

    else if(name == FRENZY_PACK)
        pix = QPixmap(":/image/frenzy.png");


    setPixmap(pix);
    setStep(1);
    setPos(x,y);
    setScale(0.1);


    connect(refreshRate, SIGNAL(timeout()), this, SLOT(move()));

}

void Equipment::move()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i){

        Jet* jet = dynamic_cast<Jet*>(colliding_items[i]);

              if(jet != nullptr){

                emit equipped(name);
                delete this;
                return;

            }
        }//Day 5


    if(y() <= 0)
        yBounceDirection = 1;

    if(x() <= 0)
        xBounceDirection = 1;

    if(y() >= 960 - pixmap().height()*scale())
        yBounceDirection = -1;

    if(x() >= 1280 - pixmap().width()*scale())
        xBounceDirection = -1;

    setPos(x()+step*xBounceDirection, y()+step*yBounceDirection);


}
