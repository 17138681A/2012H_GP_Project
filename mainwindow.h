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

    void restart(); //Recreate a new Game object

private:

    Ui::MainWindow *ui;
    Game* game; //Pointer to the Game object

    void establishGame(); //Attach Game object to the main window

};

#endif // MAINWINDOW_H
