#include "ui_auth.h"
#include "QMessageBox"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "db_connection.h"
#include "QApplication"
#include "auth.h"
#include "signup.h"
#include "forgotpassword.h"
#include "mainwindow.h"

auth::auth(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::auth)
{
    ui->setupUi(this);

    connect(ui->pushButton_2, SIGNAL(click()), this, SLOT(on_pushButton_2_clicked()));
    connect(ui->commandLinkButton, SIGNAL(click()), this, SLOT(on_commandLinkButton_clicked()));

    this->setFixedSize(this->size().width(),this->size().height());
    conn = new db_connection();

}

auth::~auth()
{
    delete ui;
    conn->~db_connection();
}

void auth::on_pushButton_clicked()
{
        conn = new db_connection();


        conn->testConnection()?qInfo() << "successful":qInfo() <<"failed";


         if(conn->testConnection()){

            QString username = ui->lineEdit->text();
            QString password = ui->lineEdit_2->text();


            if(!username.isEmpty() && !password.isEmpty() && password.length()>=8 ){

                    conn->query->prepare("select username, password, email,is_logged from users where username =:username OR email=:username AND password=:password; ");
                    conn->query->bindValue(":username", username);
                    conn->query->bindValue(":password", password);
                    conn->query->exec();

                    if(conn->query->next()){
                               conn->query->prepare("update users set is_logged=1 where username =:username OR email=:username");
                               conn->query->bindValue(":username", username);
                               conn->query->exec();

                               QString filename = QDir::currentPath()+"/autologin.txt";
                               qDebug()<<filename;
                                  QFile file(filename);
                                  if (file.open(QIODevice::ReadWrite)) {
                                      qDebug() << "file created in path";
                                      QTextStream stream(&file);
                                      stream << username << Qt::endl;
                                  } else{
                                  qDebug() << "file open error";
                                 }


                                m = new MainWindow;
                                m->show();
                                m->setFixedSize(m->size());
                                auth::~auth();


                     }else{

                            QMessageBox::warning(this,"Attention","Username or password invalid");
                     }
                   }else{

                    QMessageBox::warning(this,"Attention","Passwords must be greater than 8 charcarters ");

               }


           } else{

                QMessageBox::warning(this,"Attention","Connection Failed");

           }


}
void auth::on_pushButton_2_clicked()
{
//    QApplication a;
    sn = new signup;
    sn->show();
    auth::~auth();
}


void auth::on_commandLinkButton_clicked()
{
    fp=new forgotpassword;
    fp->show();
    auth::~auth();


}

