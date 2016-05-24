#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <climits>
#include <fstream>
#include <ctime>

using namespace std;

struct TaskComponent{
	int nr;
	int time;
	int machine;
	int nextTech;
	int prevTech;
	int nextQueue;
	int prevQueue;
	int R;
	int Q;
};

const int & max (const int & a, const int & b) {
  return (a<b)?b:a;
}

vector < vector < int > > machines;
int numberOfMachines, numberOfTasks, alreadyOnMachine = 0, cMax;

void clear(TaskComponent & a){
	a.time = a.machine = a.R = a.Q = 0;
	a.nextTech = a.prevTech = a.nextQueue = a.prevQueue = a.nr = 0;
}

void designateNextAndPrevTech(vector < TaskComponent > & components){
	int index;
	for(int i = 0; i < numberOfTasks; ++i){
		for(int j = 1; j <= numberOfMachines; ++j){
			index = i * numberOfMachines + j;
			if(j == 1){
				components[index].prevTech = 0;
				components[index].nextTech = components[index + 1].nr;
			}
			else if(j == numberOfMachines){
				components[index].prevTech = components[index - 1].nr;
				components[index].nextTech = 0;
			} 
			else{
				components[index].prevTech = components[index - 1].nr;
				components[index].nextTech = components[index + 1].nr;
			}
		}
	}
}

void loadData(vector < TaskComponent > & components, ifstream & file){
	alreadyOnMachine = numberOfTasks = numberOfMachines = 0;
	machines.clear();
	char tmpChar;
	int tmpNumber;
	TaskComponent tmp;
	clear(tmp);
	components.push_back(tmp);
	for(int i = 0; i < 9; ++i){
		file >> tmpChar;
	}
	file >> numberOfTasks >> numberOfMachines >> tmpNumber;
	for(int i = 0; i < numberOfTasks; ++i){
		file >> tmpNumber;
		for(int j = 1; j <= numberOfMachines; ++j){
			file >> tmp.machine >> tmp.time;
			tmp.nr = i * numberOfMachines + j;
			components.push_back(tmp);
		}
	}
	for(int i = 0; i < 5; ++i){
		file >> tmpChar;
	}
	file >> tmpNumber;
	for(int i = 0; i < numberOfTasks * numberOfMachines; ++i){
		file >> tmpNumber;
	}
	designateNextAndPrevTech(components);
}

void displayTasks(const vector < TaskComponent > & components){
	cout << "zadanie\tmaszyna\tczas\tpopTech\tnasTech\tpopKol\tnastKol\tR\tQ\n";
	for(int i = 0; i < components.size(); ++i){
		cout << components[i].nr << "\t" << components[i].machine 
		<< "\t" << components[i].time << "\t" << components[i].prevTech 
		<< "\t" << components[i].nextTech << "\t" << components[i].prevQueue 
		<< "\t" << components[i].nextQueue << "\t" << components[i].R 
		<< "\t" << components[i].Q << endl;
	}
}

void calculateMatrixR(vector <TaskComponent> & components, const vector <TaskComponent> & topology){
	cMax = 0;
	int indexPrevTech, indexPrevQueue;
	for(int i = 1; i < topology.size(); ++i){
		indexPrevTech = components[topology[i].nr].prevTech;
		indexPrevQueue = components[topology[i].nr].prevQueue;
		components[topology[i].nr].R = max(components[indexPrevTech].R, components[indexPrevQueue].R) + components[topology[i].nr].time;
		if(components[topology[i].nr].R > cMax)
			cMax = components[topology[i].nr].R;
	}
}

void calculateMatrixQ(vector <TaskComponent> & components, const vector <TaskComponent> & topology){
	int indexNextTech, indexNextQueue;
	for(int i = topology.size() - 1; i >= 1; --i){
		indexNextTech = components[topology[i].nr].nextTech;
		indexNextQueue = components[topology[i].nr].nextQueue;
		components[topology[i].nr].Q = max(components[indexNextTech].Q, components[indexNextQueue].Q) + components[topology[i].nr].time;
	}
}

bool comparatorTime(const TaskComponent & x, const TaskComponent & y) {
	if(x.time == y.time)
		return x.nr < y.nr;
	else
    	return x.time > y.time;
}

vector <TaskComponent> sortComponentsByTime(const vector < TaskComponent > & components){
	vector <TaskComponent> tmp = components;
	sort(tmp.begin(), tmp.end(), comparatorTime);
	return tmp;
}

void initialiseMachines(){
	vector <int> tmp;
	tmp.clear();
	for (int i = 0; i < numberOfMachines; ++i){
		machines.push_back(tmp);
	}
}

void displayMachines(ofstream & fileOutput){
	for(int i = 0; i < machines.size(); ++i){
		fileOutput << "machine" << i + 1 << ": ";
		for(int j = 0; j < machines[i].size(); ++j){
			fileOutput << machines[i][j] << " " ;
		}
		fileOutput << endl;
	}
}

