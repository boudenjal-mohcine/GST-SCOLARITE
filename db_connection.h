#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H
#include <QString>
#include <QtSql>

class db_connection
{
    QSqlDatabase db;
    QString driver;
    QString localhost;
    QString username;
    QString password;
    QString dbname;

public:
    QSqlQuery *query;
    QSqlRecord record;
    QSqlField field;
    db_connection();
    QSqlDatabase getDb();
    bool testConnection();
    ~db_connection();
};



#endif // DB_CONNECTION_H
