#include <iostream>
using namespace std;

template<class T>
class my_shared_ptr {
private:
	T* ptr;
	int* counter;
public:

	my_shared_ptr() {
		ptr = nullptr;
		counter = 0;
	}
	my_shared_ptr(T* other) {
		ptr = other;
		counter = new int(1);
	}
	
	my_shared_ptr(my_shared_ptr const& other)
	{
		if (ptr == other.ptr){
			++*counter;
		}
		else{
			ptr = other.ptr;
			counter = other.counter;
			++*counter;
		}
			
	}
	
	my_shared_ptr& operator= (my_shared_ptr const& other) {
		if (this != &other) {
			--*counter;
			ptr = other.ptr;
			counter = other.counter;
			++*counter;
		}
		return *this;
	}

	my_shared_ptr& operator=(my_shared_ptr<T>&& other) noexcept
	{
		my_shared_ptr(std::move(other)).swap(*this);
		++*counter;
		--other.*counter;
		return *this;
	}

	~my_shared_ptr() {
		if (ptr != nullptr && counter == 0) {
			delete ptr;
			//cout << "destructor!" << endl;
		}
		else {
			//cout << "destructor!";
			--*counter;
		}
	}
};

class Dog {
	int d = 1;
};

int main()
{
	my_shared_ptr<Dog> ptr1 = my_shared_ptr<Dog>(new Dog);
	my_shared_ptr<Dog> ptr2 = ptr1;
	my_shared_ptr<Dog> ptr3 = my_shared_ptr<Dog>(new Dog);
	ptr2 = ptr3;

	return 0;
}