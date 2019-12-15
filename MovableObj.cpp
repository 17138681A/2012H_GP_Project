#include "MovableObj.h"

//Set movement speed(distance per frame)
void Movable::setStep(double s){

    step = s;

}

//Get movement speed(distance per frame)
double Movable::getStep()const{

    return step;

}

