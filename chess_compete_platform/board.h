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
    ~Board();
    Player_Color get_color(int x,int y);
};

#endif // BOARD_H

