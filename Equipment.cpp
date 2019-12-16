#include "Equiment.h"
#include "Jet.h"

Equipment::Equipment(EquipmentName equipment, double x, double y, QTimer* timer):Movable(timer)
{

    name = equipment; //To indicate the current equipment

    randDirOfX = -1 + 2*(rand()%2); //Randomize initial horizontal direction of movement for each equipment
    randDirOfY = -1 + 2*(rand()%2); //Randomize initial vertical direction of movement for each equipment

    //Set proper image for the current equipment
    if(name == SPRAY_PACK)
        pix = QPixmap(":/image/sprayPack.png");

    else if(name == ULTRA_SPRAY_PACK)
        pix = QPixmap(":/image/ultraSprayPack.png");

    else if(name == HEALTH_PACK)
        pix = QPixmap(":/image/healthPack.png");

    else if(name == FRENZY_PACK)
        pix = QPixmap(":/image/frenzyPack.png");

    else if(name == FRENZY_STAR)
        pix = QPixmap(":/image/frenzyStar.png");

    setPixmap(pix);
    setStep(1); //Set movement speed
    setPos(x,y);

    if(name == FRENZY_STAR) //Set larger scale for smaller original image source
        setScale(2);
    else
        setScale(0.1);

}

void Equipment::move()
{

    //Apply current equipment's effect on jet if this equipment is collected by the player
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i){

        Jet* jet = dynamic_cast<Jet*>(colliding_items[i]); //Check if the colliding object is jet

              if(jet != nullptr){

                emit equipped(name); //Informing the game to apply effect on jet
                delete this; //Delete this equipment after colliding with jet
                return;

            }
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
