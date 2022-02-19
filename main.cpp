#include "Stream.h"
#include <vector>
#include "iostream"
#include <list>
#include <ranges>
#include <exception>
#include <algorithm>

int main() {
	std::vector<int> myVector(10, 0);
	int k = 0;
	std::cout << "myVector elements: ";
	for (auto& elem : myVector) { elem = k; k++; }
	for (auto& elem : myVector) { std::cout << elem << " "; }
	std::cout << "\n";

	std::cout << "Stream a: ";
	//Stream<int, std::vector> a(myVector.begin(), myVector.end()) | print_to(std::cout);
	Stream<int, std::vector> a(myVector.begin(), myVector.end());
	a.print_to(std::cout);
	std::cout << "\n";

	Stream<int, std::vector> b(myVector);
	std::cout << "Stream b: ";
	b.print_to(std::cout);
	std::cout << "\n";

	Stream<int, std::vector> c(std::move(myVector));
	std::cout << "Stream c: ";
	c.print_to(std::cout);
	std::cout << "\n";

	std::cout << "list elements: { 1, 2, 3, 4, 5 }";
	std::cout << "\n";
	Stream<int, std::list> l = { 1, 2, 3, 4, 5 };
	std::cout << "Stream l: ";
	l.print_to(std::cout);
	std::cout << "\n";


	/*Stream<int, std::vector> r(rand);
	std::cout << "Stream r: ";
	r.print_to(std::cout);
	std::cout << "\n";*/

	// Get n random numbers from Stream a
	std::size_t n = 3;
	//auto rez = l | get(n) | print_to(std::cout);
	std::cout << "Get " << n << " random numbers from Stream a: ";
	auto rez = a.get(n);
	for (auto elem : rez) {
		std::cout << elem << " ";
	}
	std::cout << "\n";

	Stream<int, std::vector> p(1, 2, 3, 4, 5);
	std::cout << "Stream p (from pack): ";
	p.print_to(std::cout);
	std::cout << "\n";

	int SUM =  p.sum();
	std::cout << "Sum all values in the stream p = " << SUM << std::endl;

	std::cout << "Convert stream a to vector: ";
	auto vector_a = a.to_vector();
	for (auto& elem : vector_a) { std::cout << elem << " "; }
	std::cout << "\n";
	
	std::size_t nth = 5;
	std::cout << "Get " << nth << "th element from the stream a: ";
	std::cout << a.N_th(nth); 
	std::cout << "\n";

	std::size_t amount = 3;
	std::cout << "Skip first " << amount << " items from the stream a: ";
	auto as = a.skip(amount);
	as.print_to(std::cout);
	std::cout << "\n";
	
	std::cout << "Transform the stream a(+1): ";
	Stream<int, std::vector> transformed_stream;
	transformed_stream = a.map([]( auto& elem ) { return elem + 1; });
}