#include "Game.h"

#include "Functions.h"

using namespace std;


void Game::convert_string_into_vectors(string s){
	

	field_curr.resize(n);
	for (vector<char> &v : field_curr) {
		v.resize(m);
	}

	field_prev.resize(n);
	for (vector<char> &v : field_prev) {
		v.resize(m);
	}
	int i = 0;
	for( int p = 0; p < n; p++ ){
			if ( ( i + m ) <= s.length() ){
				for( int j = 0; j < m; j++ ){
					(*field_curr_p)[p][j] = s[i + j];
					(*field_prev_p)[p][j] = s[i + j];
				}
			}
			i = i + m;
	}
}

void Game::counter_of_neighbours(){

	NoN.resize(n);
	for (vector<int> &v : NoN) {
		v.resize(m);
	}

	for( int i = 0; i < n; i++ ){
			
			for( int j = 0; j < m; j++ ){
				
				int state = 0; 
				
				if( ((i-1) > -1) && ((j-1) > -1)){ 
					if ((*field_curr_p)[i-1][j-1] == state_alive ){
						state++;
					}		
				}
				
				if( ((i-1) > -1) ){ 
					if ((*field_curr_p)[i-1][j] == state_alive ){
						state++;
					}
				}
			
				if( ((i-1) > -1) && ((j+1) < m)){ 
					if ((*field_curr_p)[i-1][j+1] == state_alive ){
						state++;
					}
				}
				
				if(  ((j-1) > -1) ){   
					if ((*field_curr_p)[i][j-1] == state_alive ){
						state++;
					}
				}
			
				if(  ((j+1) < m) ){ 
					if ((*field_curr_p)[i][j+1] == state_alive ){
						state++;
					}
				}
				
				if( ((i+1) < n) && ((j-1) > -1)){ 
						if ((*field_curr_p)[i+1][j-1] == state_alive ){
						state++;
					}
				}
				
				if(i+1 < n){  
					if ((*field_curr_p)[i+1][j] == state_alive ){
						state++;
					}
				}
				
				if( ((i+1) < n) && ((j+1) < m)){ 
					if ((*field_curr_p)[i+1][j+1] == state_alive ){
						state++;
					}
				}
				NoN[i][j] = state;
			} 	
		}
	
}

int Game::change_field(int& flag){

	flag = 0;

	int count = 0;
	int count_max = n * m;

	for( int i = 0; i < n; i++ ){
		for( int j = 0; j < m ; j++){

			if ((*field_curr_p)[i][j] == state_dead ){
				if ( NoN[i][j] == 3){
					(*field_prev_p)[i][j] = state_alive;
					//count++;
				}
			}
					
			if ((*field_curr_p)[i][j] == state_alive ){
				if ( (NoN[i][j] == 3) || (NoN[i][j] == 2) ){
					(*field_prev_p)[i][j] = state_alive;
				}else{
					(*field_prev_p)[i][j] = state_dead;
					//count++;
				}
			}

			if ((*field_curr_p)[i][j] == (*field_prev_p)[i][j]) {
				count++;
			}

		}
	}

	vector<vector<char>>* v_temp_p = field_curr_p;
	*field_curr_p = *field_prev_p;
	*field_prev_p = *v_temp_p;

	if (count == count_max) {
		flag = 1;
	}

	

	return flag;
}

void Game::print_vector_of_char() {

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << (*field_curr_p)[i][j];
			}
			cout << "\n";
		}

}
