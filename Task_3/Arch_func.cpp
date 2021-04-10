#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

#include "myArch.h"

#ifdef _WIN32
#include <windows.h>
#define SYSERROR()  GetLastError()
#else
#include <errno.h>
#define SYSERROR()  errno
#endif

using namespace std;

void myArchivator::readTxt() {

	for (auto& i : weight) 
		i = 0;
		{
			ifstream f(ad, ios_base::in | ios_base::binary);
			while (!f.eof())
			{
				unsigned char ch;
				f.read((char*)&ch, sizeof(ch)); //считывать по строчке(кто быстрее?)
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
			tree.push_back(Node{ (char)i, -1, -1, -1, false }); 
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

		tree.push_back(Node{ ' ', -1, n0, n1, false }); // пока не знаем родителя и ветку // добавляю в дерево нод
		tree[n0].parent = tree.size() - 1; // тк только что добавили в него нод 
		tree[n0].branch = false;
		tree[n1].parent = tree.size() - 1;
		tree[n1].branch = true;
		sortedWeight.insert(make_pair(w0 + w1, tree.size() - 1));

	}
}

void myArchivator::HaffmansCode() {

	ifstream f(ad, ios_base::in | ios_base::binary);
	while (!f.eof()) {
		unsigned char ch;
		f.read((char*)&ch, sizeof(ch)); 
		auto n = tree[charMap[ch]]; //взяла ноду из дерева и поднимаюсь вверх
		vector<bool> Rev; //заполняю вектор, который потом переверну
		while (n.parent != -1) { 
			Rev.push_back(n.branch);
			n = tree[n.parent];
		}
		data.insert(end(data), Rev.rbegin(), Rev.rend()); // r - reverse(пихаю в перевернутом виде)
	}
}

void myArchivator::writeToTxt() {

	ofstream f(name, ios_base::out | ios_base::trunc | ios_base::binary);
	int treeSize = tree.size();
	f.write((char*)&treeSize, sizeof(treeSize));

	for (const auto& i : tree) {
		f.write((char*)&i, sizeof(i));
	}

	for (size_t i = 0; i <= data.size() / 8; ++i) {
		unsigned char ch = 0;
		for (int j = 0; j < 8; ++j) {
			if (data[i * 8 + j]) { //выставляем бит, который сдвинут на j, в чар // data[i*8+j]
				ch |= (1 << j);
			}
		}
		f.write((char*)&ch, sizeof(ch));
	}
}

/// <summary>
/// For UNpack
/// <summary>

void myArchivator::GetInfo() {

	ifstream f("f:\\cpp\\tasks\\Task_3\\Task_3\\Task_3\\my_archive.txt", ios_base::in | ios_base::binary);
	int treeSize;
	f.read((char*)&treeSize, sizeof(treeSize));
	for (int i = 0; i < treeSize; ++i) {
		Node n;
		f.read((char*)&n, sizeof(n));
		tree.push_back(n);
	}

	while (!f.eof()) {
		unsigned char ch; 
		f.read((char*)&ch, sizeof(ch));
		for (int i = 0; i < 8; ++i) {
			data.push_back((ch & (1 << i)) != 0);
		}
	}

}

void myArchivator::UnPack() {

	ofstream of("unpacked_file.txt", ios_base::out | ios_base::trunc | ios_base::binary);

	if (of.is_open()) {

		auto n = tree.size() - 1;
		for (auto i : data) {
			if (i) {
				n = tree[n].one;
			}
			else {
				n = tree[n].zero;
			}
			if (tree[n].zero == -1) {
				of << tree[n].ch;
				n = tree.size() - 1;
			}
		}

		of.flush();
		of.close();
		cout << "wrote the file successfully!" << endl;
	}
	else {
		cerr << "Failed to open file : " << SYSERROR() << endl;
	}

}

