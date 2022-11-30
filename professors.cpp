#include "professors.h"
#include "ui_professors.h"
#include "db_connection.h"
#include "mainwindow.h"
#include <QMessageBox>

professors::professors(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::professors)
{
    ui->setupUi(this);
    conn = new db_connection();
    model = new QSqlRelationalTableModel(this,conn->getDb());
    refreshTable();
    ui->tab->setDisabled(true);
    this->setFixedSize(this->size().width(),this->size().height());

}


void professors::refreshTable(){

    model->setTable("professors");
    model->removeColumn(0);
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    model->setRelation(0, QSqlRelation("departments", "id", "name"));
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr(" Department "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr(" Chef of Department "));
    ui->professors_table->setModel(model);
    ui->professors_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->professors_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->professors_table->resizeColumnsToContents();
    conn->query->exec("select * from departments");

    ui->departmentCombo->clear();
    ui->departmentCombo_2->clear();

    while(conn->query->next()){

        ui->departmentCombo->addItem(conn->query->value(1).toString(), QVariant(conn->query->value(0).toString()));
        ui->departmentCombo_2->addItem(conn->query->value(1).toString(), QVariant(conn->query->value(0).toString()));


    }

    //records counter

    //////////////////

    conn->query->exec("SELECT COUNT(id) AS Number FROM professors;");
    while(conn->query->next()){
        professorsCounter=conn->query->value(0).toString();
    }
    ui->prof_counter->setText(professorsCounter);

    //////////////////


    //////////////////

    conn->query->exec("SELECT COUNT(id) AS Number FROM subjects;");
    while(conn->query->next()){
        subjectsCounter=conn->query->value(0).toString();
    }
    ui->sub_counter->setText(subjectsCounter);

    //////////////////


}

professors::~professors()
{
    delete ui;
}

void professors::on_back_clicked()
{
    mw=new MainWindow;
    mw->show();
    professors::~professors();
}


void professors::on_add_btn_2_clicked()
{
    QString name=ui->nameLine->text();
    QString email=ui->emailLine->text()+"@uae.ac.ma";
    QString phone=ui->phoneLine->text();
    QString department=ui->departmentCombo->currentText();
    int isChef = (ui->isChef->isChecked())?1:0;

 if(conn->testConnection()){

    if(!name.isEmpty()&&!email.isEmpty()&&!phone.isEmpty()){

        try {

            phone.toInt();

        } catch (...) {

            QMessageBox::warning(this,"Attention","Number phone must be valid");

        }

        //verifie if department has already chef


           if(isChef==1){

                conn->query->exec("select name from professors where id_department="+QString::number(ui->departmentCombo->currentData().toInt())+" AND is_chef=1");

                if(conn->query->next()){
                    QMessageBox::warning(this,"Attention",conn->query->value(0).toString()+" is already chef. Please update his statue");
                }else{

                   conn->query->prepare("insert into professors(id_department, name, email, phone, is_chef) values(:id_department, :name, :email, :phone, 1)");
                   conn->query->bindValue(":id_department", ui->departmentCombo->currentData().toInt());
                   conn->query->bindValue(":name", name);
                   conn->query->bindValue(":email", email);
                   conn->query->bindValue(":phone", phone);

                   conn->query->exec();

                   refreshTable();
                   ui->tabWidget->setCurrentWidget(ui->tab_4);

                   ui->nameLine->clear();
                   ui->emailLine->clear();
                   ui->phoneLine->clear();
                   ui->tab->setEnabled(false);
                   ui->emailLine_2->clear();
               }

            }else{

               conn->query->prepare("insert into professors(id_department, name, email, phone, is_chef) values(:id_department, :name, :email, :phone, 0)");
               conn->query->bindValue(":id_department", ui->departmentCombo->currentData().toInt());
               conn->query->bindValue(":name", name);
               conn->query->bindValue(":email", email);
               conn->query->bindValue(":phone", phone);

               conn->query->exec();

               refreshTable();
               ui->tabWidget->setCurrentWidget(ui->tab_4);
            }





       } else {

            QMessageBox::warning(this,"Attention","Write something");

        }




   }else{

        QMessageBox::warning(this,"Attention","Connection error");

   }
}

void professors::on_search_btn_2_clicked()
{
    int i;
    QString shortcutOrName = ui->searchLine->text();

    for (i=0; i<model->rowCount(); ++i)
       {
           QSqlRecord record = model->record(i);
           if (record.value("name").toString().contains(shortcutOrName) || record.value("email").toString().contains(shortcutOrName) || record.value("phone").toString().contains(shortcutOrName) || record.value("Department").toString().contains(shortcutOrName))
           {
               ui->professors_table->selectRow(i);
               break;
           }
       }
    if(i==model->rowCount()){

        QMessageBox::warning(this,"Attention","Professor not found");

    }

    ui->searchLine->clear();
}


void professors::on_delete_btn_clicked()
{
    if(conn->testConnection()){

       QString nameOrEmail = ui->deleteLine->text();



       if(!nameOrEmail.isEmpty()){

               conn->query->prepare("select * from professors where name =:nameOrEmail OR email=:nameOrEmail");
               conn->query->bindValue(":nameOrEmail", nameOrEmail);

               conn->query->exec();

               if(!conn->query->next()){

                   QMessageBox::warning(this,"Attention",nameOrEmail+" not found");
                   ui->deleteLine->clear();

               }else{

                   conn->query->prepare("delete from professors where name =:nameOrEmail OR email=:nameOrEmail");
                   conn->query->bindValue(":nameOrEmail", nameOrEmail);

                   conn->query->exec();
                   bool errorUsed = conn->query->lastError().nativeErrorCode().toInt()==1451;
                   ui->deleteLine->clear();
                   refreshTable();

                   if(errorUsed)

                          QMessageBox::warning(this,"Attention",nameOrEmail+" is already used");

                   else

                          QMessageBox::information(this,"Information",nameOrEmail+" deleted");


            }
          } else {

               QMessageBox::warning(this,"Attention","Write something");

           }



      }else{

           QMessageBox::warning(this,"Attention","Connection error");

      }
}


