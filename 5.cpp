//#include <iostream>
//using namespace std;
//
//double f1(int x, int y) {
//	return x + y;
//}
//
//double f2(int x, int y) {
//	return x / y;
//}
//
//template <class A, class B>
//auto multiply_functions(A func1, B func2) {
//
//	const auto func3 = []() {return func1(1, 2) * func2(1, 2); };
//	return func3;
//}
//
//int main() {
//	auto func = multiply_functions(f1, f2);
//}