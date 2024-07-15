#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "subwindow.h"


subWindow* MainWindow::m_subWindow=nullptr;

MainWindow::MainWindow(User&user,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),user(user)

{
    if(!m_subWindow){
        m_subWindow=new subWindow(user);
    }
    ui->setupUi(this);

    //设置界面大小
    setMinimumSize(1500, 900); setMaximumSize(1500, 900);

    //设置背景
    QPixmap pixmap = QPixmap(":/pic/cover1.png").scaled(this->size());
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    this-> setPalette( palette );

    /*set title*/
    this->setWindowTitle("Tank Battle");
    this->setWindowIcon(QIcon(":/pic/cover.png"));
    //this->setWindowIcon(QIcon(":/pic/icon.jpg"));
    /*set icon*/
    ui->pushButton->setStyleSheet("QPushButton{border-image:url(:/pic/start111.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/start222.png);}" //鼠标悬浮
                                  );
    ui->pushButton->setFixedSize(QSize(500,250));//icon size
    ui->pushButton_2->setFixedSize(QSize(80,80));//icon size
    ui->pushButton_2->setStyleSheet("QPushButton{border-image:url(:/pic/exit111.png);}" //正常
                                    "QPushButton:hover{border-image:url(:/pic/exit222.png);}" //鼠标悬浮
                                    );

    ui->btnHistory->setStyleSheet("QPushButton{border-image:url(:/image/history.png);}"); //正常
    ui->btnRank->setStyleSheet("QPushButton{border-image:url(:/image/rank.png);}"); //正常
    ui->btnHistory->setFixedSize(QSize(200,100));//icon size
    ui->btnHistory->setToolTip("历史战绩");
    ui->btnRank->setFixedSize(QSize(200,100));//icon size


    ui->btnRank->setToolTip("排行榜");

    QString username = Database::getInstance()->getUserName();
    int coins = Database::getInstance()->getUserCoins(username);
    user = User(username, coins);
}

MainWindow::~MainWindow()
{
    delete ui;

    Database::Release();
}

void MainWindow::on_pushButton_clicked()
{
   m_subWindow->reload();
   m_subWindow->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    exit(0);
}

void MainWindow::on_btnHistory_clicked()
{
    QString username = Database::getInstance()->currrentName;
    if(!commentWidget) commentWidget = new CommentWidget(username);

    commentWidget->show();
    commentWidget->showScore();
}

void MainWindow::on_btnRank_clicked()
{
    if(!rankWidget) rankWidget = new RankWidget();
    rankWidget->show();
    rankWidget->showOneScore();
    this->show();
}

void MainWindow::on_shopButton_clicked()
{
    user.coins=Database::getInstance()->getUserCoins(user.name);
    QSet<QString> boughtItems=Database::getInstance()->getUserBoughtItems(user.name);
    QString equippedItem=Database::getInstance()->getUserEquippedItem(user.name);
    user.boughtItems=boughtItems;
    user.equippedItem=equippedItem;
    shopwindow =new ShopWindow(user);
    //connect(swindow, &ShopWindow::shopWindowClosed, this, &MainWindow::on_shopWindow_closed);
    shopwindow->show();
}


