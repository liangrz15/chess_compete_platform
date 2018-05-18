#ifndef BOARD_H
#define BOARD_H
#include "player_color.h"

//从左下开始 0开始 x横轴 y竖轴
class Board{
private:
    int M,N;
    Player_Color** chess_board;
public:
    Board(int _M,int _N);
    Board(Board* _board);
    ~Board();
    Player_Color get_color(int x,int y);
    Player_Color set_color(int x,int y,Player_Color color);
    int getM(){return M;}
    int getN(){return N;}
};

#endif // BOARD_H

