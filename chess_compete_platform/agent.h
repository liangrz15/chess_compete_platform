#ifndef AGENT_H
#define AGENT_H
#include "logic.h"
#include"player_color.h"
#include"gamecontroller.h"

class Agent{
protected:
    Player_Color color;
    GameController* gameController;
public:
    //virtual void send_message(int x,int y);
    virtual void get_opponent_point(int x,int y, Player_Color _color) = 0;
    Agent(Player_Color _color, GameController* _gameController): color(_color), gameController(_gameController){}
};

#endif // AGENT_H

