#include "logic.h"
#include "player_color.h"
#include "QString"

Logic::Logic(){}
Logic::~Logic(){}

int Logic::isVaild(int x,int y,int color)
{
    return 0;
}

Player_Color Logic::win_tie()
{
    return none;
}

void Logic::play_chess(int x,int y,Player_Color color,Board* UI_board){}

bool Logic::isEnd()
{
    return true;
}

void Logic::save(QString name){}
Player_Color Logic::load(QString name){return none;}


bool Logic::withdraw(Player_Color color)
{
    return false;
}
