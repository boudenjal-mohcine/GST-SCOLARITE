#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDir>
#include<QDebug>
#include<QFile>
#include<QMessageBox>
#include "auth.h"
#include "mainwindow.h"
#include "qsqldatabase.h"
#include "qsqlquery.h"
#include "qsqlrecord.h"


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    auth auth;
    MainWindow win;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("GST-SCOLARITE");

    //QSqlRecord record;
    if(db.open())
    {
        QSqlQuery *query=new QSqlQuery("GST-SCOLARITE");

        QString filename = QDir::currentPath()+"/autologin.txt";
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", file.errorString());
        }

            QTextStream in(&file);
            QString queryString = "select is_logged from users where username = '"+in.readLine(0)+"'";
            qDebug() << queryString;

           // query->prepare(queryString);
            query->exec(queryString);

            while(query->next()){
           //  record = query->record();
             qDebug() <<query->value(0).toString();
             if(query->value(0).toString()=="1"){
                 win.show();

             }else{
                 auth.show();
             }
            }
         file.close();
    }else{
        qDebug() << "Connection FAILED.";
    }
/*
    }else{
    qDebug() << "Connection FAILED.";

    }

   //     QMessageBox::warning(0,"Information","Connection success");
   //     conn->testConnection()?qInfo() << "successful":qInfo() <<"failed";

        /*QString filename = QDir::currentPath()+"/autologin.txt";
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", file.errorString());
        }

            QTextStream in(&file);
            QString queryString = "select is_logged from users where username = '"+in.readLine(0)+"'";
            qDebug() << queryString;

         conn->query->prepare(queryString);
         conn->query->exec();

         conn->record = conn->query->record();
         qDebug() <<conn->query->value(0).toString();
         if(conn->query->value(0).toString()=="1"){
             win.show();

         }else{
             auth.show();
         }

         file.close();*/
/*
    }else{

         QMessageBox::warning(0,"Attention","Connection Failed");

     }
     */

  //  conn->~db_connection();

    return a.exec();
}
