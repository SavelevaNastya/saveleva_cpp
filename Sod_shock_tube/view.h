#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QApplication>
#include "RiemannSolver.h"
class RiemannSolver;

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QMainWindow
{
    Q_OBJECT
    friend class TestView;
public:
    View(RiemannSolver * modelPtr, QWidget *parent = nullptr);
    void Rendering(const RiemannSolver &);
    void Rendering(const QVector<double> &,const QVector<double> &,const QVector<double> &,const QVector<double> &,const QVector<double> &);
    ~View();
    void update();

private slots:
    void on_Calculate_clicked();

    void on_Play_clicked();

    void on_Right_clicked();

    void on_Left_clicked();

    void on_Stop_clicked();

private:
    Ui::View *ui;
    RiemannSolver * model;
    bool flag = true;
};
#endif // VIEW_H
