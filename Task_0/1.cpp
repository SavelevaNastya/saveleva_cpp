#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <Windows.h>

using namespace std;


int main(void)
{
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251); //Set encoding
	
	
	ifstream test;
	test.open("c:\\users\\gnome\\documents\\test2.txt"); //Open file
	
	
	string test_string, s;

    while(getline(test, s))  
		{
			test_string += s;
			test_string.append(" ");
		}//Extract data from file

	//cout << ">> " << test_string << "\n" << endl; 
	
	
	if (test.eof() == 0){
		cout << ">> End of the file was not reached \n" << endl; 
	}
	if (test.eof() == 1){
		cout << ">> End of the file was reached \n" << endl;
	}  //Check if all data from file were extracted
	
	
	test.close(); //Close our file
	
	
	int ix =  0;
	while (ix <= test_string.length()) {
    test_string[ix] = (char)tolower(test_string[ix]);  
    ix++;                                   
    }  //Set lower register for all letters
    
    string separator(" "); 
    size_t delta = separator.length();
    size_t prev = 0;
    size_t next;
    vector<string> test_vector;
    
    while((next = test_string.find(separator, prev)) != string::npos)
	{
    test_vector.push_back(test_string.substr(prev, next-prev));
    prev = next + delta;
    } 
  	
  	test_vector.push_back(test_string.substr(prev)); //Divide Into words
	
	//cout << ">> This word: " << test_vector[0] << endl; // for check
	
	//cout << ">> test_vector: " << endl;
	//for(int i=0; i < test_vector.size(); i++)
	//cout << test_vector.at(i) << ' ';
	
	vector<string> vec(test_vector);
	
	//cout << ">> vec: " << endl;
	//for(int i=0; i < vec.size(); i++)
	//cout << vec.at(i) << ' ';
		
	int n = 0; 
	int k = 0;
	vector<string> vct; 
	while (n < test_vector.size() ){ 
		k = n + 1;
		while (k < test_vector.size()){
			if(test_vector[n] != test_vector[k]){
				k++;
			}else{
				test_vector[k] = " ";
				k++;
			}
		} 
		if(test_vector[n] != " "){
			vct.push_back(test_vector[n]);
		}
		n++;
	}
	
	n = 0;
	int freq[vct.size() - 1];
	while( n < vct.size()){
		freq[n] = 0;
		k = 0;
		while( k < vec.size()){
			if(vct[n] == vec[k]){
				freq[n] = freq[n] + 1;
			}
			k++;
		}
		n++;
	}
	
	n = 0;
	double freqper[vct.size() - 1];
	while( n < vct.size()){
		freqper[n] = (double)freq[n] / (double)(vec.size() - 1);
		n++;
	}
	
	cout << ">> vec: " << endl;
	for(int i=0; i < vec.size(); i++)
	cout << vec.at(i) << ' ';
	cout << "\n>> Size: " << vec.size() - 1 << endl;
	cout << ">> Word: " << vct[3] << endl;
	cout << ">> freq: " << freq[3] << endl;
	cout << ">> freq_per: " << freqper[3] << endl;
}
