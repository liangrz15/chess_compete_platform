#ifndef BOARD_H
#define BOARD_H
#include "player_color.h"

//从左下开始 0开始 x横轴 y竖轴
class Board{
private:
    int M,N;
    Player_Color** chess_board;
public:
    Board(int _M,int _N):M(_M),N(_N){
        chess_board = new Player_Color*[M];
        for(int i = 0; i < M; i++){
            chess_board[i] = new Player_Color[N];
        }
    }

    ~Board(){
        for(int i = 0; i < M; i++){
            delete[] chess_board[i];
        }
        delete[] chess_board;
    }

    Player_Color& get_color(int x,int y){
        return chess_board[x][y];
    }

    int getWidth(){return M;}
    int getHeight(){return N;}
};

#endif // BOARD_H

