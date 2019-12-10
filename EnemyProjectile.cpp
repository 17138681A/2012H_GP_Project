#include "EnemyProjectile.h"
#include "Jet.h"

EnemyProjectile::EnemyProjectile(double degree, double x, double y, QTimer* timer, QObject* parent){

//    health = 1;
//    dropRate = -1; //Projectile won't drop any item
    damage = 50;
    pix = QPixmap(":/image/laserBlue05.png");
    projectileDegree = degree;

    setPixmap(pix);
    setStep(5);
    setPos(x-pixmap().width()/2,y);
    setScale(1);

    connect(timer,SIGNAL(timeout()), this, SLOT(move()));

}

void EnemyProjectile::move()
{

    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i){

        Jet* jet = dynamic_cast<Jet*>(colliding_items[i]);

              if(jet != nullptr){

                jet->deductHealth(damage);
                delete this; //funny bug

            }
        }//Day 5

    setRotation(projectileDegree);
    setY(y()+step*qCos(qDegreesToRadians(projectileDegree)));
    setX(x()-step*qSin(qDegreesToRadians(projectileDegree)));

    if(y() - pixmap().height()*scale() >= 960)
        delete this;


}
