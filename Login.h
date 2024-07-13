#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMessageBox>//消息盒子
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include"user.h"
#include "database.h"

class MainWindow;

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

protected:
    void resizeEvent(QResizeEvent*event)override;
private slots:
    void on_btn_signin_clicked();

    void on_btn_signup_clicked();

private:
    Ui::Login *ui;


    //Database dataBase;
    Database db;
};

#endif // LOGIN_H
