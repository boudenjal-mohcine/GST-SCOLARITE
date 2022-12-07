#include "episodes.h"
#include "mainwindow.h"
#include "ui_episodes.h"

episodes::episodes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::episodes)
{
    ui->setupUi(this);


}

episodes::~episodes()
{
    delete ui;
}

void episodes::on_back_clicked()
{
    episodes::~episodes();
    mw=new MainWindow;
    mw->show();
}


