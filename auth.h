#ifndef AUTH_H
#define AUTH_H
#include <QDialog>

class signup;
class forgotpassword;
class db_connection;
class MainWindow;

namespace Ui {
class auth;
}

class auth : public QDialog
{
    Q_OBJECT

public:
    explicit auth(QWidget *parent = nullptr);
    ~auth();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_commandLinkButton_clicked();

private:
    signup* sn;
    forgotpassword* fp;

    db_connection *conn;

    Ui::auth *ui;

    MainWindow *m;
};

#endif // AUTH_H
