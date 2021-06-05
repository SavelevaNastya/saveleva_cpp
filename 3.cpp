#include <iostream>

using namespace std;

//template <class T>
//double sum1(T t) {
//	return t;
//}
//
//template <class T, class ...Args>
//double sum1(T t, Args... args) {
//	return t + sum1(args...);
//}
//
//template <class... Args>
//double sum2(Args... arg) {
//	return (arg + ...);
//}

template <class Op, class T>
auto reduce(Op f, T a, T b) {
	return f(a, b);
}

template <class Op, class T, class... Args>
auto reduce(Op f, T t, Args... arg) {
	return f(reduce(f, arg...), t);
}

const auto lambdaPlus = [](double x, double y) {return x + y; };

int main() {

	//double res = sum1(1.0, 10);
	//cout << "3: " << res << endl;

	cout << "4: " << reduce(lambdaPlus, 6, 4, 6, 4, 6);
}