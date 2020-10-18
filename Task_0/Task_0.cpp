#include <Windows.h>

#include "Task_0.h"
#include "Task_0_functions.cpp"

using namespace std;

int main(void)
{
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251); //Set encoding
	map <string, int> m; 
	map <string, double> m_freq;
	text txt;
	
	string adres = "f:\\cpp\\saveleva_cpp\\Task_0\\test2.txt";
	txt.set_vector(adres);
	cout << "Word" << " " << "Frequency" << " " << "Frequency in percentage" << endl;
	txt.get_unique_words();
	
	txt.counter_of_freq(m, m_freq);
	txt.sorting(m, m_freq);
	
}
