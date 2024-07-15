#ifndef USER_H
#define USER_H
#include<QString>
#include<QSet>
#include<QMessageBox>

class User
{
public:
    static User* getInstance(){
    if (!user) {
            user = new User;
        }
        return user;
}
    User(){}
    User(const QString &name, int coins);

    void addCoins(int amount);
    bool spendCoins(int amount);
    int getCoins() const;

    void buyItem(const QString &item);
    bool hasBoughtItem(const QString &item) const;
    void equipItem(const QString &item);
    QString getEquippedItem() const;
    void resetEquipment();


    QString name;
    int coins;
    QSet<QString> boughtItems;
    QString equippedItem;
    static User* user;

};

#endif // USER_H
