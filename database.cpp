#include "database.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

QString Database::currrentName="null";
Database *Database::dataBase = nullptr;

Database::Database() : file("log.txt")
{

    // 连接到SQLite数据库
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QApplication::applicationDirPath() + "/tank_battle.db";
    db.setDatabaseName(path);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "open faild!";
    }


    if (!db.open()) {
        qDebug() << "Error: Failed to connect database." << db.lastError();
    } else {
        // 创建用户表
        QSqlQuery query(db);
        bool success = query.exec("CREATE TABLE IF NOT EXISTS users ("
                                  "username TEXT PRIMARY KEY, "
                                  "password TEXT NOT NULL, "
                                  "max_score INTEGER DEFAULT 0, "
                                  "two_player_max_score INTEGER DEFAULT 0, "
                                  "coins INTEGER DEFAULT 300)"
                                  );
        if (!success) {
            qDebug() << "Failed to create users table:" << query.lastError();
            db.close();
            return;
        }

        success = query.exec("CREATE TABLE IF NOT EXISTS scores ("
                                     "username TEXT NOT NULL, "
                                     "time TEXT NOT NULL, "
                                     "score INTEGER DEFAULT 0,"
                                     "two_player_score INTEGER DEFAULT 0)"
                                     );

                if (!success) {
                    qDebug() << "Failed to create scores table:" << query.lastError();}

        success = query.exec("CREATE TABLE IF NOT EXISTS user_bought_items ("
                             "username TEXT NOT NULL, "
                             "item_name TEXT NOT NULL, "
                             "PRIMARY KEY(username, item_name), "
                             "FOREIGN KEY(username) REFERENCES users(username))");
        if (!success) {
            qDebug() << "Failed to create user_bought_items table:" << query.lastError();
            db.close();
            return;}

        // 创建表结构来存储用户装备的物品信息
        success = query.exec("CREATE TABLE IF NOT EXISTS user_equipped_items ("
                             "username TEXT NOT NULL, "
                             "item_name TEXT NOT NULL, "
                             "PRIMARY KEY(username, item_name), "
                             "FOREIGN KEY(username) REFERENCES users(username))");
        if (!success) {
            qDebug() << "Failed to create user_equipped_items table:" << query.lastError();
            db.close();
            return;
        }
    }
}

Database::~Database() {
    db.close();
    file.close();
}

bool Database::registerUser(const QString &username, const QString &password) {
    // 首先检查数据库中是否已经存在该用户名
    if (username.isEmpty()) {
        qDebug() << "Registration Error: Username cannot be empty.";
        return false;
    }
    if (password.isEmpty()) {
        qDebug() << "Registration Error: Password cannot be empty.";
        return false;
    }
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT username FROM users WHERE username = ?");
    checkQuery.addBindValue(username);
    if (!checkQuery.exec()) {
        qDebug() << "Check User Existence Error:" << checkQuery.lastError();
        return false;
    }
    if (checkQuery.next()) {
        qDebug() << "Registration Error: Username already exists.";
        return false; // 如果用户名已存在，返回false表示注册失败
    }

    // 如果用户名不存在，则执行注册操作
    QSqlQuery registerQuery(db);
    registerQuery.prepare("INSERT INTO users (username, password, max_score) VALUES (?, ?, ?)");
    registerQuery.addBindValue(username);
    registerQuery.addBindValue(password);
    registerQuery.addBindValue(0); // 初始分数为0
    if (!registerQuery.exec()) {
        qDebug() << "Register Error:" << registerQuery.lastError();
        return false;
    }
    return true; // 注册成功
}

bool Database::loginUser(const QString &username, const QString &password) {
    QSqlQuery query(db);
    query.prepare("SELECT password FROM users WHERE username = ?");
    query.addBindValue(username);
    if (!query.exec()) {
        qDebug() << "Login Error:" << query.lastError();
        return false;
    }
    if (query.next() && query.value(0).toString() == password) {
        currrentName=username;
        return true;
    }
    return false;
}