void professors::on_update_btn_clicked()
{
    QString nameOrEmail = ui->deleteLine->text();


    if(conn->testConnection()){

        if(!nameOrEmail.isEmpty()){

            conn->query->prepare("select professors.*, departments.name from professors inner join departments on professors.id_department = departments.id where professors.name=:nameOrEmail OR professors.email=:nameOrEmail");
            conn->query->bindValue(":nameOrEmail", nameOrEmail);
            conn->query->exec();

            if(conn->query->next()){

                ui->idLine_2->setText(conn->query->value(0).toString());
                ui->nameLine_2->setText(conn->query->value(2).toString());
                ui->emailLine_2->setText(conn->query->value(3).toString().remove("@uae.ac.ma"));
                ui->phoneLine_2->setText(conn->query->value(4).toString());
                (conn->query->value(5).toInt()==1)?ui->isChef_2->setChecked(true):ui->isChef_2->setChecked(false);
                ui->departmentCombo_2->setCurrentText(conn->query->value(6).toString());
                ui->tab->setEnabled(true);
                ui->tabWidget->setCurrentWidget(ui->tab);


            }else{
                ui->nameLine_2->clear();
                ui->emailLine_2->clear();
                ui->phoneLine_2->clear();
                ui->idLine_2->clear();
                ui->tab->setEnabled(false);

                QMessageBox::warning(this,"Attention",nameOrEmail+" Not Found");

            }


        }else{

            QMessageBox::warning(this,"Attention","Write something");

        }


    }else{

        QMessageBox::warning(this,"Attention","Connection error");


    }

}


void professors::on_save_btn_clicked()
{
    int id = ui->idLine_2->text().toInt();
    QString newName = ui->nameLine_2->text();
    QString newPhone = ui->phoneLine_2->text();
    QString newEmail = ui->emailLine_2->text()+"@uae.ac.ma";
    QString newDepartment = ui->departmentCombo_2->currentText();
    int idDepartment;
    int newIsChef = (ui->isChef_2->isChecked())?1:0;


    if(conn->testConnection()){

            //get department id:

                conn->query->exec("select id from departments where name = '"+newDepartment+"'");
                if(conn->query->next())
                    idDepartment=conn->query->value(0).toInt();

        if(!newName.isEmpty()&&!newPhone.isEmpty()&&!ui->emailLine_2->text().isEmpty()){

            //verifie if department has already chef


               if(newIsChef==1){

                    conn->query->exec("select name from professors where id_department="+QString::number(idDepartment)+" AND is_chef=1 AND name <> '"+ui->nameLine_2->text()+"'");

                    if(conn->query->next()){
                        QMessageBox::warning(this,"Attention",conn->query->value(0).toString()+" is already chef. Please update his statue");
                    }else{

                       conn->query->prepare("update professors set name=:newName, email=:newEmail, phone=:newPhone, id_department=:idDepartment, is_chef=1 where id=:id");
                       conn->query->bindValue(":id", id);
                       conn->query->bindValue(":idDepartment", idDepartment);
                       conn->query->bindValue(":newName", newName);
                       conn->query->bindValue(":newEmail", newEmail);
                       conn->query->bindValue(":newPhone", newPhone);
                       conn->query->bindValue(":newDepartment", newDepartment);
                       conn->query->bindValue(":newPhone", newPhone);

                       conn->query->exec();

                       refreshTable();
                       ui->tabWidget->setCurrentWidget(ui->tab_4);
                       QMessageBox::information(this,"Information",newName+" updated successfully in "+newDepartment+((newIsChef==1)?" as chef":"") );

                       refreshTable();

                       ui->nameLine_2->clear();
                       ui->idLine_2->clear();
                       ui->phoneLine_2->clear();
                       ui->tab->setEnabled(false);
                       ui->emailLine_2->clear();

                       ui->tabWidget->setCurrentWidget(ui->tab_4);
                       ui->deleteLine->clear();


                   }

                }else{


                   conn->query->prepare("update professors set name=:newName, email=:newEmail, phone=:newPhone, id_department=:idDepartment, is_chef=0 where id=:id");
                   conn->query->bindValue(":idDepartment", idDepartment);
                   conn->query->bindValue(":id", id);
                   conn->query->bindValue(":newName", newName);
                   conn->query->bindValue(":newEmail", newEmail);
                   conn->query->bindValue(":newPhone", newPhone);
                   conn->query->bindValue(":newDepartment", newDepartment);
                   conn->query->bindValue(":newPhone", newPhone);

                   conn->query->exec();

                   refreshTable();
                   ui->tabWidget->setCurrentWidget(ui->tab_4);
                   QMessageBox::information(this,"Information",newName+" updated successfully in "+newDepartment+((newIsChef==1)?" as chef":"") );

                   refreshTable();

                   ui->nameLine_2->clear();
                   ui->idLine_2->clear();
                   ui->phoneLine_2->clear();
                   ui->tab->setEnabled(false);
                   ui->emailLine_2->clear();

                   ui->tabWidget->setCurrentWidget(ui->tab_4);
                   ui->deleteLine->clear();


                }





        }else{

            QMessageBox::warning(this,"Attention","Write something");

        }

    }else{

        QMessageBox::warning(this,"Attention","Connection error");


    }

    ui->deleteLine->clear();


}

