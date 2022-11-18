#include "forgotpassword.h"
#include "ui_forgotpassword.h"

forgotpassword::forgotpassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forgotpassword)
{
    ui->setupUi(this);
}

forgotpassword::~forgotpassword()
{
    delete ui;
}
