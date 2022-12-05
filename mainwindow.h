#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QPropertyAnimation"
#include "auth.h"
#include "QLineSeries"
#include "QPieSeries"
#include "QChartView"
#include "QValueAxis"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class db_connection;
class subject;
class department;
class professors;
class classrooms;
class branches;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void courbeChart();
    void pieChart();


private slots:

    void on_Instructor_clicked();

    void on_Plainning_clicked();

    void on_Home_clicked();

    void on_logoutBtn_clicked();

    void on_Subject_clicked();

    void on_menuBtn_clicked();

    void on_Department_clicked();

    void on_Classrooms_2_clicked();

    void on_Branches_clicked();

    void on_branchSelect_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QPropertyAnimation* animation;
    db_connection* conn;
    auth* ath;
    subject* sbj;
    department* dpt;
    professors* pfr;
    classrooms* crm;
    branches* brc;

    QLineSeries* courbe;
    QChart* graphe;
    QValueAxis* axeY;
    QChartView* graphique;
    QPieSeries* pieSeries;
    QChart* chartPie;

};
#endif // MAINWINDOW_H
