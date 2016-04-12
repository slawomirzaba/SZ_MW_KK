#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <string>
#include <ctime>

using namespace std;

#define MAX_TASKS 502 // max liczba zadan + 2
#define MAX_MACHINES 22 //max liczba maszyn + 2

// struktura dla pojedynczego zadania
struct Task{
  int number;
  int time;
  int allTime;
};

// funkcja do zamiany miejsc
void mySwap(int& i, int& j) {
    int t = i;
    i = j;
    j = t;
}

// funkcja potrzebna do uszeregowania zadan w kolejnosci od najwiekszego czasu wykonywania
// do najmniejszego
bool operator<(Task const & a, Task const & b)
{
  if(a.allTime == b.allTime){
    return a.number < b.number;
  }else{
    return a.allTime > b.allTime;
  }
}

int numberOfTasks, numberOfMachines; // liczba zadan i maszyn
Task* columns; // wskaznik na pojedyncza kolumne macierzy zadan
Task copyTask[1][MAX_MACHINES]; // skopiowane zadanie
Task R[MAX_TASKS][MAX_MACHINES], Q[MAX_TASKS][MAX_MACHINES]; // pomocnicze macierze do algorytmu z akcelracja

//kopiowanie kolumny
void makeCopyColumn(Task tab[MAX_TASKS][MAX_MACHINES])
{
	for (int i = 0; i < numberOfTasks; ++i){
		columns[i].number = tab[i][0].number;
		columns[i].time = tab[i][0].time;
		columns[i].allTime = tab[i][0].allTime;
	}
}

// kopiowanie zadania
void makeCopyTask(Task tab[MAX_TASKS][MAX_MACHINES], int const & number){
  for (int i = 0; i < numberOfMachines; ++i){
		copyTask[0][i].number = tab[number][i].number;
		copyTask[0][i].time = tab[number][i].time;
	}
}

// obliczanie macierzy R
void calculateR(Task tab[MAX_TASKS][MAX_MACHINES], int const & numberOfCurrentTask)
{
  // wyzerowanie
	for (int i = 0; i <= numberOfCurrentTask + 1; ++i){
		for (int j = 0; j <= numberOfMachines + 1; ++j){
			R[i][j].time = 0;
		}
	}
  //obliczenie wszystkich wartosci macierzy (czyli obliczenie dla kazdego zadania,
  // ile minelo jednostek czasu od poczatku pracy algorytmu do zakonczenia kazdego z tych zadan)
	for (int i = 1; i <= numberOfCurrentTask; ++i){
		for (int j = 1; j <= numberOfMachines; ++j){
			R[i][j].time = max(R[i-1][j].time, R[i][j-1].time) + tab[i-1][j-1].time;
		}
	}
}

//obliczanie macierzy Q
void calculateQ(Task tab[MAX_TASKS][MAX_MACHINES], int const & numberOfCurrentTask)
{
  // wyzerowanie
  for (int i = numberOfCurrentTask + 2; i > 0; --i){
		for (int j = numberOfMachines + 2; j > 0; --j){
			Q[i][j].time = 0;
		}
	}
  //obliczenie wszystkich wartosci macierzy (czyli obliczenie dla kazdego zadania,
  // ile pozostalo jednostek czasu od konca pracy algorytmu)
	for (int i = numberOfCurrentTask; i >= 0; --i){
		for (int j = numberOfMachines; j >= 0 ; --j){
			Q[i][j].time = max(Q[i+1][j].time, Q[i][j+1].time) + tab[i-1][j-1].time;
		}
	}
}

// wstawianie zadania przed zadany indeks do wybranej tablicy
void insert(Task tab[MAX_TASKS][MAX_MACHINES], int const & number)
{
	for (int i = 0; i < numberOfMachines; ++i){
		tab[number][i].time = copyTask[0][i].time;
		tab[number][i].number = copyTask[0][i].number;
	}
}