bool Database::updateMaxScore(const QString &username, int newScore) {
    if (!db.isOpen()) {
        qDebug() << "Database not open.";
        return false;
    }

    qDebug() << "Updating max score for user:" << username << "with new score:" << newScore;

    // 使用简单的更新语句，先获取当前最高分数
    int currentMaxScore = getMaxScore(username);
    if (currentMaxScore == -1) {
        qDebug() << "User not found or error retrieving max score.";
        return false;
    }

    // 只有当新分数高于当前最高分数时才更新
    if (newScore > currentMaxScore) {
        QSqlQuery query(db);
        QString sqlStr = QString("UPDATE users SET max_score = %1 WHERE username = \"%2\"").arg(newScore).arg(username);
        //query.prepare(QString("UPDATE users SET max_score = %1 WHERE username = %2").arg(newScore).arg(username));
        //        query.addBindValue(newScore);
        //        query.addBindValue(username);

        if (!query.exec(sqlStr)) {
            qDebug() << "sqlStr: " << sqlStr;
            qDebug() << "Update Max Score Error:" << query.lastError();
            QString str = "Update Max Score Error:" + query.lastError().text();
            file.write(str.toStdString().c_str());
            return false;
        }
    } else {
        qDebug() << "New score is not higher than current max score.";
    }

    return true;
}

bool Database::updateTwoPlayerMaxScore(const QString &username, int newScore)
{
    QSqlQuery query(db);
    query.prepare("UPDATE users SET two_player_max_score = ? WHERE username = ? AND two_player_max_score < ?");
    query.addBindValue(newScore);
    query.addBindValue(username);
    query.addBindValue(newScore); // 确保只有在新分数更高时才更新
    if (!query.exec()) {
        qDebug() << "Update Two Player Max Score Error:" << query.lastError();
        return false;
    }
    return true;
}


int Database::getMaxScore(const QString username) {
    qDebug() << "Preparing query with username:" << username;

    QSqlQuery query(db);
    query.prepare("SELECT max_score FROM users WHERE username = ?");
    query.addBindValue(username);
    if (!query.exec()) {
        qDebug() << "Get Max Score Error:" << query.lastError();
        return -1; // 表示出错
    }
    if (query.next()) {
        return query.value(0).toInt();
    }
    return -1; // 表示用户不存在
}

int Database::getTwoPlayerMaxScore(const QString &username)
{
    QSqlQuery query(db);
    query.prepare("SELECT two_player_max_score FROM users WHERE username = ?");
    query.addBindValue(username);
    if (!query.exec()) {
        qDebug() << "Get Two Player Max Score Error:" << query.lastError();
        return -1; // 表示出错
    }
    if (query.next()) {
        return query.value(0).toInt();
    }
    return -1; // 表示用户不存在
}

int Database::getUserCoins(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT coins FROM users WHERE username = ?");
    query.addBindValue(username);
    if (!query.exec()) {
        qDebug() << "Get User Coins Error:" << query.lastError();
        return -1; // 表示出错
    }
    if (query.next()) {
        return query.value(0).toInt();
    }
    return -1; // 表示用户不存在
}

bool Database::updateUserCoins(const QString &username, int coins)
{
    QSqlQuery query;
    query.prepare("UPDATE users SET coins = ? WHERE username = ?");
    query.addBindValue(coins);
    query.addBindValue(username);
    if (!query.exec()) {
        qDebug() << "Update User Coins Error:" << query.lastError();
        return false;
    }
    return true;

}
QList<MaxScoreInfo> Database::getMaxScoreInfo()
{
    QList<MaxScoreInfo> maxScoreList;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM users order by max_score desc");
    if (!query.exec()) {
        qDebug() << "Get MaxScoreInfo Error:" << query.lastError();
        return maxScoreList; // 表示出错
    }
    while (query.next()) {
        MaxScoreInfo scoreInfo;
        scoreInfo.username =  query.value(0).toString();
        scoreInfo.max_score = query.value(2).toInt();
        scoreInfo.max_tow_score = query.value(3).toInt();
        maxScoreList.append(scoreInfo);
    }
    return maxScoreList;
}

QList<MaxScoreInfo> Database::getTowPlayerMaxScoreInfo()
{
    QList<MaxScoreInfo> maxScoreList;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM users order by two_player_max_score desc");
    if (!query.exec()) {
        qDebug() << "Get MaxScoreInfo Error:" << query.lastError();
        return maxScoreList; // 表示出错
    }
    while (query.next()) {
        MaxScoreInfo scoreInfo;
        scoreInfo.username =  query.value(0).toString();
        scoreInfo.max_score = query.value(2).toInt();
        scoreInfo.max_tow_score = query.value(3).toInt();
        maxScoreList.append(scoreInfo);
    }

    return maxScoreList;
}

