#ifndef ENEMYPROJECTILE_H
#define ENEMYPROJECTILE_H
#include "Enemy.h"

#include "QTimer"
#include "QtMath"

class EnemyProjectile: public Movable, public QGraphicsPixmapItem{

    Q_OBJECT

public:
    EnemyProjectile(double degree, double x, double y, QTimer* timer, QObject* parent);


protected:

    QPixmap pix;
    int damage;
    double projectileDegree;



public slots:
    void move() override;
};

#endif // ENEMYPROJECTILE_H
