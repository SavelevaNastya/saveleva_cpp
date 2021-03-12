#pragma once
#include <string>
#include <map>
#include <vector>

using namespace std;

class myArchivator
{
private:

	string name;
	char act;
	string ad;

	multimap<int, int> sortedWeight; // <���, ������ � ������>
	int weight[0x100];

	struct Node {
		char ch;
		int parent;
		int zero;
		int one;
		bool branch;
	};

	vector<Node> tree;
	vector<bool> data;
	map<char, int> charMap; //<������, ������ � ������>


public:

	myArchivator(int act, string adres,string final_name) {

		this->name = final_name;
		this->act = act;
		this->ad = adres;
	}
	
	void readTxt();

	void BuildTree();

	void HaffmansCode();

	void writeToTxt();
};
