#include <iostream>
#include <cctype>
#include "math.h"


using namespace std;


double func(double x) {
    return exp(-pow(x, 0.5) + sin(x / 10.0));
}

constexpr double simpson(double(*function)(double), double a, double b, int n) {
    //static_assert(n <= 0, "n must be >= 0!");
    double sum = 0;
    double g = 0;
    double Ai = 0;
    double Bi = 0;
    double h = (b - a) / n;

    for (int i = 0; i < n; i++) {
        Ai = a + i * h;
        Bi = Ai + h;
        g = (function(Ai) + 4.0 * function((Ai + Bi) / 2.0) + function(Bi)) * (Bi - Ai) / 6.0;
        //static_assert( isdigit(g) == 0, "The value of integral is not a number");
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
    constexpr double a = 0;
	cout << "Set a - lower boundary of integral" << endl;
	cout << "a = ";
	//cin >> a;
	
    constexpr double b = 600;
	cout << "Set b - upper boundary of integral" << endl;
	cout << "b = ";
	//cin >> b;
	
    constexpr int n = 100;
    cout << "Set n - nubmer of splits" << endl;
    cout << "n = ";
    //cin >> n;

    Integrate(func, simpson, a, b, n);
}