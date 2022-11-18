#include "auth.h"
#include "ui_auth.h"
#include "QMessageBox"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "db_connection.h"

auth::auth(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::auth)
{
    ui->setupUi(this);
//    on_pushButton_clicked();

}

auth::~auth()
{
    delete ui;
}

void auth::on_pushButton_clicked()
{

        db_connection conn;
        conn.testConnection()?qInfo() << "successful":qInfo() <<"failed";

        QSqlQuery* request = new QSqlQuery("GST-SCOLARITE");


        QString username = ui->lineEdit->text();
        QString password = ui->lineEdit_2->text();

        request->prepare("insert into login(username, password) values(:username, :password)");
        request->bindValue(":username", username);
        request->bindValue(":password", password);

        request->exec();

//        QMessageBox::warning(this, "Attention", "username: "+username+", password: "+password);


//        QMessageBox::information(this, "Envoi vers BD", "Envoi complet");

}

