#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <climits>
#include <fstream>


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

vector < vector < int > > machines;
int numberOfMachines, numberOfTasks;
int alreadyOnMachine = 0;
int cMax;

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

void loadData(vector < TaskComponent > & components){
	ifstream file;
	int tmpNumber;
	TaskComponent tmp;
	clear(tmp);
	components.push_back(tmp);
	file.open("in0.txt");
	file >> numberOfTasks >> numberOfMachines >> tmpNumber;
	for(int i = 0; i < numberOfTasks; ++i){
		file >> tmpNumber;
		for(int j = 1; j <= numberOfMachines; ++j){
			file >> tmp.machine >> tmp.time;
			tmp.nr = i * numberOfMachines + j;
			components.push_back(tmp);
		}
	}
	designateNextAndPrevTech(components);
}

void displayTasks(vector < TaskComponent > & components){
	cout << "zadanie\tmaszyna\tczas\tpopTech\tnasTech\tpopKol\tnastKol\tR\tQ\n";
	for(int i = 0; i < components.size(); ++i){
		cout << components[i].nr << "\t" << components[i].machine 
		<< "\t" << components[i].time << "\t" << components[i].prevTech 
		<< "\t" << components[i].nextTech << "\t" << components[i].prevQueue 
		<< "\t" << components[i].nextQueue << "\t" << components[i].R 
		<< "\t" << components[i].Q << endl;
	}
}

void calculateMatrixR(vector <TaskComponent> & components, vector <TaskComponent> topology){
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

void calculateMatrixQ(vector <TaskComponent> & components, vector <TaskComponent> topology){
	int indexNextTech, indexNextQueue;
	for(int i = topology.size() - 1; i >= 1; --i){
		indexNextTech = components[topology[i].nr].nextTech;
		indexNextQueue = components[topology[i].nr].nextQueue;
		components[topology[i].nr].Q = max(components[indexNextTech].Q, components[indexNextQueue].Q) + components[topology[i].nr].time;
	}
}

bool comparatorTime(const TaskComponent& x, const TaskComponent& y) {
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

void displayMachines(){
	for(int i = 0; i < machines.size(); ++i){
		cout << "machine" << i + 1 << ": ";
		for(int j = 0; j < machines[i].size(); ++j){
			cout << machines[i][j] << " " ;
		}
		cout << endl;
	}
}

int max(int a, int b, int c, int d){
	int maxValue = a;
	if(b > maxValue) maxValue = b;
	if(c > maxValue) maxValue = c;
	if(d > maxValue) maxValue = d;

	return maxValue;
}

void designateBestPosition(TaskComponent & task, int indexMachine, vector <TaskComponent> & components){
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

void putTaskOnMachine(vector <TaskComponent> & components, vector <TaskComponent> componentsSortedByTime){
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
	vector <TaskComponent> components, componentsSortedByTime, topology;
	loadData(components);
	initialiseMachines();
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
	//calculateMatrixR(components);
	displayMachines();
	displayTasks(components);
	cout << cMax <<endl;

}