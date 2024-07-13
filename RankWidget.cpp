#include "RankWidget.h"
#include "ui_RankWidget.h"
#include "database.h"

RankWidget::RankWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RankWidget)
{
    ui->setupUi(this);

    setWindowTitle("排行榜");

    ui->listWidget->setIconSize(QSize(25, 25));
    ui->listWidget->setFocusPolicy(Qt::NoFocus);  //这样可禁用tab键和上下方向键并且除去复选框
    ui->listWidget->setFont(QFont("Microsoft YaHei", 11, QFont::DemiBold));
    ui->listWidget->setStyleSheet(
                    //"*{outline:0px;}"  //除去复选框
                    "QListWidget{background:rgb(245, 245, 247); border:0px; margin:0px 0px 0px 0px;}"
                    "QListWidget::Item{height:50px; border:0px; padding-left:14px; color:rgba(200, 40, 40, 255);border-radius: 7px;}"
                    "QListWidget::Item:hover{background-color:rgba(132,133,141,16); padding-left:14px;}"
                    "QListWidget::Item:selected{color:rgba(40, 40, 200, 255); padding-left:15px;}"
                    );

}

RankWidget::~RankWidget()
{
    delete ui;
}

void RankWidget::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "单人排名")
        showOneScore();
    else
        showTowScore();
}

void RankWidget::showOneScore()
{
    ui->listWidget->clear();

    QList<MaxScoreInfo> scoreInfo = Database::getInstance()->getMaxScoreInfo();

    int rankNum = 1;
    foreach(auto tmp, scoreInfo)
    {
        getItem(tmp.username, QString::number(tmp.max_score), rankNum);

        rankNum++;
    }
}

void RankWidget::showTowScore()
{
    ui->listWidget->clear();

    QList<MaxScoreInfo> scoreInfo = Database::getInstance()->getTowPlayerMaxScoreInfo();

    int rankNum = 1;
    foreach(auto tmp, scoreInfo)
    {
        getItem(tmp.username, QString::number(tmp.max_tow_score), rankNum);

        rankNum++;
    }
}


QListWidgetItem *RankWidget::getItem(QString name, QString score, int rankNum)
{
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    if(rankNum == 1) item->setIcon(QIcon(":/image/one.png"));
    else if(rankNum == 2) item->setIcon(QIcon(":/image/tow.png"));
    else if(rankNum == 3) item->setIcon(QIcon(":/image/three.png"));
    else item->setIcon(QIcon(":/image/other.png"));
    item->setSizeHint(QSize(ui->listWidget->width(), 60));

    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(widget);

    QLabel *rankLabel = new QLabel(widget);
    rankLabel->setAlignment(Qt::AlignCenter | Qt::AlignCenter);  // 设置对齐方式
    rankLabel->setText(QString("排名: %1").arg(rankNum));
    layout->addWidget(rankLabel);

    QLabel *textLabel = new QLabel(widget);
    textLabel->setAlignment(Qt::AlignCenter | Qt::AlignCenter);  // 设置对齐方式
    textLabel->setText(QString("玩家: ") + name);
    layout->addWidget(textLabel);

    QLabel *towLabel = new QLabel(widget);
    towLabel->setAlignment(Qt::AlignCenter | Qt::AlignCenter);  // 设置对齐方式
    towLabel->setText(QString("分数: ") + score);
    layout->addWidget(towLabel);

    layout->setStretch(0, 1);
    layout->setStretch(1, 1);
    layout->setStretch(2, 1);
    layout->setSpacing(0);
    widget->setLayout(layout);

    ui->listWidget->setItemWidget(item, widget);

    return item;
}
