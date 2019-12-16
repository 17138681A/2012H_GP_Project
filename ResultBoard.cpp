#include "ResultBoard.h"

ResultBoard::ResultBoard(Result result, double x, double y){


    if(result == VICTORY) //Final boss is defeated

        pix = QPixmap(":/image/victory.png");

    else //Player is defeated

        pix = QPixmap(":/image/defeat.png");

    setPixmap(pix);
    setScale(1);
    setPos(x-pixmap().width()/2, y-pixmap().height()/2);
    setZValue(1); //To prevent blocking by other overlapped objects

}
