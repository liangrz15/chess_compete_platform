#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"uiinput.h"
#include<QVector>
#include"clickablebutton.h"
#include"player_color.h"
#include<QSignalMapper>
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
    QVector<QVector<ClickableButton*>> cells;
    QSignalMapper* mapper;
    int cell_size;
    int cell_spacing;
    int left_padding;
    int top_padding;
    int width;
    int height;
public slots:
    void generateBoard(int width, int height);
    void handleClick(int);
    void setColor(int x, int y, Player_Color color);
};

#endif // MAINWINDOW_H
