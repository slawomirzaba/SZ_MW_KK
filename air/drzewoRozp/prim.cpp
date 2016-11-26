#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

struct Neighbour{
	int from;
	int to;
	int weight;

	bool operator < ( const Neighbour& neighbour ) const
	{
		return weight > neighbour.weight;
	}
};

struct Node{
	int id;
	bool isVisited;
	vector < Neighbour > neighbours;

	Node()
	: id( 0 )
	, isVisited( false ) {
		neighbours.clear();
	}
};

int curvesNumber, nodesNumber;
vector < Node > nodes;

void loadData(char* fileName);
int prim();

void loadData(char* fileName){
	ifstream file;
	Node node;
	Neighbour neighbour;
	int from, to, weight;

	file.open(fileName);
	file >> nodesNumber >> curvesNumber;
	for(int i = 0; i < nodesNumber; ++i){
		node.id = i;
		nodes.push_back(node);
	}
	for(int i = 0; i < curvesNumber; ++i){
		file >> from >> to >> weight;

		neighbour.from = from;
		neighbour.to = to;
		neighbour.weight = weight;
		nodes[from].neighbours.push_back(neighbour);

		neighbour.from = to;
		neighbour.to = from;
		neighbour.weight = weight;
		nodes[to].neighbours.push_back(neighbour);
	}
	file.close();
}

int prim(){
	int nodeId, currentNodeId, min = 0;
	Neighbour neighbour;
	priority_queue < Neighbour > queue;
	
	nodes[0].isVisited = true;
	currentNodeId = nodes[0].id;
	for(int i = 1; i < nodesNumber; ++i){
		for(int j = 0; j < nodes[currentNodeId].neighbours.size(); ++j){
			nodeId = nodes[currentNodeId].neighbours[j].to;
			if( !nodes[nodeId].isVisited ){
				queue.push(nodes[currentNodeId].neighbours[j]);
			}
		}

		do{
			neighbour = queue.top();
			queue.pop();
			nodeId = neighbour.to;
		}  while( nodes[nodeId].isVisited );
		nodes[nodeId].isVisited = true;
		cout << neighbour.from << " -> " << neighbour.to << " : " << neighbour.weight << endl;
		min += neighbour.weight;
		currentNodeId = neighbour.to;
	}


	return min;
}

int main(int argc, char* argv[]){
	int min;

	if(argc > 1){
		loadData(argv[1]);
		min = prim();
		cout << "\nMinimalna wartość drzewa rozpinającego : " << min << endl;
	}
	return 0;
}