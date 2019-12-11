#include "Game.h"
#include "QGraphicsItem"



Game::Game(QObject* parent)
{
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setFocusPolicy(Qt::NoFocus);



    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0, 1280, 960);


    setScene(scene);

    refreshRate = new QTimer(this);
    frenzyTimer = new QTimer(this);
    enemySpawningTimer = new QTimer(this);

    weapon = PLASMA_BEAM;
    numOfFrenzyPack = 0;
    stormerEffectStack = 0;
    killCount = 0;
    numOfSpiderSpawned = 0;

    jet = new Jet(0, 0, refreshRate, this);
    jet->setPos(640-jet->pixmap().width()*jet->scale()/2,960);
    scene->addItem(jet);

    guide = new Guide(640, 350, this);
    scene->addItem(guide);

    srand((unsigned)time(0));

    random_device dev;
    mt19937 rng(dev());

    refreshRate->start(10);
    connect(refreshRate, SIGNAL(timeout()), this, SLOT(opening()));


    //    setBackgroundBrush(QImage(":/images/darkPurple.png"));
    //    equipment = new Equipment(500, 500, refreshRate, this);
    //    scene->addItem(equipment);
//    initialAnimationTimer = startTimer(10);
//    guide->setPos(640-guide->pixmap().width()*guide->scale()/2,300-guide->pixmap().height()*guide->scale()/2);



//    fps = startTimer(10);

//    fireRate = -1;


//    gunslinger->setOffset(gunslinger->getX(), gunslinger->getY());
//    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(img));
//    QImage img(":/image/jewel.jpg");
}




void Game::opening(){

    if(jet->y() <= 600){

         playerControlAvailable();
         disconnect(refreshRate, SIGNAL(timeout()), this, SLOT(opening()));
         disconnect(refreshRate, SIGNAL(timeout()), jet, SLOT(move()));

    }
}

void Game::victory(){

    pause();
    gameOver = true;

}

void Game::pause(){

    refreshRate->stop();
    frenzyTimer->stop();
    enemySpawningTimer->stop();
}

void Game::playerControlAvailable()
{


    enemySpawningTimer->start(2000);
    connect(frenzyTimer, SIGNAL(timeout()), this, SLOT(fire()));
    connect(refreshRate, SIGNAL(timeout()), this, SLOT(screenEventHandler()));
    connect(enemySpawningTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));




    jet->setStep(5);


    delete guide;

    frenzyPackDisplayBar = new FrenzyPackDisplayBar(this);
    scene->addItem(frenzyPackDisplayBar);

    healthBar = new HealthBar(this);
    scene->addItem(healthBar);

    setFocus();

    //    jet->setptX(jet->x());
    //    jet->setptY(jet->y());
    //    killTimer(initialAnimationTimer);
    //    refreshRate->start(10);
}

void Game::addEquipmentEffect(EquipmentName name){

    if(name == STORMER_PACK){
        weapon = STORMER_BEAM;
        ++stormerEffectStack;
        QTimer::singleShot(10000, this, SLOT(stopStormerEffect()));
    }

    else if(name == ULTRA_STORMER_PACK){
        weapon = ULTRA_STORMER_BEAM;
        ++stormerEffectStack;
        QTimer::singleShot(10000, this, SLOT(stopStormerEffect()));
    }

    else if(name == HEALTH_PACK && jet->getHealth() < maxHealthOfJet)
        jet->addHealth(100);

    else if(name == FRENZY_PACK && numOfFrenzyPack < maxNumOfFrenzyPack)
        ++numOfFrenzyPack;

    else if(name == FRENZY_STAR)//Still developing
        victory();

}// Day 5

void Game::addEquipment(EquipmentName name, double x, double y){

    equipment = new Equipment(name, x, y, refreshRate, this);//equipment 1
    scene->addItem(equipment);
    connect(equipment, SIGNAL(equipped(EquipmentName)), this, SLOT(addEquipmentEffect(EquipmentName)));

}



