#include <iostream>
using namespace std;

constexpr double func(double x) {
    return 1 / (x + 1);
}

const auto sum = [](double(*function)(double), double a, double b) { 
    return (function(a) + 4.0 * function((a + b) / 2.0) + function(b))* (b - a) / 6.0; 
};

constexpr double simpson(double a, double b, int n) {

    double s = 0;
    double Ai = 0;
    double Bi = 0;
    double h = (b - a) / n;

    for (int i = 0; i < n; i++) {
        Ai = a + i * h;
        Bi = Ai + h;
        s = s + sum(func,Ai,Bi);
    }

    return s;
}

int main()
{
    static_assert(simpson(0,1,100) < 1, "Integral calculated incorrectly");
    static_assert(simpson(0,1,100) > 0, "Integral calculated incorrectly");

    cout << "The numerical value of the integral = " << simpson(0, 1, 100) << endl;
}