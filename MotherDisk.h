#ifndef MOTHERDISK_H
#define MOTHERDISK_H
#include "Enemy.h"

class MotherDisk: public Enemy{

    Q_OBJECT

public:

    MotherDisk(QTimer* timer);

    void deductHealth(int hp) override;


public slots:

    void emitSpawnEnemyProjectileSignal(); //This enemy can shoot projectile
    void emitSpawnEquipmentSignal(); //Drop equipment upon getting destroyed
    void startNewPhase(); //Start new attack phase

    void move() override;


private:

    //3 phases of attack each with different style
    enum AttackPhase{
        Phase1,
        Phase2,
        Phase3
    };

    int rotationDegree; //To rotate the image of this object
    int attackCounter;  //To count the number of emitted SpawnEnemyProjectileSignal in each attack phase
    int phaseCounter;   //To count the ordinal number of attack phase
    int phaseDelay;     //Delay in ms between each attack phase

    bool isArriving; //Entering the game
    bool rage;       //Special attack and behavior after getting rage

    //To determine the shooting pattern in each attack phase
    double phase1Angle;
    double phase1MaxAngle;
    double phase1ShiftAngle;

    double phase2Angle;
    double phase2MaxAngle;
    double phase2ShiftAngle;

    double phase3Angle;
    double phase3MaxAngle;
    double phase3ShiftAngle;

    AttackPhase attackPhase;

    QTimer* fireRateTimer; //To detemine the fire rate in each attack phase

    void stopPhase(); //Stop current attack phase and prepare for the next attack phase

};

#endif // MOTHERDISK_H
