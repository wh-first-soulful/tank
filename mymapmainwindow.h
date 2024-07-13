#ifndef MYMAPMAINWINDOW_H
#define MYMAPMAINWINDOW_H

#include <QMainWindow>
#include <tankwar.h>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>

namespace Ui {
class MymapMainWindow;
}

class MymapMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MymapMainWindow(QWidget *parent = nullptr);
    ~MymapMainWindow();
    Mymap mymap;
    QPixmap brick;
    QPixmap brick2;
    QPixmap forest;
    QPixmap sea2;
    QPixmap black;
    QPixmap star;
    QPixmap click;
    QPainter painter;
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *ev);
    void setarraydatas(int *array);
    bool ispermitted(int x,int y);
    int mouseposition_x;
    int mouseposition_y;
    int pre_mouseposition_x;
    int pre_mouseposition_y;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MymapMainWindow *ui;

};

#endif // MYMAPMAINWINDOW_H
