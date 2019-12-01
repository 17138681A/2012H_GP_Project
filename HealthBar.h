#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include <QGraphicsPixmapItem>

class HealthBar: public QGraphicsPixmapItem{

public:

    HealthBar(QObject* parent);
    void setHealth(int hp);


private:

    QPixmap pix;
};

#endif // HEALTHBAR_H
