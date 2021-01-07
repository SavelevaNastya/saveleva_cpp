#include "Integral.h"
#include "main_func.h"

using namespace std;

double Integral::num(){
    
    double sum = 0;
    double g = 0;
    double Ai = 0;
    double Bi = 0;
    double h = (b - a)/n;
    
    for(int i = 0; i < n; i++){
        Ai = a + i * h;
        Bi = Ai + h;
        g = ( func(Ai) + 4.0 * func( (Ai + Bi) / 2.0 ) + func(Bi) ) * (Bi - Ai) / 6.0;
        sum = sum + g;
    }
    
    return sum;
}