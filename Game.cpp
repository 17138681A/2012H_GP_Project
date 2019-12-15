#include "Game.h"
#include "QGraphicsItem"



Game::Game(QObject* parent)
{
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setFocusPolicy(Qt::NoFocus);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1280, 960); //Fixed window size: 1280x960
    setScene(scene);

    refreshTimer = new QTimer(this);
    frenzyTimer = new QTimer(this);
    enemySpawningTimer = new QTimer(this);

    weapon = DEFAULT_BEAM;
    numOfFrenzyPack = 0;
    sprayEffectStack = 0;
    numOfDestroyedMosquito = 0;
    numOfSpawnedMosquito = 0;
    numOfSpawnedBeetle = 0;
    numOfDestroyedBeetle = 0;
    goingUp = false;
    goingDown = false;
    goingLeft = false;
    goingRight = false;
    firing = false;
    frenzyMode = false;
    gameOver = false;
    miniBossFight = false;
    bossFight = false;


    srand((unsigned)time(0)); //Set seed for random number

    random_device dev;
    mt19937 rng(dev()); //Using random number generator for a fair draw of equipment

    createOpening();


}

//Create the opening scene of the game
void Game::createOpening(){

    //Jet is entering the game and moving forward
    jet = new Jet(0, 0, refreshTimer, this);
    jet->setPos(640-jet->pixmap().width()*jet->scale()/2,960);
    scene->addItem(jet);

    //An image showing the control keys
    guide = new Guide(640, 300, this);
    scene->addItem(guide);

    refreshTimer->start(10); //Refresh the scene 100 times every 1 second
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(checkJetPosition())); //Check position of jet during the opening of the game

}


//Check position of jet during the opening of the game
void Game::checkJetPosition(){

    //Stop the opening when jet is reaching a certain postition
    if(jet->y() <= 600){

         disconnect(refreshTimer, SIGNAL(timeout()), this, SLOT(checkJetPosition()));

         jet->arrived();

         setCombatEnvironment();

    }
}


//Set up event handler and display bar
void Game::setCombatEnvironment()
{

    enemySpawningTimer->start(2000); //Spawn new wave of enemy every 2 seconds

    //Attach the timer to the corresponding event handler
    connect(frenzyTimer, SIGNAL(timeout()), this, SLOT(fire()));
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(screenEventHandler()));
    connect(enemySpawningTimer, SIGNAL(timeout()), this, SLOT(spawnEnemyWave()));
//    spawnMotherDisk();

    delete guide; //Remove guide at the opening

    //Set up display bar of possessing frenzy pack
    frenzyPackDisplayBar = new FrenzyPackDisplayBar(this);
    scene->addItem(frenzyPackDisplayBar);

    //Set up health bar
    healthBar = new HealthBar(this);
    scene->addItem(healthBar);

    setFocus(); //Start handling keyboard input from player

}

void Game::spawnEnemyWave(){

    //Player need to elminate 35 mosquitos in order to proceed to the mini boss fight
    if(numOfSpawnedMosquito < 35){

            spawnMosquito();
            ++numOfSpawnedMosquito;

        if(numOfSpawnedMosquito%7 == 0){

            spawnBeetle(); //Spawn 1 beetle every 7 mosquitos is spawned
            ++numOfSpawnedBeetle;

        }

    }else if(numOfDestroyedMosquito == numOfSpawnedMosquito && numOfDestroyedBeetle == numOfSpawnedBeetle && !miniBossFight){

                //Start mini boss(Horror disk) fight after first wave of enemy are eliminated
                QTimer::singleShot(2000, this, SLOT(spawnHorrorDisk()));
                miniBossFight = true;

            }

    uniform_int_distribution<std::mt19937::result_type> dist(1, 6); //Distribution in the range [1, 6]
    unsigned int randNum = dist(rng); //Generate a random number in the range [1, 6]

    if(randNum == 1) //16.667% chance to spawn a satellite in each wave
        spawnSatellite();

    if(!bossFight)
    for(int i = 0; i < rand()%3; ++i) //Randomly spawn 0 to 2 meteor in each wave
        spawnMeteor();

}


void Game::spawnMeteor(){

    enemy = new Meteor(refreshTimer, this);
    connect(enemy, SIGNAL(spawnEquipmentSignal(double, double, double)), this, SLOT(drawEquipment(double, double, double)));
    scene->addItem(enemy);

}


void Game::spawnSatellite(){

    enemy = new Satellite(refreshTimer, this);
    connect(enemy, SIGNAL(spawnEquipmentSignal(double, double, double)), this, SLOT(drawEquipment(double, double, double)));
    scene->addItem(enemy);

}


void Game::spawnMosquito(){

    enemy = new Mosquito(refreshTimer, this);
    connect(enemy, SIGNAL(spawnEquipmentSignal(double, double, double)), this, SLOT(drawEquipment(double, double, double)));
    connect(enemy, SIGNAL(spawnEnemyProjectileSignal(double, double, double)), this, SLOT(spawnEnemyPeojectile(double, double, double)));
    scene->addItem(enemy);

}


