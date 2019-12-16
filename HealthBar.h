#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include <QGraphicsPixmapItem>

class HealthBar: public QGraphicsPixmapItem{

public:

    HealthBar();

    void setHealth(int hp); //Update the status of player's current health


private:

    QPixmap pix;

};

#endif // HEALTHBAR_H
