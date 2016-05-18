#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TaskComponent{
	int nr;
	int time;
	int machine;
	int nextTech;
	int prevTech;
	int nextQueue;
	int prevQueue;
	int numberOfPrev;
	int R;
	int Q;
};

struct Task{
	int nr;
	vector < TaskComponent > components;
};
int numberOfMachines;
int numberOfTasks;
vector <Task> tasks;

void setTask(vector <TaskComponent> tmp, int nr){
	Task tmpTask;
	tmpTask.components = tmp;
	tmpTask.nr = nr;
	tasks.push_back(tmpTask);

}
void clear(TaskComponent & a){
	a.time = a.machine = a.numberOfPrev = a.R = a.Q = 0;
	a.nextTech = a.prevTech = a.nextQueue = a.prevQueue = a.nr = -1;
}

void fillPrevAndNextTech(){
	for(int i = 0; i < tasks.size(); ++i){
		for(int j = 0; j < tasks[i].components.size(); ++j){
			if(j == 0){
				tasks[i].components[j].prevTech = -1;
				tasks[i].components[j].nextTech = tasks[i].components[j + 1].nr;
			}
			else if(j == tasks[i].components.size() - 1){
				tasks[i].components[j].prevTech = tasks[i].components[j - 1].nr;
				tasks[i].components[j].nextTech = -1;
				tasks[i].components[j].numberOfPrev ++;
			} 
			else{
				tasks[i].components[j].prevTech = tasks[i].components[j - 1].nr;
				tasks[i].components[j].nextTech = tasks[i].components[j + 1].nr;
				tasks[i].components[j].numberOfPrev ++;
			}
		}
	}
}

void updatePrevAndNext(vector <Task> & tmpTasks){
	for(int i = 0; i < tmpTasks.size(); ++i){
		for(int j = 0; j < tmpTasks[i].components.size(); ++j){
			tmpTasks[i].components[j].prevTech = -1;
			tmpTasks[i].components[j].numberOfPrev = 0;
			if(j == 0){
				tmpTasks[i].components[j].prevTech = -1;
			}
			else if(j == tmpTasks[i].components.size() - 1){
				tmpTasks[i].components[j].prevTech = tmpTasks[i].components[j - 1].nr;
				tmpTasks[i].components[j].numberOfPrev ++;
			} 
			else{
				tmpTasks[i].components[j].prevTech = tmpTasks[i].components[j - 1].nr;
				tmpTasks[i].components[j].numberOfPrev ++;
			}
			if(tmpTasks[i].components[j].prevQueue != -1)
				tmpTasks[i].components[j].numberOfPrev ++;
		}
	}
}

void loadData(){
	numberOfTasks = numberOfMachines = 3;
	TaskComponent tmp;
	vector < TaskComponent > tmpComponents;
	clear(tmp);

	tmpComponents.clear();
	tmp.nr = 0;
	tmp.time = 10;
	tmp.machine = 1;
	tmpComponents.push_back(tmp);
	tmp.nr = 1;
	tmp.time = 15;
	tmp.machine = 2;
	tmpComponents.push_back(tmp);
	tmp.nr = 2;
	tmp.time = 7;
	tmp.machine = 1;
	tmpComponents.push_back(tmp);
	setTask(tmpComponents, 0);

	tmpComponents.clear();
	tmp.nr = 3;
	tmp.time = 20;
	tmp.machine = 2;
	tmpComponents.push_back(tmp);
	tmp.nr = 4;
	tmp.time = 17;
	tmp.machine = 1;
	tmpComponents.push_back(tmp);
	tmp.nr = 5;
	tmp.time = 8;
	tmp.machine = 3;
	tmpComponents.push_back(tmp);
	setTask(tmpComponents, 1);

	tmpComponents.clear();
	tmp.nr = 6;
	tmp.time = 9;
	tmp.machine = 1;
	tmpComponents.push_back(tmp);
	tmp.nr = 7;
	tmp.time = 10;
	tmp.machine = 2;
	tmpComponents.push_back(tmp);
	tmp.nr = 8;
	tmp.time = 14;
	tmp.machine = 3;
	tmpComponents.push_back(tmp);
	setTask(tmpComponents, 2);

}

void displayTasks(){
	for(int i = 0; i < tasks.size(); ++i){
		for(int j = 0; j < tasks[i].components.size(); ++j){
			cout << tasks[i].components[j].nr << " " << tasks[i].components[j].machine 
			<< " " << tasks[i].components[j].time << " " << tasks[i].components[j].nextTech 
			<< " " << tasks[i].components[j].prevTech << " " << tasks[i].components[j].nextQueue 
			<< " " << tasks[i].components[j].prevQueue << " " << tasks[i].components[j].R 
			<< " " << tasks[i].components[j].Q << endl;
		}
		cout << endl;
	}
}

