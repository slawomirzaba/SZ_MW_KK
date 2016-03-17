#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

struct Data{
  int p;
  int w;
  int d;
};
int n, N;
Data* tabData;
int* F, *tabIndexes, *queue;

void loadData(const string& fileName){
  ifstream file;
  file.open(fileName.c_str());
  if( !file.good() )
    exit(-1);
  file >> n;
  N = 1 << n;
  tabData = new Data[n];
  queue = new int[n];
  F = new int[N];
  tabIndexes = new int[N];
  for(int i = 0; i < n; i++){
    file >> tabData[i].p >> tabData[i].w >> tabData[i].d;
  }
  file.close();
}

void displayArray(const int* tab, const int& size){
  for(int i = 0; i < size; i++){
    cout << tab[i] << " ";
  }
}

void fillTaskQueue(){
  int taskNumber = n;
  int indexOfPower;
  int j = N-1;
  while (taskNumber > 0) {
  queue[--taskNumber] = indexOfPower = tabIndexes[j] + 1;
  j = j - (1 << (indexOfPower - 1));
  }
}

int calculateCmax(int binaryNumber){
  int tmp = 0;
  int cMax = 0;
  while( binaryNumber > 0 ){
    if( binaryNumber & 1 ){
      cMax += tabData[tmp].p;
    }
    binaryNumber /= 2;
    tmp++;
  }
  return cMax;
}

void CalculateFvalue(const int& index, int cMax){
  int valueTabIndexes;
  int tmp = index;
  int tmp2 = 0;
  int Ftmp;
  while( tmp > 0){
    if(tmp & 1){
      Ftmp = F[ index - (1 << tmp2) ] + max(0, cMax - tabData[tmp2].d) * tabData[tmp2].w;
      if(F[index] >= Ftmp){
        valueTabIndexes = tmp2;
        F[index] = Ftmp;
      }
    }
    tmp /= 2;
    tmp2++;
  }
  tabIndexes[index] = valueTabIndexes;
}

void algorytm(){
  int cMax, j;
  F[0] = 0;
  for(int i = 0; i < n; i++){
    for(j = (1 << i); j < N && j < (1 << i) * 2 ; j++){
      F[j] = 10000000;
      cMax = calculateCmax(j);
      CalculateFvalue(j, cMax);
    }
  }
}

int main(){
  clock_t start;
  double t, allTime = 0;
  string fileName, tmp;
  for(int i = 1; i <= 11; i++){
    sprintf((char*)tmp.c_str(), "in%d.txt", i);
    string fileName = tmp.c_str();
    loadData(fileName);
    start = clock();
    algorytm();
    fillTaskQueue();
    t = (double)(clock() - start)/ CLOCKS_PER_SEC;
    allTime += t;
    cout << "kolejnosc zadan: ";
    displayArray(queue, n);
    cout << "\nkara: " << F[N-1] << endl;
    cout << "czas wykonania: " << t << endl << endl;
  }
  cout << "laczny czas: " << allTime <<endl;
  delete [] tabData;
  delete [] queue;
  delete [] tabIndexes;
  delete [] F;
  return 0;
}
