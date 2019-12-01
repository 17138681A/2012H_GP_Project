// Day 5
#ifndef FRENZYPACKDISPLAYBAR_H
#define FRENZYPACKDIAPLAYBAR_H
#include <QGraphicsPixmapItem>

class FrenzyPackDisplayBar: public QGraphicsPixmapItem{

public:
    FrenzyPackDisplayBar(QObject* parent);
    void setNumOfFrenzy(int num);


private:

    QPixmap pix;
};

#endif // FRENZYPACKDISPLAYBAR_H
