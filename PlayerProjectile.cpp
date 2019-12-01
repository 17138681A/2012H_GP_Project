#include "PlayerProjectile.h"
#include "QList"
#include "Enemy.h"




PlayerProjectile::PlayerProjectile( Tilt t, double x, double y, QTimer* timer, QObject *parent)
{
    pix = QPixmap(":/image/laserRed03.png");
    tilt = t;
    damage = 20;
    setPixmap(pix);

//    setDx(dx);
//    setDy(dy);
    setStep(10);
    setPos(x-pixmap().width()/2,y);
    setScale(1);

    connect(timer,SIGNAL(timeout()), this, SLOT(move()));


}

void PlayerProjectile::move(){

    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i){



        Enemy* enemy = dynamic_cast<Enemy*>(colliding_items[i]);



              if(enemy != nullptr){


                enemy->deductHealth(damage);

                // delete them from the heap to save memory
                delete this;

                // return (all code below refers to a non existint bullet)
                return;
            }
        }

    if(tilt == SlightlyTiltRight){


        setRotation(22.5);
        setY(y()-step*slightlyTiltDegreeOfY);
        setX(x()+step*slightlyTiltDegreeOfX);

    }else if(tilt == SlightlyTiltLeft){

        setRotation(-22.5);
        setY(y()-step*slightlyTiltDegreeOfY);
        setX(x()-step*slightlyTiltDegreeOfX);

    }else if(tilt == ExtremelyTiltRight){

        setRotation(45);
        setY(y()-step*extremelyTiltDegreeOfY);
        setX(x()+step*extremelyTiltDegreeOfX);

    }else if(tilt == ExtremelyTiltLeft){

        setRotation(-45);
        setY(y()-step*extremelyTiltDegreeOfY);
        setX(x()-step*extremelyTiltDegreeOfX);

    }else if(tilt == NoTilt)
            setY(y()-step);




    if(y() + pixmap().height()*scale() < 0)
        delete this;

}

//void PlayerProjectile::setFireRate(int fr){

//    fireRate = fr;

//}

//    setPos(double(x()),double(y()-step));

//void PlayerProjectile::setDx(double x){

//    dx = x;
//}

//void PlayerProjectile::setDy(double y){

//    dy = y;
//}

//void Projectile::rotate(double degree)
//{
//    setTransformOriginPoint(this->pixmap().rect().center());

//}

//            if (typeid(*(qgraphicsitem_cast<Enemy*>(colliding_items[i]))) == typeid(Enemy)){