// liczenie cMaxa dla algorytmu z akceleracja. number jest numerem miejsca, w ktore zostalo wstawione zadanie
int calculateCmaxAcceleration(int const & number)
{
	int Cmax = 0;
  Task taskR[1][MAX_MACHINES + 1];
	Task taskQ[1][MAX_MACHINES + 1];

  for (int i = 0; i <= numberOfMachines + 1; ++i){
		taskR[0][i].time = taskQ[0][i].time = 0;
  }
  for (int i = numberOfMachines; i >= 1; --i){
    // obliczenie lokalnego cMaxa macierzy Q
		taskQ[0][i].time = max(Q[number+1][i].time, taskQ[0][i+1].time) + copyTask[0][i-1].time;
  }
  for (int i = 1; i <= numberOfMachines; ++i){
      // obliczenie lokalnego cMaxa dla macierzy R
		  taskR[0][i].time = max(R[number][i].time, taskR[0][i-1].time) + copyTask[0][i-1].time;
  }
  //wybranie najlepsze wartosci cMax
  for (int i = 1; i <= numberOfMachines; ++i){
		  if((taskR[0][i].time + taskQ[0][i].time - copyTask[0][i-1].time) > Cmax){
			     Cmax = taskR[0][i].time + taskQ[0][i].time - copyTask[0][i-1].time;
      }
  }
  return Cmax;
}

// liczenie cmaxa dla algorytmu bez akceleracji
int calculatecMax(Task tab[MAX_TASKS][MAX_MACHINES], int const & numberOfCurrentTask)
{
  Task cMax[MAX_TASKS+1][MAX_MACHINES+1];
  // zerowanie
	for (int i = 0; i <= numberOfCurrentTask; ++i){
		for (int j = 0; j <= numberOfMachines; ++j){
			cMax[i][j].time = 0;
		}
	}
  // obliczanie cMaxa poprzez iteracje po wszystkich zadaniach
	for (int i = 1; i <= numberOfCurrentTask; ++i){
		for (int j = 1; j <= numberOfMachines; ++j){
			cMax[i][j].time = max(cMax[i-1][j].time, cMax[i][j-1].time) + tab[i-1][j-1].time;
		}
	}
  return cMax[numberOfCurrentTask][numberOfMachines].time;
}
// algorytm Neh z akceleracja
int nehAcc(Task tmp[MAX_TASKS][MAX_MACHINES], Task data[MAX_TASKS][MAX_MACHINES])
{
	int min = 0, best = 0, Cmax = 0;
  // zaczynamy od drugiego zadania poniewaz pierwsze juz jest w tablicy tmp
	for (int i = 1; i < numberOfTasks; ++i){
    makeCopyTask(data, (columns[i].number - 1)); //kopiujemy zadanie
		calculateR(tmp, i); //liczymy macierze R i Q
		calculateQ(tmp, i);
		insert(tmp, i); // wstawiamy skopiowane zadanie na koniec tablicy
		Cmax = calculateCmaxAcceleration(i); // liczymy cMaxa
		min = Cmax; // poczatkowo ten cMax jest nasyzm minimum
		best = i; // i to jest poczatkowo nasz najlepszy rezultat

		for (int j = i; j > 0; --j){ // przesuwamy pokolei do samego poczatku nasze skopiowane zadanie
			for(int z = 0; z < numberOfMachines; ++z){
				mySwap(tmp[j][z].time,tmp[j-1][z].time);
				mySwap(tmp[j][z].number,tmp[j-1][z].number);
			}
			Cmax = calculateCmaxAcceleration(j - 1); // liczymy dla takiego uszeregowania cMaxa
			if (Cmax <= min){ // jesli cMax jest mniejszy niz poprzedni to wybierany ta pozycje jako najlepsza
				min = Cmax;
				best = j-1;
			}
		}
		for (int j = 0; j < best; ++j){ // zrobienie miejsca dla najleoszego ulozenia
			for (int k = 0; k < numberOfMachines; ++k){
				tmp[j][k].time = tmp[j+1][k].time;
				tmp[j][k].number = tmp[j+1][k].number;
			}
		}
		for (int j = 0; j < numberOfMachines; ++j){ // wstawienie w najlepsza pozycje zadania
			tmp[best][j].time = copyTask[0][j].time;
			tmp[best][j].number = copyTask[0][j].number;
		}
	}
	return min; // zwrocenie najmniejszego cMaxa
}

