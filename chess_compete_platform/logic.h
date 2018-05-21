#ifndef LOGIC_H
#define LOGIC_H
#include "board.h"
#include <QString>
#include "player_color.h"

class Logic{
private:
    Board *board;
public:
    Logic(){}
    virtual ~Logic(){}

    //判断某子是否能在（x,y）点，能返回true 反之false
    virtual int isVaild(int x,int y,int color) = 0;

    virtual Player_Color win_tie() = 0;
    //此时x,y要为合法的落子点
    virtual void play_chess(int x,int y,Board* last_board,Player_Color color) = 0;
    //若已经结束则true 反之false
    virtual bool isEnd() = 0;
    //保存存档
    virtual void save(QString name) = 0;
    //读取存档
    virtual void load(QString name) = 0;
    //悔棋
    virtual bool withdraw(Player_Color color) = 0;
};

#endif // LOGIC_H

