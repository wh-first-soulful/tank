#ifndef COMMENTWIDGET_H
#define COMMENTWIDGET_H

#include <QWidget>
#include <QDateTime>
#include <QDebug>
#include <QSqlQuery>
#include <QCloseEvent>
#include <QListWidgetItem>
#include <QLabel>

namespace Ui {
class CommentWidget;
}

class CommentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommentWidget(QString name, QWidget *parent = 0);
    ~CommentWidget();

    void showScore();


signals:
    void sigClose();

protected:
    virtual void colseEvent(QCloseEvent *e);


private:
    QListWidgetItem *getItem(QString text, QString towScore, QString time);


private:
    Ui::CommentWidget *ui;

    QString username;
};

#endif // COMMENTWIDGET_H