void Game::spawnBeetle(){

    enemy = new Beetle(refreshTimer, this);
    connect(enemy, SIGNAL(spawnEquipmentSignal(double, double, double)), this, SLOT(drawEquipment(double, double, double)));
    connect(enemy, SIGNAL(spawnEnemyProjectileSignal(double, double, double)), this, SLOT(spawnEnemyPeojectile(double, double, double)));
    scene->addItem(enemy);

}


void Game::spawnHorrorDisk(){

    enemy = new HorrorDisk(refreshTimer, this);
    connect(enemy, SIGNAL(spawnEquipmentSignal(double, double, double)), this, SLOT(drawEquipment(double, double, double)));
    connect(enemy, SIGNAL(spawnEnemyProjectileSignal(double, double, double)), this, SLOT(spawnEnemyPeojectile(double, double, double)));
    scene->addItem(enemy);

}


void Game::spawnMotherDisk(){

    enemy = new MotherDisk(refreshTimer, this);
    connect(enemy, SIGNAL(spawnEquipmentSignal(double, double, double)), this, SLOT(drawEquipment(double, double, double)));
    connect(enemy, SIGNAL(spawnEnemyProjectileSignal(double, double, double)), this, SLOT(spawnEnemyPeojectile(double, double, double)));
    scene->addItem(enemy);

}

//Spawn enemy projectile at the current position of the enemy
void Game::spawnEnemyPeojectile(double degree, double x, double y)
{

    enemyProjectile = new EnemyProjectile(degree, x, y, refreshTimer, this);
    scene->addItem(enemyProjectile);

}


//Randomly draw 1 among 5 equipments
void Game::drawEquipment(double x, double y, double dropRate){

    if(dropRate == 0) //Don't spawn equipment if the drop rate is zero
        return;

    if(dropRate == 0.05) //Mosquito is defeated
        ++numOfDestroyedMosquito;

    if(dropRate == 0.5) //Beetle is defeated
        ++numOfDestroyedBeetle;

    if(dropRate == 20){ //Horro disk is defeated

        QTimer::singleShot(4000, this, SLOT(spawnMotherDisk()));
        bossFight = true;

    }

    if(dropRate == 999){ //Mother disk is defeated

        spawnEquipment(FRENZY_STAR, x, y); //Spawn victory item
        return;

    }

    unsigned int upperBound = (unsigned int)(20/dropRate); //Find the upperbound of the distribution according to the drop rate


    uniform_int_distribution<std::mt19937::result_type> dist(1, upperBound); //Distribution in the range [1, upperBound]

    unsigned int randNum = dist(rng); //Generate a number in the range [1, upperBound]

    // Drop rate(scale with dropRate from each enemy):
    // Frenzy Pack - 45%
    // Health Pack - 25%
    // Spray Pack - 25%
    // Ultra Spray Pack - 5%
    if(randNum == 1){

        spawnEquipment(ULTRA_SPRAY_PACK, x, y);

    }else if(randNum <= 6){

        spawnEquipment(SPRAY_PACK, x, y);

    }else if(randNum <= 11){

        spawnEquipment(HEALTH_PACK, x ,y);

    }else if(randNum <= 20){

        spawnEquipment(FRENZY_PACK, x, y);

    }
}


//Spawn equipment at the position where the enemy unit is detroyed
void Game::spawnEquipment(EquipmentName name, double x, double y){

    equipment = new Equipment(name, x, y, refreshTimer, this);
    scene->addItem(equipment);
    connect(equipment, SIGNAL(equipped(EquipmentName)), this, SLOT(applyEquipmentEffect(EquipmentName)));

}

//Apply corresponding equipment effect to the jet
void Game::applyEquipmentEffect(EquipmentName name){

    //Use stack to control the spray effect so that the expiration of 1 effect won't affect the later one
    if(name == SPRAY_PACK){
        weapon = SPRAY_BEAM;
        ++sprayEffectStack; //Push 1 spray effect to the stack
        QTimer::singleShot(6000, this, SLOT(stopSprayEffect())); //The duration of spray effect is 6 seconds
    }

    else if(name == ULTRA_SPRAY_PACK){
        weapon = ULTRA_SPRAY_BEAM;
        ++sprayEffectStack; //Push 1 spray effect to the stack
        QTimer::singleShot(6000, this, SLOT(stopSprayEffect())); //The duration of spray effect is 6 seconds
    }

    else if(name == HEALTH_PACK && jet->getHealth() < maxHealthOfJet)
        jet->heal(100); //Heal 100 health point to jet

    else if(name == FRENZY_PACK && numOfFrenzyPack < maxNumOfFrenzyPack)
        ++numOfFrenzyPack; //Store 1 frenzy pack

    else if(name == FRENZY_STAR) //Victory item
        gameIsOver(VICTORY);

}


