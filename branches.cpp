#include "branches.h"
#include "db_connection.h"
#include "qchart.h"
#include "qchartview.h"
#include "qmessagebox.h"
#include "qpieseries.h"
#include "mainwindow.h"
#include "ui_branches.h"

branches::branches(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::branches)
{
    ui->setupUi(this);
    conn= new db_connection();
    model = new QSqlRelationalTableModel(this,conn->getDb());
     this->refreshTable("All");

     ui->tab_2->setDisabled(true);

     this->setFixedSize(this->size().width(),this->size().height());



}


void branches::refreshTable(const QString &arg1){




    model->setTable("branches");
    if(arg1!="All")
        model->setFilter(QString(" path = '%1'").arg(arg1));
    model->removeColumn(0);
    model->removeColumn(5);
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    model->select();
    ui->branches_table->setModel(model);
    ui->branches_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->branches_table->resizeColumnsToContents();

    pieChart();



}

branches::~branches()
{
    delete ui;
}

void branches::on_pathCombo_currentTextChanged(const QString &arg1)
{


    if(arg1=="DEUST"){

        ui->shortcutLine->setText(ui->deustCombo->currentText());
        ui->deustCombo->setEnabled(true);
        ui->nameLine->setEnabled(false);
        ui->label_8->setEnabled(false);
        ui->sectionsSpin->setEnabled(true);
        ui->sectionsSpin->setValue(1);
        ui->semestersSpin->setValue(4);

    }else{

        ui->nameLine->setEnabled(true);
        ui->label_8->setEnabled(true);
        ui->shortcutLine->setText(arg1[0]);
        ui->deustCombo->setEnabled(false);
        ui->sectionsSpin->setEnabled(false);
        ui->sectionsSpin->setValue(0);

        if(arg1=="Licence"){

            ui->semestersSpin->setValue(2);

        }else if(arg1=="Master"){

            ui->semestersSpin->setValue(4);

        }else{

            ui->semestersSpin->setValue(6);

        }


    }
    ui->nameLine->clear();

}


void branches::on_nameLine_textChanged(const QString &arg1)
{
    for(auto a:arg1){
        if(a.isUpper()){
            ui->shortcutLine->setText(ui->shortcutLine->text()+a);
            ui->nameLine->setText(ui->nameLine->text().toLower());
        }
    }

    if(arg1.length()==0){

        ui->shortcutLine->setText(ui->shortcutLine->text()[0]);

        if(ui->pathCombo->currentText()=="DEUST")
            ui->shortcutLine->setText(ui->deustCombo->currentText());




    }

}


void branches::on_deustCombo_currentTextChanged(const QString &arg1)
{
    ui->shortcutLine->setText(arg1);

}


void branches::on_add_btn_clicked()
{
    QString shortcut = ui->shortcutLine->text();
    QString name = ui->nameLine->text();
    int semesters = ui->semestersSpin->value();
    QString path = ui->pathCombo->currentText();
    int section = (ui->pathCombo->currentText()=="DEUST")?ui->sectionsSpin->value():0;
    int groups = ui->groupsSpin->value();

    char sec;

    if(conn->testConnection()){


        if(section==0){  // Check if ther is DEUST or no

            for(int j=1;j<=groups;j++){

                conn->query->prepare("insert into branches(shortcut, name, nbr_of_semesters, path, groupe, section) values(:shortcut, :name, :nbr_of_semesters, :path, :group, NULL)");
                conn->query->bindValue(":name",path+" "+ name +" "+ QString::number(j));
                conn->query->bindValue(":shortcut", shortcut+QString::number(j));
                conn->query->bindValue(":nbr_of_semesters", semesters);
                conn->query->bindValue(":path", path);
                conn->query->bindValue(":group", j);



                conn->query->exec();

            }



        }else{

            for(int i=1;i<=section;i++){

                for(int j=1;j<=groups;j++){

                    sec= (char)(64+i);

                    conn->query->prepare("insert into branches(shortcut, name, nbr_of_semesters, path, groupe, section) values(:shortcut, :name, :nbr_of_semesters, :path, :group, :section)");
                    conn->query->bindValue(":name",path+" "+shortcut+" Sec "+((char) (64+i))+" Grp "+QString::number(j));
                    conn->query->bindValue(":shortcut", shortcut +((char) (64+i))+ QString::number(j));
                    conn->query->bindValue(":nbr_of_semesters", semesters);
                    conn->query->bindValue(":path", path);
                    conn->query->bindValue(":group", j);
                    conn->query->bindValue(":section", sec);

                    qDebug() << "========================================================";
                    qDebug() << shortcut+" Sec "+((char) (64+i))+" Grp "+QString::number(j);
                    qDebug() << shortcut;
                    qDebug() << semesters;
                    qDebug() << path;
                    qDebug() << j;
                    qDebug() << sec;


                    conn->query->exec();

                }


            }


        }

        this->refreshTable("All");
        ui->tabWidget->setCurrentWidget(ui->tab_7);
        QMessageBox::information(this,"Information","Branches added successfully !!");
        ui->nameLine->clear();


    }else{

        QMessageBox::warning(this,"Attention","Error connection");

    }
}

