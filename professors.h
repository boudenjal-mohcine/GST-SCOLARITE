#ifndef PROFESSORS_H
#define PROFESSORS_H

#include <QSqlRelationalTableModel>
#include <QDialog>

namespace Ui {
class professors;

}
class MainWindow;
class db_connection;

class professors : public QDialog
{
    Q_OBJECT

public:
    explicit professors(QWidget *parent = nullptr);
    ~professors();
    void refreshTable();

private slots:
    void on_back_clicked();

    void on_add_btn_2_clicked();

    void on_search_btn_2_clicked();

    void on_delete_btn_clicked();

    void on_update_btn_clicked();

    void on_save_btn_clicked();

private:
    Ui::professors *ui;
    db_connection* conn;
    MainWindow* mw;

    //Counters

    QString professorsCounter;
    QString subjectsCounter;
    QSqlRelationalTableModel* model;

};

#endif // PROFESSORS_H
