#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPropertyAnimation"
#include "QtCore"
#include "QEasingCurve"
#include "QStackedWidget"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->homePage);
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

