#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPropertyAnimation"
#include "QEasingCurve"
#include "QStackedWidget"
#include "auth.h"
#include "db_connection.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->homePage);
    this->setFixedSize(this->size().width(),this->size().height());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int extendre;

    if (true){

        int width = this->ui->frame_3->width();
        int normal = 0;
        if(width == 0){
            extendre = 200;
        }
        else {
            extendre = normal;
        }

        animation = new QPropertyAnimation(ui->menuBtn, "minimumWidth");
        animation->setDuration(300);
        animation->setStartValue(width);
        animation->setEndValue(extendre);
        animation->setEasingCurve(QEasingCurve::InOutQuad);
        animation->start();
    }

}


void MainWindow::on_Instructor_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->instructorPage);
}


void MainWindow::on_Student_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->studentPage);
}


void MainWindow::on_Plainning_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->plainningPage);
}



void MainWindow::on_Courses_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->coursesPage);
}


void MainWindow::on_Settings_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->settingsPage);
}


void MainWindow::on_Home_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->homePage);
}


void MainWindow::on_logoutBtn_clicked()
{
    conn = new db_connection();


    QString filename = QDir::currentPath()+"/autologin.txt";
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

        QTextStream in(&file);
        QString username = in.readLine(0);
        QString queryString = "update users set is_logged=0 where username ='"+username+"' OR email ='"+username+"'";
        qDebug() << queryString;
    if(conn->testConnection())
       // query->prepare(queryString);
        conn->query->exec(queryString);
    else
        qDebug() << "error connection";

    conn->~db_connection();


    ath = new auth();
    ath->show();
    ath->setFixedSize(ath->size());


    this->~MainWindow();


}

