#include <Windows.h>
#include <iostream>
#include <string>

#include "myArch.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); //Set encoding

	string adres = "f:\\cpp\\tasks\\Task_3\\text\\voina_i_mir_first_tom.txt";
	string final_name = "my_archive.txt";
	char action = ' ';

	//cout << "Do you want pack(P) or unpack(u)?" << endl;
	//cin >> action;

	myArchivator arch(action, adres, final_name);

	arch.readTxt();

	arch.BuildTree();

	arch.HaffmansCode();

	//try {
		arch.writeToTxt();
	//}
	//catch (const char* exception) {
	//	cout << "Error: " << exception << '\n';
	//	return 0;
	//}
	
}