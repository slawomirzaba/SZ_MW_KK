#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct Data{
  int p;
  int w;
  int d;
};
int n, N;
Data* tabData;
int* F, *q, *que;

void loadData(string fileName){
  int p, w, d;
  ifstream file;
  file.open(fileName.c_str());
  if( !file.good() )
    exit(-1);
  file >> n;
  N = pow(2, n);
  tabData = new Data[n];
  F = new int[N];
  q = new int[N];
  que = new int[n];
  for(int i = 0; i < n; i++){
    file >> tabData[i].p >> tabData[i].w >> tabData[i].d;
  }
  file.close();
}

int main(){
  int cMax = 0, j = 1, u;
  int tmp, tmp2;
  loadData("in1.txt");
  F[0] = 0;
  for(int i = 0; i < n; i++){
    for(j = pow(2, i); j < N && j < pow(2, i) * 2 ; j++){
      F[j] = 10000000;
      tmp2 = 0;
      tmp = j;
      cMax = 0;
      while( tmp > 0){
        if(tmp & 1){
          cMax += tabData[tmp2].p;
        }
        tmp /= 2;
        tmp2++;
      }
      tmp2 = 0;
      tmp = j;
      while( tmp > 0){
        if(tmp & 1){
          if(F[j] >= F[ j - int(pow(2, tmp2))] + max(0, cMax - tabData[tmp2].d) * tabData[tmp2].w){
            u = tmp2;
            F[j] = min(F[j], F[ j - int(pow(2, tmp2))] + max(0, cMax - tabData[tmp2].d) * tabData[tmp2].w );
          }
        }
        tmp /= 2;
        tmp2++;
      }
      q[j] = u;
    }
  }
  j -= 1;
  tmp = n;
  while (tmp >= 0) {
  que[tmp--] = tmp2 = q[j] + 1;
  j = j - pow(2, tmp2-1);
}
  for(int i = 0; i < n; i++){
    cout << que[i] << " ";
  }
  cout << endl << F[N-1] << endl;
  return 0;
}
