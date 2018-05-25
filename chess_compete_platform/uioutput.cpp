#include "uioutput.h"


void UIOutput::displayBoard(Board* board){
    for(int i = 0; i < board->getM(); i++){
        for(int j = 0; j < board->getN(); j++){
            mainWindow->setColor(i, j, board->get_color(i, j));
        }
    }
}
