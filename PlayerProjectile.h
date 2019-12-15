///Day 2
#ifndef PLAYERPROJECTILE_H
#define PLAYERPROJECTILE_H


#include "MovableObj.h"
#include "QTimer"
#include "QtMath"


class PlayerProjectile: public Movable, public QGraphicsPixmapItem {

    Q_OBJECT

public:

    explicit PlayerProjectile( double degree, double x, double y, QTimer* timer, QObject* parent);

    double getProjectileSpeed() const;


protected:

    int damage;
    double projectileDegree;

    QPixmap pix;

public slots:

    void move() override;

};
#endif // PLAYERPROJECTILE_H
