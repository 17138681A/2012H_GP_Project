#ifndef MOTHERDISK_H
#define MOTHERDISK_H
#include "Enemy.h"

class MotherDisk: public Enemy{

    Q_OBJECT

public:

    MotherDisk(QTimer* timer, QObject* parent);
    void deductHealth(int hp) override;

public slots:

    void emitEnemyProjectileIsLaunchedSignal();
    void emitSpawnEquipmentSignal();
    void startNewPhase();

    void move() override;



private:

    enum AttackPhase{

        Phase1,
        Phase2,
        Phase3
    };

    int rotationDegree;
    int attackCounter;
    int phaseCounter;

    bool isArriving;
    bool isRaging;

    double phase1ShiftAngle;

    double phase2Angle;
    double phase2MaxAngle;
    double phase2ShiftAngle;

    double phase3Angle;
    double phase3MaxAngle;
    double phase3ShiftAngle;



    AttackPhase attackPhase;

    QTimer* fireRateTimer;

    void stopPhase();
};

#endif // MOTHERDISK_H
