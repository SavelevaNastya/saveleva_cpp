#pragma once
#include <string>
#include <vector>
#include <map>


using namespace std;

class text
{
private:
	vector<string> v1; //all words
	vector<string> v2; //unique words
	int freq[];
public:
	void sorting(map<string, int>& M, map<string,double>& M2);
	void set_vector(string adres);
	vector<string> get_unique_words();
	void counter_of_freq(map<string, int>& m, map<string, double>& m_freq); 
};
