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
    //得到（x,y）的颜色 若在范围外返回none
    Player_Color get_color(int x,int y);
    //给（x,y)设置颜色 成功返回true 反之false
    bool set_color(int x,int y,Player_Color color);
    //测试用
    void print();
};

#endif // BOARD_H

