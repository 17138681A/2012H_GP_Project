//Day 1
#ifndef JET_H
#define JET_H



#include "QObject"
#include "MovableObj.h"
#include "QTimer"


#include "iostream"
using namespace std;


class Jet: public Movable, public QGraphicsPixmapItem  {

Q_OBJECT

public:

    enum Direction{
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

    explicit Jet(double x, double y, QTimer* timer, QObject *parent);

    void setDirection(Direction direction);
    void deductHealth(int hp);
    void addHealth(int hp);//Day 5

    int getHealth();




private:

    int health;
    QPixmap pix;
    Direction dir;


public slots:

    void move() override;

#endif // JET_H

//    void keyPressEvent(QKeyEvent* event) override;
//    void keyReleaseEvent(QKeyEvent *event) override;
////    void paintEvent(QPaintEvent* event) override;
//    void timerEvent(QTimerEvent* event) override;



//    void move(Direction) override;




};
