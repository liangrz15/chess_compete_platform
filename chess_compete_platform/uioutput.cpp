#include "uioutput.h"


void UIOutput::displayBoard(Board* board){
    int i;
    for(i = board->getWidth() - 1; i >= 0; i--){
        if(board->get_color(i, i) == Player_Color::Black)
            break;
    }
    mainWindow->test_Display(i, i);
}
