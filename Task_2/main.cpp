#include <iostream>
#include <cctype>

using namespace std;

double a = 0;
double b = 1;
#define Ai (a + curstep * (b - a) / n)
#define Bi (Ai + (b - a) / n)

template <size_t n, size_t curstep>
struct simpson { 

    inline static const double rez = (Ai + 4.0 * (Ai + Bi) / 2.0 + Bi) * (Bi - Ai) / 6.0 + simpson<100, curstep - 1>::rez;
};

template<>
struct simpson<100, 0> {
    inline static const double rez = 0;
};

int main()
{

    double integ = simpson<100, 100>::rez;

    //static_assert(simpson<100, 100>::rez < 1, "Integral calculated incorrectly");
    //static_assert(simpson<100, 100>::rez > 0, "Integral calculated incorrectly");

    cout << "The numerical value of the integral = " << integ << endl;

}