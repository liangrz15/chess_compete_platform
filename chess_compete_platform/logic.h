#ifndef LOGIC_H
#define LOGIC_H
#include "board.h"
#include <QString>
#include "player_color.h"

class Logic{
public:
    Logic(){}
    virtual ~Logic(){}

    //判断某子是否能在（x,y）点，能返回true 反之false
    virtual int isVaild(int x,int y,int color) = 0;
    //获取胜者 平局返回tie 没有结束返回none
    virtual Player_Color win_tie() = 0;
    //此时x,y要为合法的落子点
    virtual void play_chess(int x,int y,Player_Color color) = 0;
    //若已经结束则true 反之false
    virtual bool isEnd() = 0;
    //保存存档
    virtual void save(QString name) = 0;
    //读取存档 返回下一个下棋者
    virtual Player_Color load(QString name) = 0;
    //悔棋
    virtual bool withdraw(Player_Color color) = 0;
    //复制board信息
    virtual void getBoard(Board* ui_board) = 0;

    //测试用
    virtual void print(){};
};

#endif // LOGIC_H

