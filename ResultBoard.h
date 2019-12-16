#ifndef RESULTBOARD_H
#define RESULTBOARD_H
#include <QGraphicsPixmapItem>
#include "enumList.h"
class ResultBoard: public QGraphicsPixmapItem{

public:

    ResultBoard(Result result, double x, double y);


private:

    Result result; //Victory or Defeated
    QPixmap pix;

};

#endif // RESULTBOARD_H
