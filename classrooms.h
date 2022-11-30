#ifndef CLASSROOMS_H
#define CLASSROOMS_H

#include "qsqlrelationaltablemodel.h"
#include <QDialog>

namespace Ui {
class classrooms;
}

class db_connection;
class MainWindow;

class classrooms : public QDialog
{
    Q_OBJECT

public:
    explicit classrooms(QWidget *parent = nullptr);
    ~classrooms();
    void refreshTable();
    MainWindow* mw;



private slots:
    void on_back_clicked();

    void on_add_btn_clicked();

    void on_delete_btn_clicked();

    void on_update_btn_clicked();

    void on_save_btn_2_clicked();

    void on_search_btn_clicked();

private:

    Ui::classrooms *ui;
    db_connection* conn;


    QString sallesCounter;
    QString amphisCounter;
    QString departmentsCounter;
    QString classroomsCounter;
    QString averageClassroomsPerDepartment;
    QSqlRelationalTableModel* model;
};

#endif // CLASSROOMS_H
