#include "user.h"

User* User::user = nullptr;
User::User(const QString &name, int coins)
    : name(name), coins(coins) {}

void User::addCoins(int amount) {
    coins += amount;
}

bool User::spendCoins(int amount) {
    if (coins >= amount) {
        coins -= amount;
        return true;
    } else {
        return false;
    }
}

int User::getCoins() const {
    return coins;
}

void User::buyItem(const QString &item) {
    if (boughtItems.contains(item)){
        QMessageBox::warning(nullptr, "错误", "已购买当前植物");
    }else{
        QMessageBox::information(nullptr,"购买","购买成功!");
        boughtItems.insert(item);
    }
}

bool User::hasBoughtItem(const QString &item) const {
    return boughtItems.contains(item);
}

void User::equipItem(const QString &item) {
    if(item==this->equippedItem){
        QMessageBox::warning(nullptr, "装备错误", "已装备当前植物");
    }else if(item!=equippedItem){
        QMessageBox::information(nullptr, "", "装备成功!");
        equippedItem = item;
    }
}

QString User::getEquippedItem() const {
    return equippedItem;
}

void User::resetEquipment() {
    equippedItem = "";
}
