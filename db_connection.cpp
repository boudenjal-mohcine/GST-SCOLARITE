#include "db_connection.h"

db_connection::db_connection()
{
    this->driver="QMYSQL";
    this->localhost ="localhost";
    this->username="root";
    this->password="";
    this->dbname="gst-scolarite";

    this->db=QSqlDatabase::addDatabase(driver);
    this->db.setHostName(localhost);
    this->db.setDatabaseName(dbname);
    this->db.setUserName(username);
    this->db.setPassword(password);

    this->db.open();

    this->query = new QSqlQuery(dbname);
 //   this->record =QSqlRecord();
  //  this->field = new QSqlField();

}

db_connection::~db_connection(){

    this->db.close();
}

bool db_connection::testConnection(){

    bool response(db.open()?true: false);
    return response;

}
