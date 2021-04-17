#pragma once
#include <string>
#include <map>
#include <vector>

using namespace std;

class myArchivator
{
private:

	string* name;
	string* ad;

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
	// Constructor
	myArchivator(string adres,string final_name) {


		this->name = &final_name;
		this->ad = &adres;
	}
	
	// Packing //
	void readTxt();

	void BuildTree();

	void HaffmansCode();

	void writeToTxt();

	// Unpacking //
	void GetInfo();

	void UnPack();

	// Copy constructor
	myArchivator(const myArchivator& c)
		: myArchivator{ *c.name, *c.ad}
	{
		
	}

	// Move constructor
	myArchivator(myArchivator&& c) 
		: name{c.name}
	{
		c.name = nullptr;
	}

	// operator=
	myArchivator& operator= ( const myArchivator & c) {
		name = c.name;
		ad = c.ad;
	}

};
