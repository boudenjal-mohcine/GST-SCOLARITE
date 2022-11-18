#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include "auth.h"

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

private:
    auth:auth* ath;
    Ui::signup *ui;
};

#endif // SIGNUP_H
