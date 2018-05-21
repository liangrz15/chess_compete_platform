#ifndef NAIVELOGIC_H
#define NAIVELOGIC_H
#include"logic.h"
class NaiveLogic: public Logic{
private:
    int lastX;
    int lastY;
public:
    NaiveLogic():lastX(0), lastY(0){}
    //判断某子是否能在（x,y）点，能返回true 反之false
    int isVaild(int x,int y,int color){return true;}

    Player_Color win_tie(){return Player_Color::none;}
    //此时x,y要为合法的落子点
    void play_chess(int x,int y,Board* last_board,Player_Color color){
        last_board->get_color(lastX++, lastY++) = Player_Color::Black;
    }

    //若已经结束则true 反之false
    bool isEnd(){return false;}
    //保存存档
    void save(QString name){}
    //读取存档
    void load(QString name){}
    //悔棋
    bool withdraw(Player_Color color){return false;}
};

#endif // NAIVELOGIC_H
