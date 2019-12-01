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
    frenzy = new QTimer(this);
    enemySpawningTimer = new QTimer(this);

    weapon = PLASMA_BEAM;
    numOfFrenzyPack = 0;
    stormerEffectStack = 0;

    killCount = 0;

    jet = new Jet(0, 0, refreshRate, this);
    jet->setPos(640-jet->pixmap().width()*jet->scale()/2,960);
    scene->addItem(jet);




    guide = new Guide(640, 350, this);

    scene->addItem(guide);



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

void Game::playerControlAvailable()
{


    enemySpawningTimer->start(2000);
    connect(frenzy, SIGNAL(timeout()), this, SLOT(fire()));
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

    else if(name == SPEEDBOOST_PACK)//Still developing
        jet->setStep(10);

    else if(name == FRENZY_PACK && numOfFrenzyPack < maxNumOfFrenzyPack)
        ++numOfFrenzyPack;


}// Day 5

void Game::addEquipment(EquipmentName name, double x, double y){

    equipment = new Equipment(name, x, y, refreshRate, this);//equipment 1
    scene->addItem(equipment);
    connect(equipment, SIGNAL(equipped(EquipmentName)), this, SLOT(addEquipmentEffect(EquipmentName)));

}


void Game::spawnEquipment(double x, double y, int dropRate){

    if(dropRate == -1)//Don't drop any item if the eliminated enemy has -1 for their drop rate
        return;

    ++killCount;


    int randNum = rand()%(dropRate);//Randomly spawn 1 among 5 equipments

    if(randNum == 0){

        addEquipment(ULTRA_STORMER_PACK, x, y);

    }else if(randNum == 1){

        addEquipment(STORMER_PACK, x, y);

    }else if(randNum == 2){

        addEquipment(FRENZY_PACK, x ,y);

    }else if(randNum == 3){

        addEquipment(HEALTH_PACK, x, y);

    }else if(randNum == 4){

        addEquipment(FRENZY_PACK, x, y);//Spawn FRENZY_PACK instead of SPEED_BOOST_PACK because SPEED_BOOST_PACK is still under development

    }

}

void Game::spawnEnemyPeojectile(double x, double y)
{

    enemyProjectile = new EnemyProjectile(x, y, refreshRate, this);
    scene->addItem(enemyProjectile);

}

void Game::addMeteor(){

    enemy = new Meteor(refreshRate, this);
    connect(enemy, SIGNAL(enemyIsEliminated(double, double, int)), this, SLOT(spawnEquipment(double, double, int)));
    scene->addItem(enemy);

}

void Game::addSpider(){

    enemy = new Spider(refreshRate, this);
    connect(enemy, SIGNAL(enemyIsEliminated(double, double, int)), this, SLOT(spawnEquipment(double, double, int)));
    connect(enemy, SIGNAL(enemyProjectileIsLaunched(double, double)), this, SLOT(spawnEnemyPeojectile(double, double)));
    scene->addItem(enemy);

}


void Game::spawnEnemy(){



    for(int i = 0; i < rand()%3; ++i)
        addMeteor();

    cout << "spawned" << endl;

    for(int i = 0; i < 1+killCount/20; ++i)
        addSpider();



//    enemy = new Spider(refreshRate, this);
//    scene->addItem(enemy);
//    connect(enemy, SIGNAL(enemyIsEliminated(double, double, int)), this, SLOT(spawnEquipment(double, double, int)));
//    connect(enemy, SIGNAL(enemyProjectileIsLaunched(double, double)), this, SLOT(spawnEnemyPeojectile(double, double))); // ; after SIGNAL() ultra bug

}

void Game::addPlayerProjectile(Tilt tilt){

    projectile = new PlayerProjectile(tilt, jet->x()+(jet->pixmap().width())*jet->scale()/2, jet->y(), refreshRate, this);
    scene->addItem(projectile);


}

void Game::firePlasmaBeam(){

    addPlayerProjectile(NoTilt);

}

void Game::fireFlakkerBeam(){

    addPlayerProjectile(NoTilt);

    addPlayerProjectile(SlightlyTiltLeft);

    addPlayerProjectile(SlightlyTiltRight);


}

void Game::fireUltraFlakkerBeam(){

    addPlayerProjectile(NoTilt);

    addPlayerProjectile(SlightlyTiltLeft);

    addPlayerProjectile(SlightlyTiltRight);

    addPlayerProjectile(ExtremelyTiltLeft);

    addPlayerProjectile(ExtremelyTiltRight);

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

    frenzy->stop();
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


            cout << "pressing" << endl;
            cout << frenzy->isActive() << endl;


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
            frenzy->start(50);

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

void Game::pause(){

    refreshRate->stop();
    frenzy->stop();
    enemySpawningTimer->stop();
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