int max(int a, int b, int c, int d){
	int maxValue = a;
	if(b > maxValue) maxValue = b;
	if(c > maxValue) maxValue = c;
	if(d > maxValue) maxValue = d;

	return maxValue;
}

void designateBestPosition(TaskComponent & task, const int & indexMachine, vector <TaskComponent> & components){
	int min = INT_MAX, way1, way2, way3, way4, maxValue, correctPrevQueue, correctNextQueue, correctIndex;
	int indexPrevTech, indexNextTech, indexPrevQueue, indexNextQueue;
	for(int i = 0; i <= machines[indexMachine].size(); ++i){
		machines[indexMachine].insert(machines[indexMachine].begin() + i, task.nr);
		indexPrevTech = task.prevTech;
		indexNextTech = task.nextTech;
		indexPrevQueue = (i - 1 >= 0 ? machines[indexMachine][i - 1] : 0);
		indexNextQueue = (i + 1 < machines[indexMachine].size() ? machines[indexMachine][i + 1] : 0);
		way1 = components[indexPrevTech].R + components[indexNextTech].Q;
		way2 = components[indexPrevTech].R + components[indexNextQueue].Q;
		way3 = components[indexPrevQueue].R + components[indexNextTech].Q;
		way4 = components[indexPrevQueue].R + components[indexNextQueue].Q;
		maxValue = max(way1, way2, way3, way4);
		if(maxValue < min){
			min = maxValue;
			correctPrevQueue = indexPrevQueue;
			correctNextQueue = indexNextQueue;
			correctIndex = i;
		}
		machines[indexMachine].erase(machines[indexMachine].begin() + i);
	}
	task.prevQueue = correctPrevQueue;
	task.nextQueue = correctNextQueue;
	if(task.prevQueue != 0)
		components[task.prevQueue].nextQueue = task.nr;
	if(task.nextQueue != 0)
		components[task.nextQueue].prevQueue = task.nr;
	machines[indexMachine].insert(machines[indexMachine].begin() + correctIndex, task.nr);
}

void putTaskOnMachine(vector <TaskComponent> & components, const vector <TaskComponent> & componentsSortedByTime){
	int indexMachine;
	for(int i = 0; i < componentsSortedByTime.size(); ++i){
		indexMachine = componentsSortedByTime[i].machine - 1;
		if(machines[indexMachine].empty()){
			machines[indexMachine].push_back(componentsSortedByTime[i].nr);
			alreadyOnMachine ++;
		}
		else{
			designateBestPosition(components[componentsSortedByTime[i].nr], indexMachine, components);
			alreadyOnMachine ++;
			return;
		}
	}
}

vector <TaskComponent> designateTopology(vector <TaskComponent> components){
	vector <TaskComponent> topology;
	int step = 0;
	topology.push_back(components[0]);
	while(step < numberOfMachines * numberOfTasks){
		for(int i = components.size() - 1; i >= 1; --i){
			if(components[i].prevQueue == 0 && components[i].prevTech == 0){
				topology.push_back(components[i]);
				components[i].prevQueue = INT_MAX;
				components[i].prevTech = INT_MAX;
				components[components[i].nextTech].prevTech = 0;
				components[components[i].nextQueue].prevQueue = 0;
				step ++;
				if(step == numberOfMachines * numberOfTasks)
					break;
			}
		}
	}
	return topology;
}

int main(){
	clock_t start;
  	double t, allTime = 0;
	ifstream file;
	ofstream fileOutput;
	vector <TaskComponent> components, componentsSortedByTime, topology;
	file.open("in0.txt");
	fileOutput.open("output.txt");
	for(int  i = 0; i <= 80; ++i){
		topology.clear();
		componentsSortedByTime.clear();
		components.clear();
		loadData(components, file);
		initialiseMachines();
		start = clock();
		while(1){
			topology = designateTopology(components);
			calculateMatrixR(components, topology);
			calculateMatrixQ(components, topology);
			componentsSortedByTime = sortComponentsByTime(components);
			if(alreadyOnMachine > 0)
				componentsSortedByTime.erase(componentsSortedByTime.begin(),componentsSortedByTime.begin() + alreadyOnMachine);
			if(componentsSortedByTime.size() < 2)
				break;
			putTaskOnMachine(components, componentsSortedByTime);
		}
		t = (double)(clock() - start)/ CLOCKS_PER_SEC;
		allTime += t;
		cout << "\ndata " << i << ": "<< cMax <<endl << endl;
		fileOutput << "\ndata " << i << ": "<< cMax <<endl << endl;
		displayMachines(fileOutput);
	}
	cout << "\nlaczny czas: " << allTime <<endl;
	file.close();
	fileOutput.close();
}