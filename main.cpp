#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include<QDebug>
#include "auth.h"
#include "mainwindow.h"


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    auth auth;

    MainWindow win;

    win.show();



    return a.exec();
}
