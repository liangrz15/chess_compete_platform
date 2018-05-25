#include "reversilogic.h"
#include <iostream>
#include <QVector>
#include <QString>
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QtCore/QIODevice>

using namespace std;

ReversiLogic::ReversiLogic()
{
    board = new Board(8,8);
    black_num = white_num = 0;
    where.clear();
    color_order.clear();
    initboard(board);
}

ReversiLogic::~ReversiLogic()
{
    delete board;
}

void ReversiLogic::initboard(Board *new_board)
{
    new_board->set_color(3,3,Black);
    new_board->set_color(4,4,Black);
    new_board->set_color(3,4,White);
    new_board->set_color(4,3,White);
}

void ReversiLogic::changboard(int x, int y,Player_Color color,Board* _board)
{
    int direction[8][2] = {{1,0},{0,1},{-1,0},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}};
    int i,j,dir,length; //坐标（i，j)代表访问到的地方

    _board->set_color(x,y,color);
    for(dir = 0;dir < 8;dir++)
    {
        length = 0;
        i = x;
        j = y;
        while(1)
        {
            i += direction[dir][0];
            j += direction[dir][1];
            if(i >= 0 && i < 8 && j >= 0 && j < 8)
            {
                if(_board->get_color(i,j) == none)
                {
                    break;
                }
                else if(_board->get_color(i,j) == color)
                {
                    if(length != 0)
                    {
                        while(length != 0)
                        {
                            length -= 1;
                            i -= direction[dir][0];
                            j -= direction[dir][1];
                            _board->set_color(i,j,color);
                        }
                        break;
                    }
                }
                else
                {
                    length += 1;
                }
            }
            else
            {
                break;
            }
        }
    }
}

int ReversiLogic::isVaild(int x, int y, int color)
{
    int direction[8][2] = {{1,0},{0,1},{-1,0},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}};
    int i,j,dir,length; //坐标（i，j)代表访问到的地方
    bool flag = false;

    if(x >= 0 && x < 8 && y >= 0 && y < 8)
    {
        if(board->get_color(x,y) == none)
        {
            for(dir = 0;dir < 8;dir++)
            {
                length = 0;
                i = x;
                j = y;
                while(1)
                {
                    i += direction[dir][0];
                    j += direction[dir][1];
                    if(i >= 0 && i < 8 && j >= 0 && j < 8)
                    {
                        if(board->get_color(i,j) == none)
                        {
                            break;
                        }
                        else if(board->get_color(i,j) == color)
                        {
                            if(length != 0)
                            {
                                flag = true;
                            }
                            break;
                        }
                        else
                        {
                            length += 1;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }
    return flag;
}

Player_Color ReversiLogic::win_tie()
{
    int cnt_Black,cnt_White;
    int i,j;
    if(isEnd())
    {
        cnt_Black = cnt_White = 0;
        for(i = 0;i < 8;i++)
        {
            for(j = 0;j < 8;j++)
            {
                if(board->get_color(i,j) == Black)
                {
                    cnt_Black += 1;
                }
                else
                {
                    if(board->get_color(i,j) == White)
                    {
                        cnt_White += 1;
                    }
                }
            }
        }
        if(cnt_Black > cnt_White)
        {
            return Black;
        }
        else if(cnt_Black < cnt_White)
        {
            return White;
        }
        else
        {
            return tie;
        }
    }
    else
    {
        return none;
    }
}

void ReversiLogic::play_chess(int x, int y, Player_Color color)
{
    changboard(x,y,color,board);
    color_order.push_back(color);
    where.push_back(x);
    where.push_back(y);
    if(color == Black)
    {
        black_num += 1;
    }
    else
    {
        white_num += 1;
    }
}

bool ReversiLogic::isEnd()
{
    int i,j;
    for(i = 0;i < 8;i++)
    {
        for(j = 0;j < 8;j++)
        {
            if(isVaild(i,j,Black) || isVaild(i,j,White))
            {
                return false;
            }
        }
    }
    return true;
}

void ReversiLogic::save(QString name)
{
    int i;
    QFile file(name);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&file);
    out << black_num << endl;
    out << white_num << endl;

    //按照 颜色 x y为一行输出
    for(i = 0;i < (black_num + white_num);i++)
    {
        out << color_order[i] << " ";
        out << where[2 *i] << " " << where[(2 * i) + 1] << endl;
    }

    out.flush();
    file.close();
}

Player_Color ReversiLogic::load(QString name)
{
    int i;
    Player_Color temp_color;
    int temp_c,temp_x,temp_y;
    Board* new_board = new Board(8,8);
    initboard(new_board);
    QFile file(name);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);

    where.clear();
    color_order.clear();
    in >> black_num >> white_num;
    for(i = 0;i < (black_num + white_num);i++)
    {
        in >> temp_c >> temp_x >> temp_y;
        temp_color = (Player_Color)temp_c;
        color_order.push_back(temp_color);
        where.push_back(temp_x);
        where.push_back(temp_y);
        changboard(temp_x,temp_y,temp_color,new_board);
    }
    delete board;
    board = new_board;

    in.flush();
    file.close();

    if(temp_color == Black)
    {
        return White;
    }
    else
    {
        return Black;
    }
}

bool ReversiLogic::withdraw(Player_Color color)
{
    if(color == Black)
    {
        if(black_num == 0)
        {
            return false;
        }
    }
    else if(color == White)
    {
        if(white_num == 0)
        {
           return false;
        }
    }
    else
    {
        return false;
    }
    Board* new_board = new Board(8,8);
    initboard(new_board);
    Player_Color temp;
    bool end = false;
    int i;

    while(!end)
    {
        temp = color_order.back();
        if(temp == color)
        {
            end = true;
        }
        color_order.pop_back();
        where.pop_back();
        where.pop_back();
        if(temp == Black)
        {
            black_num -= 1;
        }
        else
        {
            white_num -= 1;
        }
    }
    for(i = 0;i < (black_num + white_num);i++)
    {
        changboard(where[2 *i],where[(2 *i) + 1],color_order[i],new_board);
    }
    delete board;
    board = new_board;

    return true;
}

void ReversiLogic::getBoard(Board* ui_board)
{
    int i,j;
    Player_Color temp;
    for(i = 0;i < 8;i++)
    {
        for(j = 0;j < 8;j++)
        {
            temp = board->get_color(i,j);
            ui_board->set_color(i,j,temp);
        }
    }
}


void ReversiLogic::print()
{
    int i,j;
    for(j = 0;j < 8;j++)
    {
        for(i = 0;i < 8;i++)
        {
            if(board->get_color(i,j) == Black)
            {
                cout << "B";
            }
            else if(board->get_color(i,j) == White)
            {
                cout << "W";
            }
            else
            {
                if(isVaild(i,j,Black) && (!isVaild(i,j,White)))
                {
                    cout << "0";
                }
                else if((!isVaild(i,j,Black)) && isVaild(i,j,White))
                {
                    cout << "1";
                }
                else if(isVaild(i,j,Black) && isVaild(i,j,White))
                {
                    cout << "3";
                }
                else
                {
                    cout << ".";
                }
            }
        }
        cout << endl;
    }
}
