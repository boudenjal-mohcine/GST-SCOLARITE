#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPropertyAnimation"
#include "QEasingCurve"
#include "QStackedWidget"
#include "auth.h"
#include "subject.h"
#include "db_connection.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->homePage);
    this->setFixedSize(this->size().width(),this->size().height());
    conn = new db_connection();
    QString filename = QDir::currentPath()+"/autologin.txt";
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

        QTextStream in(&file);
        QString usernameInDatabase;
        QString usernameOrEmail = in.readLine(0);
        QString queryString = "select username from users where username ='"+usernameOrEmail+"' OR email ='"+usernameOrEmail+"'";
        qDebug() << queryString;
        if(conn->testConnection()){
           // query->prepare(queryString);
            conn->query->exec(queryString);
            while(conn->query->next()){
                usernameInDatabase=conn->query->value(0).toString();
            }
        }
        else
            qDebug() << "error connection";


        ui->profBtn->setText(usernameInDatabase);
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


void MainWindow::on_Subject_clicked()
{
    sbj = new subject;
    sbj->show();
    MainWindow::~MainWindow();

}


void MainWindow::on_menuBtn_clicked()
{

    (ui->frame_3->minimumWidth()==0)?ui->frame_3->setMinimumWidth(300):ui->frame_3->setMinimumWidth(0);


}

