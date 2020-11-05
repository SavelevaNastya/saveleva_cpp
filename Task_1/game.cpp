#include "Game.h"

#include "Functions.h"

using namespace std;

void Game::convert_string_into_vectors(string s, size_t n, size_t m){
	int i = 0;
	this->n = n;
	this->m = m;
	for( int p = 0; p < n; p++ ){
			if ( ( i + m ) <= s.length() ){
				vector<char> v3;
				for( int j = 0; j < m; j++ ){
					v3.insert(v3.end(), s[i+j]);	
				}
				v.insert( v.end(), v3);
				v_temp.insert( v_temp.end(), v3);
			}
			i = i + m;
	}
}

void Game::counter_of_neighbours(){
	NoN.clear();
	for( int i = 0; i < n; i++ ){
			
			vector<int> state_line;
			
			for( int j = 0; j < m; j++ ){
				
				int state = 0; 
				
				if( ((i-1) > -1) && ((j-1) > -1)){ 
					if ( this->v[i-1][j-1] == this->state_alive ){
						state++;
					}		
				}
				
				if( ((i-1) > -1) ){ 
					if ( this->v[i-1][j] == this->state_alive ){
						state++;
					}
				}
			
				if( ((i-1) > -1) && ((j+1) < m)){ 
					if ( this->v[i-1][j+1] == this->state_alive ){
						state++;
					}
				}
				
				if(  ((j-1) > -1) ){   
					if ( this->v[i][j-1] == this->state_alive ){
						state++;
					}
				}
			
				if(  ((j+1) < m) ){ 
					if ( this->v[i][j+1] == this->state_alive ){
						state++;
					}
				}
				
				if( ((i+1) < n) && ((j-1) > -1)){ 
						if ( this->v[i+1][j-1] == this->state_alive ){
						state++;
					}
				}
				
				if(i+1 < n){  
					if ( v[i+1][j] == this->state_alive ){
						state++;
					}
				}
				
				if( ((i+1) < n) && ((j+1) < m)){ 
					if ( this->v[i+1][j+1] == this->state_alive ){
						state++;
					}
				}
				state_line.insert( state_line.end(), state );	
			} 
			this->NoN.insert(NoN.end(), state_line);	
		}
	
}

void Game::change_field(){

	for( int i = 0; i < n; i++ ){
		for( int j = 0; j < m ; j++){
			if ( v[i][j] == state_dead ){
				if ( NoN[i][j] == 3){
					v[i][j] = state_alive; 										
				}
			}
					
			if ( v[i][j] == state_alive ){
				if ( (NoN[i][j] == 3) || (NoN[i][j] == 2) ){
					v[i][j] = state_alive;										
				}else{
					v[i][j] = state_dead;										
				}
			}
						
		}
	}

}

int Game::cmp_filds(int &flag){
 	flag = 0;
 	
 	int count = 0;
	int count_max = n*m;

 	for( int i = 0; i < n; i++ ){
			for( int j = 0; j < m; j++){
				if( v[i][j] != v_temp[i][j] ) {
					v_temp[i][j] = v[i][j];												
				}else{
					count++;
				}
			}
		}
		
		if(count == count_max){
			flag = 1;
		}
		
		return flag;
 }

void Game::print_vector_of_char() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << v[i][j];
		}
		cout << "\n";
	}
}
