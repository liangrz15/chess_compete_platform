#include "mainwindow.h"
#include <QApplication>
#include"gamecontroller.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    GameController* controller = new GameController(&w);
    w.show();
    return a.exec();
}