//Handle key input
void Game::keyPressEvent(QKeyEvent *event)
{
    //Restart the game when player pressing R only if the game is over
    if(event->key() == Qt::Key_R && gameOver){

        emit restartSignal();

    }else if(!gameOver){ //If game is not over yet

        if(event->key() == Qt::Key_J && !event->isAutoRepeat()){ //Prevent player to shoot automatically by simply holding the key

            if(frenzyMode) //Stop manual firing as frenzy mode == atutomatic firing mode
                return;
            else
                fire();
        }

        //The jet will keep moving in specific direction as long as the player is holding the corresponding movement key
        else if(event->key() == Qt::Key_W)
            goingUp = true;

        else if(event->key() == Qt::Key_S)
            goingDown = true;

        else if(event->key() == Qt::Key_A)
            goingLeft = true;

        else if(event->key() == Qt::Key_D)
            goingRight = true;

        //Use 1 frenzy pack upon pressing K only if there is frenzy pack in stock and the jet is not under frenzy mode
        else if(event->key() == Qt::Key_K && numOfFrenzyPack != 0 && !frenzyMode){

            frenzyMode = true; //Jet is going frenzy
            --numOfFrenzyPack; //Spend 1 frenzy pac
            frenzyTimer->start(100); //Frenzy mode == atutomatic firing mode(fire 10 projectiles per seconds)

            QTimer::singleShot(5000, this, SLOT(stopFrenzyEffect()));//The duration of frenzy effect is 5 seconds

        }
    }
}


//The jet will stop moving in specific direction upon releasing the corresponding movement key
void Game::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
        goingUp = false;

    else if(event->key() == Qt::Key_S)
        goingDown = false;

    else if(event->key() == Qt::Key_A)
        goingLeft = false;

    else if(event->key() == Qt::Key_D)
        goingRight = false;

}


//Spawn player projectile according to current weapon type
void Game::fire(){

    if(weapon == DEFAULT_BEAM){

        fireDefaultBeam();

    }else if(weapon == SPRAY_BEAM){

        fireSprayBeam();

    }else if(weapon == ULTRA_SPRAY_BEAM){

        fireUltraSprayBeam();

    }
}


//Default player's attack that fire single projectile
void Game::fireDefaultBeam(){

    spawnPlayerProjectile(0);

}

//Special player's attack that fan out 3 projectiles
void Game::fireSprayBeam(){

    for(int i = 0; i < 3; ++i)
        spawnPlayerProjectile(337.5+22.5*i);

}

//Special player's attack that fan out 5 projectiles
void Game::fireUltraSprayBeam(){

    for(int i = 0; i < 5; ++i)
        spawnPlayerProjectile((315+22.5*i));

}


//Spawn player projectile at the current position of jet
void Game::spawnPlayerProjectile(double degree){

    projectile = new PlayerProjectile(degree, jet->x()+(jet->pixmap().width())/2, jet->y(), refreshTimer, this);
    scene->addItem(projectile);

}


//Pop 1 spray effect from the stack
void Game::stopSprayEffect(){

    if(--sprayEffectStack == 0) //Switch back to default weapon when all spray effect are expired
        weapon = DEFAULT_BEAM;

}


//Turn off frenzy mode after frenzy effect is running out
void Game::stopFrenzyEffect(){

    frenzyTimer->stop();
    frenzyMode = false;

}


//Managing the display bar and the status of jet
void Game::screenEventHandler()
{

    //Jet will move to specific direction when the boolean value of that direction is true
    if(goingUp && jet->y()>=0){
        jet->setY(jet->y()-jet->getStep());

    }

    if(goingDown && jet->y()<=int(scene->height())-jet->pixmap().rect().height()*jet->scale()){
        jet->setY(jet->y()+jet->getStep());

    }
    if(goingLeft && jet->x()>=0){
        jet->setX(jet->x()-jet->getStep());

    }
    if(goingRight && jet->x()<=int(scene->width())-jet->pixmap().width()*jet->scale()){
        jet->setX(jet->x()+jet->getStep());

    }

    //Deduct player's health if jet is colliding with enemy
    QList<QGraphicsItem *> colliding_items = jet->collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i){

        Enemy* enemy = dynamic_cast<Enemy*>(colliding_items[i]); //Check if the colliding object is inherited from Enemy

              if(enemy != nullptr){

                jet->deductHealth(enemy->getHealth()); //Deduct player's health with the amount of the enemy's health
                enemy->deductHealth(jet->getHealth()); //Vice versa


            }
        }

    frenzyPackDisplayBar->setNumOfFrenzy(numOfFrenzyPack); //Update the display bar of possessing frenzy pack

    healthBar->setHealth(jet->getHealth()); //Update the health bar

    //Pause the game if jet reach 0 health
    if(jet->getHealth()<=0){

        gameIsOver(DEFEAT);

        delete jet;

        return;
    }
}


//Stop the game and allows player to restart
void Game::gameIsOver(Result result){

    pause();
    gameOver = true; //Player can press "R" to restart the game after game is over

    resultBoard = new ResultBoard(result, 640, 300, this);
    scene->addItem(resultBoard);

}


//Freeze the program by stopping the timers
void Game::pause(){

    refreshTimer->stop();
    frenzyTimer->stop();
    enemySpawningTimer->stop();
}

