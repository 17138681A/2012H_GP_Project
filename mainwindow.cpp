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
    setWindowTitle("Sky Buster"); //Title of the game
    setFixedSize(1280, 960); //Fixed window size


}

//Attach Game object to the main window
void MainWindow::establishGame(){

    game = new Game(this);
    setCentralWidget(game);
    game->setBackgroundBrush(QImage(":/image/darkPurple.png"));
    connect(game, SIGNAL(restartSignal()), this, SLOT(restart()));

}

//Recreate a new Game object
void MainWindow::restart(){

    delete game;
    establishGame();

}

MainWindow::~MainWindow()
{
    delete ui;
}

