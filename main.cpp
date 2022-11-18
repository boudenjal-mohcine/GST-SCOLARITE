#include "mainwindow.h"
#include "db_connection.h"
#include "auth.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include<QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "GST-SCOLARITE_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    auth auth;

    auth.show();
//    w.show();

    //////////////////////////////DB_CONNECTION//////////////////////////////////////
    db_connection conn;
    conn.testConnection()?qInfo() << "successful":qInfo() <<"failed";

    /////////////////////////////////////////////////////////////////////////////////

    return a.exec();
}
