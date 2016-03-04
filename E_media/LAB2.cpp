#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <list>
#include <vector>

using namespace std;

list<string> data;
vector<int> alphabet;

void loadData()
{
	ifstream file;
	string line;

	file.open("in.txt");
	if(!file.good())
		exit(EXIT_FAILURE);
	while(!file.eof())
		data.push_back(getline(file, line));
	file.close();
}

void loadAlphabet()
{
	ifstream file;
	int number;

	file.open("abc.txt");
	if(!file.good())
		exit(EXIT_FAILURE);
	while(!file.eof())
	{
		file >> number;
		alphabet.push_back(number);
	}
	file.close();
}

void validateKey()
{

}

void generateASCIITable()
{
	ofstream file;

	file.open("abc.txt");
	if(!file.good())
		exit(EXIT_FAILURE);
	for(int i = 0; i < 256; ++i)
		file << i << " ";
	file << endl;
	file.close();
}

void showMenu()
{
	int option;

	cout << "Lab 2 E-media Szyfr Vigenere'a\n";
	cout << "\nMENU:\n";
	cout << "1. Wybor autoklucza\n2. Wybor klucza podanego w osobnym pliku\n";
	do
	{
		cin >> option;
		switch(option)
		{
			case 1:
				break;
			case 2:
				break;
			default:
				cout << "Nieobslugiwana opcja!\n";
		}
	} while(option != 1 || option != 2);
}


int main()
{
	showMenu();
	return EXIT_SUCCESS;
}