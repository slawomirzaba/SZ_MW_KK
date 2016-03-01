#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

class Data{
	private:
		int r;
		int p;
		int q;
		int taskNumber;
	public:
		Data(){ r = p = q = 0; }

		void setR(int r){ this -> r = r; }
		void setP(int p){ this -> p = p; }
		void setQ(int q){ this -> q = q; }
		int getR(){ return r; }
		int getP(){ return p; }
		int getQ(){ return q; }
		int getTaskNumber(){ return taskNumber; }
		void setTaskNumber(int nr){ this -> taskNumber = nr; }
};

vector <Data> collectionData;
vector <Data> sortData;

void loadData(char* fileName){
	int count;
	int i = 1;
	int tmpNumber;
	Data tmp;
	ifstream file;
	file.open(fileName);
	if( !file.good()){
		exit(EXIT_FAILURE);
	}
	file >> count;
	while(!file.eof()){
		tmp.setTaskNumber(i);
		file >> tmpNumber;
		tmp.setR(tmpNumber);
		file >> tmpNumber;
		tmp.setP(tmpNumber);
		file >> tmpNumber;
		tmp.setQ(tmpNumber);
		collectionData.push_back(tmp);
		i++;
	}
	file.close();
}

int minR(vector <Data> vec){
	int min = 10000;
	for(int i = 0; i < vec.size(); i++){
		if(vec[i].getR() < min){
			min = vec[i].getR();
		}
	}
	for(int i = 0; i < vec.size(); i++){
		if(vec[i].getR() == min){
			return i;
		}
	}
}
int maxQ(vector <Data> vec){
	int max = -1;
	for(int i = 0; i < vec.size(); i++){
		if(vec[i].getQ() > max){
			max = vec[i].getQ();
		}
	}
	for(int i = 0; i < vec.size(); i++){
		if(vec[i].getQ() == max){
			return i;
		}
	}
}

struct less_than
{
    bool operator() (Data data1, Data data2)
    {
        if ( data1.getR()  < data2.getR() ){
        	return true;
		}
    }
};

void sortTasks123(){
	for(int i = 0; i < collectionData.size(); i++){
		sortData.push_back(collectionData[i]);
	}
}

void sortR(){
  sortData = collectionData;
	sort(sortData.begin(), sortData.end(), less_than());
}

int shrage(){
	int indexR, indexQ;
	int t = 0, cMax = 0;
	Data e;
	while(!sortData.empty() || !collectionData.empty()){
		while(!collectionData.empty() && collectionData[indexR = minR(collectionData)].getR() <= t){
			e = collectionData[indexR];
			sortData.push_back(e);
			collectionData.erase(collectionData.begin() + indexR);
		}
		if( sortData.empty() ){
			t =  collectionData[indexR = minR(collectionData)].getR();
			continue;
		}
		e = sortData[indexQ = maxQ(sortData)];
		sortData.erase(sortData.begin() + indexQ);
		t += e.getP();
		cMax = max(cMax, t + e.getQ());
	}
	return cMax;
}


int executeTasks(){
	int cMax = 0;
	int currentTime = 0;
	int timeAfterLastFinishedTask = 0;
	int startTimeAnotherTask;
	for(int i = 0; i < sortData.size(); i++){
		startTimeAnotherTask = max(timeAfterLastFinishedTask, sortData[i].getR());
		timeAfterLastFinishedTask = startTimeAnotherTask + sortData[i].getP();
		cMax = max(cMax, (startTimeAnotherTask + sortData[i].getP() + sortData[i].getQ()));
	}
	return cMax;
}

int main(){
	char fileName[20];
	int cMax;
	int cMaxAssume = 0;
	for(int i = 1; i <= 4; i++ ){
		collectionData.clear();
		sortData.clear();	
		sprintf(fileName, "data%d.txt" ,i);
		loadData(fileName);
		cMax = shrage();
		cout << "dane" << i <<": " << cMax << "\t"; 
		cMaxAssume += cMax;
	}
	cout << "\nsuma: " << cMaxAssume << endl;
	
	return 0;
}
