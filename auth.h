#ifndef AUTH_H
#define AUTH_H
#include "signup.h"

#include <QDialog>

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

private:
    signup* sn;


    Ui::auth *ui;
};

#endif // AUTH_H
