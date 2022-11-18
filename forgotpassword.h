#ifndef FORGOTPASSWORD_H
#define FORGOTPASSWORD_H

#include <QDialog>

namespace Ui {
class forgotpassword;
}

class forgotpassword : public QDialog
{
    Q_OBJECT

public:
    explicit forgotpassword(QWidget *parent = nullptr);
    ~forgotpassword();

private:
    Ui::forgotpassword *ui;
};

#endif // FORGOTPASSWORD_H
