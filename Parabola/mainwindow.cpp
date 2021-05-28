#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->PushButton, &QPushButton::pressed, this, &MainWindow::makePlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makePlot()
{
    // a * x^2 + b * x + c = 0 //
    double a =  ui->lineEditA->text().toDouble();
    double b = ui->lineEditB->text().toDouble();
    double c = ui->lineEditC->text().toDouble();

    double N = 50, r = 10;
    double delta_x = 2*r/N;
    QVector<double> x,y;

    for(double k = 0; k <= N; k++){
        x.push_back(-r+k*delta_x);
        y.push_back(a*(-r+k*delta_x)*(-r+k*delta_x) + b*(-r+k*delta_x) + c);
    }

    ui->customPlot->clearGraphs();
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);

    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");

    ui->customPlot->xAxis->setRange(-r-5, r+5);

    ui->customPlot->yAxis->setRange(*std::min_element(y.begin(),y.end()) - 2,*std::min_element(y.begin(),y.end()) + 10);

    ui->customPlot->replot();
}
