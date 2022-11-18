#include "signup.h"
#include "ui_signup.h"
#include "auth.h"
#include <QMessageBox>


signup::signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
//    connect(ui->pushButton_2, SIGNAL(click()), this, SLOT(on_pushButton_2_clicked()));
    this->setFixedSize(this->size().width(),this->size().height());

    conn = new db_connection();



}

signup::~signup()
{
    delete ui;
}


void signup::on_pushButton_2_clicked()
{

    if(conn->testConnection()){

        QString username = ui->lineEdit->text();
        QString email = ui->lineEdit_2->text();
        QString password = ui->lineEdit_3->text();
        QString password_2 = ui->lineEdit_5->text();
        QString school = ui->comboBox->currentText();




        if(!email.contains("@uae.ac.ma", Qt::CaseInsensitive)||email.length()<11){

            QMessageBox::warning(this,"Attention","Email must be include @uae.ac.ma");

        } else if(password.length()<8){

            QMessageBox::warning(this,"Attention","Passwords must be greater than 8 charcarters ");


        }else if(password.contains(" ", Qt::CaseInsensitive)||password.isEmpty()||password!=password_2){

            QMessageBox::warning(this,"Attention","No matching passwords");

        }else{

          //  QMessageBox::information(this,"Attention","Succes");


        conn->query->prepare("insert into login(username, password, email, school) values(:username, :password, :email, :school)");
        conn->query->bindValue(":username", username);
        conn->query->bindValue(":password", password);
        conn->query->bindValue(":email", email);
        conn->query->bindValue(":school", school);

        conn->query->exec();


        ath = new auth;
        ath->show();
        ath->setFixedSize(ath->size());
        signup::~signup();
     }
    }else{

        QMessageBox::warning(this,"Attention","Connection Failed");

    }






}

