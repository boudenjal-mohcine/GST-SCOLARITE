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
    db_connection();
    bool testConnection();
};



#endif // DB_CONNECTION_H
