#pragma once
#include <iterator>
#include <random>
#include <algorithm>

template <typename  T, template<typename ...> typename Container>
class Stream {
private:
	Container<T> container;
public:
	Stream() {};
		/**
		 * print stream into std::ostream and return this std::ostream
		 * @example
		 * Stream s{1, 2, 3, 4, 5} | print_to(std::cout) << std::endl;
		*/
	void print_to(std::ostream& os, const char* delimiter = " ") {
		for (auto& elem : container) {
			os << elem << delimiter;
		}
	};

		/**
		* construct Stream from range [begin, end)
		* range must be alive during stream operations
		* @example Stream a(myVector.begin(), myVector.end())
		*/
	template<typename Iterator>
	Stream(Iterator begin, Iterator end) {
		for (auto it = begin; it != end; it++){
			container.push_back(*it);
		}
	};
	
		///**
		// * construct Stream from the Container
		// * container must be alive during stream operations
		// * @example Stream a(myVector)
		//*/
	template< template<typename ...> typename InputContainer>
	Stream(const InputContainer<T, std::allocator<T>>& other_cont) {
		container.reserve(other_cont.size());
		copy(other_cont.begin(), other_cont.end(), back_inserter(container));
	};

		///**
		// * construct Stream from the rref Container
		// * @example Stream a(std::move(myVector))
		//*/
	template< template<typename ...> typename InputContainer>
	Stream(InputContainer<T, std::allocator<T>>&& other_cont) {
		container.reserve(other_cont.size());
		copy(other_cont.begin(), other_cont.end(), back_inserter(container));
		other_cont.clear();
	};

		///**
		// * construct Stream from the initializer_list
		// * @example Stream a = {1, 2, 3, 4, 5}
		//*/
	Stream(std::initializer_list<T> init) {
		copy(init.begin(), init.end(), back_inserter(container));
	};

		///**
		// * constructs Stream whose values the return values
		// * of repeated calls to the generate function with no arguments.
		// * @example
		// * Stream a(rand())
		// * a | sum() //compile time error with clear message, because stream is infinite
		//*/
	/*template<typename Generator>
	Stream(Generator&& generator) {
		T elem;
		for (;;) {
			elem = generator();
			container.push_back(elem);
		}
	};*/

		///**
		// * get n elements from Stream
		// * @example
		// * Stream s(rand) | get(10) | print_to(std::cout)
		// * should be 10 random numbers
		//*/
	Container<T> get(std::size_t n) {
		Container<T> container_out;
		std::sample(container.begin(), container.end(), back_inserter(container_out),
			n, std::mt19937{ std::random_device{}() });
		return container_out;
	};

		///**
		// * construct Stream from the pack
		// * @example
		// * Stream a(1, 2, 3, 4, 10)
		//*/
	template<typename Value1, typename ...Values>
	Stream(Value1 value1, Values ...values) {
		container.push_back(value1);
		push_back_cont(container, values...);
	};
	template<typename Value1, typename ...Values, template<typename ...> typename InputContainer>
	void push_back_cont(InputContainer<T, std::allocator<T>>& cont, Value1 value1, Values ...values)
	{
		cont.push_back(value1);
		push_back_cont(cont, values...);
	};
	template<typename Value, template<typename ...> typename InputContainer>
	void push_back_cont(InputContainer<T, std::allocator<T>>& cont, Value value)
	{
		cont.push_back(value);
	};

		///**
		// * transform the stream and return a new transformed stream
		//*/
	template<typename Transform>
	Stream map(Transform&& transform) {
		Stream<T, Container> new_stream;
		for (auto& elem : new_stream.container) {
			new_stream.container.push_back(transform(container));
		}
	};

		///**
		// * @pseudocode
		// * U result = identity(stream[0]);
		// * for(T element : stream[1...]) {
		// * result = accum(result, element);
		// * }
		// * return result;
		//*/
	//template<typename Accumulator>
	//reduce(Accumulator&& accum) {};

	//template<typename Accumulator, typename IdentityFn>
	//reduce(IdentityFn&& identityFn, Accumulator&& accum) {};

		///**
		// * filter the stream and return new one
		// * @example
		// * Stream s{1, 2, 3, 4, 5} | filter([](int x) {return x % 2 == 0;})
		// * | print_to(std::cout);
		// * should be 2, 4
		//*/
	//template<typename Predicate>
	//filter(Predicate&& predicate) {};
		///**
		// * skip first amount items from the stream and return new one
		// * @example
		// * Stream s{1, 2, 3, 4, 5} | skip(3) | print_to(std::cout);
		// * should be 4, 5
		//*/
	Stream skip(std::size_t amount){
		Stream<T, Container> new_stream(container);
		new_stream.container.erase(new_stream.container.begin(), new_stream.container.begin() + amount);
		return new_stream;
	};
		///**
		// * group items in stream by N return stream of std::vector<value> with size <=N
		// * @example
		// * Stream s{1, 2, 3, 4, 5} | group(3);
		// * should be (1, 2, 3), (4, 5)
		//*/
	//Stream<std::vector, std::vector> group(std::size_t N) {};

		///**
		// * sum all values in the stream
		// * @example
		// * int s = Stream s{1, 2, 3, 4, 5} | sum();
		// * s should be 15
		//*/
	T sum() {
		T sum_of_elems = 0;
		for (auto it = container.begin(); it != container.end(); ++it) {
			sum_of_elems += *it;
		}
		return sum_of_elems;
	};

		///**
		// * convert to vector
		// * @example
		// * std::vector<int> vec = Stream s{1, 2, 3, 4, 5} | to_vector();
		// */
	std::vector<T> to_vector() {
		std::vector<T> vec;
		vec.resize(container.size());
		
		std::size_t i = 0;
		for (auto& elem : container) {
			vec[i] = elem;
			i++;
		}

		return vec;
	};

		///**
		// * get the nth element from the stream
		// * @example
		// * int third = Stream s{1, 2, 3, 4, 5} | nth(3);
		// * third should be 4
		//*/
	T N_th(std::size_t index) {
		/*if (index >= 0 & index < container.end()){
			for (auto it = container.begin(); it != container.end(); ++it) {
				if (it == index) {
					return container(*it);
				}
			}
		}*/

		/*if (index >= 0 & index < container.end()) {
			return container[index];
		}*/

		return container.at(index);

	};

};