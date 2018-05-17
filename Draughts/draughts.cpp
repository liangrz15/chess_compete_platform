#include "draughts.h"
#include "ui_draughts.h"

draughts::draughts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::draughts),
    player(new QMediaPlayer),
    playlist(new QMediaPlaylist)
{
    ui->setupUi(this);
    this->setWindowTitle("Draughts");

    int i,j;
    for(i = 0;i < 10;i++)
    {
        for(j = 0;j < 10;j++)
        {
            if_move[i][j] = false;
            if_been_eaten[i][j] = false;
            if_will_been_eaten[i][j] = false;
            draughtsman[i][j] = 0;
        }
    }
    x = -1;
    y = -1;
    if_continue = false;
    turn = true;
    ifgameover = false;
    limit = 0;

    color = 1;  //先默认为黑色  
}

draughts::~draughts()
{
    delete ui;
}

void draughts::on_musicon_clicked()
{
    playlist->addMedia(QUrl::fromLocalFile("C:\\Users\\hp\\Desktop\\Draughts\\music.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    player->setPlaylist(playlist);
    player->setVolume(30);
    player->play();
}

void draughts::on_musicoff_clicked()
{
    player->stop();
}

void draughts::paintEvent(QPaintEvent *e)
{
    int i,j;
    QPainter painter(this);

    QPen pen_a(Qt::black,1);
    QPen pen_b(Qt::black,3);
    QPen pen_c(Qt::white,3);
    QPen pen_d(Qt::red,2);
    QBrush brush_a(Qt::gray);
    QBrush brush_b(Qt::black);
    QBrush brush_c(Qt::white);
    QFont font("Arial");
    font.setPixelSize(35);
    painter.setFont(font);

    //画格子
    for(i = 0;i < 10;i++)
    {
        for(j = 0;j < 10;j++)
        {
            if((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))
            {
                painter.setBrush(brush_a);
                painter.drawRect((i * 50) + 20,(j * 50) + 20,50,50);
            }
        }
    }

    //画线
    for(i = 0;i < 11;i++)
    {
        painter.setPen(pen_a);
        painter.drawLine(20 + (50 * i),20,20 + (50 * i),520);
        painter.drawLine(20,20 + (50 * i),520,20 + (50 * i));
    }

    //点击棋子后
    if((x != -1 && y != -1) && (draughtsman[x][y] * color) > 0)
    {
        painter.setPen(pen_d);
        painter.drawLine(20 + (50 * x),(y * 50) + 20,70 + (50 * x),(y * 50) + 20);
        painter.drawLine(20 + (50 * x),(y * 50) + 20,20 + (50 * x),(y * 50) + 70);
        painter.drawLine(70 + (50 * x),(y * 50) + 20,70 + (50 * x),(y * 50) + 70);
        painter.drawLine(20 + (50 * x),(y * 50) + 70,70 + (50 * x),(y * 50) + 70);

        for(i = 0;i < 10;i++)
        {
            for(j = 0;j < 10;j++)
            {
                if(if_move[i][j])
                {
                    painter.drawLine(20 + (50 * i),(j * 50) + 20,70 + (50 * i),(j * 50) + 20);
                    painter.drawLine(20 + (50 * i),(j * 50) + 20,20 + (50 * i),(j * 50) + 70);
                    painter.drawLine(70 + (50 * i),(j * 50) + 20,70 + (50 * i),(j * 50) + 70);
                    painter.drawLine(20 + (50 * i),(j * 50) + 70,70 + (50 * i),(j * 50) + 70);
                }
            }
        }
    }

    //画棋子
    for(i = 0;i < 10;i++)
    {
        for(j = 0;j < 10;j++)
        {
            if(draughtsman[i][j] > 0)   //黑棋
            {
                if(draughtsman[i][j] == 1)   //普通黑
                {
                    painter.setPen(pen_a);
                    painter.setBrush(brush_b);
                    painter.drawEllipse(25 + (i * 50),25 + (j * 50),40,40);
                }
                else    //黑王
                {
                    painter.setPen(pen_a);
                    painter.setBrush(brush_b);
                    painter.drawEllipse(25 + (i * 50),25 + (j * 50),40,40);
                    painter.setPen(pen_c);
                    painter.drawText(36 + (i * 50),58 + (j * 50),"+");
                }
            }
            if(draughtsman[i][j] < 0)
            {
                if(draughtsman[i][j] == -1)   //普通白
                {
                    painter.setPen(pen_c);
                    painter.setBrush(brush_c);
                    painter.drawEllipse(25 + (i * 50),25 + (j * 50),40,40);
                }
                else    //白王
                {
                    painter.setPen(pen_c);
                    painter.setBrush(brush_c);
                    painter.drawEllipse(25 + (i * 50),25 + (j * 50),40,40);
                    painter.setPen(pen_b);
                    painter.drawText(36 + (i * 50),58 + (j * 50),"+");
                }
            }
        }
    }
}

void draughts::mousePressEvent(QMouseEvent *e)
{
    if(e->x() > 20 && e->x() < 520 && e->y() > 20 && e->y() <520)
    {
        int i,j;
        i = (e->x()-20) / 50;
        j = (e->y()-20) / 50;

        if(draughtsman[i][j] != 0)    //点击的格子里有棋子
        {
            if(!if_continue)
            {
                if((draughtsman[i][j] * color) > 0)
                {
                    if((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))
                    {
                        x = i;
                        y = j;
                        checkmove();
                    }
                }
            }
            else
            {
                QMessageBox::information(this,"警告","必须继续吃子");
            }
        }
        else    //点击的格子里没有棋子
        {
            if(turn)
            {
                if(if_move[i][j])
                {
                    moveto(x,y,i,j);
                }
                else    //不合法的移动
                {
                    if(x != -1 && y != -1)
                    {
                        QMessageBox::information(this,"警告","不能这么移动");
                    }
                }
            }
        }
        this->update();
    }
}

void draughts::checkmove()
{           
    int i,j,u;
    clickchess = draughtsman[x][y];
    for(i = 0;i < 10;i++)
    {
        for(j = 0;j < 10;j++)
        {
            if_move[i][j] = false;
        }
    }

    if(draughtsman[x][y] == color)    //普通子
    {
        if(limit == 0)
        {


                if((x - 1) >= 0 && (y - 1) >= 0)
                {
                    if(draughtsman[x - 1][y - 1] == 0)
                    {
                       if_move[x - 1][y - 1] = true;
                    }
                }
                if((x + 1) < 10 && (y - 1) >= 0)
                {
                    if(draughtsman[x + 1][y - 1] == 0)
                    {
                       if_move[x + 1][y - 1] = true;
                    }
                }


        }

        if((x - 2) >= 0 && (y - 2) >= 0)
        {
            if((draughtsman[x - 1][y - 1] * color < 0 && if_been_eaten[x - 1][y - 1] == false) && draughtsman[x - 2][y - 2] == 0)
            {

                will_limit = 0;
                if_will_been_eaten[x - 1][y - 1] = true;
                getcaneat(x - 2,y - 2,0);
                if(will_limit == limit -1|| limit < 2)
                {
                    if_move[x - 2][y - 2] = true;
                }
                if_will_been_eaten[x - 1][y - 1] = false;
            }
        }
        if((x + 2) < 10 && (y - 2) >= 0)
        {
            if((draughtsman[x + 1][y - 1] * color < 0 && if_been_eaten[x + 1][y - 1] == false) && draughtsman[x + 2][y - 2] == 0)
            {
                will_limit = 0;
                if_will_been_eaten[x + 1][y - 1] = true;
                 getcaneat(x + 2,y - 2,0);
                if(will_limit == limit -1 || limit < 2)
                {
                    if_move[x + 2][y - 2] = true;
                }
                if_will_been_eaten[x + 1][y - 1] = false;
            }
        }
        if((x - 2) >= 0 && (y + 2) < 10)
        {
            if((draughtsman[x - 1][y + 1] * color < 0 && if_been_eaten[x - 1][y + 1] == false) && draughtsman[x - 2][y + 2] == 0)
            {
                will_limit = 0;
                if_will_been_eaten[x - 1][y + 1] = true;
                getcaneat(x - 2,y + 2,0);
                if(will_limit == limit -1|| limit < 2)
                {
                    if_move[x - 2][y + 2] = true;
                }
                if_will_been_eaten[x - 1][y + 1] = false;
            }
        }
        if((x + 2) < 10 && (y + 2) < 10)
        {
            if((draughtsman[x + 1][y + 1] * color < 0 && if_been_eaten[x + 1][y + 1] == false) && draughtsman[x + 2][y + 2] == 0)
            {
                will_limit = 0;
                if_will_been_eaten[x + 1][y + 1] = true;
                getcaneat(x + 2,y + 2,0);
                if(will_limit == limit -1|| limit < 2)
                {
                    if_move[x + 2][y + 2] = true;
                }
                if_will_been_eaten[x + 1][y + 1] = false;
            }
        }
    }
    if(draughtsman[x][y] == color * 2)  //王棋
    {
        i = 1;
        while((x - i) >= 0 && (y - i) >= 0)
        {
            if(draughtsman[x - i][y - i] == 0)
            {
                if(limit == 0)
                {
                    if_move[x - i][y - i] = true;
                }
            }
            else
            {
                i+= 1;
                if(draughtsman[x - (i - 1)][y - (i - 1)] * color < 0 && if_been_eaten[x - (i - 1)][y - (i - 1)] == false)
                {

                    u = i;
                    if_will_been_eaten[x - (u - 1)][y - (u - 1)] = true;
                    while((x - i) >= 0 && (y - i) >= 0)
                    {
                        if(draughtsman[x - i][y - i] == 0)
                        {
                            will_limit = 0;
                            getcaneat(x - i,y - i,0);
                            if(will_limit == limit - 1|| limit < 2)
                            {
                                if_move[x - i][y - i] = true;
                            }
                        }
                        else
                        {
                            break;
                        }
                        i+= 1;
                    }
                    if_will_been_eaten[x - (u - 1)][y - (u - 1)] = false;
                }
                break;
            }
            i+= 1;
        }

        i = 1;
        while((x - i) >= 0 && (y + i) < 10)
        {
            if(draughtsman[x - i][y + i] == 0)
            {
                if(limit == 0)
                {
                    if_move[x - i][y + i] = true;
                }
            }
            else
            {
                i+= 1;
                if(draughtsman[x - (i - 1)][y + (i - 1)] * color < 0 && if_been_eaten[x - (i - 1)][y + (i - 1)] == false)
                {

                    u = i;
                    if_will_been_eaten[x - (u - 1)][y + (u - 1)] = true;
                    while((x - i) >= 0 && (y + i) < 10)
                    {
                        if(draughtsman[x - i][y + i] == 0)
                        {
                            will_limit = 0;
                            getcaneat(x - i,y + i,0);
                            if(will_limit == limit - 1|| limit < 2)
                            {
                                if_move[x - i][y + i] = true;
                            }
                        }
                        else
                        {
                            break;
                        }
                        i+= 1;
                    }
                    if_will_been_eaten[x - (u - 1)][y + (u - 1)] = false;
                }
                break;
            }
            i+= 1;
        }

        i = 1;
        while((x + i) < 10 && (y - i) >= 0)
        {
            if(draughtsman[x + i][y - i] == 0)
            {
                if(limit == 0)
                {
                    if_move[x + i][y - i] = true;
                }
            }
            else
            {
                i+= 1;
                if(draughtsman[x + (i - 1)][y - (i - 1)] * color < 0 && if_been_eaten[x + (i - 1)][y - (i - 1)] == false)
                {

                    u = i;
                    if_will_been_eaten[x + (u - 1)][y - (u - 1)] = true;
                    while((x + i) < 10 && (y - i) >= 0)
                    {
                        if(draughtsman[x + i][y - i] == 0)
                        {
                            will_limit = 0;
                            getcaneat(x + i,y - i,0);
                            if(will_limit == limit - 1|| limit < 2)
                            {
                                if_move[x + i][y - i] = true;
                            }
                        }
                        else
                        {
                            break;
                        }
                        i+= 1;
                    }
                    if_will_been_eaten[x + (u - 1)][y - (u - 1)] = false;
                }
                break;
            }
            i+= 1;
        }

        i = 1;
        while((x + i) < 10 && (y + i) < 10)
        {
            if(draughtsman[x + i][y + i] == 0)
            {
                if(limit == 0)
                {
                    if_move[x + i][y + i] = true;
                }
            }
            else
            {
                i+= 1;
                if(draughtsman[x + (i - 1)][y + (i - 1)] * color < 0 && if_been_eaten[x + (i - 1)][y + (i - 1)] == false)
                {

                    u = i;
                    if_will_been_eaten[x + (u - 1)][y + (u - 1)] = true;
                    while((x + i) >= 0 && (y + i) < 10)
                    {
                        if(draughtsman[x + i][y + i] == 0)
                        {
                            will_limit = 0;
                            getcaneat(x + i,y + i,0);
                            if(will_limit == limit - 1|| limit < 2)
                            {
                                if_move[x + i][y + i] = true;
                            }
                        }
                        else
                        {
                            break;
                        }
                        i+= 1;
                    }
                    if_will_been_eaten[x + (u - 1)][y + (u - 1)] = false;
                }
                break;
            }
            i+= 1;
        }

    }
}

void draughts::checkmove(int m,int n,int k)
{
    int i,j;
    for(i = 0;i < 10;i++)
    {
        for(j = 0;j < 10;j++)
        {
            a[i][j][k] = false;
        }
    }

    if(clickchess == color)    //普通子
    {


            if((m - 1) >= 0 && (n - 1) >= 0)
            {
                if(draughtsman[m - 1][n - 1] == 0)
                {
                   can_move = true;
                }
            }
            if((m + 1) < 10 && (n - 1) >= 0)
            {
                if(draughtsman[m + 1][n - 1] == 0)
                {
                   can_move = true;
                }
            }



        if((m - 2) >= 0 && (n - 2) >= 0)
        {
            if(draughtsman[m - 1][n - 1] * color < 0 && if_will_been_eaten[m - 1][n - 1] == false && draughtsman[m - 2][n - 2] == 0 && if_been_eaten[m - 1][n - 1] == false)
            {

                a[m - 2][n - 2][k] = true;
            }
        }
        if((m + 2) < 10 && (n - 2) >= 0)
        {
            if(draughtsman[m + 1][n - 1] * color < 0 && if_will_been_eaten[m + 1][n - 1] == false && draughtsman[m + 2][n - 2] == 0 && if_been_eaten[m + 1][n - 1] == false)
            {
               a[m + 2][n - 2][k] = true;
            }
        }
        if((m - 2) >= 0 && (n + 2) < 10)
        {
            if(draughtsman[m - 1][n + 1] * color < 0 && if_will_been_eaten[m - 1][n + 1] == false && draughtsman[m - 2][n + 2] == 0 && if_been_eaten[m - 1][n + 1] == false)
            {
               a[m - 2][n + 2][k] = true;
            }
        }
        if((m + 2) < 10 && (n + 2) < 10)
        {
            if(draughtsman[m + 1][n + 1] * color < 0 && if_will_been_eaten[m + 1][n + 1] == false && draughtsman[m + 2][n + 2] == 0 && if_been_eaten[m + 1][n + 1] == false)
            {
               a[m + 2][n + 2][k] = true;
            }
        }
    }
    if(clickchess == color * 2)  //王棋
    {
        i = 1;
        while((m - i) >= 0 && (n - i) >= 0)
        {
            if(draughtsman[m - i][n - i] == 0)
            {
                can_move = true;
            }
            else
            {
                i+= 1;
                if(draughtsman[m - (i - 1)][n - (i - 1)] * color < 0 && if_will_been_eaten[m - (i - 1)][n - (i - 1)] == false && if_been_eaten[m - (i - 1)][n - (i - 1)] == false)
                {
                    while((m - i) >= 0 && (n - i) > 0)
                    {
                        if(draughtsman[m - i][n - i] == 0)
                        {
                            a[m - i][n - i][k] = true;
                        }
                        else
                        {
                            break;
                        }
                        i+= 1;
                    }
                }
                break;
            }
            i+= 1;
        }


        i = 1;
        while((m - i) >= 0 && (n + i) < 10)
        {
            if(draughtsman[m - i][n + i] == 0)
            {
                can_move = true;
            }
            else
            {
                i+= 1;
                if(draughtsman[m - (i - 1)][n + (i - 1)] * color < 0 && if_will_been_eaten[m - (i - 1)][n + (i - 1)] == false && if_been_eaten[m - (i - 1)][n + (i - 1)] == false)
                {
                    while((m - i) >= 0 && (n + i) < 10)
                    {
                        if(draughtsman[m - i][n + i] == 0)
                        {
                            a[m - i][n + i][k] = true;
                        }
                        else
                        {
                            break;
                        }
                        i+= 1;
                    }
                }
                break;
            }
            i+= 1;
        }

        i = 1;
        while((m + i) < 10 && (n - i) >= 0)
        {
            if(draughtsman[m + i][n - i] == 0)
            {
                can_move = true;
            }
            else
            {
                i+= 1;
                if(draughtsman[m + (i - 1)][n - (i - 1)] * color < 0 && if_will_been_eaten[m + (i - 1)][n - (i - 1)] == false && if_been_eaten[m + (i - 1)][n - (i - 1)] == false)
                {
                    while((m + i) < 10 && (n - i) >= 0)
                    {
                        if(draughtsman[m + i][n - i] == 0)
                        {
                            a[m + i][n - i][k] = true;
                        }
                        else
                        {
                            break;
                        }
                        i+= 1;
                    }
                }
                break;
            }
            i+= 1;
        }

        i = 1;
        while((m + i) < 10 && (n + i) < 10)
        {
            if(draughtsman[m + i][n + i] == 0)
            {
                can_move = true;
            }
            else
            {
                i+= 1;
                if(draughtsman[m + (i - 1)][n + (i - 1)] * color < 0 && if_will_been_eaten[m + (i - 1)][n + (i - 1)] == false && if_been_eaten[m + (i - 1)][n + (i - 1)] == false)
                {
                    while((m + i) < 10 && (n + i) < 10)
                    {
                        if(draughtsman[m + i][n + i] == 0)
                        {
                            a[m + i][n + i][k] = true;
                        }
                        else
                        {
                            break;
                        }
                        i+= 1;
                    }
                }
                break;
            }
            i+= 1;
        }


    }
}

void draughts::getcaneat(int m,int n,int k)
{
    int i,j;
    int p,q;
    p = m;
    q = n;
    if(k > will_limit)
    {
        will_limit = k;
    }

    checkmove(m,n,k);
    for(i = 0;i < 10;i++)
    {
        for(j = 0;j < 10;j++)
        {
            if(a[i][j][k])
            {
                m = p;
                n = q;
                while(m != i)   //吃子
                {
                    if((i - m) > 0)
                    {
                        if((j - n) > 0)
                        {
                            m+= 1;
                            n+= 1;
                            if(m != i)
                            {
                                if_will_been_eaten[m][n] = true;
                            }
                        }
                        else
                        {
                            m+= 1;
                            n-= 1;
                            if(m != i)
                            {
                                if_will_been_eaten[m][n] = true;
                            }
                        }
                    }
                    else
                    {
                        if((j - n) > 0)
                        {
                            m-= 1;
                            n+= 1;
                            if(m != i)
                            {
                                if_will_been_eaten[m][n] = true;
                            }
                        }
                        else
                        {
                            m-= 1;
                            n-= 1;
                            if(m != i)
                            {
                                if_will_been_eaten[m][n] = true;
                            }
                        }
                    }
                }


                getcaneat(i,j,k + 1);

                m = p;
                n = q;

                while(m != i)   //吐子
                {
                    if((i - m) > 0)
                    {
                        if((j - n) > 0)
                        {
                            m+= 1;
                            n+= 1;
                            if(m != i)
                            {
                                if_will_been_eaten[m][n] = false;
                            }
                        }
                        else
                        {
                            m+= 1;
                            n-= 1;
                            if(m != i)
                            {
                                if_will_been_eaten[m][n] = false;
                            }
                        }
                    }
                    else
                    {
                        if((j - n) > 0)
                        {
                            m-= 1;
                            n+= 1;
                            if(m != i)
                            {
                                if_will_been_eaten[m][n] = false;
                            }
                        }
                        else
                        {
                            m-= 1;
                            n-= 1;
                            if(m != i)
                            {
                                if_will_been_eaten[m][n] = false;
                            }
                        }
                    }
                }
            }
        }
    }
}


void draughts::if_next_limit()
{
    int i,j;
    limit = 0;
    for(i = 0;i < 10;i++)
    {
        for(j = 0;j < 10;j++)
        {
            if(draughtsman[i][j] * color > 0)
            {
                clickchess = draughtsman[i][j];
                will_limit = 0;
                getcaneat(i,j,0);
                if(will_limit > limit)
                {
                    limit = will_limit;
                }
            }
        }
    }
}

void draughts::moveto(int m,int n,int i,int j)  //只能判断自己的棋子是否变成王 判断对面需要在网络部分实现
{
    int p,q;
    p = m;
    q = n;
    while(m != i)   //吃子
    {
        if((i - m) > 0)
        {
            if((j - n) > 0)
            {
                m+= 1;
                n+= 1;
                if(m != i)
                {
                    if_been_eaten[m][n] = true;
                }
            }
            else
            {
                m+= 1;
                n-= 1;
                if(m != i)
                {
                    if_been_eaten[m][n] = true;
                }
            }
        }
        else
        {
            if((j - n) > 0)
            {
                m-= 1;
                n+= 1;
                if(m != i)
                {
                    if_been_eaten[m][n] = true;
                }
            }
            else
            {
                m-= 1;
                n-= 1;
                if(m != i)
                {
                    if_been_eaten[m][n] = true;
                }
            }
        }
    }

    draughtsman[i][j] = draughtsman[p][q];
    draughtsman[p][q] = 0;

    if(turn)
    {
        if(limit > 1)
        {
            limit-= 1;
            x = i;
            y = j;
            checkmove();
            if_continue = true;
            write((1000 * p) + (100 * q) + (10 * i) + j);
        }
        else
        {
            if(j == 0)
            {
                draughtsman[i][j] = 2 * color;
            }
            clearborad();
            if_continue = false;
            x = -1;
            y = -1;
            turn = false;
            write(10000 + (1000 * p) + (100 * q) + (10 * i) + j);
        }
    }

    this->update();
}

void draughts::clearborad()
{
    int i,j;
    turn = true;
    for(i = 0;i < 10;i++)
    {
        for(j = 0;j < 10;j++)
        {
            if(if_been_eaten[i][j])
            {
                draughtsman[i][j] = 0;
                if_been_eaten[i][j] = false;
            }
        }
    }
}

void draughts::if_finish()
{
    int i,j;
    bool a = false;
    for(i = 0;i < 10;i++)
    {
        for(j = 0;j < 10;j++)
        {
            if(draughtsman[i][j] * color > 0)
            {
                checkmove(i,j,0);
                if(if_move)
                {
                    a = true;
                    break;
                }
            }
        }
        if(a)
        {
            break;
        }
    }
    if(!a)
    {
        turn = false;
        QMessageBox::information(this,"LOSE","YOU LOSE");
        ifgameover = true;
        write(-7);
    }
}

void draughts::putchess(int k)
{
    int i;
    if(k == 1)
    {
         for(i = 0;i < 5;i++)
         {
             draughtsman[2*i][1] = -1;
             draughtsman[2*i][3] = -1;
             draughtsman[2*i][7] = 1;
             draughtsman[2*i][9] = 1;
             draughtsman[2*i + 1][0] = -1;
             draughtsman[2*i + 1][2] = -1;
             draughtsman[2*i + 1][6] = 1;
             draughtsman[2*i + 1][8] = 1;
         }
         color = 1;
         turn = true;
         this->update();
         QMessageBox::information(this,"注意","注意你执黑子");
    }
    if(k == -1)
    {
         for(i = 0;i < 5;i++)
         {
             draughtsman[2*i][1] = 1;
             draughtsman[2*i][3] = 1;
             draughtsman[2*i][7] = -1;
             draughtsman[2*i][9] = -1;
             draughtsman[2*i + 1][0] = 1;
             draughtsman[2*i + 1][2] = 1;
             draughtsman[2*i + 1][6] = -1;
             draughtsman[2*i + 1][8] = -1;
         }
         color = -1;
         turn = false;
         this->update();
         QMessageBox::information(this,"注意","注意你执白子");
    }
    if_next_limit();
}

void draughts::write(int n)
{
    emit number(n);
}

void draughts::on_giveup_clicked()
{
    if(!ifgameover)
    {
        write(-3);
        turn = false;
        ifgameover = true;
        QMessageBox::information(this,"LOSE","YOU LOSE");
    }
}

void draughts::oppositegiveup()
{
    turn = false;
    ifgameover = true;
    QMessageBox::information(this,"WIN","The other side gives up");
}

void draughts::on_peace_clicked()
{
    if(!ifgameover)
    {
        write(-4);
        QMessageBox::information(this,"Please wait","Request sent");
    }
}

void draughts::ifpeace()
{
    QMessageBox::StandardButton rb = QMessageBox::question(NULL, "Armistice request ", "Do you agree? ", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(rb == QMessageBox::Yes)
    {
        turn = false;
        ifgameover = true;
        QMessageBox::information(this,"Draw","It ends in a draw");
        write(-5);
    }
    else
    {
        write(-6);
    }
}

void draughts::agreepeace()
{
    turn = false;
    ifgameover = true;
    QMessageBox::information(this,"Draw","The other side agreed to a tie");
}

void draughts::disagreepeace()
{
    QMessageBox::information(this,"Warning","The other side doesn't agree with the draw");
}

void draughts::youwin()
{
    turn = false;
    ifgameover = true;
    QMessageBox::information(this,"WIN","YOU WIN");
}

void draughts::turntoking(int i,int j)
{
    draughtsman[i][j] = -2 * color;
    this->update();
}
