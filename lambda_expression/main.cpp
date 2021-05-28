#include <iostream>
using namespace std;

constexpr double func(double x) {
    return 1 / (x + 1);
}

const auto sum = [](double(*function)(double), double a, double b, int method) {
    if (method == 0)
        return (function(a) + 4.0 * function((a + b) / 2.0) + function(b))* (b - a) / 6.0; 
    if (method == 1)
        return (function(a) + function(b)) * (b - a) / 2.0;
};

constexpr double simpson(double a, double b, int n, int method) {

    double s = 0;
    double Ai = 0;
    double Bi = 0;
    double h = (b - a) / n;

    for (int i = 0; i < n; i++) {
        Ai = a + i * h;
        Bi = Ai + h;
        s = s + sum(func,Ai,Bi, method);
    }

    return s;
}

enum Methods {
    TRAP, //0
    SIMP //1
};

int main()
{
    const Methods m(TRAP);
    static_assert(simpson(0,1,100, m) < 1, "Integral calculated incorrectly");
    static_assert(simpson(0,1,100, m) > 0, "Integral calculated incorrectly");

    cout << "The numerical value of the integral = " << simpson(0, 1, 100, m) << endl;
}