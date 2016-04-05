#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

struct Operation{
  int time;
  int idMachine;
};

struct Task{
  int number;
  int allTime;
  vector<Operation> operations;
};

bool operator<(Task const & a, Task const & b)
{
    return a.allTime > b.allTime;
}

vector<Task> tasks;
int numberOfmachines, numberOftasks;
void loadData(const char* fileName){
  tasks.clear();
  Operation tmpOperation;
  Task tmpTask;
  vector <Operation> tmpVectorOperations;
  fstream file;
  file.open(fileName);
  file >> numberOftasks >> numberOfmachines;
  for(int i = 0; i < numberOftasks; i++){
    tmpVectorOperations.clear();
    tmpTask.number = i;
    for(int j = 0; j < numberOfmachines; j++){
      file >> tmpOperation.time;
      tmpOperation.idMachine = j;
      tmpVectorOperations.push_back(tmpOperation);
    }
    tmpTask.operations = tmpVectorOperations;
    tmpTask.allTime = 0;
    for(int k = 0; k < numberOfmachines; k++){
      tmpTask.allTime += tmpTask.operations[k].time;
    }
    tasks.push_back(tmpTask);
  }
  sort(tasks.begin(), tasks.end());
  file.close();
}
int calculateCmax(int nTasks, vector<Task> tmpVector){
  Operation tmp;
  Task* tabCmax = new Task[nTasks + 1];
	for (int i = 0; i <= nTasks; i++){
		for (int j = 0; j <= numberOfmachines; j++){
      tmp.time = 0;
      tmp.idMachine = j;
			tabCmax[i].operations.push_back(tmp);
    }
  }
	for (int i = 1; i <= nTasks; i++){
		for (int j = 1; j <= numberOfmachines; j++){
			tabCmax[i].operations[j].time = max(tabCmax[i-1].operations[j].time, tabCmax[i].operations[j-1].time) + tmpVector[i-1].operations[j-1].time;
    }
  }
  return tabCmax[nTasks].operations[numberOfmachines].time;
}

void displayVector(vector<Task> dane){
  for(vector <Task> :: iterator it = dane.begin(); it != dane.end(); it++){
    for(vector <Operation> :: iterator j = it -> operations.begin(); j != it -> operations.end(); j++){
      cout << j -> time << " ";
    }
    cout <<"suma: "<< it -> allTime;
    cout <<"\n";
  }
  cout <<"\n";
}

void neh(){
  int tmp, i, j;
  int cMax = 10000;
  int position;
  vector <Task> sortTasks;
  vector <Task> :: iterator it;
  sortTasks.push_back(tasks[0]);
  for(i = 1; i < numberOftasks; i++){
    it = sortTasks.begin();
    cMax = 10000;
    for(j = 0; j <= i; j++){
      sortTasks.insert(it + j, tasks[i]);
      it = sortTasks.begin();
      if((tmp = calculateCmax(i + 1, sortTasks)) < cMax){
        cMax = tmp;
        position = j;
      }
      sortTasks.erase(it + j);
    }
    sortTasks.insert(it + position, tasks[i]);
  }
  for( int  i = 0; i < numberOftasks; i++){
    cout << sortTasks[i].number + 1<< " ";
  }
  cout << "\n" << cMax <<endl;
}

int main(){
  int cMax;
  loadData("in1.txt");
  displayVector(tasks);
  neh();
  return 0;
}
