#ifndef MYDRAUGHTS_H
#define MYDRAUGHTS_H

#include <QDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QMessageBox>

namespace Ui {
class mydraughts;
}

class mydraughts : public QDialog
{
    Q_OBJECT

public:
    explicit mydraughts(QWidget *parent = 0);
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void moveto(int,int,int,int);   //移动棋子 起始xy ij是结束
    void if_finish();   //判断游戏是否结束
    void if_next_limit();   //下一回合走棋是否受限制
    void clearborad();
    ~mydraughts();

private slots:
    void on_musicon_clicked();
    void on_musicoff_clicked();
    void on_delete_2_clicked();
    void on_black_clicked();
    void on_blackking_clicked();
    void on_white_clicked();
    void on_whiteking_clicked();
    void on_blackstart_clicked();
    void on_whitestart_clicked();

private:
    int chess;
    int clickchess;
    bool a[10][10][10];
    Ui::mydraughts *ui;
    bool if_move[10][10];   //选中棋子可移动的位置
    bool can_move;      //某颗棋子是否能移动 在checkmove中判断
    int limit;      //下一步吃子最多数
    int will_limit;
    bool if_continue;   //是否必须连跳
    int draughtsman[10][10];    //1为普通黑 2为黑王 0为空 -1为普通白 -2为白王
    int color;  //代表你的颜色 1为黑 -1为白
    bool turn;   //代表回合 true为你的 false为对方回合
    int x,y;    //选中棋子的坐标
    void checkmove();
    void checkmove(int,int,int);
    void getcaneat(int,int,int);
    bool if_been_eaten[10][10]; //用于clearboard
    bool if_will_been_eaten[10][10]; //在getcaneat中记录一个格子中棋子是否被吃过
    bool ifgameover;    //记录一局游戏是否结束
};

#endif // MYDRAUGHTS_H
