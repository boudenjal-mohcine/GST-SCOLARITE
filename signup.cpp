#include "signup.h"
#include "ui_signup.h"
#include "auth.h"

signup::signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
//    connect(ui->pushButton_2, SIGNAL(click()), this, SLOT(on_pushButton_2_clicked()));

}

signup::~signup()
{
    delete ui;
}

void signup::on_pushButton_2_clicked()
{
    ath = new auth;
    ath->show();

    signup::~signup();

}

