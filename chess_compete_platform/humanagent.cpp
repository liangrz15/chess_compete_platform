#include "humanagent.h"
#include"gamecontroller.h"



void HumanAgent::get_opponent_point(int x, int y, Player_Color _color){

}

void HumanAgent::inputPoint(int x, int y){
    if(this->gameController->getNextPlayerColor() == this->color){
        this->gameController->receive_input(x, y, this->color);
    }
}
