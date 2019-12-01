#ifndef METEOR_H
#define METEOR_H
#include "Enemy.h"

class Meteor: public Enemy{

    Q_OBJECT

public:

    explicit Meteor(QTimer* timer, QObject* parent);


public slots:

    void move() override;

private:

    int rotationDegree;
    int randMeteor;

};

#endif // METEOR_H
