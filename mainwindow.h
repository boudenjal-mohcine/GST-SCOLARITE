#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QPropertyAnimation"
#include "auth.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class db_connection;
class subject;
class department;
class professors;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_Instructor_clicked();

    void on_Student_clicked();

    void on_Plainning_clicked();

    void on_Courses_clicked();

    void on_Settings_clicked();

    void on_Home_clicked();

    void on_logoutBtn_clicked();

    void on_Subject_clicked();

    void on_menuBtn_clicked();

    void on_Department_clicked();

private:
    Ui::MainWindow *ui;
    QPropertyAnimation* animation;
    db_connection* conn;
    auth* ath;
    subject* sbj;
    department* dpt;
    professors* pfr;


};
#endif // MAINWINDOW_H