//Randomly spawn 1 among 5 equipments
void Game::spawnEquipment(double x, double y, double dropRate){


    if(dropRate < 0)//Don't drop any item if the eliminated enemy has -1 for their drop rate
        return;

    if(dropRate < 1)
        ++killCount;

    if(dropRate > 1){

        if(dropRate > 21){

            cout << "spawned" << endl;

            addEquipment(FRENZY_STAR, x, y);
            return;

        }else QTimer::singleShot(4000, this, SLOT(spawnMotherDisk()));

    }




    unsigned int upperBound = (unsigned int)(21/dropRate); //Find the upperbound of the random distribution's range according to the drop rate


    uniform_int_distribution<std::mt19937::result_type> dist(1, upperBound); //Distribution in the range [1, upperBound]

    unsigned int randNum = dist(rng); //Generate a number in the range [1, upperBound]
    cout << "upperBound: " << randNum << endl;
    if(randNum == 1){

        addEquipment(ULTRA_STORMER_PACK, x, y);

    }else if(randNum <= 6){

        addEquipment(STORMER_PACK, x, y);

    }else if(randNum <= 11){

        addEquipment(FRENZY_PACK, x ,y);

    }else if(randNum <= 16){

        addEquipment(HEALTH_PACK, x, y);

    }else if(randNum <= 21){

        addEquipment(FRENZY_PACK, x, y);//Spawn FRENZY_PACK instead of SPEED_BOOST_PACK because SPEED_BOOST_PACK is still under development

    }

}

void Game::spawnEnemyPeojectile(double degree, double x, double y)
{

    enemyProjectile = new EnemyProjectile(degree, x, y, refreshRate, this);
    scene->addItem(enemyProjectile);

}

void Game::addMeteor(){

    enemy = new Meteor(refreshRate, this);
    connect(enemy, SIGNAL(spawnEquipmentSignal(double, double, double)), this, SLOT(spawnEquipment(double, double, double)));
    scene->addItem(enemy);

}

void Game::addSpider(){

    enemy = new Spider(refreshRate, this);
    connect(enemy, SIGNAL(spawnEquipmentSignal(double, double, double)), this, SLOT(spawnEquipment(double, double, double)));
    connect(enemy, SIGNAL(enemyProjectileIsLaunched(double, double, double)), this, SLOT(spawnEnemyPeojectile(double, double, double)));
    scene->addItem(enemy);

}

void Game::addSatellite(){
    enemy = new Satellite(refreshRate, this);
    connect(enemy, SIGNAL(spawnEquipmentSignal(double, double, double)), this, SLOT(spawnEquipment(double, double, double)));
    scene->addItem(enemy);
}

void Game::spawnHorrorDisk(){

    enemy = new HorrorDisk(refreshRate, this);
    connect(enemy, SIGNAL(spawnEquipmentSignal(double, double, double)), this, SLOT(spawnEquipment(double, double, double)));
    connect(enemy, SIGNAL(enemyProjectileIsLaunched(double, double, double)), this, SLOT(spawnEnemyPeojectile(double, double, double)));
    scene->addItem(enemy);

}

void Game::spawnMotherDisk(){

    enemy = new MotherDisk(refreshRate, this);
    connect(enemy, SIGNAL(spawnEquipmentSignal(double, double, double)), this, SLOT(spawnEquipment(double, double, double)));
    connect(enemy, SIGNAL(enemyProjectileIsLaunched(double, double, double)), this, SLOT(spawnEnemyPeojectile(double, double, double)));
    scene->addItem(enemy);

}

