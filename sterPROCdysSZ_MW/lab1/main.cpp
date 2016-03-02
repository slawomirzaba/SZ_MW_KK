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
vector <Data> ready;

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

int minP(vector <Data> vec){
	int min = 1000000;
	for(int i = 0; i < vec.size(); i++){
		if(vec[i].getP() < min){
			min = vec[i].getP();
		}
	}
	for(int i = 0; i < vec.size(); i++){
		if(vec[i].getP() == min){
			return i;
		}
	}
}

int minR(vector <Data> vec){
	int min = 1000000;
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
int findIndexByTaskNumber(vector <Data> vec, int nr){
	for(int i = 0; i < vec.size(); i++){
		if(vec[i].getTaskNumber() == nr){
			return i;
		}
	}
}
int getTaskIndexWithMaxQAndMinP(vector <Data> vec){
	vector <Data> tmp;
	int max = -1;
	for(int i = 0; i < vec.size(); i++){
		if(vec[i].getQ() > max){
			max = vec[i].getQ();
		}
	}
	for(int i = 0; i < vec.size(); i++){
		if(vec[i].getQ() == max){
			tmp.push_back(vec[i]);
		}
	}
	return findIndexByTaskNumber(vec, tmp[minP(tmp)].getTaskNumber());
}
void shrage(){
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
		}
		else{
			e = sortData[indexQ = getTaskIndexWithMaxQAndMinP(sortData)];
			cout << e.getTaskNumber() << endl;
			ready.push_back(e);
			sortData.erase(sortData.begin() + indexQ);
		}
		t += e.getP();
	}
}

int executeTasks(){
	int cMax = 0;
	int currentTime = 0;
	int timeAfterLastFinishedTask = 0;
	int startTimeAnotherTask;
	for(int i = 0; i < ready.size(); i++){
		startTimeAnotherTask = max(timeAfterLastFinishedTask, ready[i].getR());
		timeAfterLastFinishedTask = startTimeAnotherTask + ready[i].getP();
		cMax = max(cMax, (startTimeAnotherTask + ready[i].getP() + ready[i].getQ()));
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
		ready.clear();
		sprintf(fileName, "data%d.txt" ,i);
		loadData(fileName);
		shrage();
		cMax = executeTasks();
		cout << "dane" << i <<": " << cMax << "\t"; 
		cMaxAssume += cMax;
		system("pause");
	}
	cout << "\nsuma: " << cMaxAssume << endl;
	
	return 0;
}
