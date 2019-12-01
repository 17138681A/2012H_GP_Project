//Day 4
#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "MovableObj.h"
#include "enumList.h"
#include "QObject"

class Equipment: public Movable, public QGraphicsPixmapItem{

Q_OBJECT

public:



    Equipment(EquipmentName name, double x, double y, QTimer* timer, QObject* parent);

protected:

    EquipmentName name;
    int randNum;
    int xBounceDirection;
    int yBounceDirection;
    QPixmap pix;
    QTimer* refreshRate;

signals:
    void equipped(EquipmentName); //Day 5


public slots:
    void move() override;
};
#endif // EQUIPMENT_H
