#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(test_Input()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(test_Input()));
    //QObject::connect(this->uiInput, SIGNAL())
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test_Display(int x, int y){
    qDebug() << x << " " << y;
    ui->label->setText(QString::number(x));
    ui->label_2->setText(QString::number(y));
}

void MainWindow::test_Input(){
    uiInput->getInput(2,2);
}
