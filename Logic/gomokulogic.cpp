#include "gomokulogic.h"
#include <iostream>
#include <QVector>
#include <QString>
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QtCore/QIODevice>


using namespace std;

GumokuLogic::GumokuLogic()
{
    board = new Board(9,9);
    black_num = white_num = 0;
    where.clear();
    color_order.clear();
}

GumokuLogic::~GumokuLogic()
{
    delete board;
}

int GumokuLogic::isVaild(int x, int y, int color)
{
    if(x >= 0 && x < 9 && y >= 0 && y < 9)
    {
        if(board->get_color(x,y) == none)
        {
            return true;
        }
    }
    return false;
}

Player_Color GumokuLogic::win_tie()
{
    int direction[4][2] = {{1,0},{0,1},{1,1},{1,-1}};
    Player_Color player;
    int i,j,x,y,dir,length;

    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            player = board->get_color(i,j);
            if(player != none)
            {
                for(dir = 0; dir < 4; dir++)
                {
                    length = 0;
                    x = i;
                    y = j;
                    while(x >= 0 && x < 9 && y >= 0 && y < 9)
                    {
                        if(board->get_color(x,y) == player)
                        {
                            length += 1;
                            if(length == 5)
                            {
                                return player;
                            }
                            x += direction[dir][0];
                            y += direction[dir][1];
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
    return none;
}

void GumokuLogic::play_chess(int x, int y, Player_Color color, Board *ui_board)
{
    if(ui_board != nullptr)
    {
        ui_board->set_color(x,y,color);
    }
    board->set_color(x,y,color);
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

bool GumokuLogic::isEnd()
{
    if(win_tie() != none)
    {
        return true;
    }
    else
    {
        if((white_num + black_num) == 81)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void GumokuLogic::save(QString name)
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

Player_Color GumokuLogic::load(QString name)
{
    int i;
    Player_Color temp_color;
    int temp_c,temp_x,temp_y;
    Board* new_board = new Board(9,9);
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
        new_board->set_color(temp_x,temp_y,temp_color);
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

bool GumokuLogic::withdraw(Player_Color color)
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
    Board* new_board = new Board(9,9);
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
            white_num -=1;
        }
    }
    for(i = 0;i < (black_num + white_num);i++)
    {
        new_board->set_color(where[2 *i],where[(2 *i) + 1],color_order[i]);
    }
    delete board;
    board = new_board;

    return true;
}
