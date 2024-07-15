#include "login.h"
#include "ui_Login.h"
#include "signup.h"

#include "mainwindow.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    setWindowTitle("登录");


    /*QPixmap *pix = new QPixmap(":/pic/");
    QSize sz = ui->label_image->size();
    ui->label_image->setPixmap(pix->scaled(sz));*/



    //设置阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(-3, 0);
    shadow->setColor(QColor("#888888"));
    shadow->setBlurRadius(30);

}

Login::~Login()
{
    delete ui;
}

void Login::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
        QPalette palette = this->palette();
        palette.setBrush(QPalette::Background, QPixmap(":/image/login/").scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        this->setPalette(palette);
}

void Login::on_btn_signin_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    bool result = Database::getInstance()->loginUser(username, password);

    //判断执行结果
    if(!result)
    {
        qDebug()<<"Login error";
        QMessageBox::information(this,"登录认证","登录失败,账户或者密码错误");

    }
    else
    {
        qDebug()<<"Login success";
        QMessageBox::information(this,"登录认证","登陆成功!");
        int coins = Database::getInstance()->getUserCoins(username);
        //User user(username, coins);
        User::getInstance()->name=username;
        User::getInstance()->coins=coins;

        MainWindow *mainWindow = new MainWindow(*User::getInstance());
        mainWindow->show();

        this->close();
    }
}

void Login::on_btn_signup_clicked()
{
    this->close();
    Signup *s = new Signup;
    s->show();

}
