#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>

namespace Ui {
class department;
}
class MainWindow;
class db_connection;

class department : public QMainWindow
{
    Q_OBJECT

public:
    explicit department(QWidget *parent = nullptr);
    ~department();

private slots:
    void on_back_clicked();
    void refreshTable();

    void on_add_btn_2_clicked();

    void on_save_btn_clicked();

    void on_update_btn_clicked();

    void on_search_btn_2_clicked();

    void on_delete_btn_clicked();

private:
    Ui::department *ui;
    MainWindow* mw;
    db_connection* conn;
    QSqlRelationalTableModel *model;

    QString instractorsCounter;
    QString departementsCounter;
    QString episodesCounter;
    QString subjectsCounter;

};

#endif // DEPARTMENT_H
