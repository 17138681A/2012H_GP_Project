#ifndef FRENZYPACKDISPLAYBAR_H
#define FRENZYPACKDIAPLAYBAR_H
#include <QGraphicsPixmapItem>

class FrenzyPackDisplayBar: public QGraphicsPixmapItem{

public:

    FrenzyPackDisplayBar();

    void setNumOfFrenzy(int num); //Update the image of the display bar that showing the remaining frenzy packs


private:

    QPixmap pix;

};

#endif // FRENZYPACKDISPLAYBAR_H
