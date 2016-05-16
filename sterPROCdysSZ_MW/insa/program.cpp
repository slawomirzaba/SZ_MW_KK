#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <climits>


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
int alreadyOnMachine = 0;
int numberOfMachines, numberOfTasks;

void clear(TaskComponent & a){
	a.time = a.machine = a.R = a.Q = 0;
	a.nextTech = a.prevTech = a.nextQueue = a.prevQueue = a.nr = 0;
}

void loadData(vector < TaskComponent > & tmpComponents){
	numberOfTasks = numberOfMachines = 3;
	TaskComponent tmp;
	clear(tmp);
	tmpComponents.clear();

	tmp.nr = 1;
	tmp.time = 10;
	tmp.machine = 1;
	tmpComponents.push_back(tmp);

	tmp.nr = 2;
	tmp.time = 15;
	tmp.machine = 2;
	tmpComponents.push_back(tmp);

	tmp.nr = 3;
	tmp.time = 7;
	tmp.machine = 1;
	tmpComponents.push_back(tmp);

	tmp.nr = 4;
	tmp.time = 20;
	tmp.machine = 2;
	tmpComponents.push_back(tmp);

	tmp.nr = 5;
	tmp.time = 17;
	tmp.machine = 1;
	tmpComponents.push_back(tmp);

	tmp.nr = 6;
	tmp.time = 8;
	tmp.machine = 3;
	tmpComponents.push_back(tmp);

	tmp.nr = 7;
	tmp.time = 9;
	tmp.machine = 1;
	tmpComponents.push_back(tmp);

	tmp.nr = 8;
	tmp.time = 10;
	tmp.machine = 2;
	tmpComponents.push_back(tmp);

	tmp.nr = 9;
	tmp.time = 14;
	tmp.machine = 3;
	tmpComponents.push_back(tmp);

}

void updateNextAndPrevTech(vector < TaskComponent > & tmpComponents){
	int index;
	for(int i = 0; i < numberOfTasks; ++i){
		for(int j = 0; j < numberOfMachines; ++j){
			index = i * numberOfTasks + j;
			if(j == 0){
				tmpComponents[index].prevTech = 0;
				tmpComponents[index].nextTech = tmpComponents[index + 1].nr;
			}
			else if(j == numberOfMachines - 1){
				tmpComponents[index].prevTech = tmpComponents[index - 1].nr;
				tmpComponents[index].nextTech = 0;
			} 
			else{
				tmpComponents[index].prevTech = tmpComponents[index - 1].nr;
				tmpComponents[index].nextTech = tmpComponents[index + 1].nr;
			}
		}
	}
}

int numberOfPrevious(TaskComponent component){
	if(component.prevQueue != 0 && component.prevTech != 0)
		return 2;
	else if((component.prevQueue == 0 && component.prevTech != 0) || (component.prevQueue != 0 && component.prevTech == 0))
		return 1;
	else
		return 0;
}

int numberOfNext(TaskComponent component){
	if(component.nextQueue != 0 && component.nextTech != 0)
		return 2;
	else if((component.nextQueue == 0 && component.nextTech != 0) || (component.nextQueue != 0 && component.nextTech == 0))
		return 1;
	else
		return 0;
}

void displayTasks(vector < TaskComponent > & tmpComponents){
	int index;
	for(int i = 0; i < tmpComponents.size(); ++i){
		index = i;
		cout << tmpComponents[index].nr << " " << tmpComponents[index].machine 
		<< " " << tmpComponents[index].time << " " << tmpComponents[index].nextTech 
		<< " " << tmpComponents[index].prevTech << " " << tmpComponents[index].nextQueue 
		<< " " << tmpComponents[index].prevQueue << " " << tmpComponents[index].R 
		<< " " << tmpComponents[index].Q << endl;
	}
}

int findIndex(vector <TaskComponent> tmpComponents, int nr){
	for(int i = 0; i < tmpComponents.size(); ++i){
		if(tmpComponents[i].nr == nr){
			return i;
		}
	}
}

void removeComponents(vector < TaskComponent > & tmpComponents, vector <int> toDelete){
	int index;
	for(int i = 0; i < tmpComponents.size(); ++i){
		for(int j = 0 ; j < toDelete.size(); ++j){
			if(toDelete[j] == tmpComponents[i].nr){
				if(tmpComponents[i + 1].prevTech != 0){
					tmpComponents[i + 1].prevTech = 0;
				}
				if(tmpComponents[i].nextQueue != 0){
					index = findIndex(tmpComponents, tmpComponents[i].nextQueue);
					tmpComponents[index].prevQueue = 0;
				}
				if(tmpComponents[i].prevQueue != 0){
					index = findIndex(tmpComponents, tmpComponents[i].prevQueue);
					tmpComponents[index].nextQueue = 0;
				}
				tmpComponents.erase(tmpComponents.begin() + i);
			}
		}
	}
}