void Game::spawnEnemy(){

//    if(killCount == numOfSpiderSpawned){

//        QTimer::singleShot(3000, this, SLOT(spawnBoss()));

//    }



    if(killCount < 35){

        for(int i = 0; i < 1 + killCount/15; ++i){

            addSpider();
            ++numOfSpiderSpawned;

        }

    }else if(killCount == numOfSpiderSpawned){

                QTimer::singleShot(2000, this, SLOT(spawnHorrorDisk()));
                numOfSpiderSpawned = 0;

            }


    uniform_int_distribution<std::mt19937::result_type> dist(1, 5); //Distribution in the range [1, 5]
    unsigned int randNum = dist(rng); //Generate a number in the range [1, 5]

    if(randNum == 1)//20% chance to spawn a satellite when spawning new enemies
        addSatellite();

    for(int i = 0; i < rand()%3; ++i)
        addMeteor();





    cout << "killed: "<< killCount << endl;
    cout << "enemySpawned: " << numOfSpiderSpawned << endl;

//    enemy = new Spider(refreshRate, this);
//    scene->addItem(enemy);
//    connect(enemy, SIGNAL(enemyIsEliminated(double, double, int)), this, SLOT(spawnEquipment(double, double, int)));
//    connect(enemy, SIGNAL(enemyProjectileIsLaunched(double, double)), this, SLOT(spawnEnemyPeojectile(double, double))); // ; after SIGNAL() ultra bug

}

void Game::addPlayerProjectile(double degree){

    projectile = new PlayerProjectile(degree, jet->x()+(jet->pixmap().width())*jet->scale()/2, jet->y(), refreshRate, this);
    scene->addItem(projectile);


}

void Game::firePlasmaBeam(){

    addPlayerProjectile(0);

}

void Game::fireFlakkerBeam(){

    for(int i = 0; i < 3; ++i)
        addPlayerProjectile(337.5+22.5*i);



}

void Game::fireUltraFlakkerBeam(){

    for(int i = 0; i < 5; ++i)
        addPlayerProjectile((315+22.5*i));

}

void Game::fire(){

    if(weapon == PLASMA_BEAM){

        firePlasmaBeam();


    }else if(weapon == STORMER_BEAM){

        fireFlakkerBeam();

    }else if(weapon == ULTRA_STORMER_BEAM){

        fireUltraFlakkerBeam();

    }

    ///    weapon = new PlayerProjectile(100, SlightlyTiltLeft, jet->x()+(jet->pixmap().width())/4, jet->y(), refreshRate, this);
    ///    weapon->setPos(weapon->x()-weapon->pixmap().width()*weapon->scale()/4, weapon->y());
}

void Game::stopStormerEffect(){

    if(--stormerEffectStack == 0)
        weapon = PLASMA_BEAM;
}



void Game::stopFrenzyEffect(){

    frenzyTimer->stop();
    frenzyMode = false;
}

void Game::keyPressEvent(QKeyEvent *event)
{
    //If game is over
    if(event->key() == Qt::Key_R && gameOver){

        cout << "restart game" << endl;
        emit restart();

    }else if(!gameOver){ //If game is not over yet

        if(event->key() == Qt::Key_J && !event->isAutoRepeat()){ //We use fire-by-click mode here which mean player can not hold the key to fire.


            if(frenzyMode)
                return;
            else
                fire();


//            cout << "Newpressing" << endl;
//            cout << frenzyTimer->isActive() << endl;


        }

        else if(event->key() == Qt::Key_W)
            goingUp = true;

        else if(event->key() == Qt::Key_S)
            goingDown = true;

        else if(event->key() == Qt::Key_A)
            goingLeft = true;

        else if(event->key() == Qt::Key_D)
            goingRight = true;

        else if(event->key() == Qt::Key_K && numOfFrenzyPack != 0 && !frenzyMode){



            QTimer::singleShot(5000, this, SLOT(stopFrenzyEffect()));
            frenzyMode = true;
            --numOfFrenzyPack;
            frenzyTimer->start(100);

        }
    }
}

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

///    else if(event->key() == Qt::Key_Enter && gameOver){


///        emit gameIsOver();

///    }
}


void Game::screenEventHandler()
{

    //Check if the player is colliding with object inherited from class Enemy
    QList<QGraphicsItem *> colliding_items = jet->collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i){

        Enemy* enemy = dynamic_cast<Enemy*>(colliding_items[i]);

              if(enemy != nullptr){

                jet->deductHealth(enemy->getHealth()); //Deduct player health with the value of the collided enemy's health
                enemy->deductHealth(jet->getHealth()); //Vice versa


            }
        }

    //Check if player reach 0 health
    if(jet->getHealth()<=0){

        delete healthBar;

        //Pause the game
        pause();

        gameOver = true;//Used by keyPressEvent(), player can press "R" to restart the game after gameOver is true

        return;
    }

    //Set player position according to 4 boolean value that each represented 1 direction
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


