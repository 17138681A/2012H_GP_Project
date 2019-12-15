#include "PlayerProjectile.h"
#include "QList"
#include "Enemy.h"




PlayerProjectile::PlayerProjectile( double degree, double x, double y, QTimer* timer, QObject *parent)
{


    damage = 20;
    projectileDegree = degree; //Projectile can shoot from different angle

    pix = QPixmap(":/image/laserRed03.png");
    setPixmap(pix);

    setStep(10); //Set projectile speed
    setPos(x-pixmap().width()/2,y);
    setScale(1);

    refreshTimer = timer;
    connect(refreshTimer,SIGNAL(timeout()), this, SLOT(move())); //Update object's status and position

}

void PlayerProjectile::move(){


    //Deduct the enemy health if the player's projectile is colliding with the enemy
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i){

        Enemy* enemy = dynamic_cast<Enemy*>(colliding_items[i]); //Check if the colliding object is inherited from Enemy

              if(enemy != nullptr){

                enemy->deductHealth(damage); //Deal damage to enemy

                delete this; //Delete this projectile when colliding with enemy

                return;
            }
        }

    setRotation(projectileDegree); //Rotate the image of projectile

    //The projectile speed will stay the same when shooting from different angle
    setY(y()-step*qCos(qDegreesToRadians(projectileDegree)));
    setX(x()+step*qSin(qDegreesToRadians(projectileDegree)));

    if(y() + pixmap().height()*scale() < 0)
        delete this; //Delete this projectile when going out of scene

}

