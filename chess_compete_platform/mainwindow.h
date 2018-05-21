#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"uiinput.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setUIInput(UIInput* input){uiInput = input;}

private:
    Ui::MainWindow *ui;
    UIInput* uiInput;

public slots:
    void test_Display(int x, int y);
    void test_Input();
};

#endif // MAINWINDOW_H
