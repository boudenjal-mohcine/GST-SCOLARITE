#ifndef SUBJECTS_H
#define SUBJECTS_H

#include <QDialog>
#include "db_connection.h"




namespace Ui {
class subjects;
}

class subjects : public QDialog
{
    Q_OBJECT

public:
    explicit subjects(QWidget *parent = nullptr);
    ~subjects();


private:
    db_connection *conn;
    Ui::subjects *ui;
};

#endif // SUBJECTS_H
