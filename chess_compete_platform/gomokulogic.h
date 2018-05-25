#ifndef GOMOKULOGIC
#define GOMOKULOGIC

#include "logic.h"
#include "board.h"
#include <QString>
#include <QVector>

//9x9 五子棋
class GomokuLogic : public Logic{
private:
    Board *board;
    int black_num,white_num; //记录黑白棋分别走的步数
    QVector<int> where; //记录历史的落子位置 按xyxyxyxy。。。
    QVector<Player_Color> color_order; //记录落子的顺序
public:
    ~GomokuLogic();
    GomokuLogic();

    int isVaild(int x, int y, int color) override;
    Player_Color win_tie() override;
    void play_chess(int x, int y, Player_Color color) override;
    bool isEnd() override;
    void save(QString name) override;
    Player_Color load(QString name) override; //返回下一个下棋的人时默认每回合都换色下棋
    bool withdraw(Player_Color color) override;
    void getBoard(Board* ui_board) override;

    //测试用
    void print(){board->print();}
};

#endif // GOMOKULOGIC

