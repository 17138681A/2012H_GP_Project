#include "Jet.h"
#include "QList"
#include "Enemy.h"

using namespace std;



Jet::Jet(double x, double y, QTimer* timer, QObject* parent){

    pix = QPixmap(":/image/playerShip1_red.png");
    health = 300;
    setPixmap(pix);
    setStep(1);
    setPos(x,y);
    setScale(1);
    setZValue(1);
    connect(timer,SIGNAL(timeout()), this, SLOT(move()));


//    startTimer(10);
    //    setHeight(100);
    //    setWidth(100);

}

int Jet::getHealth(){

    return health;
}

void Jet::setDirection(Direction direction){

    dir = direction;

}

void Jet::deductHealth(int hp){

    health -= hp;
    if(health <= 0)
        delete this;

}

void Jet::addHealth(int hp)
{
    health += hp;
    if(health >= 500)
        health = 500;

}

void Jet::move(){





    setY(y()-step); //Move forward in default


}

///End of jet.cpp
////////////////////////////////////////////////////////////////////////////////////




//void Gunslinger::timerEvent(QTimerEvent*){


//    if(goingUp){
//        setY(ptY - step);
////        cout << "Up" << endl;
////        QWidget::update();
//    }

//    if(goingDown){
//        setY(ptY + step);
////        cout << "Down" << endl;
////        QWidget::update();
//    }
//    if(goingLeft){
//        setX(ptX - step);
////        cout << "Left" << endl;
////        QWidget::update();
//    }
//    if(goingRight){
//        setX(ptX + step);
////        cout << "Right" << endl;
////        QWidget::update();
//    }


//}

//void Gunslinger::keyPressEvent(QKeyEvent *event){


//    if(event->key() == Qt::Key_Up || event->key() == Qt::Key_W)
//        goingUp = true;

//    else if(event->key() == Qt::Key_Down || event->key() == Qt::Key_S)
//        goingDown = true;

//    else if(event->key() == Qt::Key_Left || event->key() == Qt::Key_A)
//        goingLeft = true;

//    else if(event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
//        goingRight = true;

////    switch(event->key()){
////    case Qt::Key_Up:
////        goingUp = true;
////        break;

////    case Qt::Key_Down:
////        goingDown = true;
////        break;

////    case Qt::Key_Left:
////        goingLeft = true;
////        break;

////    case Qt::Key_Right:
////        goingRight = true;
////        break;

////    default:
////        break;
////    }

//}

//void Gunslinger::keyReleaseEvent(QKeyEvent *event){


//    if(event->key() == Qt::Key_Up || event->key() == Qt::Key_W)
//        goingUp = false;

//    else if(event->key() == Qt::Key_Down || event->key() == Qt::Key_S)
//        goingDown = false;

//    else if(event->key() == Qt::Key_Left || event->key() == Qt::Key_A)
//        goingLeft = false;

//    else if(event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
//        goingRight = false;

////    switch(event->key()){
////    case Qt::Key_Up:
////        goingUp = false;
////        break;

////    case Qt::Key_Down:
////        goingDown = false;
////        break;

////    case Qt::Key_Left:
////        goingLeft = false;
////        break;

////    case Qt::Key_Right:
////        goingRight = false;
////        break;

////    default:
////        break;
////    }
//}

////void Gunslinger::paintEvent(QPaintEvent *event){

////    cout << "debug2" << endl;
////    Q_UNUSED(event)
////    QPainter painter;
////    painter.begin(this);
////    painter.setBrush(Qt::red);
////    painter.drawEllipse(ptX, ptY, objWidth, objHeight);
////    painter.end();

////}
