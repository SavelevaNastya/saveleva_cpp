#include "view.h"
#include "ui_view.h"

View::View(RiemannSolver * modelPtr, QWidget *parent): QMainWindow(parent), ui(new Ui::View)
{
    model = modelPtr;
    ui->setupUi(this);
}

View::~View()
{
    delete ui;
}

void View::Rendering(const RiemannSolver & solver){
    ui->DensityPlot->clearGraphs();
    ui->DensityPlot->addGraph();
    ui->DensityPlot->graph(0)->setData(solver.Position, solver.rho);
    ui->DensityPlot->xAxis->setRange(ui->Lmin->text().toDouble(), ui->Lmax->text().toDouble());
    ui->DensityPlot->yAxis->setRange(*std::min_element(solver.rho.begin(),solver.rho.end())
                                     ,*std::max_element(solver.rho.begin(),solver.rho.end()));
    ui->DensityPlot->replot();


    ui->PressurePlot->clearGraphs();
    ui->PressurePlot->addGraph();
    ui->PressurePlot->graph(0)->setData(solver.Position,solver.Pressure);
    ui->PressurePlot->xAxis->setRange(ui->Lmin->text().toDouble(), ui->Lmax->text().toDouble());
    ui->PressurePlot->yAxis->setRange(*std::min_element(solver.Pressure.begin(),solver.Pressure.end())
                                     ,*std::max_element(solver.Pressure.begin(),solver.Pressure.end()));
    ui->PressurePlot->replot();

    ui->TemperaturePlot->clearGraphs();
    ui->TemperaturePlot->addGraph();
    ui->TemperaturePlot->graph(0)->setData(solver.Position,solver.Temperature);
    ui->TemperaturePlot->xAxis->setRange(ui->Lmin->text().toDouble(), ui->Lmax->text().toDouble());
    ui->TemperaturePlot->yAxis->setRange(*std::min_element(solver.Temperature.begin(),solver.Temperature.end()) - 0.1
                                     ,*std::max_element(solver.Temperature.begin(),solver.Temperature.end()));
    ui->TemperaturePlot->replot();


    ui->VelocityPlot->clearGraphs();
    ui->VelocityPlot->addGraph();
    ui->VelocityPlot->graph(0)->setData(solver.Position,solver.Velocity);
    ui->VelocityPlot->xAxis->setRange(ui->Lmin->text().toDouble(), ui->Lmax->text().toDouble());
    ui->VelocityPlot->yAxis->setRange(*std::min_element(solver.Velocity.begin(),solver.Velocity.end())
                                     ,*std::max_element(solver.Velocity.begin(),solver.Velocity.end()));
    ui->VelocityPlot->replot();
}

void View::Rendering( const QVector<double> & Pos,const QVector<double> & P,const QVector<double> &U,
                      const QVector<double> & T,const QVector<double> &D){
    ui->DensityPlot->clearGraphs();
    ui->DensityPlot->addGraph();
    ui->DensityPlot->graph(0)->setData(Pos,D);
    ui->DensityPlot->xAxis->setRange(ui->Lmin->text().toDouble(), ui->Lmax->text().toDouble());
    ui->DensityPlot->yAxis->setRange(*std::min_element(D.begin(),D.end())
                                     ,*std::max_element(D.begin(),D.end()));
    ui->DensityPlot->replot();


    ui->PressurePlot->clearGraphs();
    ui->PressurePlot->addGraph();
    ui->PressurePlot->graph(0)->setData(Pos,P);
    ui->PressurePlot->xAxis->setRange(ui->Lmin->text().toDouble(), ui->Lmax->text().toDouble());
    ui->PressurePlot->yAxis->setRange(*std::min_element(P.begin(),P.end())
                                     ,*std::max_element(P.begin(),P.end()));
    ui->PressurePlot->replot();

    ui->TemperaturePlot->clearGraphs();
    ui->TemperaturePlot->addGraph();
    ui->TemperaturePlot->graph(0)->setData(Pos,T);
    ui->TemperaturePlot->xAxis->setRange(ui->Lmin->text().toDouble(), ui->Lmax->text().toDouble());
    ui->TemperaturePlot->yAxis->setRange(*std::min_element(T.begin(),T.end()) - 0.1
                                     ,*std::max_element(T.begin(),T.end()));
    ui->TemperaturePlot->replot();


    ui->VelocityPlot->clearGraphs();
    ui->VelocityPlot->addGraph();
    ui->VelocityPlot->graph(0)->setData(Pos,U);
    ui->VelocityPlot->xAxis->setRange(ui->Lmin->text().toDouble(), ui->Lmax->text().toDouble());
    ui->VelocityPlot->yAxis->setRange(*std::min_element(U.begin(),U.end())
                                     ,*std::max_element(U.begin(),U.end()));
    ui->VelocityPlot->replot();
}

void View::on_Calculate_clicked()
{
    double uL = ui->VelocityLeft->text().toDouble();
    double uR = ui->VelocityRight->text().toDouble();
    double pL = ui->PressureLeft->text().toDouble();
    double pR = ui->PressureRight->text().toDouble();
    double dR = ui->DensityRight->text().toDouble();
    double dL = ui->DensityLeft->text().toDouble();
    int Nx = ui->Nx->text().toInt();
    double leght = ui->Lmax->text().toDouble() - ui->Lmin->text().toDouble();

    model->state.Nx = Nx;
    model->state.MPa = 1.0;
    model->state.Lenght = leght;
    model->state.VarOnLeftSide[0] = dL;
    model->state.VarOnLeftSide[1] = uL;
    model->state.VarOnLeftSide[2] = pL;

    model->state.VarOnRightSide[0] = dR;
    model->state.VarOnRightSide[1] = uR;
    model->state.VarOnRightSide[2] = pR;

    model->gammas.gamma = model->state.gamma;
    double time = model->state.timeout;

    model->Pressure.resize(Nx);
    model->Velocity.resize(Nx);
    model->rho.resize(Nx);
    model->Temperature.resize(Nx);
    model->Position.resize(Nx);

    model->Solve(time);
}

