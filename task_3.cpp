#include <mutex>
#include <cassert> // для assert()

class Singleton {
private:
	static Singleton* singleton;
public:
	static Singleton* instance() {
		static std::mutex m;
		if (singleton == nullptr) {
			std::unique_lock<std::mutex> ul(m);
			if (singleton == nullptr) {
				singleton = new Singleton;
			}
		}
		return singleton;
	}
};
Singleton* Singleton::singleton = nullptr;

class Singleton_MB {
private:
	std::atomic<Singleton_MB*> singleton;
	std::mutex mutex;
public:
	Singleton_MB* instance() {
		Singleton_MB* tmp = singleton.load(std::memory_order_relaxed);
		std::atomic_thread_fence(std::memory_order_acquire);
		if (tmp == nullptr) {
			std::lock_guard<std::mutex> lock(mutex);
			tmp = singleton.load(std::memory_order_relaxed);
			if (tmp == nullptr) {
				tmp = new Singleton_MB;
				std::atomic_thread_fence(std::memory_order_release);
				singleton.store(tmp, std::memory_order_relaxed);
			}
		}
		return tmp;
	}
};
