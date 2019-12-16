#include "MotherDisk.h"

MotherDisk::MotherDisk(QTimer* timer):Enemy(timer){

    health = 5000;      //Set health
    dropRate = 999;     //Drop victory item upon getting destroyed
    rotationDegree = 0; //To rotate the image of this object
    attackCounter = 0;  //To count the number of emitted SpawnEnemyProjectileSignal in each attack phase
    phaseCounter = 0;   //To count the ordinal number of attack phase
    phaseDelay = 2000;  //Delay in ms between each attack phase
    isArriving = true;  //Entering the game
    rage = false;       //Special attack and behavior after getting rage

    //To determine the shooting pattern in each attack phase
    phase1Angle = 0;
    phase1MaxAngle = 180;
    phase1ShiftAngle = 30;

    phase2Angle = 100;
    phase2MaxAngle = -100;
    phase2ShiftAngle = -10;

    phase3Angle = 90;
    phase3MaxAngle = 450;
    phase3ShiftAngle = 5;

    pix = QPixmap(":/image/ufoYellow.png");
    setPixmap(pix);

    setStep(0.5); //Set movement speed
    setScale(3);
    setPos(640-pixmap().width()/2, 0-pixmap().height()*scale());

    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);

}

void MotherDisk::deductHealth(int hp)
{
    if(isArriving)

        health -= hp/2; //Consume less damage when entering the game

    else if(health > 0){

        health -= hp;

        if(health <= 0){

            fireRateTimer->stop(); //Stop attacking after defeated

            QTimer::singleShot(3000, this, SLOT(emitSpawnEquipmentSignal())); //Spawn victory item 3 seconds after defeated

        }
    }



}


//Drop equipment upon getting destroyed
void MotherDisk::emitSpawnEquipmentSignal()
{

    emit spawnEquipmentSignal(x(), y(), dropRate);
    delete this;

}

void MotherDisk::emitSpawnEnemyProjectileSignal()
{

    if(attackPhase == Phase1){

        //Shoot 9 projectiles in all direction
        for(double j = phase1Angle; j < phase1Angle+360; j+=40)
            emit spawnEnemyProjectileSignal(j, x()+pixmap().width()/2, y()+pixmap().height()/2);

        //End this phase after spreading the projectiles in a desired range
        if(phase1Angle == phase1MaxAngle){

            stopPhase();
            phase1Angle = 0; //Reset shooting angle for next of this phase

            //Burst the projectiles from the opposite direction in next of this phase
            phase1ShiftAngle *= -1;
            phase1MaxAngle *= -1;

            return;

        }

        phase1Angle += phase1ShiftAngle;

    }else if(attackPhase == Phase2){

            //Shoot 1 projectile in 1 direction
            emit spawnEnemyProjectileSignal(phase2Angle, x()+pixmap().width()/2, y()+pixmap().height()/2);

            //End this phase after spreading the projectiles in a desired range
            if(phase2Angle == phase2MaxAngle){

                stopPhase();

                //Burst the projectiles from the opposite direction in next of this phase
                phase2ShiftAngle *= -1;
                phase2MaxAngle *= -1;
                return;

            }

            phase2Angle += phase2ShiftAngle;

        }else if(attackPhase == Phase3){


                //Shoot 2 projectiles in the opposite direction simultaneously
                for(int i = 0; i < 2; ++i)
                    emit spawnEnemyProjectileSignal(phase3Angle+i*180, x()+pixmap().width()/2, y()+pixmap().height()/2);

                //End this phase after spreading the projectiles in a desired range
                if(phase3Angle == phase3MaxAngle){

                    stopPhase();

                    //Burst the projectiles from the opposite direction in next of this phase
                    phase3ShiftAngle *= -1;
                    phase3MaxAngle *= -1;
                    phase3Angle = phase3MaxAngle/5;
                    return;

                }

                phase3Angle += phase3ShiftAngle;
            }

}

//Stop current attack phase and prepare for the next attack phase
void MotherDisk::stopPhase(){

    disconnect(fireRateTimer, SIGNAL(timeout()), this, SLOT(emitSpawnEnemyProjectileSignal()));
    QTimer::singleShot(phaseDelay, this, SLOT(startNewPhase()));

}

//Start new attack phase
void MotherDisk::startNewPhase(){

    phaseCounter++;

    if(phaseCounter%5 == 0){ //Make Phase3 attack in every 5 attack phases(override Phase2 and Phase1)

        attackPhase = Phase3;
        fireRateTimer->setInterval(50);

    }else if(phaseCounter%3 == 0){ //Make Phase2 attack in about every 3 attack phases(override Phase1)

        attackPhase = Phase2;
        fireRateTimer->setInterval(50);

    }else{ //Make Phase1 attack

        attackPhase = Phase1;
        fireRateTimer->setInterval(200);
    }

    connect(fireRateTimer, SIGNAL(timeout()), this, SLOT(emitSpawnEnemyProjectileSignal()));

}

void MotherDisk::move(){

    setRotation(++rotationDegree); //Rotation speed is 1 degree per refresh interval

    if(health <= 1500 && !rage){

        rage = true;

        phaseDelay = 1500; //Shorter delay between attack phase when getting rage
        phase1MaxAngle *= 1.5; //Range of Phase1 attack become larger when getting rage

        pix = QPixmap(":/image/ufoRed.png");
        setPixmap(pix);

    }

    //Trembling upon defeated
    if(health <= 0){

        int randDirOfX = -2 + 4*(rand()%2);
        int randDirOfY = -2 + 4*(rand()%2);

        setPos(x() + randDirOfX, y() + randDirOfY);

    }


    if(isArriving){

        setY(y()+step); //Entering the game

        if(y() >= 250){ //Entering combat mode after reaching a certain postion

            isArriving = false;

            fireRateTimer = new QTimer(this);
            fireRateTimer->start(50);
            QTimer::singleShot(1000, this, SLOT(startNewPhase())); //Start first phase of attack

            setStep(0); //Stay still in combat mode

        }
    }
}
