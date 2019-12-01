#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QGraphicsView"
#include "QtGui"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    establishGame();
    setWindowTitle("Sky Buster");
    setFixedSize(1280, 960);




//    game = new Game(this);
//    setCentralWidget(game);
//    setWindowTitle("Bullet Master");
//    setFixedSize(game->sceneRect().width(),game->sceneRect().height());

//    game->setBackgroundBrush(QImage(":/image/darkPurple.png"));



    //    setFocusPolicy(Qt::StrongFocus);
    //    startTimer(100);
    //    setCentralWidget(g);
//    centralWidget()->setStyleSheet("background-image:url(\"darkPurple.png\"); background-position: center; ");
    //    QPixmap bkgnd(":/image/jewel.jpg");
    //        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    //        QPalette palette;
    //        palette.setBrush(QPalette::Background, bkgnd);
    //        centralWidget()->setPalette(palette);

}

void MainWindow::establishGame(){

    game = new Game(this);
    setCentralWidget(game);
    game->setBackgroundBrush(QImage(":/image/darkPurple.png"));
    connect(game, SIGNAL(restart()), this, SLOT(restart()));

}

void MainWindow::restart(){
    cout << "game is over" << endl;
    delete game;
    establishGame();

}

MainWindow::~MainWindow()
{
    delete ui;
}

/// of MainWindow.cpp
////////////////////////////////////////////////////////////////////////////////

//void MainWindow::keyPressEvent(QKeyEvent* event){

//    if(event->key() == Qt::Key_Enter && gameOver){

//       delete game;
//       establishGame();
//       gameOver = false;

//    }

//}

//void MainWindow::keyReleaseEvent(QKeyEvent *event){

//    if(event->key() == Qt::Key_Up || event->key() == Qt::Key_W)
//        goingUp = false;

//    else if(event->key() == Qt::Key_Down || event->key() == Qt::Key_S)
//        goingDown = false;

//    else if(event->key() == Qt::Key_Left || event->key() == Qt::Key_A)
//        goingLeft = false;

//    else if(event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
//        goingRight = false;
//}

//void MainWindow::timerEvent(QTimerEvent *event){

//    if(goingUp){
//        gunslinger.setY(gunslinger.getY() - gunslinger.getStep());
////        cout << "Up" << endl;
////        QWidget::update();
//    }

//    if(goingDown){
//        gunslinger.setY(gunslinger.getY() + gunslinger.getStep());
////        cout << "Down" << endl;
////        QWidget::update();
//    }
//    if(goingLeft){
//        gunslinger.setX(gunslinger.getX() - gunslinger.getStep());
////        cout << "Left" << endl;
////        QWidget::update();
//    }
//    if(goingRight){
//        gunslinger.setX(gunslinger.getX() + gunslinger.getStep());
////        cout << "Right" << endl;
////        QWidget::update();
//    }

//}



