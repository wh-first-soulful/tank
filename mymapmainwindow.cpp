#include "mymapmainwindow.h"
#include "ui_mymapmainwindow.h"
#include "parameters.h"
#include "tankwar.h"
#include "subwindow.h"

MymapMainWindow::MymapMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MymapMainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("地图编辑器");
    black.load(":/pic/black.png");
    brick.load(":/pic/brick.jpg");
    brick2.load(":/pic/brick2.png");
    forest.load(":/pic/forest.jpg");
    sea2.load(":/pic/sea2.jpg");
    star.load(":/pic/brain.jpg");
    click.load(":/pic/click.png");
    pre_mouseposition_x = -1;
    pre_mouseposition_y = -1;
}

MymapMainWindow::~MymapMainWindow()
{
    delete ui;
}

void MymapMainWindow::paintEvent(QPaintEvent *event)
{
    painter.begin(this);
    for(int i=0;i<WIDTH;i++)
    {
        for(int j=0;j<LENGTH;j++)
        {
            switch(Mymap::mymap[i * LENGTH + j])
            {
            case EMPTY:
                painter.drawPixmap(30*j,30*i,30,30,black);
                break;
            case BRICK_WALL:
                painter.drawPixmap(30*j,30*i,30,30,brick);
                break;
            case STEEL_WALL:
                painter.drawPixmap(30*j,30*i,30,30,brick2);
                break;
            case FOREST:
                painter.drawPixmap(30*j,30*i,30,30,forest);
                break;
            case SEA:
                painter.drawPixmap(30*j,30*i,30,30,sea2);
                break;
            case STAR:
                if(j==LENGTH/2-1&&i==WIDTH-3)
                    painter.drawPixmap(30*j, 30*i, 60, 60,star);
                break;
            case CLICK:
                painter.drawPixmap(30*j,30*i,30,30,click);
                break;
            }
        }
    }
    painter.end();
}

void MymapMainWindow::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        mouseposition_x = ev -> x();
        mouseposition_y = ev -> y();
        mouseposition_x = mouseposition_x / 30;
        mouseposition_y = mouseposition_y / 30;
        if(mouseposition_x == 0 ||mouseposition_x == LENGTH - 1||mouseposition_y == 0 ||mouseposition_y == WIDTH - 1)
        {
            Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] = BRICK_WALL;
        }
        else if(Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] == STAR)
        {
            Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] = STAR;
        }
        else if(mouseposition_x < LENGTH - 1 && mouseposition_x > 0 && ispermitted(mouseposition_x,mouseposition_y))
        {
            if(pre_mouseposition_x != -1 && pre_mouseposition_y != -1 && Mymap::mymap[pre_mouseposition_y * LENGTH + pre_mouseposition_x] == CLICK)
            {
                Mymap::mymap[pre_mouseposition_y * LENGTH + pre_mouseposition_x] = EMPTY;
            }
            ui -> label_2 -> setText("");
            Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] = CLICK;
        }
        else if(ispermitted(mouseposition_x,mouseposition_y) == false)
        {
            if(pre_mouseposition_x != -1 && pre_mouseposition_y != -1 && Mymap::mymap[pre_mouseposition_y * LENGTH + pre_mouseposition_x] == CLICK)
            {
                Mymap::mymap[pre_mouseposition_y * LENGTH + pre_mouseposition_x] = EMPTY;
            }
            ui -> label_2 -> setText("此处不能放置方块！");
            QFont font = ui -> label_2 -> font();
            font.setPointSize(14);
            ui -> label_2 ->setFont(font);
        }
        pre_mouseposition_x = mouseposition_x;
        pre_mouseposition_y = mouseposition_y;
        update();
    }
}

void MymapMainWindow::setarraydatas(int *array)
{
    for(int i = 0;i < WIDTH;i++)
    {
        for(int j = 0;j < LENGTH;j++)
        {
            Mymap::mymap[i * LENGTH + j] = array[i * LENGTH + j];
        }
    }
}

