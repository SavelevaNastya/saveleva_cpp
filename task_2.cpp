// Task 2
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;

class Car {
private:
	bool state;
public:
	Car() {
		state = 0;
	}
	void setInstance(bool new_state){
		state = new_state;
	}
	bool getInstance(){
		return state;
	}
};

class Painter {
private:
	Car* car;
public:
	Painter() {
		car = nullptr;
	}
	Painter(Car& car) {
		this->car = &car;
	}
	void Pain(){
		{
			std::unique_lock<std::mutex> ul(m);
			cv.wait(ul, [&]() {return (*car).getInstance() == 0; });
			(*car).setInstance(1);
			cv.notify_one();
		}
	}
};

class Dryer {
private:
	Car* car;
public:
	Dryer() {
		car = nullptr;
	}
	Dryer(Car& car) {
		this->car = &car;
	}
	void Dry(){
		{
		std::unique_lock<std::mutex> ul(m);
		cv.wait(ul, [&]() {return (*car).getInstance() == 1; });
		(*car).setInstance(0);
		cv.notify_one();
		}
	}
};
