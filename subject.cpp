#include "subject.h"
#include "ui_subject.h"
#include "mainwindow.h"
#include "db_connection.h"
#include <QSqlTableModel>
#include <QMessageBox>


subject::subject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::subject)
{
    ui->setupUi(this);
    conn = new db_connection();
    model = new QSqlTableModel(this);
    refreshTable();
    ui->tab->setDisabled(true);
}

void subject::refreshTable(){

    model->setTable("subjects");
    model->removeColumn(0);
    model->select();
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    ui->subject_table->setModel(model);
    ui->subject_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->subject_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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

subject::~subject()
{
    delete ui;
}

void subject::on_back_clicked()
{

    mw=new MainWindow;
    mw->show();
    subject::~subject();

}


void subject::on_delete_btn_clicked()
{
    if(conn->testConnection()){

       QString shortcut = ui->deleteLine->text();



       if(!shortcut.isEmpty()){


               conn->query->prepare("delete from subjects where shortcut =:shortcut");
               conn->query->bindValue(":shortcut", shortcut);

                   conn->query->exec();
                   bool error = conn->query->lastError().nativeErrorCode().toInt()==1451;
                   ui->deleteLine->clear();
                   refreshTable();

                   if(error)

                          QMessageBox::warning(this,"Attention",shortcut+" is already used");

                   else

                          QMessageBox::information(this,"Information",shortcut+" deleted");

          } else {

               QMessageBox::warning(this,"Attention","Write something");

           }



      }else{

           QMessageBox::warning(this,"Attention","Connection error");

      }
}


void subject::on_add_btn_2_clicked()
{
    if(conn->testConnection()){

       QString name = ui->nameLine->text();
       QString shortcut = ui->shortcutLine->text();
       int semester = ui->semesterLine->text().toInt();

       qDebug()<<semester;

       if(!name.isEmpty()&&!shortcut.isEmpty()){

               conn->query->prepare("insert into subjects(name, shortcut, semester) values(:name, :shortcut, :semester)");
               conn->query->bindValue(":name", name);
               conn->query->bindValue(":shortcut", shortcut);
               conn->query->bindValue(":semester", semester);


               try {
                   conn->query->exec();
                   subject::refreshTable();
                   QMessageBox::information(this,"Attention","Subject added");
                   ui->nameLine->clear();
                   ui->shortcutLine->clear();
                   ui->semesterLine->clear();


               } catch (...) {

                   QMessageBox::warning(this,"Attention","Subject not added");

               }

          } else {

               QMessageBox::warning(this,"Attention","Fill all");

           }



      }else{

           QMessageBox::warning(this,"Attention","Connection error");

      }

}


void subject::on_search_btn_2_clicked()
{
    int i;
    QString shortcutOrName = ui->searchLine->text();

    for (i=0; i<model->rowCount(); ++i)
       {
           QSqlRecord record = model->record(i);
           if (record.value("name").toString().contains(shortcutOrName) || record.value("shortcut").toString().contains(shortcutOrName))
           {
               ui->subject_table->selectRow(i);
               break;
           }
       }
    if(i==model->rowCount()){

        QMessageBox::warning(this,"Attention","Subject not found");

    }

    ui->searchLine->clear();
}


void subject::on_update_btn_clicked()
{

    QString shortcut = ui->deleteLine->text();




    if(conn->testConnection()){

        if(!shortcut.isEmpty()){

            conn->query->prepare("select * from subjects where shortcut=:shortcut");
            conn->query->bindValue(":shortcut", shortcut);
            conn->query->exec();
            if(conn->query->next()){

                ui->nameLine_2->setText(conn->query->value(1).toString());
                ui->shortcutLine_2->setText(conn->query->value(2).toString());
                ui->semesterLine_2->setValue(conn->query->value(3).toInt());
                ui->idLine->setText(conn->query->value(0).toString());
                ui->tab->setEnabled(true);
                ui->tabWidget->setCurrentWidget(ui->tab);






            }else{
                ui->nameLine_2->clear();
                ui->shortcutLine_2->clear();
                ui->semesterLine_2->clear();
                ui->tab->setEnabled(false);

                QMessageBox::warning(this,"Attention",shortcut+" Not Found");

            }


        }else{

            QMessageBox::warning(this,"Attention","Write something");

        }




    }else{

        QMessageBox::warning(this,"Attention","Connection error");


    }

}


void subject::on_save_btn_clicked()
{
    int id = ui->idLine->text().toInt();
    QString newName = ui->nameLine_2->text();
    QString newShortcut = ui->shortcutLine_2->text();
    int newSemester = ui->semesterLine_2->text().toInt();


    if(conn->testConnection()){

        if(!newName.isEmpty()&&!newShortcut.isEmpty()){

            conn->query->prepare("update subjects set name=:newName, shortcut=:newShortcut, semester=:newSemester where id=:id");
            conn->query->bindValue(":newName", newName);
            conn->query->bindValue(":newShortcut", newShortcut);
            conn->query->bindValue(":newSemester", newSemester);
            conn->query->bindValue(":id", id);
            conn->query->exec();


            QMessageBox::information(this,"Information","Subject updated successfully");
            refreshTable();

            ui->nameLine_2->clear();
            ui->shortcutLine_2->clear();
            ui->semesterLine_2->clear();
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

