#include <iostream>
#include <cctype>

using namespace std;

constexpr double func(double x) {
    return x; 
}

constexpr double simpson(double(*function)(double), double a, double b, int n) {

    double sum = 0;
    double g = 0;
    double Ai = 0;
    double Bi = 0;
    double h = (b - a) / n;

    for (int i = 0; i < n; i++) {
        Ai = a + i * h;
        Bi = Ai + h;
        g = (function(Ai) + 4.0 * function((Ai + Bi) / 2.0) + function(Bi)) * (Bi - Ai) / 6.0;
        sum = sum + g;
    }

    return sum; 
}

template<typename Meth, typename Function>
void Integrate(Function func, Meth method, double a, double b, int n) {
    cout << "The numerical value of the integral = " << method(func, a, b, n) << endl;
}

int main()
{
    constexpr double a = 0; /*lower boundary of integral*/

    constexpr double b = 1; /*upper boundary of integral*/
	
    constexpr int n = 1000; /*nubmer of splits*/

    static_assert(simpson(func, a, b, n) < 1, "Integral calculated incorrectly");
    static_assert(simpson(func, a, b, n) > 0, "Integral calculated incorrectly");

    Integrate(func, simpson, a, b, n);
}