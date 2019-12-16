#include "HealthBar.h"
#include "iostream"
using namespace std;

HealthBar::HealthBar(){


    pix = QPixmap(":/image/hp07.png");
    setPixmap(pix);

    setScale(0.18);
    setPos(40, 820);

}

//Update the status of player's current health
void HealthBar::setHealth(int hp){

    //Each image indicates each status of player's current health
    if(hp <= 25)
        pix = QPixmap(":/image/hp01.png");

    else if(hp <= 50)
        pix = QPixmap(":/image/hp02.png");

    else if(hp <= 100)
        pix = QPixmap(":/image/hp03.png");

    else if(hp <= 150)
        pix = QPixmap(":/image/hp04.png");

    else if(hp <= 200)
        pix = QPixmap(":/image/hp05.png");

    else if(hp <= 250)
        pix = QPixmap(":/image/hp06.png");

    else if(hp <= 300)
        pix = QPixmap(":/image/hp07.png");

    setPixmap(pix);

    if(hp <= 0)
        delete this;

}
