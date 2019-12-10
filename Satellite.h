#ifndef SATELLITE_H
#define SATELLITE_H
#include "Enemy.h"

class Satellite: public Enemy{

    Q_OBJECT

public:
    Satellite(QTimer* timer, QObject* parent);

public slots:
    void move() override;

private:
    int rotationDegree;
    int randDir;

};

#endif // SATELLITE_H
