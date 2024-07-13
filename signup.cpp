#include "signup.h"
#include "ui_signup.h"
#include "login.h"

Signup::Signup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);

    setWindowTitle("注册");
    QPixmap *pix = new QPixmap(":/pic/");
    QSize sz = ui->label_image->size();
    ui->label_image->setPixmap(pix->scaled(sz));
}

Signup::~Signup()
{
    delete ui;
}

//返回登录按钮
void Signup::on_btn_return_clicked()
{
    Login *w = new Login;
    w->show();
    this->close();
}

//注册按钮
void Signup::on_pushButton_2_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_passwd->text();
    QString surepass = ui->lineEdit_surepasswd->text();
    //判断密码是否一致
    if(password == surepass)
    {
        bool result = Database::getInstance()->registerUser(username, password);

        //判断执行结果
        if(!result)
        {
            qDebug()<<"insert into error";
            QMessageBox::information(this,"注册认证","用户名或密码不能为空！");
        }
        else
        {
            qDebug()<<"insert into success";
            QMessageBox::information(this,"注册认证","注册成功！");
            Login *w = new Login;
            w->show();
            this->close();
        }

    }else{
        QMessageBox::information(this,"注册认证","两次密码输入不一致");
    }
}
