#include "shopwindow.h"
#include "ui_shopwindow.h"
#include <QVBoxLayout>
#include<QHBoxLayout>
#include<QMessageBox>
#include<QPixmap>
#include<QDebug>
#include<QColor>
#include<QFont>
#include"subwindow.h"
#include"mainwindow.h"
#include"ui_shopwindow.h"

ShopWindow::ShopWindow(User& user, QMainWindow *parent) :
    QMainWindow(parent), user(user),ui(new Ui::ShopWindow)
{
    setMinimumSize(1500, 900);
    setMaximumSize(1500, 900);
    QPixmap pixmap = QPixmap(":/pic/shopcover.png").scaled(this->size());
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    this->setPalette( palette );
    ui->setupUi(this);
    if(user.hasBoughtItem("Item 1"))
    {
        ui->buy1->setStyleSheet("QPushButton{border-image:url(:/pic/havebuy1.png);}" //正常
                                "QPushButton:hover{border-image:url(:/pic/havebuy2.png);}" //鼠标悬浮
                                );
        ui->buy1->setFixedSize(QSize(400,25));
    }
    else
    {
        ui->buy1->setStyleSheet("QPushButton{border-image:url(:/pic/buy1.png);}" //正常
                                "QPushButton:hover{border-image:url(:/pic/buy2.png);}" //鼠标悬浮
                                );
        ui->buy1->setFixedSize(QSize(400,25));
    }
    if(user.hasBoughtItem("Item 2"))
    {
        ui->buy2->setStyleSheet("QPushButton{border-image:url(:/pic/havebuy1.png);}" //正常
                                "QPushButton:hover{border-image:url(:/pic/havebuy2.png);}" //鼠标悬浮
                                );
        ui->buy2->setFixedSize(QSize(400,25));
    }
    else
    {
        ui->buy2->setStyleSheet("QPushButton{border-image:url(:/pic/buy1.png);}" //正常
                                "QPushButton:hover{border-image:url(:/pic/buy2.png);}" //鼠标悬浮
                                );
        ui->buy2->setFixedSize(QSize(400,25));
    }
    if(user.hasBoughtItem("Item 3"))
    {
        ui->buy3->setStyleSheet("QPushButton{border-image:url(:/pic/havebuy1.png);}" //正常
                                "QPushButton:hover{border-image:url(:/pic/havebuy2.png);}" //鼠标悬浮
                                );
        ui->buy3->setFixedSize(QSize(400,25));
    }
    else
    {
        ui->buy3->setStyleSheet("QPushButton{border-image:url(:/pic/buy1.png);}" //正常
                                "QPushButton:hover{border-image:url(:/pic/buy2.png);}" //鼠标悬浮
                                );
        ui->buy3->setFixedSize(QSize(400,25));
    }
    if(user.hasBoughtItem("Item 4"))
    {
        ui->buy4->setStyleSheet("QPushButton{border-image:url(:/pic/havebuy1.png);}" //正常
                                "QPushButton:hover{border-image:url(:/pic/havebuy2.png);}" //鼠标悬浮
                                );
        ui->buy4->setFixedSize(QSize(400,25));
    }
    else
    {
        ui->buy4->setStyleSheet("QPushButton{border-image:url(:/pic/buy1.png);}" //正常
                                "QPushButton:hover{border-image:url(:/pic/buy2.png);}" //鼠标悬浮
                                );
        ui->buy4->setFixedSize(QSize(400,25));
    }
    updateEquippedItemDisplay();
    updateCoinsDisplay();
    ui->return_2->setStyleSheet("QPushButton{border-image:url(:/pic/shopreturn1.png);}" //正常
                            "QPushButton:hover{border-image:url(:/pic/return2.png);}" //鼠标悬浮
                            );
    ui->return_2->setFixedSize(QSize(100,25));
}

ShopWindow::~ShopWindow()
{
    updateDatabase();
    delete ui;
}




