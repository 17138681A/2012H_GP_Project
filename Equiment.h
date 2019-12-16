#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "MovableObj.h"
#include "enumList.h"


class Equipment: public Movable, public QGraphicsPixmapItem{

    Q_OBJECT

public:

    Equipment(EquipmentName name, double x, double y, QTimer* timer);


protected:

    EquipmentName name; //To indicate the current equipment

    int randDirOfX; //Randomize initial horizontal direction of movement for each equipment
    int randDirOfY; //Randomize initial vertical direction of movement for each equipment

    QPixmap pix;


signals:

    void equipped(EquipmentName); //Informing the game to apply effect on jet


public slots:

    void move() override;

};
#endif // EQUIPMENT_H
