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



    return a.exec();
}