// Pie Chart Method
void branches::pieChart()
{

    int nbrOfBranches;
    QString branche;

    pieSeries = new QPieSeries();

    conn->query->prepare("SELECT path,COUNT(id) FROM branches GROUP BY path");
    conn->query->exec();
    while(conn->query->next()){
        nbrOfBranches = conn->query->value(1).toInt();
        branche = conn->query->value(0).toString();
        pieSeries->append(branche, nbrOfBranches);
    }

    // Pie Chart
    chartPie = new QChart();
    chartPie->addSeries(pieSeries);
    chartPie->setTitle("Numbre of branches for each path");
    chartPie->setAnimationOptions(QChart::SeriesAnimations);

    QPieSlice* slice = pieSeries->slices().at(0);
    slice->setLabelVisible(true);

    QChartView* chartViewPie = new QChartView(chartPie);
    chartViewPie->setRenderHint(QPainter::Antialiasing);
    chartViewPie->setParent(ui->frame);
    chartViewPie->setFixedSize(400,400);

}

void branches::on_delete_btn_clicked()
{
    if(conn->testConnection()){

       QString shortcut = ui->deleteLine->text();



       if(!shortcut.isEmpty()){

           conn->query->prepare("select * from branches where shortcut =:shortcut");
           conn->query->bindValue(":shortcut", shortcut);

           conn->query->exec();

           if(!conn->query->next()){

               QMessageBox::warning(this,"Attention",shortcut+" not found");
               ui->deleteLine->clear();

           }else{


               conn->query->prepare("delete from branches where shortcut =:shortcut");
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


void branches::on_update_btn_clicked()
{
    QString shortcut = ui->deleteLine->text();


    if(conn->testConnection()){

        if(!shortcut.isEmpty()){

            conn->query->prepare("select id, shortcut, name from branches where shortcut=:shortcut");
            conn->query->bindValue(":shortcut", shortcut);
            conn->query->exec();

            if(conn->query->next()){

                ui->idLine->setText(conn->query->value(0).toString());
                ui->shortcutLine_2->setText(conn->query->value(1).toString());
                ui->nameLine_2->setText(conn->query->value(2).toString());
                ui->tab_2->setEnabled(true);
                ui->tabWidget->setCurrentWidget(ui->tab_2);



            }else{

                QMessageBox::warning(this,"Attention",shortcut+" Not Found");
                ui->deleteLine->clear();

            }


        }else{

            QMessageBox::warning(this,"Attention","Write something");

        }


    }else{

        QMessageBox::warning(this,"Attention","Connection error");


    }
}





void branches::on_save_btn_2_clicked()
{
    int id = ui->idLine->text().toInt();
    QString shortcut = ui->shortcutLine_2->text();
    QString name = ui->nameLine_2->text();

    if(conn->testConnection()){


        if(!shortcut.isEmpty() && !name.isEmpty()){

            //verifie if department has already chef

                       conn->query->prepare("update branches set shortcut=:shortcut, name=:name where id=:id");
                       conn->query->bindValue(":id", id);
                       conn->query->bindValue(":shortcut", shortcut);
                       conn->query->bindValue(":name", name);


                       conn->query->exec();

                       refreshTable("All");
                       ui->tabWidget->setCurrentWidget(ui->tab_7);
                       QMessageBox::information(this,"Information",shortcut+" updated successfully");

                       ui->nameLine_2->clear();
                       ui->shortcutLine_2->clear();
                       ui->idLine->clear();
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


void branches::on_comboBox_currentTextChanged(const QString &arg1)
{



        refreshTable(arg1);


}


void branches::on_back_clicked()
{
    mw = new MainWindow();

    mw->show();
    this->~branches();


}

