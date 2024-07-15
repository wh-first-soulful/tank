#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"KeyPressEventFilter.h"
#include "subwindow.h"
#include "CommentWidget.h"
#include "RankWidget.h"
#include"user.h"
#include"shopwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(User&user,QWidget *parent = nullptr);
    ~MainWindow();
    QPalette palette;
    static subWindow *m_subWindow;
    friend class MymapMainWindow;
  private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_btnHistory_clicked();

    void on_btnRank_clicked();

    void on_shopButton_clicked();


private:
    Ui::MainWindow *ui;

    CommentWidget *commentWidget = nullptr;
    RankWidget *rankWidget = nullptr;
    ShopWindow*shopwindow=nullptr;

    User user;
};


#endif // MAINWINDOW_H
