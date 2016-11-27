#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <algorithm> 
#include <ctime>
using namespace std;

struct Curve{
	int firstNode;
	int secondNode;
	int weight;

	bool operator < ( const Curve& curve ) const
	{
		return weight > curve.weight;
	}
};

struct Node{
	int number;
	int group;
};

struct Group{
	int representant;
	int rank;

	Group() 
	: representant ( -1 )
	, rank ( 0 ) {}

	Group(int repr, int r)
	: representant( repr )
	, rank ( r ) {}
};

struct DisJoint{
	vector < Group > groups;

	DisJoint(){
		groups.clear();
	}

	void initDisJoint(int nodes);
	void setGroupRepresentant(int groupIndex);
	int findRepresentant(int node);
	void connectDisJointCollection(Curve curve);

};

vector < Curve > curves;
int nodesNumber, curvesNumber;
DisJoint disJoint;

void sortCurves();
void loadData(char* fileName);
int kruskal();

void DisJoint::initDisJoint(int nodes){
	Group group;

	for(int i = 0; i < nodes; ++i){
		group.representant = i;
		groups.push_back(group);
	}
}

void DisJoint::setGroupRepresentant(int groupIndex){
	groups[groupIndex].representant = groupIndex;
}

int DisJoint::findRepresentant(int node){
	if(groups[node].representant != node) 
		groups[node].representant = findRepresentant(groups[node].representant);

  	return groups[node].representant;
}

void DisJoint::connectDisJointCollection(Curve curve){
	int firstParent = findRepresentant(curve.firstNode);
	int secondParent = findRepresentant(curve.secondNode);

	if(groups[firstParent].rank > groups[secondParent].rank){
		groups[secondParent].representant = firstParent;
	}
	else if(groups[firstParent].rank < groups[secondParent].rank){
		groups[firstParent].representant = secondParent;
	}
	else if(firstParent != secondParent){
		groups[secondParent].representant = firstParent;
		groups[firstParent].rank ++;
	}
}

void sortCurves(){
	make_heap (curves.begin(), curves.end());
}

void loadData(char* fileName){
	ifstream file;
	Curve curve;
	Node node;

	file.open(fileName);
	file >> nodesNumber >> curvesNumber;
	for(int i = 0; i < curvesNumber; ++i){
		file >> curve.firstNode >> curve.secondNode >> curve.weight;
		curves.push_back(curve);
	}
	file.close();
	disJoint.initDisJoint(nodesNumber);
}

int kruskal(){
	int minPath = 0;
	Curve curve;

	sortCurves();
	for(int i = 1; i < nodesNumber; ++i){
		do{

			curve = curves.front();
			pop_heap (curves.begin(), curves.end()); 
			curves.pop_back();

		} while(disJoint.findRepresentant(curve.firstNode) == disJoint.findRepresentant(curve.secondNode));
		disJoint.connectDisJointCollection(curve);
		cout << curve.firstNode << " -> " << curve.secondNode << " : " << curve.weight << endl;
		minPath += curve.weight;
	}
	return minPath;
}

int main(int argc, char* argv[]){
	int min;
	if(argc == 2){
		loadData(argv[1]);
		cout << "\nDrzewo rozpinające:\n";
		const clock_t begin = clock();
		min = kruskal();
		const float end = static_cast<float>( clock() - begin ) / CLOCKS_PER_SEC * 1000;
		cout << "\nSuma wag w minimalnym drzewie rozpinającym: " << min << endl;
		cout << "\nCzas wykonania: " << end << "ms" << endl << endl;
	}
	return 0;
}