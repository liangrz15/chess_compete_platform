#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include <QString>
#include <QMessageBox>
#include <QtNetwork>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QInputDialog>
#include <ctime>
#include <stdlib.h>
#include "draughts.h"
#include "mydraughts.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    void closeEvent(QCloseEvent * event);

    ~Dialog();

private slots:
    void on_close_clicked();
    void on_creatgame_clicked();
    void acceptConnection();
    void on_joingame_clicked();
    //-1为初始化为白方 -2为初始化为黑方 -3为对方认输
    ///-4请求求和 -5同意求和 -6拒绝求和 -7胜利
    void recvMessage();
    void writetosocket(int);


    void on_mydraughts_clicked();

private:
    Ui::Dialog *ui;
    draughts *d;
    mydraughts *md;
    QTcpServer  *listenSocket;
    QTcpSocket  *readWriteSocket;
};

#endif // DIALOG_H
