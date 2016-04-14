#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <string>
#include <fstream>
#include <vector>
#include <bitset>
#include <climits>

#define MESSAGE "message.txt"
#define SIZE 4096
#define LIMIT 100000;

typedef unsigned long long ullong;
typedef std::vector < std::bitset<SIZE> > vec_bitset;
typedef std::pair < std::bitset<SIZE>, ullong > rsa_pair;

ullong pow_modulo(const ullong &base, const ullong &index, const ullong &modulo)
{
	ullong a = base % modulo;
	ullong x = a;
	ullong result = 1;
	std::bitset<SIZE> bits(index);

	for( std::size_t i = 0; i < bits.size(); ++i )
	{
		if( bits[i] == 1 )
		{
			result *= x;
			result %= modulo;
		}
		x *= x;
		x %= modulo;
	}
	return result;
}

long pow(const long &base, const long &index, const long &modulo)
{
	long result = base;

	for( int i = 1; i < index; ++i )
		result = ( result * base ) % modulo; 
	return result;
}

bool isPrimary(const ullong &number)
{
	if( number < 2 )
		return false;
	for( int i = 2; i * i <= number; ++i )
	{
		if( number % i == 0 )
			return false;
	}
	return true;
}

// int spreadNumberTillOne(const int &number, const int &factor)
// {
// 	int element, factor_copy;

// 	element = number % factor;
// 	if( element > 1 )
// 		factor_copy = spreadNumberTillOne(factor, element);
// 	else if( element == 0 )
// 		factor_copy = 0;
// 	else
// 		factor_copy = factor;
// 	return factor_copy;
// }

int countNWD( ullong a, ullong b)
{
	while( a != b )
	{
		if( a < b ) b -= a;
		else a -= b;
	}
	return a;
}

ullong findENumber(const ullong &module, const ullong &euler_function)
{
	for( ullong i = 2; i < module; ++i )
	{
		if( countNWD(i, euler_function) == 1 )
			return i;
	}
	std::cout << "Nie znaleziono liczby wzglednie pierwszej do " << euler_function << std::endl;
	exit(EXIT_FAILURE);


	// //Brute Force method 
	// for( int i = 2; ; ++i )
	// {
	// 	if( spreadNumberTillOne(euler_function, i) != 0 )
	// 	{
	// 		if( i % 2 != 0 && ( i > 1 && i < module ) )
	// 			return i;
	// 	}		
	// }
	// return 0; 
}

ullong findDNumber(const ullong &e_number, const ullong &euler_function)
{
	ullong q, u, w, x, z;

	u = 1;
	x = 0;
	w = e_number;
	z = euler_function;
	while( w != 0 )
	{
		if( w < z )
		{
			std::swap(u, x);
			std::swap(w, z);
		}
		q = w / z;
		u -= q * x;
		w -= q * z;
	}
	if( z != 1 )
	{
		std::cout << "Brak rozwiazania!\n";
		exit(EXIT_FAILURE);
	}
	if( x < 0 ) x += euler_function;
	return x;	
}

void loadMessage(std::string &message)
{
	char byte;
	std::string filename;
	std::ifstream file;
	std::size_t found;

	std::cout << "Wczytaj nazwe pliku: ";
	std::cin >> filename;
	found = filename.find(".bin");
	if( found != std::string::npos ) 
		file.open(filename, std::ios::binary);
	else
		file.open(filename);
	if( file.bad() )
	{
		std::cout << "Nie udalo sie otworzyc pliku!\n";
		exit(EXIT_FAILURE);
	}
	getline(file, message);
	// while( file >> byte )
	// 	message += byte;
	file.close();
}

// void encryptMessage(const std::pair <long, long> &key, const std::string &message,
// 					std::vector <long> &cryptogram)
// {
// 	long block;

// 	for( char byte : message )
// 	{
// 		if( static_cast<int>(byte) < key.second )
// 		{
// 			block = pow( byte, key.first, key.second);
// 			cryptogram.push_back(block);
// 		}
// 		else
// 			std::cout << "Blok wiekszy niz wartosc n!" << std::endl;
// 	}
// }

// std::string decryptMessage(const std::pair <long, long> &key, const std::vector <long> &cryptogram)
// {
// 	long block;
// 	std::string decrypted_message = "";

// 	for( long elem : cryptogram )
// 	{
// 		block = pow( elem, key.first, key.second);
// 		decrypted_message += block;
// 	}
// 	return decrypted_message;
// }

void encryptMessageUsingXORMethod( const std::string &message, const rsa_pair &key, vec_bitset &cryptogram )
{
	std::bitset<SIZE> m, c;

	for( char byte : message)
	{
		m = byte;
		c = m ^ key.first;
		cryptogram.push_back(c);
	}
}

void decryptMessageUsingXORMethod( const rsa_pair &key, const vec_bitset &cryptogram, vec_bitset &message )
{
	std::bitset<SIZE> m;
	for( std::bitset<SIZE> code : cryptogram )
	{
		m = code ^ key.first;
		message.push_back(m);
	}
}

int main()
{
	srand( time( NULL ) );

	ullong p, q;
	ullong n, fi;
	std::bitset<SIZE> e, d;
	std::string message = "", decoded = "";
	std::vector <ullong> cipher;
	vec_bitset cipherXOR_Encrypted, cipherXOR_Decrypted;
	rsa_pair public_key, private_key;
	
	cipherXOR_Encrypted.clear();
	cipherXOR_Decrypted.clear();

	loadMessage(message); // wczytywanie informacji
	std::cout << "Wiadomosc: " << message << std::endl;

	// losowanie duzych liczb pierwszych, ktorych iloczyn nie przekracza zakresu 
	// typu unsigned long long
	do
	{
		p = rand() % LIMIT;
	} while( !(isPrimary( p )) );
	std::cout << "Wylosowane p: " << p << std::endl;
	do
	{
		q = rand() % LIMIT;
	} while( !(isPrimary( q )) && q < ULLONG_MAX / p );
	std::cout << "Wylosowane q: " << q << std::endl;

	n = p * q;
	std::cout << "n: " << n << std::endl;

	fi = ( p - 1 ) * ( q - 1 );
	std::cout << "fi: " << fi << std::endl;

	e = findENumber(n, fi);
	std::cout << "Znaleziono liczbe e: " << e.to_ullong() << std::endl;
	
	d = findDNumber(e.to_ullong(), fi);
	std::cout << "Znaleziono liczbe d: " << d.to_ullong() << std::endl;

	public_key = std::make_pair(e, n);
	private_key = std::make_pair(d, n);

	encryptMessageUsingXORMethod( message, public_key, cipherXOR_Encrypted );
	std::cout << "Zaszyfrowano wiadomosc!\n";

	decryptMessageUsingXORMethod( public_key, cipherXOR_Encrypted, cipherXOR_Decrypted );
	std::cout << "Odszyfrowano wiadomosc!\n";
	for( std::bitset<SIZE> code : cipherXOR_Decrypted )
	{
		decoded += code.to_ulong();
	}
	std::cout << "Odszyfrowana wiadomosc: " << decoded << std::endl;
	return 0;
	//encryptMessage(public_key, message, cipher);
	// std::cout << "Zaszyfrowana wiadomosc: ";
	// for( int elem : cipher )
	// 	std::cout << elem << " ";
	// std::cout << std::endl;
	// decoded = decryptMessage(private_key, cipher);
	
}