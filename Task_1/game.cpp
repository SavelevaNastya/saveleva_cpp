#include "Game.h"

#include "Functions.h"

using namespace std;


void Game::convert_string_into_vectors(string s){
	int i = 0;
	//field_curr.reserve(n, vector<char>(m));
	//field_curr.resize(n, vector<char>(m));
	for( int p = 0; p < n; p++ ){
			if ( ( i + m ) <= s.length() ){
				vector<char> v3;
				for( int j = 0; j < m; j++ ){
					//field_curr[p][j] = s[i+j];
					v3.insert(v3.end(), s[i+j]);	
				}
				field_curr.insert(field_curr.end(), v3);
				//field_prev.insert(field_prev.end(), v3);
			}
			i = i + m;
	}
}

void Game::counter_of_neighbours(){

	//NoN.resize(n, vector<int>(m));
	NoN.clear();
	for( int i = 0; i < n; i++ ){
			
			vector<int> state_line;
			
			for( int j = 0; j < m; j++ ){
				
				int state = 0; 
				
				if( ((i-1) > -1) && ((j-1) > -1)){ 
					if ( this->field_curr[i-1][j-1] == this->state_alive ){
						state++;
					}		
				}
				
				if( ((i-1) > -1) ){ 
					if ( this->field_curr[i-1][j] == this->state_alive ){
						state++;
					}
				}
			
				if( ((i-1) > -1) && ((j+1) < m)){ 
					if ( this->field_curr[i-1][j+1] == this->state_alive ){
						state++;
					}
				}
				
				if(  ((j-1) > -1) ){   
					if ( this->field_curr[i][j-1] == this->state_alive ){
						state++;
					}
				}
			
				if(  ((j+1) < m) ){ 
					if ( this->field_curr[i][j+1] == this->state_alive ){
						state++;
					}
				}
				
				if( ((i+1) < n) && ((j-1) > -1)){ 
						if ( this->field_curr[i+1][j-1] == this->state_alive ){
						state++;
					}
				}
				
				if(i+1 < n){  
					if ( field_curr[i+1][j] == this->state_alive ){
						state++;
					}
				}
				
				if( ((i+1) < n) && ((j+1) < m)){ 
					if ( this->field_curr[i+1][j+1] == this->state_alive ){
						state++;
					}
				}
				//this->NoN[i][j] = state;
				state_line.insert( state_line.end(), state );	
			} 
			this->NoN.insert(NoN.end(), state_line);	
		}
	
}

int Game::change_field(int& flag){

	flag = 0;

	int count = 0;
	int count_max = n * m;
	vector<vector<char>>* v_temp_p;

	for( int i = 0; i < n; i++ ){
		for( int j = 0; j < m ; j++){
			if (field_curr[i][j] == state_dead ){
				if ( NoN[i][j] == 3){
					field_prev[i][j] = state_alive;
				}
			}
					
			if (field_curr[i][j] == state_alive ){
				if ( (NoN[i][j] == 3) || (NoN[i][j] == 2) ){
					field_prev[i][j] = state_alive;
				}else{
					field_prev[i][j] = state_dead;
				}
			}

			v_temp_p = field_curr_p;
			field_curr_p = field_prev_p;
			field_prev_p = v_temp_p;

			if (field_curr[i][j] == field_prev[i][j]) {
				count++;
			}
			else {
				field_prev[i][j] = field_curr[i][j];
			}

		}
	}

	if (count == count_max) {
		flag = 1;
	}
	return flag;
}

void Game::print_vector_of_char() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << field_curr[i][j];
		}
		cout << "\n";
	}
}
