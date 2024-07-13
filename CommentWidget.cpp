#include "CommentWidget.h"
#include "ui_CommentWidget.h"
#include "database.h"

CommentWidget::CommentWidget(QString name, QWidget *parent) :
    username(name),
    QWidget(parent),
    ui(new Ui::CommentWidget)
{
    ui->setupUi(this);

    setWindowTitle("历史战绩");
    ui->label->setText(name);

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

CommentWidget::~CommentWidget()
{
    delete ui;
}

void CommentWidget::showScore()
{
    ui->listWidget->clear();

    QList<ScoreInfo> scoreInfo = Database::getInstance()->getScoreInfo(username);

    foreach(auto tmp, scoreInfo)
    {
        getItem(QString::number(tmp.score), QString::number(tmp.tow_score), tmp.time);
    }
}

void CommentWidget::colseEvent(QCloseEvent *e)
{
    emit sigClose();
}

QListWidgetItem *CommentWidget::getItem(QString text, QString towScore, QString time)
{
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    item->setIcon(QIcon(":/image/score.png"));
    item->setSizeHint(QSize(ui->listWidget->width(), 60));

    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(widget);

    QLabel *textLabel = new QLabel(widget);
//    textLabel->setWordWrap(true);
//    textLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);  // 设置大小策略
    textLabel->setAlignment(Qt::AlignCenter | Qt::AlignCenter);  // 设置对齐方式

    textLabel->setText(QString("单人: ") + text);
    layout->addWidget(textLabel);

    QLabel *towLabel = new QLabel(widget);
    towLabel->setAlignment(Qt::AlignCenter | Qt::AlignCenter);  // 设置对齐方式
    towLabel->setText(QString("双人: ") + towScore);
    layout->addWidget(towLabel);



    QString decodedTime = QString::fromUtf8(time.toUtf8());
        QLabel *timeLabel = new QLabel(widget);
        timeLabel->setAlignment(Qt::AlignCenter | Qt::AlignCenter);  // 设置对齐方式
        timeLabel->setText(QString("时间: ") + decodedTime);
        layout->addWidget(timeLabel);

    layout->setStretch(0, 1);
    layout->setStretch(1, 1);
    layout->setStretch(2, 1);
    layout->setSpacing(0);
    widget->setLayout(layout);

    ui->listWidget->setItemWidget(item, widget);

    return item;
}
