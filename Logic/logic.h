#ifndef LOGIC_H
#define LOGIC_H
#include "board.h"
#include <QString>
#include "player_color.h"

class Logic{
//board在子类中声明这里基类还是只规定接口
//为了子类访问方便 以及语法的规范性
//private:
//    Board *board;
public:
    Logic();
    virtual ~Logic() = 0;

    //判断某子是否能在（x,y）点，能返回true 反之false
    virtual int isVaild(int x,int y,int color);

    virtual Player_Color win_tie();
    //此时x,y要为合法的落子点 传入的ui_board参数是为了更新ui显示的棋盘
    virtual void play_chess(int x,int y,Player_Color color,Board* UI_board);
    //若已经结束则true 反之false
    virtual bool isEnd();
    //保存存档
    virtual void save(QString name);
    //读取存档 返回下一步该谁走
    virtual Player_Color load(QString name);
    //悔棋
    virtual bool withdraw(Player_Color color);

    //测试用
    virtual void print(){};
};

#endif // LOGIC_H

