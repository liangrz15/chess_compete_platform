#ifndef UIINPUT_H
#define UIINPUT_H

#include <QObject>
#include<QVector>
#include"InputPointObserver.h"
class UIInput :QObject
{
public:
    UIInput();
    void addPointObserver(InputPointObserver* observer);
public slots:
    void getInput(int x, int y);

private:
    QVector<InputPointObserver*> observers;
};

#endif // UIINPUT_H