void designateTopology(vector <Task> tmpTasks, vector <int> & topology, int step){
	for(int i = 0; i < tmpTasks.size(); ++i){
		for(int j = 0; j < tmpTasks[i].components.size(); ++j){
			if(tmpTasks[i].components[j].numberOfPrev == 0){
				topology.push_back(tmpTasks[i].components[j].nr);
				tmpTasks[i].components.erase(tmpTasks[i].components.begin() + j);
				step ++;
			}
		}
	}
	updatePrevAndNext(tmpTasks);
	if(step >= (numberOfMachines * numberOfTasks) - 1){
		for(int i = 0; i < numberOfTasks; ++i){
			for(int j = 0; j < numberOfMachines; ++j){
				cout << topology[i * 3 + j] << " ";
			}
		}
		cout << endl;
		return;
	}
	else
		designateTopology(tmpTasks, topology, step);
}

void calculateR(vector <int> & topology){
	int taskIndex, componentIndex;
	for(int i = 0; i < topology.size(); ++i){
		taskIndex = i / (numberOfTasks);
		componentIndex = i % numberOfMachines;\
		if (tasks[taskIndex].components[componentIndex].numberOfPrev == 0)
		{
			tasks[taskIndex].components[componentIndex].R = tasks[taskIndex].components[componentIndex].time;
		}
		else if(tasks[taskIndex].components[componentIndex].numberOfPrev == 1){
			tasks[taskIndex].components[componentIndex].R = tasks[taskIndex].components[componentIndex - 1].R 
			+ tasks[taskIndex].components[componentIndex].time;
		}
		else if(tasks[taskIndex].components[componentIndex].numberOfPrev == 2){
			int tmpTask = tasks[taskIndex].components[componentIndex].prevQueue / numberOfTasks, 
			tmpComponent = tasks[taskIndex].components[componentIndex].prevQueue % numberOfMachines;;
			tasks[taskIndex].components[componentIndex].R = max(tasks[taskIndex].components[componentIndex - 1].R, tasks[tmpTask].components[tmpComponent].R) 
			+ tasks[taskIndex].components[componentIndex].time;
		}
	}
}

void calculateQ(vector <int> & topology){
	int taskIndex, componentIndex;
	for(int i = numberOfMachines * numberOfTasks - 1; i >= 0; --i){
		taskIndex = i / (numberOfTasks);
		componentIndex = i % numberOfMachines;\
		//cout << tasks[taskIndex].components[componentIndex].nextTech << " " << tasks[taskIndex].components[componentIndex].nextQueue << endl;
		if (tasks[taskIndex].components[componentIndex].nextTech == -1 
			&& tasks[taskIndex].components[componentIndex].nextQueue == -1)
		{
			tasks[taskIndex].components[componentIndex].Q = tasks[taskIndex].components[componentIndex].time;
		}
		else if(tasks[taskIndex].components[componentIndex].nextTech != -1 
			&& tasks[taskIndex].components[componentIndex].nextQueue == -1){
			tasks[taskIndex].components[componentIndex].Q = tasks[taskIndex].components[componentIndex + 1].Q 
			+ tasks[taskIndex].components[componentIndex].time;
		}
		else if(tasks[taskIndex].components[componentIndex].nextTech != -1 
			&& tasks[taskIndex].components[componentIndex].nextQueue != -1){
			int tmpTask = tasks[taskIndex].components[componentIndex].nextQueue / numberOfTasks, 
			tmpComponent = tasks[taskIndex].components[componentIndex].nextQueue % numberOfMachines;;
			tasks[taskIndex].components[componentIndex].Q = max(tasks[taskIndex].components[componentIndex + 1].Q, tasks[tmpTask].components[tmpComponent].Q) 
			+ tasks[taskIndex].components[componentIndex].time;
		}
	}
}

bool comparatorTime(const TaskComponent& x, const TaskComponent& y) {
    return x.time > y.time;
}


vector <TaskComponent> sortByTime(vector <Task> tmpTasks){
	vector <TaskComponent> tmp;
	for(int i = 0; i < tmpTasks.size(); ++i){
		for(int j = 0; j < tmpTasks[i].components.size(); ++j){
			tmp.push_back(tmpTasks[i].components[j]);
		}
	}
	sort(tmp.begin(), tmp.end(), comparatorTime);
	for(int i = 0; i < numberOfTasks; ++i){
		for(int j = 0; j < numberOfMachines; ++j){
			cout << tmp[i * 3 + j].nr << " " << tmp[i * 3 + j].time << endl;
		}
	}
	return tmp;
}

int main(){
	vector <int> topology;
	topology.clear();
	loadData();
	fillPrevAndNextTech();
	designateTopology(tasks, topology, 0);
	calculateR(topology);
	calculateQ(topology);
	displayTasks();
	sortByTime(tasks);
}