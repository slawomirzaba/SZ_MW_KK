#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define SIZE 256

int pairs[SIZE];
int reversed_pairs[SIZE];
string text, output = "";

void generateRandomKey(){
	ofstream file;
	int index;
	int numbers[2][SIZE];

	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < SIZE; ++j)
			numbers[i][j] = j;
	for(int i = 0; i < SIZE; ++i)
	{
		index = rand() % SIZE;
		swap(numbers[1][i], numbers[1][index]);
	}
	file.open("key.txt");
	if(!file.good())
		exit(EXIT_FAILURE);
	for(int i = 0; i < SIZE; i++)
		file << numbers[0][i] << " - " << numbers[1][i] << "\n";
	file.close();
}

void loadKey()
{
	char sign;
	int left_val, right_val;
	ifstream file;

	file.open("key.txt");
	if(!file.good())
		exit(EXIT_FAILURE);
	while(!file.eof())
	{
		file >> left_val >> sign >> right_val;
		pairs[left_val] = right_val;
		reversed_pairs[right_val] = left_val;
	}
	file.close();
}

void validateKey()
{
	for(int i=0; i<SIZE; ++i)
    {
		for(int j=0; j<SIZE; ++j)
		{
			if(j != i)
			{
				if(pairs[i] == pairs[j] || reversed_pairs[i] == reversed_pairs[j])
				{
					cout << "Plik z kluczem jest niepoprawny!";
					exit(EXIT_FAILURE);
				}
			}
		}
    }
    cout << "Sprawdzono poprawnosc pliku z kluczem\n";
}

string encodeOrDecodeText(const string &text_, const bool &switch_)
{
	int index;
	char sign;
	string result = "";

	for(int i = 0; i < text_.length(); ++i)
	{
		index = text_[i];
		if(switch_)
			sign = pairs[index];
		else
			sign = index < 0 ? reversed_pairs[256 + index] : reversed_pairs[index];
		result += sign;
	}
	cout << endl;
	return result;
}

void loadData(){
	ifstream file;
    string encoded_text, decoded_text;

	file.open("in.txt");
	if(!file.good())
		exit(EXIT_FAILURE);
	while(!file.eof())
	{
		getline(file, text);
		encoded_text = encodeOrDecodeText(text, true);
		cout << text << " ---> " << encoded_text << endl;
		decoded_text = encodeOrDecodeText(encoded_text, false);
		cout << encoded_text << " ---> " << decoded_text << endl;
		output += encoded_text + "\n";
	}
	file.close();
}

void saveData()
{
	ofstream file;

	file.open("out.txt");
	if(!file.good())
		exit(EXIT_FAILURE);
	file << output;
	file.close();
}

int main(){
	srand( time( NULL ) );
	generateRandomKey();
	loadKey();
	validateKey();
	loadData();
	saveData();
	return 0;
}
