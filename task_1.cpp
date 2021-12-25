#include <thread>

class threadRAII {
private:
	std::thread thread;
public:
	threadRAII(std::thread&& th) :thread(std::move(th)) {}

	~threadRAII() {
		if (thread.joinable()) {
			thread.join();
		}
	}
};
