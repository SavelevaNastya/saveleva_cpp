#pragma once
#include <string>
#include <map>
#include <vector>

using namespace std;

class myArchivator
{
private:

	string name;
	string ad;

	multimap<int, int> sortedWeight; // <вес, индекс в дереве>
	int weight[0x100];

	struct Node {
		char ch;
		int parent;
		int zero;
		int one;
		bool branch;
	};

	vector<Node>* tree;
	vector<bool> data;
	map<char, int> charMap; //<символ, индекс в дереве>


public:
	
	// Packing //
	void readTxt();

	void BuildTree();

	void HaffmansCode();

	void writeToTxt();

	// Unpacking //
	void GetInfo();

	void UnPack();

	// Constructor
	myArchivator(vector<Node> c) {

		tree = new vector<Node>;
		*tree = c;

	}

	// Copy constructor
	myArchivator(const myArchivator& c)
		: myArchivator{ *c.tree}
	{
		
	}

	// Move constructor
	myArchivator(myArchivator&& c) noexcept
		: tree{c.tree}
	{
		c.tree = nullptr;
	}

	// operator=
	myArchivator& operator= ( const myArchivator & c) {
		tree = c.tree;
	}

	// Оператор присваивания перемещением (move assignment)
	myArchivator& operator=(myArchivator&& c) noexcept
	{
		if (this == &c)
			return *this;

		delete[] tree;
		tree = c.tree;
		c.tree = nullptr;
		return *this;
	}

	~myArchivator()
	{
		delete[] tree;
	}

};
