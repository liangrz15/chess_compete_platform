#ifndef HUMANAGENT_H
#define HUMANAGENT_H
#include"agent.h"
#include"InputPointObserver.h"
#include"uiinput.h"
class HumanAgent: public Agent, public InputPointObserver
{
public:
    HumanAgent(Player_Color _color, GameController* _gameController, UIInput* uiInput) : Agent(_color, _gameController){
        uiInput->addPointObserver(this);
    }
    void get_opponent_point(int x,int y, Player_Color _color);
    void inputPoint(int x, int y);
};

#endif // HUMANAGENT_H
