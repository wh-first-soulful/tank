#ifndef RANKWIDGET_H
#define RANKWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QLabel>

namespace Ui {
class RankWidget;
}

class RankWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RankWidget(QWidget *parent = 0);
    ~RankWidget();
    void showOneScore();
    void showTowScore();

private:

    QListWidgetItem * getItem(QString text, QString towScore, int rankNum);

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::RankWidget *ui;

    QString username;
};

#endif // RANKWIDGET_H
