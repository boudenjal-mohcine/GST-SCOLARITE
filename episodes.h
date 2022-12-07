#ifndef EPISODES_H
#define EPISODES_H

#include <QDialog>

namespace Ui {
class episodes;
}
class db_connection;
class MainWindow;

class episodes : public QDialog
{
    Q_OBJECT

public:
    int idBranch;
    explicit episodes(QWidget *parent = nullptr);
    ~episodes();

private slots:
    void on_back_clicked();

private:
    Ui::episodes *ui;
    MainWindow *mw;
};

#endif // EPISODES_H
