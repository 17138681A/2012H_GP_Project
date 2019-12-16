#ifndef JET_H
#define JET_H
#include "QObject"
#include "MovableObj.h"
#include "QTimer"

using namespace std;


class Jet: public Movable, public QGraphicsPixmapItem  {

Q_OBJECT

public:

    explicit Jet(double x, double y, QTimer* timer);

    void arrived(); //Jet is ready for combat
    void deductHealth(int hp); //Deduct certain health point
    void heal(int hp); //Add certain health point

    int getHealth(); //Get current health point


private:

    const int maxHealth = 300; //Maximum health

    int health; //Current health

    bool isArriving; //Entering the game

    QPixmap pix;


public slots:

    void move() override;

};

#endif // JET_H
