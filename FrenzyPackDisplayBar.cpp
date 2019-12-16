#include "FrenzyPackDisplayBar.h"


FrenzyPackDisplayBar::FrenzyPackDisplayBar(){

    pix = QPixmap(":/image/frenzyx0.png");
    setPixmap(pix);
    setScale(0.15);
    setPos(40, 850);

}


//Update the image of the display bar that showing the remaining frenzy packs
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
