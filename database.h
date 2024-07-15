#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QString>
#include <QDateTime>
#include <QFile>
#include <QApplication>

struct ScoreInfo{
    QString time;
    int score;
    int tow_score;
};

struct MaxScoreInfo{
    QString username;
    int max_score;
    int max_tow_score;
};

struct ItemInfo {
    int item_id;
    QString item_name;
    int item_price;
    bool is_equipped;
};

class Database {
public:
    Database();
    ~Database();

    static Database *getInstance(){
        if(!dataBase) dataBase = new Database;

        return dataBase;
    }

    static void Release(){
        if(!dataBase) return;

        delete dataBase;
        dataBase = nullptr;
    }

    bool registerUser(const QString &username, const QString &password);
    bool loginUser(const QString &username, const QString &password);
    bool updateMaxScore(const QString &username, int newScore);
    bool updateTwoPlayerMaxScore(const QString &username, int newScore);
    int getMaxScore(const QString username);
    int getTwoPlayerMaxScore(const QString &username);
    int getUserCoins(const QString &username);
    bool updateUserCoins(const QString &username, int coins);

    QList<MaxScoreInfo> getMaxScoreInfo();

    QList<MaxScoreInfo> getTowPlayerMaxScoreInfo();

    bool insertScore(int score, int tow_score, QString userName);

    QList<ScoreInfo> getScoreInfo(QString userName);


    // 添加用户购买的物品信息
        bool addUserBoughtItems(const QString &username, const QSet<QString> &boughtItems);

        // 添加用户装备的物品信息
        bool addUserEquippedItem(const QString &username, const QString &equippedItem);

        // 获取用户购买的物品信息
        QSet<QString> getUserBoughtItems(const QString &username);

        // 获取用户装备的物品信息
        QString getUserEquippedItem(const QString &username);

    QString getUserName();

    static QString currrentName;

private:
    QSqlDatabase db;

    static Database *dataBase;
    QFile file;
};
#endif // DATABASE_H
