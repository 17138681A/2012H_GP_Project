///Day 2
#ifndef PLAYERPROJECTILE_H
#define PLAYERPROJECTILE_H


#include "MovableObj.h"
#include "enumList.h"
#include "QTimer"
#include "QtMath"


class PlayerProjectile: public Movable, public QGraphicsPixmapItem {

    Q_OBJECT

public:

    explicit PlayerProjectile( Tilt t, double x, double y, QTimer* timer, QObject* parent);


    double getProjectileSpeed() const;

//    int getFireRate() const;
//    void setFireRate(int fr);


//    double getDx() const;
//    double getDy() const;
//    void setDx(double x);
//    void setDy(double y);
//    void rotate(double degree);


protected:

//    int fireRate;
    int damage;

    QPixmap pix;
    Tilt tilt;

    const double slightlyTiltDegreeOfX = qSin(qDegreesToRadians(22.5));
    const double slightlyTiltDegreeOfY = qCos(qDegreesToRadians(22.5));
    const double extremelyTiltDegreeOfX = qSin(qDegreesToRadians(45.0));
    const double extremelyTiltDegreeOfY = qCos(qDegreesToRadians(45.0));

//    const double projectileSpeed = 10;

public slots:

    void move() override;

};
#endif // PLAYERPROJECTILE_H
