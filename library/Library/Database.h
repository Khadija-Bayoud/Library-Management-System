#ifndef DATABASE_H
#define DATABASE_H

#endif // DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QDir>

class Database {

public:
    void connectDB();

private:
    QSqlDatabase db;

    QString filename = QDir::homePath() + "/libraryDB.sqlite";
};
