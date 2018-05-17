#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    d(new draughts),
    md(new mydraughts)
{
    ui->setupUi(this);

    this->setWindowTitle("Draughts");

    QString localName = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localName);
    QString localip;
    foreach(QHostAddress address,info.addresses())
    {
         if(address.protocol() == QAbstractSocket::IPv4Protocol)

         localip = address.toString();
    }
    ui->yourip->setText(localip);

    connect(d,SIGNAL(number(int)),this,SLOT(writetosocket(int)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_creatgame_clicked()
{
   QString Dk;
   int dk;
   Dk = ui->yourdk->text();
   dk = Dk.toInt();

   this->listenSocket = new QTcpServer;
   this->listenSocket->listen(QHostAddress::Any,dk);
   QObject::connect(this->listenSocket,SIGNAL(newConnection()),this,SLOT(acceptConnection()));


   this->hide();
   d->show();
   d->exec();
   this->show();
}

void Dialog::on_close_clicked()
{
    this->close();
}

void Dialog::closeEvent(QCloseEvent *e)
{
    int ret = QMessageBox::warning(0, tr("Draughts"), tr("您真的想要退出？"), QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes)
    {
        e->accept(); //确认退出
    }
    else
    {
        e->ignore(); //继续玩
    }
}

void Dialog::on_joingame_clicked()
{
    bool a;
    QString Hostip = QInputDialog::getText(NULL, tr("请输入主机IP"),tr("IP:"),QLineEdit::Normal,"",&a);
    QString Hostdk = QInputDialog::getText(NULL, tr("请输连接端口"),tr("端口:"),QLineEdit::Normal,"",&a);
    int dk = Hostdk.toInt();

    this->readWriteSocket = new QTcpSocket;
    this->readWriteSocket->connectToHost(QHostAddress(Hostip),dk);
    QObject::connect(this->readWriteSocket,SIGNAL(readyRead()),this,SLOT(recvMessage()));

    this->hide();
    d->show();
    d->exec();
    this->show();
}

void Dialog::acceptConnection()
{
    this->readWriteSocket =this->listenSocket->nextPendingConnection();
    QObject::connect(this->readWriteSocket,SIGNAL(readyRead()),this,SLOT(recvMessage()));

    srand((unsigned)time(0));
    int i;
    i = rand() % 2;
    if(i == 0)
    {
        d->putchess(1);

        QByteArray *array =new QByteArray;
        array->clear();
        array->append("-1");
        this->readWriteSocket->write(array->data());
    }
    else
    {
        d->putchess(-1);

        QByteArray *array =new QByteArray;
        array->clear();
        array->append("-2");
        this->readWriteSocket->write(array->data());
    }
}

void Dialog::recvMessage()
{
    QString info;
    info = this->readWriteSocket->readAll();
    int k;
    k = info.toInt();
    if(k == -1)
    {
        d->putchess(-1);
    }
    if(k == -2)
    {
        d->putchess(1);
    }
    if(k == -3)
    {
        d->oppositegiveup();
    }
    if(k == -4)
    {
        d->ifpeace();
    }
    if(k == -5)
    {
        d->agreepeace();
    }
    if(k == -6)
    {
        d->disagreepeace();
    }
    if(k == -7)
    {

    }
    if(k > 0)
    {
        int m,n,i,j;
        j = k % 10;
        k-= j;
        k/= 10;
        i = k % 10;
        k-= i;
        k/= 10;
        n = k % 10;
        k-= n;
        k/= 10;
        m = k % 10;
        k-= m;
        k/= 10;

        if(k == 1)
        {
            d->moveto(9 - m,9 - n,9 - i,9 - j);
            if(j == 0)
            {
                d->turntoking(9 - i,9 - j);
            }
            d->clearborad();
            d->if_finish();
            d->if_next_limit();
        }
        else
        {
            d->moveto(9 - m,9 - n,9 - i,9 - j);
        }
    }
}

void Dialog::writetosocket(int n)
{
    QString number;
    number = QString::number(n);

    QByteArray *array =new QByteArray;
    array->clear();
    array->append(number);
    this->readWriteSocket->write(array->data());
}

void Dialog::on_mydraughts_clicked()
{
    this->hide();
    md->show();
    md->exec();
    this->show();
}