void View::on_Play_clicked()
{
    double uL = ui->VelocityLeft->text().toDouble();
    double uR = ui->VelocityRight->text().toDouble();
    double pL = ui->PressureLeft->text().toDouble();
    double pR = ui->PressureRight->text().toDouble();
    double dR = ui->DensityRight->text().toDouble();
    double dL = ui->DensityLeft->text().toDouble();
    int Nx = ui->Nx->text().toInt();
    double length = ui->Lmax->text().toDouble() - ui->Lmin->text().toDouble();

    model->state.Nx = Nx;
    model->state.MPa = 1.0;
    model->state.Lenght = length;
    model->state.VarOnLeftSide[0] = dL;
    model->state.VarOnLeftSide[1] = uL;
    model->state.VarOnLeftSide[2] = pL;

    model->state.VarOnRightSide[0] = dR;
    model->state.VarOnRightSide[1] = uR;
    model->state.VarOnRightSide[2] = pR;

    model->state.SetFromFile("data.txt");

    model->gammas.gamma = model->state.gamma;
    double timeout = model->state.timeout;

    ui->Stop->setEnabled(true);
    flag = true;
    double dt = model->state.dt;
    double time = 0;
    int N = timeout/dt;

    model->Pressure.resize(Nx);
    model->Velocity.resize(Nx);
    model->rho.resize(Nx);
    model->Temperature.resize(Nx);
    model->Position.resize(Nx);

    for(int i = 1; i <= N; i++){

        /*QVector<double> Pos(Nx);
        QVector<double> Press(Nx);
        QVector<double> Temp(Nx);
        QVector<double> Vel(Nx);
        QVector<double> Den(Nx);

        for(int j = 0; j < Nx; j++){
            Pos[j] = solver.Position[j + i*Nx];
            Press[j] = solver.Pressure[j + i*Nx];
            Temp[j] = solver.Temperature[j + i*Nx];
            Vel[j] = solver.Velocity[j + i*Nx];
            Den[j] = solver.rho[j + i*Nx];
        }*/

        time = i*dt;
        model->Solve(time);
        QCoreApplication::processEvents(QEventLoop::AllEvents);

        if(flag == false){
            break;
        }
    }
}

void View::on_Right_clicked()
{

    double uL = ui->VelocityLeft->text().toDouble();
    double uR = ui->VelocityRight->text().toDouble();
    double pL = ui->PressureLeft->text().toDouble();
    double pR = ui->PressureRight->text().toDouble();
    double dR = ui->DensityRight->text().toDouble();
    double dL = ui->DensityLeft->text().toDouble();
    int Nx = ui->Nx->text().toInt();
    double leght = ui->Lmax->text().toDouble() - ui->Lmin->text().toDouble();

    model->state.Nx = Nx;
    model->state.MPa = 1.0;
    model->state.Lenght = leght;
    model->state.VarOnLeftSide[0] = dL;
    model->state.VarOnLeftSide[1] = uL;
    model->state.VarOnLeftSide[2] = pL;

    model->state.VarOnRightSide[0] = dR;
    model->state.VarOnRightSide[1] = uR;
    model->state.VarOnRightSide[2] = pR;

    model->gammas.gamma = model->state.gamma;
    double timeout = model->state.timeout;
    double cur_time = model->current_time;

    model->Pressure.resize(Nx);
    model->Velocity.resize(Nx);
    model->rho.resize(Nx);
    model->Temperature.resize(Nx);
    model->Position.resize(Nx);

    if (cur_time - model->state.dt >= timeout){
        ui->Right->setEnabled(false);
        cur_time = timeout;
        return;
    }
    if(cur_time > 0){
        ui->Left->setEnabled(true);
    }
    model->Solve(cur_time + model->state.dt);

}

void View::on_Left_clicked()
{
    double uL = ui->VelocityLeft->text().toDouble();
    double uR = ui->VelocityRight->text().toDouble();
    double pL = ui->PressureLeft->text().toDouble();
    double pR = ui->PressureRight->text().toDouble();
    double dR = ui->DensityRight->text().toDouble();
    double dL = ui->DensityLeft->text().toDouble();
    int Nx = ui->Nx->text().toInt();
    double leght = ui->Lmax->text().toDouble() - ui->Lmin->text().toDouble();

    model->state.Nx = Nx;
    model->state.MPa = 1.0;
    model->state.Lenght = leght;
    model->state.VarOnLeftSide[0] = dL;
    model->state.VarOnLeftSide[1] = uL;
    model->state.VarOnLeftSide[2] = pL;

    model->state.VarOnRightSide[0] = dR;
    model->state.VarOnRightSide[1] = uR;
    model->state.VarOnRightSide[2] = pR;

    model->gammas.gamma = model->state.gamma;
    double timeout = model->state.timeout;
    double cur_time = model->current_time;

    model->Pressure.resize(Nx);
    model->Velocity.resize(Nx);
    model->rho.resize(Nx);
    model->Temperature.resize(Nx);
    model->Position.resize(Nx);


    if(cur_time >= model->state.dt){
        cur_time -= model->state.dt;
    }
    model->Solve(cur_time);

}


void View::on_Stop_clicked()
{
    flag = false;
}

void View::update(){
    Rendering(*model);
}