void ShopWindow::updateCoinsDisplay()
{
    qDebug()<<user.coins;
    ui->label_5->setText("Coins: " + QString::number(user.getCoins()));
    QFont font = ui -> label_5 -> font();
    QColor color(Qt::white);
    font.setPointSize(14);
    ui -> label_5 -> setFont(font);
    ui -> label_5 -> setStyleSheet("color:#FFFFFF");

}

void ShopWindow::updateEquippedItemDisplay()
{
    if(user.getEquippedItem() == "Item 1")
    {
        ui->equip1->setStyleSheet("QPushButton{border-image:url(:/pic/haveequip1.png);}" //正常
                                "QPushButton:hover{border-image:url(:/pic/haveequip2.png);}" //鼠标悬浮
                                );
        ui->equip1->setFixedSize(QSize(400,25));
        ui->equip2->setStyleSheet("QPushButton{border-image:url(:/pic/equip1.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/equip2.png);}" //鼠标悬浮
                                  );
        ui->equip2->setFixedSize(QSize(400,25));
        ui->equip3->setStyleSheet("QPushButton{border-image:url(:/pic/equip1.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/equip2.png);}" //鼠标悬浮
                                  );
        ui->equip3->setFixedSize(QSize(400,25));
        ui->equip4->setStyleSheet("QPushButton{border-image:url(:/pic/equip1.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/equip2.png);}" //鼠标悬浮
                                  );
        ui->equip4->setFixedSize(QSize(400,25));
    }
    else if(user.getEquippedItem() == "Item 2")
    {
        ui->equip1->setStyleSheet("QPushButton{border-image:url(:/pic/equip1.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/equip2.png);}" //鼠标悬浮
                                  );
        ui->equip1->setFixedSize(QSize(400,25));
        ui->equip2->setStyleSheet("QPushButton{border-image:url(:/pic/haveequip1.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/haveequip2.png);}" //鼠标悬浮
                                  );
        ui->equip2->setFixedSize(QSize(400,25));
        ui->equip3->setStyleSheet("QPushButton{border-image:url(:/pic/equip1.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/equip2.png);}" //鼠标悬浮
                                  );
        ui->equip3->setFixedSize(QSize(400,25));
        ui->equip4->setStyleSheet("QPushButton{border-image:url(:/pic/equip1.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/equip2.png);}" //鼠标悬浮
                                  );
        ui->equip4->setFixedSize(QSize(400,25));
    }
    else if(user.getEquippedItem() == "Item 3")
    {
        ui->equip1->setStyleSheet("QPushButton{border-image:url(:/pic/equip1.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/equip2.png);}" //鼠标悬浮
                                  );
        ui->equip1->setFixedSize(QSize(400,25));
        ui->equip2->setStyleSheet("QPushButton{border-image:url(:/pic/equip1.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/equip2.png);}" //鼠标悬浮
                                  );
        ui->equip2->setFixedSize(QSize(400,25));
        ui->equip3->setStyleSheet("QPushButton{border-image:url(:/pic/haveequip1.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/haveequip2.png);}" //鼠标悬浮
                                  );
        ui->equip3->setFixedSize(QSize(400,25));
        ui->equip4->setStyleSheet("QPushButton{border-image:url(:/pic/equip1.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/equip2.png);}" //鼠标悬浮
                                  );
        ui->equip4->setFixedSize(QSize(400,25));
    }
    else if(user.getEquippedItem() == "Item 4")
    {
        ui->equip1->setStyleSheet("QPushButton{border-image:url(:/pic/equip1.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/equip2.png);}" //鼠标悬浮
                                  );
        ui->equip1->setFixedSize(QSize(400,25));
        ui->equip2->setStyleSheet("QPushButton{border-image:url(:/pic/equip1.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/equip2.png);}" //鼠标悬浮
                                  );
        ui->equip2->setFixedSize(QSize(400,25));
        ui->equip3->setStyleSheet("QPushButton{border-image:url(:/pic/equip1.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/equip2.png);}" //鼠标悬浮
                                  );
        ui->equip3->setFixedSize(QSize(400,25));
        ui->equip4->setStyleSheet("QPushButton{border-image:url(:/pic/haveequip1.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/haveequip2.png);}" //鼠标悬浮
                                  );
        ui->equip4->setFixedSize(QSize(400,25));
    }
    else
    {
        ui->equip1->setStyleSheet("QPushButton{border-image:url(:/pic/equip1.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/equip2.png);}" //鼠标悬浮
                                  );
        ui->equip1->setFixedSize(QSize(400,25));
        ui->equip2->setStyleSheet("QPushButton{border-image:url(:/pic/equip1.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/equip2.png);}" //鼠标悬浮
                                  );
        ui->equip2->setFixedSize(QSize(400,25));
        ui->equip3->setStyleSheet("QPushButton{border-image:url(:/pic/equip1.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/equip2.png);}" //鼠标悬浮
                                  );
        ui->equip3->setFixedSize(QSize(400,25));
        ui->equip4->setStyleSheet("QPushButton{border-image:url(:/pic/equip1.png);}" //正常
                                  "QPushButton:hover{border-image:url(:/pic/equip2.png);}" //鼠标悬浮
                                  );
        ui->equip4->setFixedSize(QSize(400,25));
    }
}