bool MymapMainWindow::ispermitted(int x,int y)
{
    if(((x>2 && x<6) && (y>0 && y<4))||((x>16 && x<20) && (y>0 && y<4))||((x>30 && x<34) && (y>0 && y<4)))
    {
        return false;
    }
    else if(((x>13 && x<17) && (y>25 && y<29))||((x>25 && x<29) && (y>25 && y<29)))
    {
        return false;
    }
    else
    {
        return true;
    }
}


void MymapMainWindow::on_pushButton_clicked()
{
    if(mouseposition_x == 0 ||mouseposition_x == LENGTH - 1||mouseposition_y == 0 ||mouseposition_y == WIDTH - 1)
    {
        Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] = BRICK_WALL;
    }
    else if(Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] == STAR)
    {
        Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] = STAR;
    }
    else if(mouseposition_x < LENGTH - 1 && mouseposition_x > 0 && ispermitted(mouseposition_x,mouseposition_y))
    {
        Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] = BRICK_WALL;
    }
    update();
}


void MymapMainWindow::on_pushButton_2_clicked()
{
    if(mouseposition_x == 0 ||mouseposition_x == LENGTH - 1||mouseposition_y == 0 ||mouseposition_y == WIDTH - 1)
    {
        Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] = BRICK_WALL;
    }
    else if(Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] == STAR)
    {
        Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] = STAR;
    }
    else if(mouseposition_x < LENGTH - 1 && mouseposition_x > 0 && ispermitted(mouseposition_x,mouseposition_y))
    {
        Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] = STEEL_WALL;
    }
    update();
}


void MymapMainWindow::on_pushButton_3_clicked()
{
    if(mouseposition_x == 0 ||mouseposition_x == LENGTH - 1||mouseposition_y == 0 ||mouseposition_y == WIDTH - 1)
    {
        Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] = BRICK_WALL;
    }
    else if(Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] == STAR)
    {
        Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] = STAR;
    }
    else if(mouseposition_x < LENGTH - 1 && mouseposition_x > 0 && ispermitted(mouseposition_x,mouseposition_y))
    {
        Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] = FOREST;
    }
    update();
}


void MymapMainWindow::on_pushButton_4_clicked()
{
    if(mouseposition_x == 0 ||mouseposition_x == LENGTH - 1||mouseposition_y == 0 ||mouseposition_y == WIDTH - 1)
    {
        Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] = BRICK_WALL;
    }
    else if(Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] == STAR)
    {
        Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] = STAR;
    }
    else if(mouseposition_x < LENGTH - 1 && mouseposition_x > 0 && ispermitted(mouseposition_x,mouseposition_y))
    {
        Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] = SEA;
    }
    update();
}


void MymapMainWindow::on_pushButton_5_clicked()
{
    if(mouseposition_x == 0 ||mouseposition_x == LENGTH - 1||mouseposition_y == 0 ||mouseposition_y == WIDTH - 1)
    {
        Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] = BRICK_WALL;
    }
    else if(Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] == STAR)
    {
        Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] = STAR;
    }
    else if(mouseposition_x < LENGTH - 1 && mouseposition_x > 0 && ispermitted(mouseposition_x,mouseposition_y))
    {
        Mymap::mymap[mouseposition_y * LENGTH + mouseposition_x] = EMPTY;
    }
    update();
}


void MymapMainWindow::on_pushButton_6_clicked()
{
    subWindow *first = new subWindow();
    subWindow::open = true;
    first -> setarraydata(Mymap::mymap);
    this -> close();
    delete this;
    first -> show();
}


void MymapMainWindow::on_pushButton_7_clicked()
{
    subWindow *first = new subWindow();
    this -> close();
    delete this;
    first -> show();
}


void MymapMainWindow::on_pushButton_8_clicked()
{
    subWindow *first = new subWindow();
    subWindow::save = true;
    first -> setarraydata(Mymap::mymap);
    this -> close();
    delete this;
    first -> show();
}

