//Day 1
#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "QDebug"
#include "QTime"
#include "QKeyEvent"
#include "iostream"
#include "Game.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:

    void restart();

private:

    Ui::MainWindow *ui;
    Game* game;

    void establishGame();


    //    bool gameOver = false;
    //    Gunslinger gunslinger;
    //    bool goingUp = false, goingDown = false, goingLeft = false, goingRight = false;
    //    void keyPressEvent(QKeyEvent* event) override;
    //    void keyReleaseEvent(QKeyEvent *event) override;
    ////    void paintEvent(QPaintEvent* event) override;
        //    void timerEvent(QTimerEvent* event) override;
};

#endif // MAINWINDOW_H
