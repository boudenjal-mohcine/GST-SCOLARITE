#include "classrooms.h"
#include "ui_classrooms.h"
#include "db_connection.h"
#include "mainwindow.h"
#include <QMessageBox>

classrooms::classrooms(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::classrooms)
{

    conn = new db_connection();

    ui->setupUi(this);
    model = new QSqlRelationalTableModel(this,conn->getDb());
    this->refreshTable("All");

    ui->tab_2->setDisabled(true);

    this->setFixedSize(this->size().width(),this->size().height());




}


void classrooms::refreshTable(const QString &arg1){

    model->setTable("classrooms");
    if(arg1!="All")
        model->setFilter(QString(" type = '%1'").arg(arg1));
    model->removeColumn(0);
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    model->setRelation(3, QSqlRelation("departments", "id", "name"));
    model->select();
    model->setHeaderData(3, Qt::Horizontal, QObject::tr(" Department "));
    ui->classrooms_table->setModel(model);
    ui->classrooms_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->classrooms_table->resizeColumnsToContents();
    conn->query->exec("select * from departments");

    ui->departmentCombo->clear();
    ui->departmentCombo_2->clear();

    while(conn->query->next()){

        ui->departmentCombo->addItem(conn->query->value(1).toString(), QVariant(conn->query->value(0).toString()));
        ui->departmentCombo_2->addItem(conn->query->value(1).toString(), QVariant(conn->query->value(0).toString()));


    }

    //records counter

    //////////////////

    conn->query->exec("SELECT COUNT(id) AS Number FROM classrooms;");
    while(conn->query->next()){
        classroomsCounter=conn->query->value(0).toString();
    }
    ui->classrooms_counter->setText(classroomsCounter);

    //////////////////


    //////////////////

    conn->query->exec("SELECT COUNT(id) AS Number FROM classrooms where type='salle';");
    while(conn->query->next()){
        sallesCounter=conn->query->value(0).toString();
    }
    ui->salles_count->setText(sallesCounter);

    //////////////////


    //////////////////

    conn->query->exec("SELECT COUNT(id) AS Number FROM classrooms where type='amphi';");
    while(conn->query->next()){
        amphisCounter=conn->query->value(0).toString();
    }
    ui->amphis_count->setText(amphisCounter);

    //////////////////


    //////////////////

    conn->query->exec("SELECT COUNT(id) AS Number FROM departments ;");
    while(conn->query->next()){
        departmentsCounter=conn->query->value(0).toString();
    }

    ui->average_count->setText(QString::number((float)(departmentsCounter.toInt()/classroomsCounter.toInt()))+" %");

    //////////////////



}

classrooms::~classrooms()
{
    delete ui;
}

void classrooms::on_back_clicked()
{
    mw = new MainWindow();

    mw->show();
    this->~classrooms();

}


void classrooms::on_add_btn_clicked()
{
    QString shortcut=ui->shortcutLine->text();
    int capacity=ui->capacitySpin->value();
    int isAmphi=(ui->amphiRadio->isChecked())?1:0;
    int department=ui->departmentCombo->currentData().toInt();

 if(conn->testConnection()){

    if(!shortcut.isEmpty()){

                   conn->query->prepare("insert into classrooms(shortcut, capacity, type, id_department) values(:shortcut, :capacity, :type, :id_department)");
                   conn->query->bindValue(":id_department", department);
                   conn->query->bindValue(":shortcut", shortcut);
                   conn->query->bindValue(":capacity", capacity);
                   conn->query->bindValue(":type", (isAmphi==1)?"amphi":"salle");

                   conn->query->exec();

                   refreshTable("All");
                   ui->tabWidget->setCurrentWidget(ui->tab_7);

                   ui->shortcutLine->clear();
                   ui->capacitySpin->clear();




       } else {

            QMessageBox::warning(this,"Attention","Required shortcut");

        }




   }else{

        QMessageBox::warning(this,"Attention","Connection error");

   }
}



