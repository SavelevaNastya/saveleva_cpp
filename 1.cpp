//#include <iostream>
//#include <memory>
//using namespace std;
//
//template<class T>
//class my_shared_ptr {
//private:
//	shared_ptr<T>* ptr;
//public:
//	my_shared_ptr() {
//		ptr = nullptr;
//	}
//	
//	my_shared_ptr(const my_shared_ptr<T>& other)
//	{
//		this->ptr = other.ptr;
//	}
//
//	my_shared_ptr(shared_ptr<T>& other)
//	{
//		this->ptr = &other;
//	}
//	
//	my_shared_ptr(my_shared_ptr<T>&& other) {
//		this->ptr = other.ptr;
//		other.ptr = nullptr;
//	}
//	
//	my_shared_ptr<T>& operator= (my_shared_ptr<T> other) {
//		my_shared_ptr tmp(other);
//		return *this;
//	}
//
//	~my_shared_ptr() {
//
//	}
//};
//class B;
//
//class A {
//
//public:
//	A() {
//		cout << "A - constructor" << endl;
//	}
//	~A() {
//		cout << "A - destructor" << endl;
//	}
//
//	shared_ptr<B> Bptr;
//};
//
//class B {
//public:
//	B() {
//		cout << "B - constructor" << endl;
//	}
//	~B() {
//		cout << "B - destructor" << endl;
//	}
//
//	my_shared_ptr<A> Aptr;
//};
//int main()
//{
//	auto a = std::make_shared<A>();
//
//	a->Bptr = std::make_shared<B>();
//	a->Bptr->Aptr = a;
//
//	return 0;
//}