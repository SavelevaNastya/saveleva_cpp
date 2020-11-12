#include "Functions.h"

using namespace std;

pair<pair<size_t,size_t>,string> GetInfo(const string& adres){
	
	string s;
	string str;
	size_t n;
	size_t m;
	ifstream txt;

	txt.open(adres.c_str());

	if ( txt.is_open() == false) {
		throw "File not found";
	}
	else {
		getline(txt, s);
		stringstream dim(s);
		dim >> n >> m;
	}

	while (getline(txt, s)) {
		str.append(s);
	}

	return make_pair(make_pair(n,m),str);
}





























	
