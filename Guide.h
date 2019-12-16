#ifndef GUIDE_H
#define GUIDE_H

#include <QGraphicsPixmapItem>


class Guide: public QGraphicsPixmapItem{

public:

    Guide(double x, double y);


private:

    QPixmap pix;

};

#endif // GUIDE_H
