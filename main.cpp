#include "mainwindow.h"
#include "db_connection.h"
#include "auth.h"
#include "signup.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include<QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    auth auth;

    auth.show();

//    w.show();

//    signup sn;
//    sn.show();

    //////////////////////////////DB_CONNECTION//////////////////////////////////////




    /////////////////////////////////////////////////////////////////////////////////

    return a.exec();
}
