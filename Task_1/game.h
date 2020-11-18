#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include <vector>
#include <utility> //for pair

using namespace std;

class Game{
private:
	size_t n;
	size_t m;
	vector<vector<char>> field_curr;
	vector<vector<char>> field_prev;
	vector<vector<char>>* field_curr_p = &field_curr;
	vector<vector<char>>* field_prev_p = &field_prev;
	static const char state_alive = '*';
	static const char state_dead = '_';
	
	vector<vector<int> > NoN; /* NoN - Number of alive Neighbours*/
	vector<vector<int>>* NoN_p = &NoN;
 	
public:

	Game(size_t n, size_t m) {
		this->n = n;
		this->m = m;
	}
	
	void convert_string_into_vectors(string s);
	
	void counter_of_neighbours();
	
	int change_field(int& flag);

	void print_vector_of_char();
	
};
