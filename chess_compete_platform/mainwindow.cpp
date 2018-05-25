#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mapper = nullptr;
    cell_size = 50;
    cell_spacing = 10;
    left_padding = 10;
    top_padding = 10;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::generateBoard(int width, int height){
    if(mapper){
        delete mapper;
    }
    mapper = new QSignalMapper(this);
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(handleClick(int)));
    while(!this->cells.empty()){
        int last_index = this->cells.size() - 1;
        while(!this->cells[last_index].empty()){
            ClickableButton* cell = this->cells[last_index][this->cells[last_index].size() - 1];
            delete cell;
            this->cells[last_index].pop_back();
        }
        this->cells.pop_back();
    }
    this->cells.resize(width);
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            ClickableButton* cell = new ClickableButton(this);
            cell->setGeometry(this->left_padding + i * (this->cell_size + this->cell_spacing),
                              this->top_padding + j * (this->cell_size + this->cell_spacing),
                              this->cell_size,
                              this->cell_size);
            cell->setText("Hi");
            this->cells[i].push_back(cell);
            mapper->setMapping(cells[i][j], i * height + j);
            connect(cells[i][j], SIGNAL(clicked()), mapper, SLOT(map()));
        }
    }
    this->width = width;
    this->height = height;
}

void MainWindow::handleClick(int index){
    int x = index / height;
    int y = index % height;
    this->uiInput->getInput(x, height - 1 - y);
}

void MainWindow::setColor(int x, int y, Player_Color color){
    y = height - 1 - y;
    if(x < 0 || x >= width || y < 0 || y >= height){
        return;
    }
    ClickableButton* cell = this->cells[x][y];
    switch(color){
    case Player_Color::Black:
        cell->setText("B");
        break;
    case Player_Color::White:
        cell->setText("W");
        break;
    default:
        cell->setText("N");
    }
}
