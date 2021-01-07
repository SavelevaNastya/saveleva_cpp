#include <iostream>
#include <string>
#include <math.h>

using namespace std;


class Integral{
    
private:
    
    double a;
    double b;
    const static int n = 1000;

public:

    Integral(double a, double b){
        this->a = a;
		this->b = b;
    }
    
    double num();
};