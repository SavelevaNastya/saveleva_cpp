#include "Functions.h"

using namespace std;

pair<pair<size_t,size_t>,string> GetInfo(const string& adres){
	
	ifstream txt;
	txt.open(adres.c_str()); 
	string s;
	string str;
	getline(txt,s);
	stringstream lines(s);
	size_t n;
	size_t m;
	lines >> n >> m; 

	while(getline(txt,s)){	
		str.append(s);	
	}
	
	return make_pair(make_pair(n,m),str);
}





























	
