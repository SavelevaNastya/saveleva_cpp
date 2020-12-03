#include "Integral.h"
#include "main_func.h"

using namespace std;

int main()
{
    double a;
	cout << "Set a - lower boundary of integral" << endl;
	cout << "a = ";
	cin >> a;
	
	double b;
	cout << "Set b - upper boundary of integral" << endl;
	cout << "b = ";
	cin >> b;
	
	Integral simpson(a,b); //Set boundary
	
	double s = 0;
	
	s = simpson.num();
	
	cout << "the numerical value of the integral = " << s << endl;
}