#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <ctime>

#define ABC "abc.txt"
#define KEY "key.txt"
#define IN  "in.txt"

using namespace std;

list<string> text_lines;
vector<int> alphabet;
vector<char> key;

void loadData()
{
	ifstream file;
	string line;

	file.open(IN);
	if(!file.good())
		exit(EXIT_FAILURE);
	while(!file.eof())
	{
		getline(file, line);
		text_lines.push_back(line);
	}
	file.close();
}

template <typename type>
void verifyCollection(const type &collection, const string &file_name)
{
	for(int i = 0; i < collection.size(); ++i)
	{
		for(int j = 0; j < collection.size(); ++j)
		{
			if(i != j && collection[i] == collection[j])
			{
				cout << "W pliku " << file_name << " wystepuja powtorzenia! Koniec programu\n";
				exit(EXIT_FAILURE);
			}
		}
	}
	cout << "Plik " << file_name << " jest poprawny!\n";
}

template <typename collection_type, typename data_type>
void loadConfig(collection_type &collection, const string &file_name)
{
	ifstream file;
	data_type data;

	file.open(file_name.c_str());
	if(!file.good())
		exit(EXIT_FAILURE);
	while(file >> data)
		collection.push_back(data);
	file.close();
	verifyCollection <collection_type>(collection, file_name);
}

void generateASCIITable()
{
	ofstream file;

	file.open(ABC);
	if(!file.good())
		exit(EXIT_FAILURE);
	for(int i = 0; i < 256; ++i)
		file << i << " ";
	file.close();
}

void askFirstQuestion()
{
	char first_answer;

	cout << "Czy wygenerowac alfabet w postaci tablicy znakow ASCII? (t\\n)... ";
	do
	{
		cin >> first_answer;
		switch(first_answer)
		{
			case 't':
				generateASCIITable();
				break;
			case 'n':
				cout << "Wczytano domyslny alfabet z pliku " << ABC << endl;
				break;
			default:
				cout << "Nieobslugiwana opcja!... ";
				break; 
		}
	} while(first_answer != 't' && first_answer != 'n');
	loadConfig < vector<int>, int >(alphabet, ABC);
}

void askSecondQuestion()
{
	char autokey;
	int second_answer, number;

	cout << "1. Wybor autoklucza\n2. Wybor klucza podanego w pliku key.txt\n";
	do
	{
		cout << "Wprowadz opcje... ";
		cin >> second_answer;
		switch(second_answer)
		{
			case 1:
				do // losowanie autoklucza z zakresu malych i duzych liter
				{
				 	number = rand() % 256;
				} while(number < 65 || number > 122 || (number > 90 && number < 97));
				autokey = number;
				cout << "Znak '" << autokey << "' zostal wylosowany jako autoklucz\n";
				key.push_back(autokey);
				break;
			case 2:
				cout << "Wczytano domyslny klucz z pliku " << KEY << endl;
				loadConfig < vector<char>, char >(key, KEY);
				break;
			default:
				cout << "Nieobslugiwana opcja!\n";
				break;
		}
	} while(second_answer != 1 && second_answer != 2);
}

void showMenu()
{
	cout << "Lab 2 E-media Szyfr Vigenere'a\n";
	askFirstQuestion();
	cout << "\nMENU:\n";
	askSecondQuestion();
}

void encryptData()
{
	
}

int main()
{
	srand(time(NULL));
	loadData();
	showMenu();
	encryptData();
	decryptData();

	return EXIT_SUCCESS;
}