void designateTopology(vector < TaskComponent > tmpComponents, vector <int> & topology, int step){
	vector <int> toDelete;
	for(int i = 0; i < tmpComponents.size(); ++i){
		if(numberOfPrevious(tmpComponents[i]) == 0){
			topology.push_back(tmpComponents[i].nr);
			toDelete.push_back(tmpComponents[i].nr);
			step ++;
		}
	}
	removeComponents(tmpComponents, toDelete);
	if(step >= (numberOfMachines * numberOfTasks) - 1){
		for(int i = 0; i < numberOfTasks; ++i){
			for(int j = 0; j < numberOfMachines; ++j){
				cout << topology[i * 3 + j] << " ";
			}
		}
		cout << endl;
		return;
	}
	else{
		designateTopology(tmpComponents, topology, step);
	}
		
}

void calculateR(vector < TaskComponent > & tmpComponents, vector <int> topology){
	int index, indexPrevTech, indexPrevQueue;
	for(int i = 0; i < topology.size(); ++i){
		index = topology[i] - 1;
		if(numberOfPrevious(tmpComponents[index]) == 0){
			tmpComponents[index].R = tmpComponents[index].time;
		}
		else if(numberOfPrevious(tmpComponents[index]) == 1){
			indexPrevTech = tmpComponents[index].prevTech - 1;
			tmpComponents[index].R = tmpComponents[indexPrevTech].R + tmpComponents[index].time;
		}
		else{
			indexPrevTech = tmpComponents[index].prevTech - 1;
			indexPrevQueue = tmpComponents[index].prevQueue - 1;
			tmpComponents[index].R = max(tmpComponents[indexPrevTech].R, tmpComponents[indexPrevQueue].R) 
			+ tmpComponents[index].time;
		}
	}
}

void calculateQ(vector < TaskComponent > & tmpComponents, vector <int> topology){
	int index, indexNextTech, indexNextQueue;
	for(int i = topology.size() - 1; i >= 0; --i){
		index = topology[i] - 1;
		if(numberOfNext(tmpComponents[index]) == 0){
			tmpComponents[index].Q = tmpComponents[index].time;
		}
		else if(numberOfNext(tmpComponents[index]) == 1){
			indexNextTech = tmpComponents[index].nextTech - 1;
			tmpComponents[index].Q = tmpComponents[indexNextTech].Q + tmpComponents[index].time;
		}
		else{
			indexNextTech = tmpComponents[index].nextTech - 1;
			indexNextQueue = tmpComponents[index].nextQueue - 1;
			tmpComponents[index].Q = max(tmpComponents[indexNextTech].Q, tmpComponents[indexNextQueue].Q) 
			+ tmpComponents[index].time;
		}
	}
}

bool comparatorTime(const TaskComponent& x, const TaskComponent& y) {
	if(x.time == y.time)
		return x.nr > y.nr;
	else
    	return x.time > y.time;
}

