#ifndef ENEMYPROJECTILE_H
#define ENEMYPROJECTILE_H
#include "Enemy.h"


class EnemyProjectile: public Movable, public QGraphicsPixmapItem{

    Q_OBJECT

public:

    EnemyProjectile(double degree, double x, double y, QTimer* timer);


protected:

    int damage;

    double projectileDegree; //Projectile can shoot from different angle

    QPixmap pix;


public slots:

    void move() override;

};

#endif // ENEMYPROJECTILE_H
