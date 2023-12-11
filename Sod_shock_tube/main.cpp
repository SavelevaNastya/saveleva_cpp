#include "view.h"
#include "RiemannSolver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RiemannSolver solver;
    View view(&solver);
    solver.subscribe(&view);
    view.show();
    return a.exec();
}
