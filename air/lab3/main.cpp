#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <climits>
using namespace std;

struct Node{
	int id;
	int earliestStart;
	int earliestFinish;
	int lateStart;
	int lateFinish;
	int operationTime;
	int totalFloat;
	map < int, Node* > previous;
	map < int, Node* > next;
};

map <int, Node> nodes;
vector < Node > criticalPath;
int nodesNumber, curvesNumber;

void initNode(Node & node){
	node.earliestStart = node.earliestFinish = node.lateStart = node.lateFinish = node.operationTime = node.totalFloat = 0;
}

void loadData(string fileName){
	ifstream file;
	Node tmpNode;
	int from, to;

	initNode(tmpNode);
	file.open(fileName.c_str());
	file >> nodesNumber >> curvesNumber;
	for(int i = 0; i < nodesNumber; ++i){
		file >> tmpNode.operationTime;
		tmpNode.id = i;
		nodes[i] = tmpNode;
	}
	for(int i = 0; i < curvesNumber; ++i){
		file >> from >> to;
		from = from - 1;
		to = to - 1;
		nodes[from].next[to] = &nodes[to];
		nodes[to].previous[from] = &nodes[from];
	}
	file.close();
}

int findBiggestEarliestFinishTimeInMap(map<int, Node*> m){
	int maxTime = 0;
	for(map <int, Node*>::iterator obj = m.begin(); obj != m.end(); ++obj){
		if(obj -> second -> earliestFinish > maxTime){
			maxTime = obj -> second -> earliestFinish;
		}
	}
	return maxTime;
}

int findMinLatestStartTimeInMap(map<int, Node*> m){
	int minTime = INT_MAX;
	for(map <int, Node*>::iterator obj = m.begin(); obj != m.end(); ++obj){
		if(obj -> second -> lateStart < minTime){
			minTime = obj -> second -> lateStart;
		}
	}
	return minTime;
}

void calculateGraf(){
	Node node;
	int maxEarliestFinish = 0;

	for(map <int, Node>::iterator obj = nodes.begin(); obj != nodes.end(); ++obj){
		if(obj -> second.previous.empty()){
			obj -> second.earliestStart = 0;
		} else {
			obj -> second.earliestStart = findBiggestEarliestFinishTimeInMap(obj -> second.previous);
		}
		obj -> second.earliestFinish = obj -> second.earliestStart + obj -> second.operationTime;
		if(obj -> second.earliestFinish > maxEarliestFinish)
			maxEarliestFinish = obj -> second.earliestFinish;
	}

	for(map <int, Node>::reverse_iterator obj = nodes.rbegin(); obj != nodes.rend(); ++obj){
		if(obj -> second.next.empty()){
			obj -> second.lateFinish = maxEarliestFinish;
		} else {
			obj -> second.lateFinish = findMinLatestStartTimeInMap(obj -> second.next);
		}
		obj -> second.lateStart = obj -> second.lateFinish - obj -> second.operationTime;
		obj -> second.totalFloat = obj -> second.lateStart - obj -> second.earliestStart;
		if(obj -> second.totalFloat == 0)
			criticalPath.push_back(obj -> second);
	}

}

void displayNode(int key){
	if(nodes.find(key) != nodes.end()){
		cout << "\t\t\t\twierzchołek: " << key << endl;
		cout << nodes[key].earliestStart << "\t" << nodes[key].operationTime << "\t" << nodes[key].earliestFinish << endl;
		cout << nodes[key].lateStart << "\t" << nodes[key].totalFloat << "\t" << nodes[key].lateFinish << endl << endl; 
	}
}

void displayNodes(){
	for(int i = 0; i < nodesNumber; ++i){
		displayNode(i);
	}
}

void displayCriticalPath(){
	for(int i = 0; i < criticalPath.size(); ++i){
		displayNode(criticalPath[i].id);
	}
}

int main(){
	loadData("in2.txt");
	calculateGraf();
	displayNodes();
	return 0;
}