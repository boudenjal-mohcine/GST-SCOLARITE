#include "subjects.h"
#include "ui_subjects.h"
#include <QMessageBox>



subjects::subjects(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::subjects)
{
    ui->setupUi(this);
    this->setFixedSize(this->size().width(),this->size().height());

    conn = new db_connection();

}

subjects::~subjects()
{
    delete ui;
}
