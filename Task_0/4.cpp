#include <iostream>

using namespace std;

template<typename T>
void MySwap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}


int main()
{
	int a = 1;
	int b = 2;
	int* aptr = new int;
	int* bptr = new int;
	*aptr = 1;
	*bptr = 2;

	cout << "before swap" << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "*aptr = " << *aptr << endl;
	cout << "*bptr = " << *bptr << endl;

	MySwap(a, b);
	MySwap(aptr, bptr);

	cout << "after swap" << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "*aptr = " << *aptr << endl;
	cout << "*bptr = " << *bptr << endl;

	delete aptr, bptr;

}