///        jet->setptX(jet->getX() + jet->getStep());
///        cout << "Right" << endl;
///        QWidget::update();
    }

    frenzyPackDisplayBar->setNumOfFrenzy(numOfFrenzyPack);

    healthBar->setHealth(jet->getHealth());

}

///END OF Game.cpp


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//void Game::timerEvent(QTimerEvent *event){



//    if(event->timerId() == initialAnimationTimer){

//        jet->setPos(jet->x(), jet->y()-1);

//        if(jet->y() <= 600)
//             playerControlAvailable();
//    }

//}

//void Game::timerEvent(QTimerEvent *event)
//{



//if(event->timerId() == fps){
//    if(goingUp && jet->getY()!=0){
//        jet->setptY(jet->getY() - jet->getStep());
////        cout << "Up" << endl;
////        QWidget::update();
//    }

//    if(goingDown && jet->getY()<=int(scene->height())-jet->pixmap().rect().height()*jet->scale()){
//        jet->setptY(jet->getY() + jet->getStep());
////        cout << "Down" << endl;
////        QWidget::update();
//    }
//    if(goingLeft && jet->getX()!=0){
//        jet->setptX(jet->getX() - jet->getStep());
////        cout << "Left" << endl;
////        QWidget::update();
//    }
//    if(goingRight && jet->getX()<=int(scene->width())-jet->pixmap().width()*jet->scale()){
//        jet->setptX(jet->getX() + jet->getStep());
////        cout << "Right" << endl;
////        QWidget::update();
//    }}



//}

//if(event->timerId() == fireRate){
//    cout << "up: " << goingUp << endl;
//    cout << "down: " << goingDown << endl;
//    cout << "left: " << goingLeft << endl;
//    cout << "right: " << goingRight << endl << endl;

//        weapon = new Projectile(100, 0, -1, gunslinger->getX()+(gunslinger->pixmap().width())/8, gunslinger->getY(), timer, this);
//        scene->addItem(weapon);

//    /*}else if(goingUp && !goingDown && goingLeft && !goingRight){

//        weapon = new Projectile(100, -tilt, -tilt, gunslinger->getX(), gunslinger->getY(), timer, this);
//        scene->addItem(weapon);
//        cout << "firing to left right direction" << endl;

//    }else if(!goingUp && !goingDown && goingLeft && !goingRight){

//        weapon = new Projectile(100, -1, 0, gunslinger->getX(), gunslinger->getY(), timer, this);
//        scene->addItem(weapon);

//    }else if(!goingUp && goingDown && goingLeft && !goingRight){

//        weapon = new Projectile(100, -tilt, tilt, gunslinger->getX(), gunslinger->getY(), timer, this);
//        scene->addItem(weapon);

//    }else if(!goingUp && goingDown && !goingLeft && !goingRight){

//        weapon = new Projectile(100, 0, 1, gunslinger->getX(), gunslinger->getY(), timer, this);
//        scene->addItem(weapon);

//    }else if(!goingUp && goingDown && !goingLeft && goingRight){

//        weapon = new Projectile(100, tilt, tilt, gunslinger->getX(), gunslinger->getY(), timer, this);
//        scene->addItem(weapon);

//    }else if(!goingUp && !goingDown && !goingLeft && goingRight){

//        weapon = new Projectile(100, 1, 0, gunslinger->getX(), gunslinger->getY(), timer, this);
//        scene->addItem(weapon);

//    }else if(goingUp && !goingDown && !goingLeft && goingRight){

//        weapon = new Projectile(100, tilt, -tilt, gunslinger->getX(), gunslinger->getY(), timer, this);
//        scene->addItem(weapon);
//    }*/




//}




