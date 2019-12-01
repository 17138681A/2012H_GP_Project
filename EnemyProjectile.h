#ifndef ENEMYPROJECTILE_H
#define ENEMYPROJECTILE_H
#include "Enemy.h"

class EnemyProjectile: public Movable, public QGraphicsPixmapItem{

    Q_OBJECT

public:
    EnemyProjectile(double x, double y, QTimer* timer, QObject* parent);


protected:

    QPixmap pix;
    int damage;



public slots:
    void move() override;
};

#endif // ENEMYPROJECTILE_H
