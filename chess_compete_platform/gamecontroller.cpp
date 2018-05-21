#include "gamecontroller.h"
#include"agent.h"
#include"humanagent.h"
#include"NaiveLogic.h"
#include"NaiveErrorHandling.h"
#include"uiinput.h"
GameController::GameController(MainWindow* mainWindow)
{
    this->board = new Board(9,9);
    /*Agent* black_agent;
    Agent* white_agent;
    Logic* logic;
    Player_Color next_player_color;
    Error_handling* black_error_handler;
    Error_handling* white_error_handler;
    Board* board;
    UIOutput* uiOutput;*/

    this->logic = new NaiveLogic;
    this->next_player_color = Black;
    this->black_error_handler = new Naive_Error_Handling();
    this->white_error_handler = new Naive_Error_Handling();
    this->uiOutput = new UIOutput(mainWindow);
    UIInput* uiInput = new UIInput();
    this->black_agent = new HumanAgent(Black, this, uiInput);
    this->white_agent = new HumanAgent(White, this, uiInput);
    mainWindow->setUIInput(uiInput);

}

void GameController::receive_input(int x, int y, Player_Color color){
    if(!logic->isVaild(x, y, color)){
        Error_handling* handler = (color == Black ? black_error_handler : white_error_handler);
        handler->handle_error(x, y);
        return;
    }
    logic->play_chess(x, y , board, color);
    this->black_agent->get_opponent_point(x, y, color);
    this->white_agent->get_opponent_point(x, y, color);
    this->uiOutput->displayBoard(board);
    this->next_player_color = (next_player_color == Black ? White : Black);
}
