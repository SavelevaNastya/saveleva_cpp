#include "Functions.cpp"
#include "Game.h"

using namespace std;
 
int main(void)
{

	pair<pair<size_t,size_t>, string> store = GetInfo("f:\\cpp\\tasks\\Task_1\\txt\\Test.txt");
	
	Field game;
	
	size_t n = store.first.first;
	size_t m = store.first.second;
	string info = store.second;
	
	int i = 0; /* current line (max = n)*/
	int j = 0; /* current column (max = m)*/
	
	game.convert_string_into_vectors(info, n, m);
	
	int flag = 0;
	int iter = 0;
		
	while(flag == 0){
		
		if ( iter == 0 ){
			cout << "First generation: " << endl;
		}else{
			cout << "Next generation: " << endl;
		}
		
		game.counter_of_neighbours();

		game.change_field();
		
		game.cmp_filds(flag);

		iter++;
	}	
	
}
