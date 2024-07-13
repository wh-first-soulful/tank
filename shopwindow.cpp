#include "shopwindow.h"
#include "ui_shopwindow.h"
#include <QVBoxLayout>
#include<QHBoxLayout>
#include <QMessageBox>
#include<QPixmap>
#include<QDebug>
#include"subwindow.h"
#include"mainwindow.h"
#include"ui_shopwindow.h"

ShopWindow::ShopWindow(User& user, QMainWindow *parent) :
    QMainWindow(parent), user(user),ui(new Ui::ShopWindow)
{
    setMinimumSize(1500, 900);
    setMaximumSize(1500, 900);
    ui->setupUi(this);
    ui->buy1->setText(user.hasBoughtItem("Item 1") ? "已购买" : "购买");
    ui->buy2->setText(user.hasBoughtItem("Item 2") ? "已购买" : "购买");
    ui->buy3->setText(user.hasBoughtItem("Item 3") ? "已购买" : "购买");
    ui->buy4->setText(user.hasBoughtItem("Item 4") ? "已购买" : "购买");
    updateEquippedItemDisplay();
    updateCoinsDisplay();
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
}

void ShopWindow::updateEquippedItemDisplay()
{
    ui->equip1->setText(user.getEquippedItem() == "Item 1" ? "已装备" : "装备");
    ui->equip2->setText(user.getEquippedItem() == "Item 2" ? "已装备" : "装备");
    ui->equip3->setText(user.getEquippedItem() == "Item 3" ? "已装备" : "装备");
    ui->equip4->setText(user.getEquippedItem() == "Item 4" ? "已装备" : "装备");

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
    ui->buy1->setText(user.hasBoughtItem("Item 1") ? "已购买" : "购买");
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
    ui->buy2->setText(user.hasBoughtItem("Item 2") ? "已购买" : "购买");
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
    ui->buy3->setText(user.hasBoughtItem("Item 3") ? "已购买" : "购买");
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
    ui->buy4->setText(user.hasBoughtItem("Item 4") ? "已购买" : "购买");
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
