#ifndef UIOUTPUT_H
#define UIOUTPUT_H

#include <QObject>
#include"board.h"
#include"mainwindow.h"
class UIOutput
{
public:
    UIOutput(MainWindow* _window): mainWindow(_window){}
    void displayBoard(Board* board);

private:
    MainWindow* mainWindow;
};

#endif // UIOUTPUT_H
