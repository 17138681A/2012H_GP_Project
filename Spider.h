//Day 4
#ifndef SPIDER_H
#define SPIDER_H
#include "Enemy.h"

class Spider: public Enemy{

    Q_OBJECT

public:

    explicit Spider(QTimer* timer, QObject* parent);


public slots:
    void emitEnemyProjectileIsLaunchedSignal();
    void move() override;

};

#endif // SPIDER_H
