#include "mainwindow.h"
#include "QBarCategoryAxis"
#include "QChart"
#include "branches.h"
#include "classrooms.h"
#include "department.h"
#include "professors.h"
#include "ui_mainwindow.h"
#include "QPropertyAnimation"
#include "QEasingCurve"
#include "QStackedWidget"
#include "auth.h"
#include "subject.h"
#include "db_connection.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    conn = new db_connection();




    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->homePage);

    courbe = new QLineSeries();
    courbeChart();
    pieChart();

    this->setFixedSize(this->size().width(),this->size().height());
    QString filename = QDir::currentPath()+"/autologin.txt";
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

        QTextStream in(&file);
        QString usernameInDatabase;
        QString usernameOrEmail = in.readLine(0);
        QString queryString = "select username from users where username ='"+usernameOrEmail+"' OR email ='"+usernameOrEmail+"'";
        qDebug() << queryString;
        if(conn->testConnection()){
           // query->prepare(queryString);
            conn->query->exec(queryString);
            while(conn->query->next()){
                usernameInDatabase=conn->query->value(0).toString();
            }
        }
        else
            qDebug() << "error connection";


        ui->profBtn->setText(usernameInDatabase);
        }

void MainWindow::courbeChart()
{


    QList<QString> values;
    values.append("Monday");
    values.append("Thursday");
    values.append("Wednesday");
    values.append("Thusday");
    values.append("Friday");
    values.append("Saturday");

    int episods;
    QStringList categories;
    QBarCategoryAxis *axisX = new QBarCategoryAxis();


    if(conn->testConnection()){
        qDebug() << "Sucess";
    }
    for (int i = 0; i < values.size(); i++) {

        categories.append(values[i]);

//        conn->testConnection() ? qDebug() << "sucess" : qDebug() << "Failed";

        conn->query->prepare("select count(id) from episodes where day=:day");
        conn->query->bindValue(":day", values[i]);
        conn->query->exec();
        while(conn->query->next()){
            episods = conn->query->value(0).toInt();
            courbe->append(i, episods);
        }


    }

    // Technique n°2
    courbe->setName(QString::fromUtf8("Extérieur"));
    QPen pen(0x059605);
    pen.setWidth(3);
    pen.setStyle(Qt::DashLine);
    courbe->setPen(pen);

    // Le graphe
    graphe = new QChart();
    graphe->addSeries(courbe);
    graphe->setTitle("Graph of Episods");
    graphe->setAnimationOptions(QChart::SeriesAnimations);


    // Légende
    //graphe->legend()->hide();
    graphe->legend()->setAlignment(Qt::AlignBottom);

    // Les axes
    // Par défaut


    // Axe X
    axisX->append(categories);
    axisX->setTitleText("Days");
    graphe->addAxis(axisX, Qt::AlignBottom);
    courbe->attachAxis(axisX);

    // Axe Y
    axeY = new QValueAxis;
    axeY->setRange(0, 5);
    axeY->setLabelsVisible(true);
//    axeY->hide();
    axeY->setTitleText(QString::fromUtf8("Episods"));
    axeY->setLabelFormat("%d");
    graphe->addAxis(axeY, Qt::AlignLeft);
    courbe->setPointsVisible(true);
//    courbe->setPointLabelsFormat("@yPoint °C");
    courbe->setPointLabelsVisible(true);
    courbe->attachAxis(axeY);

    // Le widget
    graphique = new QChartView(graphe);
    graphique->setRenderHint(QPainter::Antialiasing);
//    setCentralWidget(graphique);
    graphique->setParent(ui->frame_5);
    graphique->setFixedSize(400,400);
}


// Pie Chart Method
void MainWindow::pieChart()
{

    conn = new db_connection();

    int nbOfProf;
    QString name;

    pieSeries = new QPieSeries();

    conn->query->prepare("SELECT COUNT(professors.name), departments.name FROM professors INNER JOIN departments ON  professors.id_department=departments.id GROUP BY professors.id_department");
    conn->query->exec();
    while(conn->query->next()){
        nbOfProf = conn->query->value(0).toInt();
        name = conn->query->value(1).toString().remove("Departement");
        pieSeries->append(name, nbOfProf);
    }

    // Pie Chart
    chartPie = new QChart();
    chartPie->addSeries(pieSeries);
    chartPie->setTitle("Numbre of professors in each department");
    chartPie->setAnimationOptions(QChart::SeriesAnimations);

    QPieSlice* slice = pieSeries->slices().at(0);
    slice->setLabelVisible(true);

    QChartView* chartViewPie = new QChartView(chartPie);
    chartViewPie->setRenderHint(QPainter::Antialiasing);
    chartViewPie->setParent(ui->frame_6);
    chartViewPie->setFixedSize(400,400);

}



MainWindow::~MainWindow()
{
    conn->getDb().close();
    delete ui;
}




void MainWindow::on_Instructor_clicked()
{
    MainWindow::~MainWindow();
    pfr = new professors;
    pfr->show();
}




void MainWindow::on_Plainning_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->plainningPage);
    //Remplissage du branche select

    conn->query->exec("select id,shortcut from branches");

    while(conn->query->next()){

        ui->branchSelect->addItem(conn->query->value(1).toString(), QVariant(conn->query->value(0).toString()));

    }

}





void MainWindow::on_Home_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->homePage);
}


void MainWindow::on_logoutBtn_clicked()
{


    QString filename = QDir::currentPath()+"/autologin.txt";
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

        QTextStream in(&file);
        QString username = in.readLine(0);
        QString queryString = "update users set is_logged=0 where username ='"+username+"' OR email ='"+username+"'";
        qDebug() << queryString;
    if(conn->testConnection())
       // query->prepare(queryString);
        conn->query->exec(queryString);
    else
        qDebug() << "error connection";

    conn->~db_connection();


    ath = new auth();
    ath->show();
    ath->setFixedSize(ath->size());


    this->~MainWindow();


}


void MainWindow::on_Subject_clicked()
{
    MainWindow::~MainWindow();
    sbj = new subject;
    sbj->show();

}


void MainWindow::on_menuBtn_clicked()
{

    (ui->frame_3->minimumWidth()==0)?ui->frame_3->setMinimumWidth(300):ui->frame_3->setMinimumWidth(0);


}


void MainWindow::on_Department_clicked()
{
    MainWindow::~MainWindow();
    dpt = new department;
    dpt->show();

}


void MainWindow::on_Classrooms_2_clicked()
{

    MainWindow::~MainWindow();
    crm= new classrooms;
    crm->show();

}


void MainWindow::on_Branches_clicked()
{
    MainWindow::~MainWindow();
    brc = new branches;
    brc->show();
}


void MainWindow::on_branchSelect_currentTextChanged(const QString &arg1)
{

    QMessageBox::information(this,"Attention","You selected "+arg1);

}

