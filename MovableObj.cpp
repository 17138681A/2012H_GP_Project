#include "MovableObj.h"

//Connect the game's refreshTimer to the move() function so to achieve consistent refresh rate among the children
Movable::Movable(QTimer* timer){

    refreshTimer = timer;
    connect(refreshTimer,SIGNAL(timeout()), this, SLOT(move())); //Update object's status and position

}


//Set movement speed(distance per frame)
void Movable::setStep(double s){

    step = s;

}


//Get movement speed(distance per frame)
double Movable::getStep()const{

    return step;

}

