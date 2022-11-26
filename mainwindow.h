#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QPropertyAnimation"
#include "auth.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class db_connection;
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

private:
    Ui::MainWindow *ui;
    QPropertyAnimation* animation;
    db_connection* conn;
    auth* ath;


};
#endif // MAINWINDOW_H
