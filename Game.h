#ifndef GAME_H
#define GAME_H

#include "Jet.h"
#include "PlayerProjectile.h"
#include "Guide.h"

#include "FrenzyPackDisplayBar.h"
#include "HealthBar.h"
#include "ResultBoard.h"
#include "Equiment.h"
#include "Meteor.h"
#include "Satellite.h"
#include "Mosquito.h"
#include "Beetle.h"
#include "HorrorDisk.h"
#include "MotherDisk.h"
#include "EnemyProjectile.h"
#include "enumList.h"
#include <QMainWindow>
#include "QDebug"
#include "QTime"
#include "QKeyEvent"
#include "QGraphicsView"
#include "iostream"
#include "QtMath"
#include "QList"
#include "QRandomGenerator"
#include "random"
#include "iostream"

using namespace std;

class Game: public QGraphicsView{


public:

    Game(QObject* parent);

signals:

    void restartSignal();

public slots:

    void checkJetPosition();
    void setCombatEnvironment();

    void spawnEnemyWave();
    void spawnHorrorDisk();
    void spawnMotherDisk();

    void drawEquipment(double x, double y, double dropRate);
    void applyEquipmentEffect(EquipmentName);/// Day 5

    void fire();
    void spawnEnemyPeojectile(double degree, double x, double y);

    void stopSprayEffect(); //Pop 1 spray effect from the stack
    void stopFrenzyEffect(); //Turn off frenzy mode after frenzy effect is running out

    void screenEventHandler(); //Managing the display bar and the status of jet

private:

    Q_OBJECT

    const int maxNumOfFrenzyPack = 3;
    const int maxHealthOfJet = 300;

    //Pointers to all objects that need to add to the graphic view
    QGraphicsScene* scene;
    Jet* jet;
    PlayerProjectile* projectile;
    Guide* guide;
    Equipment* equipment;
    Enemy* enemy;
    EnemyProjectile* enemyProjectile;
    FrenzyPackDisplayBar* frenzyPackDisplayBar;
    HealthBar* healthBar;
    ResultBoard* resultBoard;

    //Timers  for handling the game events
    QTimer* refreshTimer;
    QTimer* frenzyTimer;
    QTimer* enemySpawningTimer;
    QTimer* openingTimer;

    mt19937 rng;//Random number generator

    ProjectileType weapon;

    int numOfFrenzyPack;
    int sprayEffectStack;
    int numOfDestroyedMosquito;
    int numOfDestroyedBeetle;
    int numOfSpawnedMosquito;
    int numOfSpawnedBeetle;

    bool goingUp;
    bool goingDown;
    bool goingLeft;
    bool goingRight;
    bool firing;
    bool frenzyMode;
    bool gameOver;
    bool bossFight;
    bool miniBossFight;

    void createOpening();
    void pause(); //Freeze the program by stopping the timers
    void gameIsOver(Result result); //Stopping the game and allowing player to restart

    void spawnPlayerProjectile(double degree); //Spawn player projectile at the current position of jet
    void spawnEquipment(EquipmentName name, double x, double y);
    void spawnMosquito();
    void spawnBeetle();
    void spawnMeteor();
    void spawnSatellite();

    void fireDefaultBeam();
    void fireSprayBeam();
    void fireUltraSprayBeam(); //Special player's attack that fan out 5 projectiles

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

};

#endif // GAME_H
