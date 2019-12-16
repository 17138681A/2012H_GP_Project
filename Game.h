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

#include "QMainWindow"
#include "QDebug"
#include "QTime"
#include "QKeyEvent"
#include "QGraphicsView"
#include "QtMath"
#include "QList"
#include "QRandomGenerator"
#include "random"
#include "iostream"

using namespace std;

class Game: public QGraphicsView{


public:

    Game();


signals:

    void restartSignal(); //Informing the main window to restart the game


public slots:

    void checkJetPosition(); //Check position of jet during the opening of the game
    void setCombatEnvironment(); //Set up event handler and display bar

    void spawnEnemyWave(); //Spawn enemy wave with specified time interval in enemySpawningTimer
    void spawnHorrorDisk(); //Mini boss
    void spawnMotherDisk(); //Final boss

    void drawEquipment(double x, double y, double dropRate); //Randomly draw 1 among 4 common equipments(frenzy star is excluded)
    void applyEquipmentEffect(EquipmentName); //Apply equipment effect to the jet

    void fire(); //Spawn player projectile according to current weapon type
    void spawnEnemyPeojectile(double degree, double x, double y); //Spawn enemy projectile at the current position of the enemy

    void stopSprayEffect(); //Pop 1 spray effect from the stack
    void stopFrenzyEffect(); //Turn off frenzy mode after frenzy effect is running out

    void screenEventHandler(); //Managing the display bar and the status of jet


private:

    Q_OBJECT

    const int maxNumOfFrenzyPack = 3;
    const int maxHealthOfJet = 300;

    //Pointers to all objects that will be added to the graphic view
    Jet* jet;
    Enemy* enemy;
    Guide* guide;
    Equipment* equipment;
    HealthBar* healthBar;
    QGraphicsScene* scene;
    ResultBoard* resultBoard;
    PlayerProjectile* projectile;
    EnemyProjectile* enemyProjectile;
    FrenzyPackDisplayBar* frenzyPackDisplayBar;



    //Timers  for handling the game events
    QTimer* frenzyTimer;
    QTimer* openingTimer;
    QTimer* refreshTimer;
    QTimer* enemySpawningTimer;


    mt19937 rng; //Random number generator

    ProjectileType weapon;

    int numOfFrenzyPack;
    int sprayEffectStack;
    int numOfSpawnedBeetle;
    int numOfSpawnedMosquito;
    int numOfDestroyedBeetle;
    int numOfDestroyedMosquito;

    //To assist 8 direction movement of jet
    bool goingUp;
    bool goingDown;
    bool goingLeft;
    bool goingRight;

    bool firing;
    bool frenzyMode;

    bool gameOver;
    bool bossFight;
    bool miniBossFight;


    void createOpening(); //Launch the opening scene of the game
    void pause(); //Freeze the program by stopping the timers
    void gameIsOver(Result result); //Stopping the game and allowing player to restart

    void spawnPlayerProjectile(double degree); //Spawn player projectile at the current position of jet
    void spawnEquipment(EquipmentName name, double x, double y); //Spawn equipment at the position where the enemy unit is detroyed
    void spawnMosquito();
    void spawnBeetle();
    void spawnMeteor();
    void spawnSatellite();

    void fireDefaultBeam(); //Default player's attack that fire single projectile
    void fireSprayBeam(); //Special player's attack that fan out 3 projectiles
    void fireUltraSprayBeam(); //Special player's attack that fan out 5 projectiles

    void keyPressEvent(QKeyEvent* event) override; //Handle key input
    void keyReleaseEvent(QKeyEvent *event) override; //The jet will stop moving in specific direction upon releasing the corresponding movement key

};

#endif // GAME_H
