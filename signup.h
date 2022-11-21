#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include "db_connection.h"

class auth;
namespace Ui {
class signup;
}

class signup : public QDialog
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();

private slots:
    void on_pushButton_2_clicked();

    void on_toolButton_3_clicked();

private:
    db_connection *conn;
    auth* ath;
    Ui::signup *ui;
};

#endif // SIGNUP_H
