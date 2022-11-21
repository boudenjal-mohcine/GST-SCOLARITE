#ifndef FORGOTPASSWORD_H
#define FORGOTPASSWORD_H

#include <QDialog>

namespace Ui {
class auth;
class forgotpassword;
}

class forgotpassword : public QDialog
{
    Q_OBJECT

public:
    explicit forgotpassword(QWidget *parent = nullptr);
    ~forgotpassword();

private slots:
    void on_toolButton_3_clicked();

private:
    Ui::forgotpassword *ui;
    Ui::auth* a;

};

#endif // FORGOTPASSWORD_H
