#include "mainwindow.h"
#include <QApplication>
#include"gamecontroller.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    GameController* controller = new GameController(&w);
    return a.exec();
}
