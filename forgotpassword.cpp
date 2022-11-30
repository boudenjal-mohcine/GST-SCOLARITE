#include "forgotpassword.h"
#include "ui_forgotpassword.h"
#include "auth.h"

forgotpassword::forgotpassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forgotpassword)
{
    a = new auth;

    ui->setupUi(this);
   connect(ui->toolButton_3, SIGNAL(click()), this, SLOT(on_toolButton_3_clicked()));

}

forgotpassword::~forgotpassword()
{
    delete ui;
}

void forgotpassword::on_toolButton_3_clicked()
{


    a->show();
    forgotpassword::~forgotpassword();


}

