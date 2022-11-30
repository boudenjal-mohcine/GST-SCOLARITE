#include "department.h"
#include "ui_department.h"
#include "mainwindow.h"
#include "db_connection.h"
#include <QMessageBox>

department::department(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::department)
{
    ui->setupUi(this);
    conn=new db_connection();
    model = new QSqlRelationalTableModel(this);
    ui->tab->setDisabled(true);
    refreshTable();
    ui->tabWidget->setCurrentWidget(ui->departments_table);
    this->setFixedSize(this->size().width(),this->size().height());


}

void department::refreshTable(){

    model->setTable("departments");
    model->select();
    ui->departments_table->setModel(model);
    ui->departments_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->departments_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //records counter

    //////////////////

    conn->query->exec("SELECT COUNT(id) AS NumberOfProducts FROM subjects;");
    while(conn->query->next()){
        subjectsCounter=conn->query->value(0).toString();
    }
    ui->sub_counter->setText(subjectsCounter);

    //////////////////


    //////////////////

    conn->query->exec("SELECT COUNT(id) AS NumberOfProducts FROM departments;");
    while(conn->query->next()){
        departementsCounter=conn->query->value(0).toString();
    }
    ui->dep_counter->setText(departementsCounter);

    //////////////////



    //////////////////

    conn->query->exec("SELECT COUNT(id) AS NumberOfProducts FROM episodes;");
    while(conn->query->next()){
        episodesCounter=conn->query->value(0).toString();
    }
    ui->epi_counter->setText(episodesCounter);

    //////////////////



    //////////////////

    conn->query->exec("SELECT COUNT(id) AS NumberOfProducts FROM professors;");
    while(conn->query->next()){
       instractorsCounter=conn->query->value(0).toString();
    }
    ui->ins_counter->setText(instractorsCounter);

    //////////////////



}

department::~department()
{
    delete ui;
}

void department::on_back_clicked()
{

    mw = new MainWindow;

    mw->show();
    department::~department();

}


void department::on_add_btn_2_clicked()
{

    if(conn->testConnection()){

       QString name = ui->nameLine->text();


       if(!name.isEmpty()){

               conn->query->prepare("insert into departments(name) values(:name)");
               conn->query->bindValue(":name", name);


               try {
                   conn->query->exec();
                   department::refreshTable();
                   QMessageBox::information(this,"Attention","Department added");
                   ui->nameLine->clear();
                   ui->tabWidget->setCurrentWidget(ui->tab_4);


               } catch (...) {

                   QMessageBox::warning(this,"Attention","Department not added");

               }

          } else {

               QMessageBox::warning(this,"Attention","Fill the name");

           }



      }else{

           QMessageBox::warning(this,"Attention","Connection error");

      }

}


void department::on_update_btn_clicked()
{

    int id = ui->deleteLine->text().toInt();




    if(conn->testConnection()){

        if(!ui->deleteLine->text().isEmpty()){

            conn->query->prepare("select * from departments where id=:id");
            conn->query->bindValue(":id", id);
            conn->query->exec();
            if(conn->query->next()){

                ui->nameLine_2->setText(conn->query->value(1).toString());
                ui->idLine->setText(conn->query->value(0).toString());
                ui->tab->setEnabled(true);
                ui->tabWidget->setCurrentWidget(ui->tab);


            }else{
                ui->nameLine_2->clear();
                ui->tab->setEnabled(false);
                QMessageBox::warning(this,"Attention","Not Found");

            }


        }else{

            QMessageBox::warning(this,"Attention","Write something");

        }




    }else{

        QMessageBox::warning(this,"Attention","Connection error");


    }

}


void department::on_save_btn_clicked(){


    int id = ui->idLine->text().toInt();
    QString newName = ui->nameLine_2->text();


    if(conn->testConnection()){

        if(!newName.isEmpty()){

            conn->query->prepare("update departments set name=:newName where id=:id");
            conn->query->bindValue(":newName", newName);
            conn->query->bindValue(":id", id);
            conn->query->exec();


            QMessageBox::information(this,"Information","Department updated successfully");
            refreshTable();

            ui->nameLine_2->clear();
            ui->tab->setEnabled(false);
            ui->deleteLine->clear();
            ui->tabWidget->setCurrentWidget(ui->tab_4);



        }else{

            QMessageBox::warning(this,"Attention","Write something");

        }

    }else{

        QMessageBox::warning(this,"Attention","Connection error");



}
}

void department::on_search_btn_2_clicked()
{
    int i;
    QString nameOrId = ui->searchLine->text();

    for (i=0; i<model->rowCount(); ++i)
       {
           QSqlRecord record = model->record(i);
           if (record.value("id").toString().contains(nameOrId) || record.value("name").toString().contains(nameOrId))
           {
               ui->departments_table->selectRow(i);
               break;
           }
       }
    if(i==model->rowCount()){

        QMessageBox::warning(this,"Attention","department not found");

    }

    ui->searchLine->clear();
}


void department::on_delete_btn_clicked()
{
    if(conn->testConnection()){

       int id = ui->deleteLine->text().toInt();



       if(!ui->deleteLine->text().isEmpty()){

               conn->query->prepare("select * from departments where id =:id");
               conn->query->bindValue(":id", id);

               conn->query->exec();

               if(!conn->query->next()){

                   QMessageBox::warning(this,"Attention",QString::number(id)+" not found");
                   ui->deleteLine->clear();

               }else{

               conn->query->prepare("delete from departments where id =:id");
               conn->query->bindValue(":id", id);

                   conn->query->exec();
                   bool error = conn->query->lastError().nativeErrorCode().toInt()==1451;
                   ui->deleteLine->clear();
                   refreshTable();

                   if(error)

                          QMessageBox::warning(this,"Attention",ui->deleteLine->text()+" is already used");

                   else

                          QMessageBox::information(this,"Information",ui->deleteLine->text()+" deleted");
 }
          } else {

               QMessageBox::warning(this,"Attention","Write something");

           }



      }else{

           QMessageBox::warning(this,"Attention","Connection error");

      }
}

