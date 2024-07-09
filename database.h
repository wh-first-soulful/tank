#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QString>

class Database {
public:
    Database();
    ~Database();

    bool registerUser(const QString &username, const QString &password);
    bool loginUser(const QString &username, const QString &password);
    bool updateMaxScore(const QString &username, int newScore);
    bool updateTwoPlayerMaxScore(const QString &username, int newScore);
    int getMaxScore(const QString username);
    int getTwoPlayerMaxScore(const QString &username);
    QString getUserName();

    static QString currrentName;

private:
    QSqlDatabase db;
};
#endif // DATABASE_H
