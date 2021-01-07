#include "main_func.h"

double func(double x){
    
    double y = exp( -pow(x,0.5)  + sin(x/10.0) );
    return y;
    
}