vector <TaskComponent> sortComponentsByTime(const vector < TaskComponent > & tmpComponents){
	vector <TaskComponent> tmp = tmpComponents;
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

int rForTask(int indexMachine, int indexQueue, TaskComponent task, vector <TaskComponent> tmpComponents){
	if(indexQueue == 0 && task.prevTech == 0)
		return 0;
	if(indexQueue == 0 && task.prevTech != 0)
		return tmpComponents[task.prevTech - 1].R;
	if(indexQueue != 0 && task.prevTech == 0)
		return tmpComponents[machines[indexMachine][indexQueue - 1] - 1].R;
	if(indexQueue != 0 && task.prevTech != 0){
		return max(tmpComponents[task.prevTech - 1].R, tmpComponents[machines[indexMachine][indexQueue - 1] - 1].R);
	}
}

int qForTask(int indexMachine, int indexQueue, TaskComponent task, vector <TaskComponent> tmpComponents){
	if(indexQueue == machines[indexMachine].size() - 1 && task.nextTech == 0)
		return 0;
	if(indexQueue == machines[indexMachine].size() - 1 && task.nextTech != 0)
		return tmpComponents[task.nextTech - 1].Q;
	if(indexQueue != machines[indexMachine].size() - 1 && task.nextTech == 0)
		return tmpComponents[machines[indexMachine][indexQueue + 1] - 1].Q;
	if(indexQueue != machines[indexMachine].size() - 1 && task.nextTech != 0){
		return max(tmpComponents[task.nextTech - 1].Q, tmpComponents[machines[indexMachine][indexQueue + 1] - 1].Q);
	}
}

void calculateMinCmax(vector <TaskComponent> & tmpComponents, int indexMachine, TaskComponent task){
	int min = INT_MAX, r, q, correctIndex, indexNext, indexPrev;
	TaskComponent prevQueue, nextQueue;
	for(int i = 0; i <= machines[indexMachine].size(); ++i){
		machines[indexMachine].insert(machines[indexMachine].begin() + i, task.nr);
		r = rForTask(indexMachine, i, task, tmpComponents);
		q = qForTask(indexMachine, i, task, tmpComponents);
		if(r + task.time + q < min){
			min = r + task.time + q;
			correctIndex = i;
		}
		machines[indexMachine].erase(machines[indexMachine].begin() + i);
	}
	machines[indexMachine].insert(machines[indexMachine].begin() + correctIndex, task.nr);
	alreadyOnMachine++;
	if(correctIndex == 0){
		indexNext = machines[indexMachine][correctIndex + 1] - 1;
		tmpComponents[task.nr - 1].nextQueue = machines[indexMachine][correctIndex + 1];
		tmpComponents[task.nr - 1].prevQueue = 0;
		tmpComponents[indexNext].prevQueue = task.nr;
	}
	else if(correctIndex == machines[indexMachine].size() - 1){
		indexPrev = machines[indexMachine][correctIndex - 1] - 1;
		tmpComponents[task.nr - 1].nextQueue = 0;
		tmpComponents[task.nr - 1].prevQueue = machines[indexMachine][correctIndex - 1];
		tmpComponents[indexPrev].nextQueue = task.nr;
	}
	else{
		indexNext = machines[indexMachine][correctIndex + 1] - 1;
		indexPrev = machines[indexMachine][correctIndex - 1] - 1;
		tmpComponents[task.nr - 1].nextQueue = machines[indexMachine][correctIndex + 1];
		tmpComponents[task.nr - 1].prevQueue = machines[indexMachine][correctIndex - 1];
		tmpComponents[indexPrev].nextQueue = task.nr;
		tmpComponents[indexNext].prevQueue = task.nr;
	}
}

void putTask(vector <TaskComponent> sortedComponents, vector <TaskComponent> & tmpComponents){
	int indexMachine;
	for(int i = 0; i < sortedComponents.size(); ++i){
		indexMachine = sortedComponents[i].machine - 1;
		if(machines[indexMachine].empty()){
			machines[indexMachine].push_back(sortedComponents[i].nr);
			alreadyOnMachine++;
		}
		else{
			calculateMinCmax(tmpComponents, indexMachine, sortedComponents[i]);
			return;
		}
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

int main(){
	vector <TaskComponent> components, sortedComponents;
	vector <int> topology;

	loadData(components);
	updateNextAndPrevTech(components);
	initialiseMachines();
	designateTopology(components, topology, 0);
	calculateR(components, topology);
	calculateQ(components, topology);
	sortedComponents = sortComponentsByTime(components);
	//sortedComponents.erase(sortedComponents.begin() + alreadyOnMachine);
	putTask(sortedComponents, components);
	displayMachines();
	displayTasks(components);

	topology.clear();
	designateTopology(components, topology, 0);
	calculateR(components, topology);
	calculateQ(components, topology);
	sortedComponents = sortComponentsByTime(components);
	cout << alreadyOnMachine << endl;
	sortedComponents.erase(sortedComponents.begin(),sortedComponents.begin() + alreadyOnMachine);
	putTask(sortedComponents, components);
	displayMachines();
	displayTasks(components);

	topology.clear();
	designateTopology(components, topology, 0);
	/*calculateR(components, topology);
	calculateQ(components, topology);
	sortedComponents = sortComponentsByTime(components);
	cout << alreadyOnMachine << endl;
	sortedComponents.erase(sortedComponents.begin(),sortedComponents.begin() + alreadyOnMachine);
	putTask(sortedComponents, components);
	displayMachines();
	displayTasks(sortedComponents);

	topology.clear();
	designateTopology(components, topology, 0);
	calculateR(components, topology);
	calculateQ(components, topology);
	sortedComponents = sortComponentsByTime(components);
	cout << alreadyOnMachine << endl;
	sortedComponents.erase(sortedComponents.begin(),sortedComponents.begin() + alreadyOnMachine);
	putTask(sortedComponents, components);
	displayMachines();
	displayTasks(sortedComponents);

	topology.clear();
	designateTopology(components, topology, 0);
	calculateR(components, topology);
	calculateQ(components, topology);
	sortedComponents = sortComponentsByTime(components);
	cout << alreadyOnMachine << endl;
	sortedComponents.erase(sortedComponents.begin(),sortedComponents.begin() + alreadyOnMachine);
	putTask(sortedComponents, components);
	displayMachines();
	displayTasks(sortedComponents);

	topology.clear();
	designateTopology(components, topology, 0);
	calculateR(components, topology);
	calculateQ(components, topology);
	sortedComponents = sortComponentsByTime(components);
	cout << alreadyOnMachine << endl;
	sortedComponents.erase(sortedComponents.begin(),sortedComponents.begin() + alreadyOnMachine);
	putTask(sortedComponents, components);
	displayMachines();
	displayTasks(sortedComponents);*/
}