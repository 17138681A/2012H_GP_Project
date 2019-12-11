#include "MotherDisk.h"

MotherDisk::MotherDisk(QTimer* timer, QObject* parent):Enemy(timer, parent){

    health = 5000;
    dropRate = 999;
    rotationDegree = 0;
    attackCounter = 0;
    phaseCounter = 0;
    isArriving = true;
    isRaging = false;

    phase1ShiftAngle = 0;

    phase2Angle = 100;
    phase2MaxAngle = -100;
    phase2ShiftAngle = -10;

    phase3Angle = 90;
    phase3MaxAngle = 450;
    phase3ShiftAngle = 5;



    attackPhase = Phase2;

    pix = QPixmap(":/image/ufoYellow.png");

    setPixmap(pix);
    setStep(0.5);
    setScale(3);
    setPos(640-pixmap().width()/2, 0-pixmap().height()*scale());
    cout << pixmap().height()/2 << endl;
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);

}

void MotherDisk::deductHealth(int hp)
{
    health -= hp;
    if(health <= 0){

        QTimer::singleShot(3000, this, SLOT(emitSpawnEquipmentSignal()));

    }

}



void MotherDisk::emitSpawnEquipmentSignal()
{

    emit spawnEquipmentSignal(x(), y(), dropRate);
    delete this;

}

void MotherDisk::emitEnemyProjectileIsLaunchedSignal()
{

    if(attackPhase == Phase1){



        for(double j = phase1ShiftAngle; j < phase1ShiftAngle+360; j+=45)
            emit enemyProjectileIsLaunched(j, x()+pixmap().width()/2, y()+pixmap().height()/2);

        if(phase1ShiftAngle == 90){
            stopPhase();
            phase1ShiftAngle = 0;
            return;
        }

        phase1ShiftAngle += 22.5;

    }else if(attackPhase == Phase2){

            emit enemyProjectileIsLaunched(phase2Angle, x()+pixmap().width()/2, y()+pixmap().height()/2);

            if((int)(phase2Angle) == (int)phase2MaxAngle){

                stopPhase();
                phase2ShiftAngle *= -1;
                phase2MaxAngle *= -1;
                return;

            }

            phase2Angle += phase2ShiftAngle;

        }else if(attackPhase == Phase3){

                cout << x()+pixmap().width()*scale()/2 << endl;

                for(int i = 0; i < 2; ++i)
                    emit enemyProjectileIsLaunched(phase3Angle+i*180, x()+pixmap().width()/2, y()+pixmap().height()/2);

                cout << phase3Angle << endl;
                if((int)(phase3Angle) == (int)phase3MaxAngle){

                    stopPhase();
                    phase3ShiftAngle *= -1;
                    phase3MaxAngle *= -1;
                    phase3Angle = phase3MaxAngle/5;
                    return;

                }

                phase3Angle += phase3ShiftAngle;
            }

}

void MotherDisk::stopPhase(){

    disconnect(fireRateTimer, SIGNAL(timeout()), this, SLOT(emitEnemyProjectileIsLaunchedSignal()));
    QTimer::singleShot(2000, this, SLOT(startNewPhase()));

}

void MotherDisk::startNewPhase(){

    phaseCounter++;

    if(phaseCounter%5 == 0){

        attackPhase = Phase3;
        fireRateTimer->setInterval(50);

    }else if(phaseCounter%3 == 0){

        attackPhase = Phase2;
        fireRateTimer->setInterval(50);

    }else{

        attackPhase = Phase1;
        fireRateTimer->setInterval(500);
    }



    connect(fireRateTimer, SIGNAL(timeout()), this, SLOT(emitEnemyProjectileIsLaunchedSignal()));



}

void MotherDisk::move(){

    setRotation(++rotationDegree);

    if(health <= 0){

        int randDirOfX = -2 + 4*(rand()%2);
        int randDirOfY = -2 + 4*(rand()%2);

        setPos(x() + randDirOfX, y() + randDirOfY);

    }


    if(isArriving){

        setY(y()+step);

        if(y() >= 250){

            isArriving = false;

            fireRateTimer = new QTimer(this);
            fireRateTimer->start(50);
            QTimer::singleShot(1000, this, SLOT(startNewPhase()));

//            attackTimer = new QTimer(this);
//            attackTimer->start(2000);
//            connect(attackTimer, SIGNAL(timeout()), this, SLOT(emitEnemyProjectileIsLaunchedSignal()));

//            emitEnemyProjectileIsLaunchedSignal();

            setStep(0);

        }
    }
}
