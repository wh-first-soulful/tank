#ifndef SHOPWINDOW_H
#define SHOPWINDOW_H

#include <QMainWindow>
#include"user.h"
#include<QPushButton>
#include<QLabel>
#include"database.h"
#include<QPixmap>
#include"database.h"

namespace Ui {
class ShopWindow;
}

class ShopWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShopWindow(User&user,QMainWindow *parent = nullptr);
    ~ShopWindow();


    QPixmap item1Icon;
    QPixmap item2Icon;
    QPixmap item3Icon;
    QPixmap item4Icon;


private slots:


    void on_buy1_clicked();

    void on_equip1_clicked();

    void on_buy2_clicked();

    void on_buy3_clicked();

    void on_buy4_clicked();

    void on_equip2_clicked();

    void on_equip3_clicked();

    void on_equip4_clicked();

    void on_return_2_clicked();

protected:
     void closeEvent(QCloseEvent *event) override;

private:
    Ui::ShopWindow *ui;
    User user;


    void updateCoinsDisplay();
    void updateEquippedItemDisplay();
    bool confirmPurchase(const QString &itemName, int cost);
    bool confirmEquip(const QString &itemName);
    void updateDatabase();

};

#endif // SHOPWINDOW_H
