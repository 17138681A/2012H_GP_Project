#include "Jet.h"
#include "QList"
#include "Enemy.h"




Jet::Jet(double x, double y, QTimer* timer):Movable(timer){


    health = maxHealth; //Set full health
    isArriving = true; //Entering the game

    pix = QPixmap(":/image/playerShip1_red.png");
    setPixmap(pix);

    setStep(1); //Set movement speed
    setPos(x,y);
    setScale(1);
    setZValue(1); //To prevent blocking by the health bar and display bar

}

//Get current health point
int Jet::getHealth(){

    return health;
}

//Deduct certain health point
void Jet::deductHealth(int hp){

    health -= hp;

}

//Add certain health point
void Jet::heal(int hp)
{
    health += hp;

    if(health >= maxHealth)
        health = maxHealth;

}

//Jet is ready for combat
void Jet::arrived(){

    isArriving = false;

    setStep(5); //Default speed during combat

}

void Jet::move(){


    if(isArriving)

        setY(y()-step); //Move forward when player's control is not available

    else

        disconnect(refreshTimer,SIGNAL(timeout()), this, SLOT(move())); //Jet movement is controlled by the player now

}