bool Database::insertScore(int score, int tow_score, QString username)
{
    QSqlQuery query(db);

    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString sqlStr = QString("INSERT INTO scores (username, time, score, two_player_score) VALUES (\"%1\", \"%2\", %3, %4)")
            .arg(username).arg(currentTime).arg(score).arg(tow_score);
    //query.prepare(QString("INSERT INTO scores (username, time, score, two_player_score) VALUES (%1, %2, %3, %4)")
    //             .arg(username).arg(currentTime).arg(score).arg(tow_score));

    //    query.addBindValue(username);
    //    query.addBindValue(currentTime);
    //    query.addBindValue(score); // 初始分数为0
    //    query.addBindValue(tow_score);
    if (!query.exec(sqlStr)) {
        qDebug() << "sqlStr: " << sqlStr;
        qDebug() << "insert Error:" << query.lastError();
        QString str = "insert Error:" + query.lastError().text();
        file.write(str.toStdString().c_str());
        return false;
    }

    return true; // 插入成功
}

QList<ScoreInfo> Database::getScoreInfo(QString username)
{
    QList<ScoreInfo> scoreList;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM scores WHERE username = ? order by time desc");
    query.addBindValue(username);
    if (!query.exec()) {
        qDebug() << "Get ScoreInfo Error:" << query.lastError();
        return scoreList; // 表示出错
    }
    while (query.next()) {
        ScoreInfo scoreInfo;
        scoreInfo.time =  query.value(1).toString();
        scoreInfo.score = query.value(2).toInt();
        scoreInfo.tow_score = query.value(3).toInt();
        scoreList.append(scoreInfo);
    }
    return scoreList;
}

QString Database::getUserName()
{
    return currrentName;
}

bool Database::addUserBoughtItems(const QString &username, const QSet<QString> &boughtItems)
{
    for (const QString &itemName : boughtItems) {
        QSqlQuery query(db);
        query.prepare("SELECT item_name FROM user_bought_items WHERE username = ? AND item_name = ?");
                query.addBindValue(username);
                query.addBindValue(itemName);
                if (query.exec() && query.next()) {
                    // 如果已购买的物品已存在，则跳过
                    continue;
                }
                query.prepare("INSERT INTO user_bought_items (username, item_name) VALUES (?, ?)");
                query.addBindValue(username);
                query.addBindValue(itemName);
                if (!query.exec()) {
                    qDebug() << "Failed to add user bought items:" << query.lastError();
                    return false;
                }
    }
    return true;
}

bool Database::addUserEquippedItem(const QString &username, const QString &equippedItem)
{
    QSqlQuery query(db);
    query.prepare("SELECT username FROM user_equipped_items WHERE username = ?");
    query.addBindValue(username);

    if (!query.exec()) {
        qDebug() << "Failed to check user existence:" << query.lastError();
        return false;
    }

    if (query.first()) {
        // 如果用户存在，尝试更新装备物品
        query.prepare("UPDATE user_equipped_items SET item_name = ? WHERE username = ?");
        query.addBindValue(equippedItem);
        query.addBindValue(username);
        if (!query.exec()) {
            // 如果更新失败，记录错误并返回 false
            qDebug() << "Failed to update user equipped item:" << query.lastError();
            return false;
        }
    } else {
        // 如果用户不存在，尝试插入新记录
        query.prepare("INSERT INTO user_equipped_items (username, item_name) VALUES (?, ?)");
        query.addBindValue(username);
        query.addBindValue(equippedItem);
        if (!query.exec()) {
            // 如果插入失败，记录错误并返回 false
            qDebug() << "Failed to insert new user equipped item:" << query.lastError();
            return false;
        }
    }
    return true;
}

QSet<QString> Database::getUserBoughtItems(const QString &username)
{
    QSet<QString> boughtItems;
    QSqlQuery query(db);
    query.prepare("SELECT item_name FROM user_bought_items WHERE username = ?");
    query.addBindValue(username);
    if (query.exec() && query.next()) {
        do {
            boughtItems.insert(query.value(0).toString());

        } while (query.next());
    } else {

        qDebug() << "Failed to get user bought items:" << query.lastError();
    }

    if (boughtItems.isEmpty()) {
            qDebug() << "No bought items found for username: " << username;
        }
    return boughtItems;
}

QString Database::getUserEquippedItem(const QString &username)
{
    QString equippedItem;
    QSqlQuery query(db);
    query.prepare("SELECT item_name FROM user_equipped_items WHERE username = ?");
    query.addBindValue(username);
    if (query.exec() && query.next()) {
        equippedItem = query.value(0).toString();

    } else {
        qDebug() << "Failed to get user equipped item:" << query.lastError();
    }
    return equippedItem;
}

