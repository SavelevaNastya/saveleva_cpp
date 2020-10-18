#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <Windows.h>
#include <regex>
#include <map>
#include <algorithm>
#include "Task_0.h"

struct cmp{
	bool operator()(const pair<string, size_t> &a, const pair<string, size_t> &b)
	{
		return a.second > b.second;
	}
};

void text::sorting(map<string, int>& M, map<string,double>& M2) 
{ 
    vector<pair<string, int> > A; 
    vector<pair<string, double> > A2;
    
    for (auto& it : M) { // Copy key-value pair from Map to vector of pairs 
        A.push_back(it); 
    } 
    for (auto& it2 : M2) { 
        A2.push_back(it2); 
    } 
    sort(A.begin(), A.end(), cmp()); // Sort using comparator function
    sort(A2.begin(), A2.end(), cmp()); 

    for ( auto& it : A  ) {     // Print the sorted value 
    	for (auto& it2 : A2 ){
    		if (it2.first == it.first){
    		cout << it.first << " " << it.second << " " << it2.second << endl; 
			}
		}
    } 
}

vector<string> split_up(const string & s, string rgx_str = "\\s+") {
    vector<string> elems;
    regex rgx(rgx_str);
    sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
    sregex_token_iterator end;
    while (iter != end)  {
    	elems.push_back(*iter);
        ++iter;
    }
    return elems;
}

void text::set_vector(string adres){
	ifstream test;
	test.open(adres); //Open file
	string s;
	while(getline(test,s)){
		size_t i = 0;
		while (i <= s.length()) {
    			s[i] = (char)tolower(s[i]); //Set lower register for all letters 
    			i++;                                   
    		}
    	s.erase(remove(s.begin(), s.end(), '.' ), s.end());
    	s.erase(remove(s.begin(), s.end(), ',' ), s.end());
    	s.erase(remove(s.begin(), s.end(), '!' ), s.end());
    	s.erase(remove(s.begin(), s.end(), '?' ), s.end()); 
		s.erase(remove(s.begin(), s.end(), ';' ), s.end()); 
		s.erase(remove(s.begin(), s.end(), ':' ), s.end());		
    	vector<string> test_vector = split_up(s); //Split vector of letters into words
    	this->v1.insert(end(v1), begin(test_vector), end(test_vector));
	}
	test.close(); //Close our file*/
}
	
vector<string> text::get_unique_words(){
	vector<string> v_temp(v1);
	int n = 0; 
	int k = 0;
	while (n < v_temp.size() ){ 
		k = n + 1;
		while (k < v_temp.size()){
			if(v_temp[n] != v_temp[k]){
				k++;
			}else{
				v_temp[k] = " ";
				k++;
			}
		} 
		if(v_temp[n] != " "){
			this->v2.push_back(v_temp[n]); // Vector of unique words
		}
		n++;
	} 
	return this->v2;
}
	
void text::counter_of_freq(map <string, int>& m, map <string, double>& m_freq){
	int n = 0;
	map <string, int> M(m);
	map <string, double> M_freq(m_freq);
	while( n < this->v2.size()){
		int k = 0;
		while( k < this->v1.size()){
			if(this->v2[n] == this->v1[k]){
				m[this->v2[n]] = m[this->v2[n]] + 1; // Counter of frequency
				m_freq[this->v2[n]] = (double)m[this->v2[n]] / (double)(v1.size());  
			}
			k++;
		}
		n++;
	}
}	
