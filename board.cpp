#include "board.h"
#include "player_color.h"
#include <iostream>

using namespace std;

Board::Board(int _M,int _N)
{
    int i,j;
    //M 为x轴长度，N为y轴长度
    M = _M;
    N = _N;

    chess_board = new Player_Color*[M];
    for(i = 0;i < M;i++)
    {
        chess_board[i] = new Player_Color[N];
        for(j = 0;j < N;j++)
        {
            chess_board[i][j] = none;
        }
    }
}

Board::~Board()
{
    int i;
    for(i = 0;i < M;i++)
    {
        delete[] chess_board[i];
    }
    delete[] chess_board;
}

Player_Color Board::get_color(int x,int y)
{
    if(x >= 0 && x < M && y >= 0 && y < N)
    {
        return chess_board[x][y];
    }
    else
    {
        return none;
    }
}

bool Board::set_color(int x,int y,Player_Color color)
{
    if(x >= 0 && x < M && y >= 0 && y < N)
    {
        chess_board[x][y] = color;
        return true;
    }
    else
    {
        return false;
    }
}

void Board::print()
{
    int i,j;
    for(i = 0;i < N;i++)
    {
        for(j = 0;j < M;j++)
        {
            if(chess_board[j][i] == Black)
            {
                cout << "B";
            }
            else if(chess_board[j][i] == White)
            {
                cout << "W";
            }
            else
            {
                cout << "N";
            }
        }
        cout << endl;
    }
}