bool ShopWindow::confirmPurchase(const QString &itemName, int cost)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Purchase",
                                  QString("Are you sure you want to buy %1 for %3 coins?").arg(itemName).arg(cost),
                                  QMessageBox::Yes | QMessageBox::No);
    return reply == QMessageBox::Yes;
}

bool ShopWindow::confirmEquip(const QString &itemName)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Equip",
                                  QString("Are you sure you want to equip %1?").arg(itemName),
                                  QMessageBox::Yes | QMessageBox::No);
    return reply == QMessageBox::Yes;
}

void ShopWindow::updateDatabase()
{
    qDebug()<<"updating...";
    Database::getInstance()->updateUserCoins(user.name, user.getCoins());
    Database::getInstance()->addUserBoughtItems(user.name,user.boughtItems);
    Database::getInstance()->addUserEquippedItem(user.name,user.equippedItem);
}


void ShopWindow::closeEvent(QCloseEvent *event) {

    updateDatabase();
    QMainWindow::closeEvent(event);
}

void ShopWindow::on_buy1_clicked()
{
    /*if (user.hasBoughtItem("Item 1")) {
        QMessageBox::warning(this, "Already Purchased", "You have already purchased Item 1.");
        return; // 直接返回，不执行购买逻辑
    }*/
    if (confirmPurchase("Item 1", 10)) {
        if (user.spendCoins(10)) {
            user.buyItem("Item 1");
        } else {
            QMessageBox::warning(this, "Insufficient Coins", "You don't have enough coins ");
        }
    }
    if(user.hasBoughtItem("Item 1"))
    {
        ui->buy1->setStyleSheet("QPushButton{border-image:url(:/pic/havebuy1.png);}" //正常
                                "QPushButton:hover{border-image:url(:/pic/havebuy2.png);}" //鼠标悬浮
                                );
        ui->buy1->setFixedSize(QSize(400,25));
    }

    //ui->buy1->setText(user.hasBoughtItem("Item 1") ? "已购买" : "购买");
    updateCoinsDisplay();
    updateDatabase();
}



void ShopWindow::on_buy2_clicked()
{
    if (user.hasBoughtItem("Item 2")) {
        QMessageBox::warning(this, "Already Purchased", "You have already purchased Item 2.");
        return; // 直接返回，不执行购买逻辑
    }
    if (confirmPurchase("Item 2", 20)) {
        if (user.spendCoins(20)) {

            user.buyItem("Item 2");
        } else {
            QMessageBox::warning(this, "Insufficient Coins", "You don't have enough coins ");
        }
    }
    //ui->buy2->setText(user.hasBoughtItem("Item 2") ? "已购买" : "购买");
    if(user.hasBoughtItem("Item 2"))
    {
        ui->buy2->setStyleSheet("QPushButton{border-image:url(:/pic/havebuy1.png);}" //正常
                                "QPushButton:hover{border-image:url(:/pic/havebuy2.png);}" //鼠标悬浮
                                );
        ui->buy2->setFixedSize(QSize(400,25));
    }

    updateCoinsDisplay();
    updateDatabase();

}

