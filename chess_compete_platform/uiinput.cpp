#include "uiinput.h"

UIInput::UIInput()
{

}


void UIInput::addPointObserver(InputPointObserver* observer){
    this->observers.push_back(observer);
}

void UIInput::getInput(int x, int y){
    for(auto observer: observers){
        observer->inputPoint(x,y);
    }
}
