#include "Functions.h"
#include "Game.h"

using namespace std;

#include <iostream>
int main(void)
{
	pair<pair<size_t, size_t>, string> store;

	try{
		store = GetInfo("f:\\cpp\\tasks\\Task_1\\txt\\test.txt");
	}catch (const char* exception) {
		cout << "Error: " << exception << '\n';
		return 0;
	}

	Game game(store.first.first, store.first.second);

	string info = store.second;
	game.convert_string_into_vectors(info);

	int i = 0; /* current line (max = n)*/
	int j = 0; /* current column (max = m)*/

	int flag = 0;

	bool inter = 0;
	cout << "Choice regim of game: 0 - not interactive; 1 - interactve " << endl;
	cin >> inter;

	cout << "First generation: " << endl;
	game.print_vector_of_char();

	if (inter == 0) {
		while (flag == 0) {

			game.counter_of_neighbours();

			game.change_field(flag);

			if (flag == 0) {
				cout << "Next generation: " << endl;
				game.print_vector_of_char();
			}
			//return 0;
		}
	}else{

		int iter, k = 0;
		cout << "Enter end iter: ";
		cin >> iter;

		while (flag == 0) {

			game.counter_of_neighbours();

			game.change_field(flag);

			if (k == iter) {
				cout << k << "-iteration: " << endl;
				game.print_vector_of_char();
				return 0;
			}
			k++;
		}

		game.print_vector_of_char();

	}
	

}
