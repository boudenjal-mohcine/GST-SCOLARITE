#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include<QDebug>
#include "auth.h"


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    auth auth;

    auth.show();


//    w.show();

//    signup sn;
//    sn.show();

    //////////////////////////////DB_CONNECTION//////////////////////////////////////




    /////////////////////////////////////////////////////////////////////////////////

    return a.exec();
}
