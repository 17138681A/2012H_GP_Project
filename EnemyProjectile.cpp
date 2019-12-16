#include "EnemyProjectile.h"
#include "Jet.h"

EnemyProjectile::EnemyProjectile(double degree, double x, double y, QTimer* timer):Movable(timer){

    damage = 50;
    projectileDegree = degree; //Projectile can shoot from different angle

    pix = QPixmap(":/image/laserBlue05.png");
    setPixmap(pix);

    setStep(5); //Set projectile speed
    setPos(x-pixmap().width()/2,y);
    setScale(1);

}

void EnemyProjectile::move()
{

    //Deduct the health of jet if the enemy's projectile is colliding with jet
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i){

        Jet* jet = dynamic_cast<Jet*>(colliding_items[i]); //Check if the colliding object is jet

              if(jet != nullptr){

                jet->deductHealth(damage); //Deal damage to jet
                delete this; //Delete this equipment after colliding with jet

            }
        }

    setRotation(projectileDegree); //Rotate the image of projectile

    //The projectile speed will remain the same when shooting from different angle
    setY(y()+step*qCos(qDegreesToRadians(projectileDegree)));
    setX(x()-step*qSin(qDegreesToRadians(projectileDegree)));

    if(y() >= 960 || x() >= 1280 || x()+pixmap().height()*scale() <= 0 || y()+pixmap().height()*scale() <= 0){
        delete this; //Delete this projectile when going out of scene

    }


}
