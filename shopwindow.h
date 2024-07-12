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
    explicit ShopWindow(User&user,QWidget *parent = nullptr);
    ~ShopWindow();


    QPixmap item1Icon;
    QPixmap item2Icon;
    QPixmap item3Icon;
    QPixmap item4Icon;


private slots:
    void buyItem1();
    void buyItem2();
    void buyItem3();
    void buyItem4();
    void equipItem1();
    void equipItem2();
    void equipItem3();
    void equipItem4();
    void close();

private:
    Ui::ShopWindow *ui;
    User user;
    QLabel*label;
    QLabel* equippedItemLabel;
    QPushButton *item1Button;
    QPushButton *item2Button;
    QPushButton *item3Button;
    QPushButton *item4Button;
    QPushButton *equipItem1Button;
    QPushButton *equipItem2Button;
    QPushButton *equipItem3Button;
    QPushButton *equipItem4Button;
    QPushButton*backButton;

    void updateCoinsDisplay();
    void updateEquippedItemDisplay();
    bool confirmPurchase(const QString &itemName, int cost);
    bool confirmEquip(const QString &itemName);
    void updateDatabase();
    void closeEvent(QCloseEvent *event) override;
};

#endif // SHOPWINDOW_H
