#include "FrenzyPackDisplayBar.h"
#include "iostream"
using namespace std;

FrenzyPackDisplayBar::FrenzyPackDisplayBar(QObject* parent){


    pix = QPixmap(":/image/frenzyx0.png");
    setPixmap(pix);
    setScale(0.15);
    setPos(40, 850);

    //cout << "setting diplay bar" << endl;

}

void FrenzyPackDisplayBar::setNumOfFrenzy(int num)
{
    if(num == 0)
        pix = QPixmap(":/image/frenzyx0.png");

    else if(num == 1)
        pix = QPixmap(":/image/frenzyx1.png");

    else if(num == 2)
        pix = QPixmap(":/image/frenzyx2.png");

    else if(num == 3)
        pix = QPixmap(":/image/frenzyx3.png");

    setPixmap(pix);
}
