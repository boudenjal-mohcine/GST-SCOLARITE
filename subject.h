#ifndef SUBJECT_H
#define SUBJECT_H

#include <QSqlTableModel>
#include <QDialog>

namespace Ui {
class subject;
}

class db_connection;
class MainWindow;
class subject : public QDialog
{
    Q_OBJECT

public:
    explicit subject(QWidget *parent = nullptr);
    ~subject();

private slots:
    void on_back_clicked();
    void refreshTable();

    void on_delete_btn_clicked();

    void on_add_btn_2_clicked();

    void on_search_btn_2_clicked();


    void on_update_btn_clicked();

    void on_save_btn_clicked();

private:
    Ui::subject *ui;
    MainWindow *mw;
    db_connection *conn;
    QSqlTableModel *model;


    //records counter

    QString instractorsCounter;
    QString departementsCounter;
    QString episodesCounter;
    QString subjectsCounter;

};

#endif // SUBJECT_H