// algorytm Neh bez akceleracji
int neh(Task tmp[MAX_TASKS][MAX_MACHINES], Task data[MAX_TASKS][MAX_MACHINES])
{
	int min = 0, best = 0, Cmax = 0;
	for (int i = 1; i < numberOfTasks; ++i){
    makeCopyTask(data, (columns[i].number - 1));
		insert(tmp, i);
		Cmax = calculatecMax(tmp, i+1);
		min = Cmax;
		best = i;
		for (int j = i; j > 0; --j){
			for(int z = 0; z < numberOfMachines; ++z){
				mySwap(tmp[j][z].time,tmp[j-1][z].time);
				mySwap(tmp[j][z].number,tmp[j-1][z].number);
			}
			Cmax = calculatecMax(tmp, i+1);
			if (Cmax <= min){
				min = Cmax;
				best = j-1;
			}
		}
		for (int j = 0; j < best; ++j){
			for (int k = 0; k < numberOfMachines; ++k){
				tmp[j][k].time = tmp[j+1][k].time;
				tmp[j][k].number = tmp[j+1][k].number;
			}
		}
		for (int j = 0; j < numberOfMachines; ++j){
			tmp[best][j].time = copyTask[0][j].time;
			tmp[best][j].number = copyTask[0][j].number;
		}
	}
	return min;
}
// funkcja sprawdzajaca czy uszeregowania podane w pliku sa zgodne z rezultatami z zadania
bool compareResults(Task dataAfterNeh[MAX_TASKS][MAX_MACHINES], int correctResults[MAX_TASKS]){
  for(int i = 0; i < numberOfTasks; i++){
    if(dataAfterNeh[i][0].number != correctResults[i]){
      return false;
    }
  }
  return true;
}

int main(){
  clock_t start;
  double t, allTime = 0;
  string nehText;
  int cMax, correctNeh;
  Task dataAfterNeh[MAX_TASKS][MAX_MACHINES];
  Task sortData[MAX_TASKS][MAX_MACHINES];
  int correctResults[MAX_TASKS];
  ifstream file;
  ofstream fileOut, fileCorrect;
  file.open("in1.txt");
  fileOut.open("out1.txt");
  fileCorrect.open("isCorrect.txt");
  for ( int e = 0; e < 121; ++e){
    for(int i = 0; i < MAX_TASKS; ++i){
      for(int j = 0; j < MAX_MACHINES; ++j){
        sortData[i][j].number = sortData[i][j].time = sortData[i][j].allTime = 0;
        dataAfterNeh[i][j].number = dataAfterNeh[i][j].time = dataAfterNeh[i][j].allTime = 0;
      }
    }
    // wczytywanie z pliku
    file >> nehText;
    file >> numberOfTasks >> numberOfMachines;
    for(int i = 0; i < numberOfTasks; ++i){
      for(int j = 0; j < numberOfMachines; ++j){
        sortData[i][j].number = i+1;
        file >> sortData[i][j].time;
      }
    }
    file >> nehText;
    file >> correctNeh;
    for(int i = 0; i < numberOfTasks; i++){
      file >> correctResults[i];
    }
    //obliczenie lacznych czasow
    for(int i = 0; i < numberOfTasks; ++i){
      sortData[i][0].allTime = 0;
      for(int j = 0; j < numberOfMachines; ++j){
        sortData[i][0].allTime = sortData[i][0].allTime + sortData[i][j].time;
      }
    }
    // sortowanie od najdluzszego do najkrotszego zadania
    columns = new Task[numberOfTasks];
    makeCopyColumn(sortData);
    sort(columns, columns + numberOfTasks);

    for(int i = 0; i < numberOfMachines; ++i){
  		dataAfterNeh[0][i].time = sortData[columns[0].number-1][i].time;
  		dataAfterNeh[0][i].number = sortData[columns[0].number-1][i].number;
  	}
    start = clock(); // uruchomienie zegara
    cMax = nehAcc(dataAfterNeh, sortData); // wykonanie algorytmu
    t = (double)(clock() - start)/ CLOCKS_PER_SEC; // stop zegara
    allTime += t;
    fileOut << cMax << endl;
    for(int i = 0; i < numberOfTasks; ++i){
      fileOut << dataAfterNeh[i][0].number << " ";
    }
    fileOut << endl << endl;
    if(compareResults(dataAfterNeh, correctResults) && cMax == correctNeh){ // porownanie wynikow
      fileCorrect << "wynik poprawny" << endl;
    }else{
      fileCorrect << "wynik zly!!" << endl;
    }
    delete[] columns;
  }
  file.close();
  fileOut.close();
  fileCorrect.close();
  cout << "calkowity czas: " << allTime <<"s" << endl;
  return 0;
}