void classrooms::on_delete_btn_clicked()
{
    if(conn->testConnection()){

       QString shortcut = ui->deleteLine->text();



       if(!shortcut.isEmpty()){

           conn->query->prepare("select * from classrooms where shortcut =:shortcut");
           conn->query->bindValue(":shortcut", shortcut);

           conn->query->exec();

           if(!conn->query->next()){

               QMessageBox::warning(this,"Attention",shortcut+" not found");
               ui->deleteLine->clear();

           }else{


               conn->query->prepare("delete from classrooms where shortcut =:shortcut");
               conn->query->bindValue(":shortcut", shortcut);

                   conn->query->exec();
                   bool error = conn->query->lastError().nativeErrorCode().toInt()==1451;
                   ui->deleteLine->clear();
                   refreshTable("All");

                   if(error)

                          QMessageBox::warning(this,"Attention",shortcut+" is already used");

                   else

                          QMessageBox::information(this,"Information",shortcut+" deleted");
          }
          } else {

               QMessageBox::warning(this,"Attention","Write something");

           }



      }else{

           QMessageBox::warning(this,"Attention","Connection error");

      }
}


void classrooms::on_update_btn_clicked()
{
    QString shortcut = ui->deleteLine->text();


    if(conn->testConnection()){

        if(!shortcut.isEmpty()){

            conn->query->prepare("select classrooms.*, departments.name from classrooms inner join departments on classrooms.id_department = departments.id where classrooms.shortcut=:shortcut");
            conn->query->bindValue(":shortcut", shortcut);
            conn->query->exec();

            if(conn->query->next()){

                ui->idLine->setText(conn->query->value(0).toString());
                ui->shortcutLine_2->setText(conn->query->value(1).toString());
                ui->capacitySpin_2->setValue(conn->query->value(2).toInt());
                (conn->query->value(3).toString()=="amphi"?ui->amphiRadio_2->setChecked(true):ui->salleRadio_2->setChecked(true));
                ui->departmentCombo_2->setCurrentText(conn->query->value(5).toString());
                ui->tab_2->setEnabled(true);
                ui->tabWidget->setCurrentWidget(ui->tab_2);


            }else{

                QMessageBox::warning(this,"Attention",shortcut+" Not Found");

            }


        }else{

            QMessageBox::warning(this,"Attention","Write something");

        }


    }else{

        QMessageBox::warning(this,"Attention","Connection error");


    }

}


void classrooms::on_save_btn_2_clicked()
{

    int id = ui->idLine->text().toInt();
    QString newShortcut = ui->shortcutLine_2->text();
    QString newCapacity = ui->capacitySpin_2->text();
    QString newType = (ui->amphiRadio_2->isChecked())?"amphi":"salle";
    int idDepartment=ui->departmentCombo_2->currentData().toInt();


    if(conn->testConnection()){


        if(!newShortcut.isEmpty()){

            //verifie if department has already chef

                       conn->query->prepare("update classrooms set shortcut=:newShortcut, capacity=:newCapacity, type=:newType, id_department=:idDepartment where id=:id");
                       conn->query->bindValue(":id", id);
                       conn->query->bindValue(":idDepartment", idDepartment);
                       conn->query->bindValue(":newShortcut", newShortcut);
                       conn->query->bindValue(":newCapacity", newCapacity);
                       conn->query->bindValue(":newType", newType);

                       conn->query->exec();

                       refreshTable("All");
                       ui->tabWidget->setCurrentWidget(ui->tab_7);
                       QMessageBox::information(this,"Information",newShortcut+" updated successfully");

                       refreshTable("All");

                       ui->shortcutLine_2->clear();
                       ui->idLine->clear();
                       ui->capacitySpin_2->clear();
                       ui->tab_2->setEnabled(false);

                       ui->tabWidget->setCurrentWidget(ui->tab_7);
                       ui->deleteLine->clear();




        }else{

            QMessageBox::warning(this,"Attention","Write something");

        }

    }else{

        QMessageBox::warning(this,"Attention","Connection error");


    }

    ui->deleteLine->clear();
}


void classrooms::on_search_btn_clicked()
{
    int i;
    QString shortcut = ui->searchLine_2->text();

    for (i=0; i<model->rowCount(); ++i)
       {
           QSqlRecord record = model->record(i);
           if (record.value("shortcut").toString().contains(shortcut))
           {
               ui->classrooms_table->selectRow(i);
               break;
           }
       }
    if(i==model->rowCount()){

        QMessageBox::warning(this,"Attention",shortcut+" not found");

    }

    ui->searchLine_2->clear();
}


void classrooms::on_comboBox_currentTextChanged(const QString &arg1)
{

        refreshTable(arg1);

}

