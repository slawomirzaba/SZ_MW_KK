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

char **characters_table;
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
	for(int i = 33; i < 126; ++i)
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
				 	number = rand() % 128;
				} while(number < 33 || number > 126);
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

void prepareTable()
{
	int index;

	characters_table = new char* [alphabet.size()];
	for(int i = 0; i < alphabet.size(); ++i)
		characters_table[i] = new char [alphabet.size()];

	for(int i = 0; i < alphabet.size(); ++i)
	{
		index = 0;
		for(int j = i; j < alphabet.size(); ++j)
		{
			if(j == alphabet.size() - 1)
			{
				characters_table[i][index++] = alphabet[j];
				for(j = 0; j < i; ++j)
				{
					characters_table[i][index++] = alphabet[j];
				}
				break;
			}
			characters_table[i][index++] = alphabet[j];
		}
	}
}

void showMenu()
{
	cout << "Lab 2 E-media Szyfr Vigenere'a\n";
	askFirstQuestion();
	cout << "\nMENU:\n";
	askSecondQuestion();
	prepareTable();
}

string createKeyWord(const string &text_line)
{
	int next = 1;
	string key_word = "";
	int key_size = key.size();


	if(key_size == 1)
	{
		key_word += key[0];
		for(int i = 0; i < text_line.length() - 1;)
		{
			if(text_line[i+next] != ' ')
			{
				if(text_line[i] == ' ')
				{
					i++;
					next--;
				}
				key_word += text_line[i++];
			}
			else
			{
				key_word += ' ';
				next++;	
			}
		}
	}
	else
	{
		for(int i = 0, j = 0; i < text_line.length(); ++i, ++j)
		{
			j = j % key_size;
			if(text_line[i] != ' ')
				key_word += key[j];
			else
			{
				key_word += ' ';
				j--;
			}
		}
	}
	return key_word;
}

int findCharactersIndex(const char &character)
{
	int index = 0;

	for(int i = 0; i < alphabet.size(); ++i)
	{
		if(characters_table[0][i] == character)
			return index;
		index++;
	}
}

string invertKeyWord(const string &key_word)
{
	int index;
	char wanted_sign;
	string inverted_key_word = "";

	for(int i = 0; i < key_word.length(); ++i)
	{
		if(key_word[i] == ' ')
			inverted_key_word += ' ';
		else
		{
			index = findCharactersIndex(key_word[i]);
			wanted_sign = alphabet[(alphabet.size() - index) % alphabet.size()];
			inverted_key_word += wanted_sign;
		}
	}
	return inverted_key_word;
}

bool existsInAlphabet(const char &sign)
{
	for(int i = 0; i < alphabet.size(); ++i)
	{
		if(int(sign) == alphabet[i])
			return true;
	}
	return false;
}

string encryptData(const string &data, const string &key_word)
{
	int row, column;
	string cryptogram = "";

	for(int i = 0; i < data.length(); ++i)
	{
		if(data[i] == ' ')
			cryptogram += ' ';
		else
		{
			if(!existsInAlphabet(data[i]))
			{
				cryptogram += data[i];
				continue;
			}
			row = findCharactersIndex(data[i]);
			column = findCharactersIndex(key_word[i]);
			cryptogram += characters_table[row][column];
		}
	}
	return cryptogram;
}

int main()
{
	string cryptogram, key_word;

	srand(time(NULL));
	loadData();
	showMenu();
	for(list<string>::iterator iter = text_lines.begin(); iter != text_lines.end(); ++iter)
	{
		cryptogram = "";
		key_word = createKeyWord(*iter);
		cryptogram = encryptData(*iter, key_word);
		cout.width(22);
		cout << right << "Tekst jawny: " << *iter << endl;
		cout.width(22);
		cout << right << "Klucz: " << key_word << endl;
		cout.width(22);
		cout << right << "Tekst zaszyfrowany: " << cryptogram << endl;
		key_word = invertKeyWord(key_word);
		cout.width(22);
		cout << right << "Tekst odszyfrowany: " << encryptData(cryptogram, key_word) << endl;
	}
	for(int i = 0; i < alphabet.size(); ++i)
		delete [] characters_table[i];
	delete [] characters_table;
	return EXIT_SUCCESS;
}