#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include <vector>
#include <utility> //for pair

using namespace std;

class Game{
private:

	vector<vector<char> > v;
	vector<vector<char> > v_temp;
	size_t n;
	size_t m;
	static const char state_alive = '*';
	static const char state_dead = '_';
	
	vector<vector<int> > NoN; /* NoN - Number of alive Neighbours*/
	
public:
	
	void convert_string_into_vectors(string s, size_t n, size_t m);
	
	void counter_of_neighbours();
	
	void change_field();

	void print_vector_of_char();
	
	int cmp_filds(int& flag);
	
};
