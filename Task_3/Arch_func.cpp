#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

#include "myArch.h"

using namespace std;

void myArchivator::readTxt() {

	for (auto& i : weight) 
		i = 0;
		{
			ifstream f(ad);
			while (!f.eof())
			{
				unsigned char ch;
				f.read((char*)&ch, sizeof(ch));
				++weight[ch];
			}
		}
	
	
	/*for (int i = 0; i < 0x100; ++i) {
		if (weight[i] > 0) {
			cout << weight[i] << " " << (char)i << endl;
		}
	}*/

	
}

void myArchivator::BuildTree() {

	for (size_t i = 0; i < 0x100; ++i) {
		if (weight[i] > 0) {
			tree.push_back(Node{ (char)i, -1, -1, -1, false }); //emplase_back ?
			charMap[i] = tree.size() - 1;
			sortedWeight.insert(make_pair(weight[i], tree.size() - 1));
		}
	}

	while (sortedWeight.size() > 1) {

		int w0 = begin(sortedWeight)->first; // беру два первых элемента
		int n0 = begin(sortedWeight)->second; 
		sortedWeight.erase(begin(sortedWeight)); // вытаскиваю сам элемент 
		int w1 = begin(sortedWeight)->first; // точно есть два элемента
		int n1 = begin(sortedWeight)->second;
		sortedWeight.erase(begin(sortedWeight));

		//cout << w0 << " " << n0 << " " << w1 << " " << n1 << " " << endl;

		tree.push_back(Node{ ' ', -1, n0, n1, false }); // пока не знаем родителя и ветку // добавляю в дерево нод
		tree[n0].parent = tree.size() - 1; // тк только что добавили в него нод 
		tree[n0].branch = false;
		tree[n1].parent = tree.size() - 1;
		tree[n1].branch = true;
		sortedWeight.insert(make_pair(w0 + w1, tree.size() - 1));

	}
}

void myArchivator::HaffmansCode() {

	ifstream f(ad);
	while (!f.eof()) {
		unsigned char ch;
		f.read((char*)&ch, sizeof(ch)); 
		auto n = tree[charMap[ch]]; //взяла ноду из дерева и поднимаюсь вверх
		vector<bool> compressedChar; //заполняю вектор, который потом переверну
		while (n.parent != -1) { 
			compressedChar.push_back(n.branch);
			n = tree[n.parent];
		}
		data.insert(end(data), compressedChar.rbegin(), compressedChar.rend()); // r - reverse(пихаю в перевернутом виде)

	}
}

void myArchivator::writeToTxt() {

	ofstream f(name);

	//if (f.is_open() == false) {
	//	throw "File not found";
	//}
	//else {
		for (size_t i = 0; i <= data.size() / 8.0; ++i) {
			unsigned char ch = 0;
			for (int j = 0; j < 8; ++j) {
				if (data[i * 8 + j]) { //выставляем бит, который сдвинут на j, в чар 
					ch |= (1 << j);
				}
				f.write((char*)&ch, sizeof(ch));
			}
		}
	//}

	
}
