#ifndef BRANCHES_H
#define BRANCHES_H

#include "qpieseries.h"
#include "qsqlrelationaltablemodel.h"
#include <QDialog>

namespace Ui {
class branches;
}

class db_connection;
class MainWindow;
class branches : public QDialog
{
    Q_OBJECT

public:
    explicit branches(QWidget *parent = nullptr);
    ~branches();
    void refreshTable(const QString&);
    void pieChart();

private slots:
    void on_pathCombo_currentTextChanged(const QString &arg1);

    void on_nameLine_textChanged(const QString &arg1);

    void on_deustCombo_currentTextChanged(const QString &arg1);

    void on_add_btn_clicked();

    void on_delete_btn_clicked();

    void on_update_btn_clicked();

    void on_save_btn_2_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_back_clicked();

private:
    Ui::branches *ui;
    db_connection* conn;
    QSqlRelationalTableModel* model;
    QPieSeries* pieSeries;
    QChart* chartPie;

    MainWindow* mw;


};

#endif // BRANCHES_H
