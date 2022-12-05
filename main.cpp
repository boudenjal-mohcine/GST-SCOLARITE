#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDir>
#include<QDebug>
#include<QFile>
#include<QMessageBox>
#include "classrooms.h"
#include "auth.h"
#include "mainwindow.h"
#include "professors.h"
#include "qsqldatabase.h"
#include "qsqlquery.h"
#include "branches.h"


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
            auth.show();
        }else{

            QTextStream in(&file);
            QString username = in.readLine(0);
            QString queryString = "select is_logged from users where username = '"+username+"' OR email = '"+username+"'";
            qDebug() << queryString;

           // query->prepare(queryString);
            query->exec(queryString);

            if(query->next()){
           //  record = query->record();
             qDebug() <<query->value(0).toString();
             if(query->value(0).toString()=="1"){
                 win.show();

             }else{
                 auth.show();
             }
            }else{
                auth.show();

            }
         file.close();
        }
    }else{
        qDebug() << "Connection FAILED.";
    }



    return a.exec();
}
