#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include"player_color.h"
#include"logic.h"
#include"board.h"
#include"error_handling.h"
#include"uioutput.h"
#include"mainwindow.h"
class Agent;
class GameController
{
public:
    GameController(MainWindow* mainWindow);
    void receive_input(int x, int y, Player_Color color);
    Player_Color getNextPlayerColor() const{return next_player_color;}
private:
    Agent* black_agent;
    Agent* white_agent;
    Logic* logic;
    Player_Color next_player_color;
    Error_handling* black_error_handler;
    Error_handling* white_error_handler;
    Board* board;
    UIOutput* uiOutput;
};

#endif // GAMECONTROLLER_H
