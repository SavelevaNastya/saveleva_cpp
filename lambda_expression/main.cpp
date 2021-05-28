#include <iostream>
using namespace std;
//function is y=x
const auto sum = [](double a, double b) { return (a + 4.0 * (a + b) / 2.0 + b)* (b - a) / 6.0; };

constexpr double simpson(double a, double b, int n) {

    double s = 0;
    double Ai = 0;
    double Bi = 0;
    double h = (b - a) / n;

    for (int i = 0; i < n; i++) {
        Ai = a + i * h;
        Bi = Ai + h;
        s = s + sum(Ai,Bi);
    }

    return s;
}

int main()
{
    static_assert(simpson(0,1,100) < 1, "Integral calculated incorrectly");
    static_assert(simpson(0,1,100) > 0, "Integral calculated incorrectly");

    cout << "The numerical value of the integral = " << simpson(0, 1, 100) << endl;
}