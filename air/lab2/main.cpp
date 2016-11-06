#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

vector < vector <int> > graf;
vector < vector <bool> > isModified;
vector < int > previous;
int curvesNumber, nodesNumber;

void initGraf(){
  vector <int> tmpRowGraf;
  vector < bool > tmpRowModified;

  graf.clear();
  isModified.clear();
  for(int i = 0; i < nodesNumber; ++i){
    tmpRowGraf.clear();
    tmpRowModified.clear();
    for(int j = 0; j < nodesNumber; ++j){
      tmpRowGraf.push_back(0);
      tmpRowModified.push_back(false);
    }
    isModified.push_back(tmpRowModified);
    graf.push_back(tmpRowGraf);
  }
}

void initPrevious(){
  previous.clear();
  for(int i = 0; i < nodesNumber; ++i){
    previous.push_back(0);
  }
}

void loadData(char * fileName){
  int from, to, weight;
  ifstream file;

  file.open(fileName);
  file >> nodesNumber >> curvesNumber;
  initGraf();
  initPrevious();
  for(int i = 0; i < curvesNumber; ++i){
    file >> from >> to >> weight;
    graf[from][to] = weight;
  }
  file.close();
}

bool bfs(){
  int from;
  vector < bool > isVisited;
  queue < int > q;

  for(int i = 0; i < nodesNumber; ++i){
    isVisited.push_back(false);
  }
  q.push(0);
  isVisited[0] = true;
  while(!q.empty()){
    from = q.front();
    q.pop();

    for(int i = 0; i < nodesNumber; ++i){
      if(!isVisited[i] && graf[from][i] != 0){
        q.push(i);
        previous[i] = from;
        isVisited[i] = true;
      }
    }
  }
  return (isVisited[nodesNumber - 1] == true);
}

void algorithm(){
  int fMax = 0, flow, from;

  while(bfs()){
    flow = INT_MAX;
    for(int i = nodesNumber - 1; i != 0; i = previous[i]){
      from = previous[i];
      flow = min(flow, graf[from][i]);
    }
    for(int i = nodesNumber - 1; i != 0; i = previous[i]){
      from = previous[i];
      graf[from][i] -= flow;
      graf[i][from] += flow;
      isModified[i][from] = true;
      isModified[from][i] = true;
    }
    fMax += flow;
  }
  cout << endl << "Maksymalny przeplyw: " << fMax << endl;
}

void displayPath(vector < vector <int> >& grafTmp){
  int* value;

  cout << "Przeplywy:" << endl;
  for(int i = 0; i < nodesNumber; ++i){
    for(int j = 0; j < nodesNumber; ++j){
      if(graf[i][j] && isModified[i][j]){
        if(grafTmp[i][j] != 0){
          value = &grafTmp[i][j];
        } else {
          value = &grafTmp[j][i];
        }
        cout << i << " -> " << j << " : " << graf[i][j] << " z mozliwych: " << *value << endl;
        *value -= graf[i][j];
      }
    }
  }
  cout << endl;
}

void displayNotUsedPaths(vector < vector <int> >& grafTmp){
  int* value;

  cout << "kanaly niewykorzystane: " << endl;
  for(int i = 0; i < nodesNumber; ++i){
    for(int j = 0; j < nodesNumber; ++j){
      if(graf[i][j] && !isModified[i][j]){
        if(grafTmp[i][j] != 0){
          value = &grafTmp[i][j];
        } else {
          value = &grafTmp[j][i];
        }
        cout << i << " -> " << j << " : " << graf[i][j] << " z mozliwych: " << *value << endl;
      }
    }
  }
  cout << endl;
}

int main(){
  vector < vector <int> > grafTmp;
  char fileName [10];
  clock_t start;
  double t;

  for(int i = 1; i <= 3; ++i){
    sprintf(fileName, "in%d.txt", i);
    cout << "\t\t\t" << fileName << endl;
    loadData(fileName);
    grafTmp = graf;
    start = clock();
    algorithm();
    t = (double)(clock() - start)/ (CLOCKS_PER_SEC / 1000);
    displayPath(grafTmp);
    displayNotUsedPaths(grafTmp);
    cout << "czas wykonania: " << t << "ms" << endl << endl;
  }
  return 0;
}
