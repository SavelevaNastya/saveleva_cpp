//#include <iostream>
//
//using namespace std;
//
//template<class T>
//bool close_enough(T a, T b) {
//	T eps = 0.0001;
//	if (is_same<T, int>::value || is_same<T, unsigned int>::value) {
//		cout << "a = b" << endl;
//		return a == b;
//	}
//	else {
//		double res = abs(a - b);
//		cout << res << endl;
//		return (res >= eps);
//	}
//}
//
//int main()
//{
//	close_enough(1.2,1.23);
//	return 0;
//}