void ShopWindow::on_buy3_clicked()
{
    if (user.hasBoughtItem("Item 3")) {
        QMessageBox::warning(this, "Already Purchased", "You have already purchased Item 3.");
        return; // 直接返回，不执行购买逻辑
    }
    if (confirmPurchase("Item 3", 30)) {
        if (user.spendCoins(-30)) {
            user.buyItem("Item 3");
        } else {
            QMessageBox::warning(this, "Insufficient Coins", "You don't have enough coins ");
        }
    }
    if(user.hasBoughtItem("Item 3"))
    {
        ui->buy3->setStyleSheet("QPushButton{border-image:url(:/pic/havebuy1.png);}" //正常
                                "QPushButton:hover{border-image:url(:/pic/havebuy2.png);}" //鼠标悬浮
                                );
        ui->buy3->setFixedSize(QSize(400,25));
    }
    //ui->buy3->setText(user.hasBoughtItem("Item 3") ? "已购买" : "购买");
    updateCoinsDisplay();
    updateDatabase();
}

void ShopWindow::on_buy4_clicked()
{
    if (user.hasBoughtItem("Item 4")) {
        QMessageBox::warning(this, "Already Purchased", "You have already purchased Item 4.");
        return; // 直接返回，不执行购买逻辑
    }
    if (confirmPurchase("Item 4", 40)) {
        if (user.spendCoins(40)) {
            user.buyItem("Item 4");
        } else {
            QMessageBox::warning(this, "Insufficient Coins", "You don't have enough coins ");
        }
    }
    if(user.hasBoughtItem("Item 4"))
    {
        ui->buy4->setStyleSheet("QPushButton{border-image:url(:/pic/havebuy1.png);}" //正常
                                "QPushButton:hover{border-image:url(:/pic/havebuy2.png);}" //鼠标悬浮
                                );
        ui->buy4->setFixedSize(QSize(400,25));
    }
    //ui->buy4->setText(user.hasBoughtItem("Item 4") ? "已购买" : "购买");
    updateCoinsDisplay();
    updateDatabase();

}
void ShopWindow::on_equip1_clicked()
{
    if (user.hasBoughtItem("Item 1") ){
        if(confirmEquip("Item 1")) {
            user.equipItem("Item 1");
            Database::getInstance()->addUserEquippedItem(user.name,"Item 1");

            updateDatabase();
        }
    }else{
        QMessageBox::warning(this, "警告", "你没有购买此植物");
    }

    updateEquippedItemDisplay();

}

void ShopWindow::on_equip2_clicked()
{
    if (user.hasBoughtItem("Item 2") ){
        if(confirmEquip("Item 2")) {
            user.equipItem("Item 2");
            Database::getInstance()->addUserEquippedItem(user.name,"Item 2");
            updateDatabase();

        }
    }else{
        QMessageBox::warning(this, "警告", "你没有购买此植物");
    }
    updateEquippedItemDisplay();

}



void ShopWindow::on_equip3_clicked()
{
    if (user.hasBoughtItem("Item 3") ){
        if(confirmEquip("Item 3")) {
            user.equipItem("Item 3");
            Database::getInstance()->addUserEquippedItem(user.name,"Item 3");
            updateDatabase();

        }
    }else{
        QMessageBox::warning(this, "警告", "你没有购买此植物");
    }
    updateEquippedItemDisplay();

}

void ShopWindow::on_equip4_clicked()
{if (user.hasBoughtItem("Item 4") ){
        if(confirmEquip("Item 4")) {
            user.equipItem("Item 4");
            Database::getInstance()->addUserEquippedItem(user.name,"Item 4");
            updateDatabase();

        }
    }else{
        QMessageBox::warning(this, "警告", "你没有购买此植物");
    }
    updateEquippedItemDisplay();
}

void ShopWindow::on_return_2_clicked()
{
    this->close();
}
