#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

int max(int a, int b){
	if(a > b)
		return a;
	return b;
}
class Data{
	private:
		int r;
		int p;
		int q;
		int taskNumber;
	public:
		Data(){
			r = p = q = 0;
		}
		void setR(int r){
			this -> r = r;
		}
		void setP(int p){
			this -> p = p;
		}
		void setQ(int q){
			this -> q = q;
		}
		void setTaskNumber(int nr){
			this -> taskNumber = nr;
		}
		int getR(){
			return r;
		}
		int getP(){
			return p;
		}
		int getQ(){
			return q;
		}
		int getTaskNumber(){
			return taskNumber;
		}
};

vector <Data> collectionData;
vector <Data> sortData;

void loadData(string fileName){
	int count;
	int i = 1;
	int tmpNumber;
	Data tmp;
	ifstream file;
	file.open(fileName.c_str());
	if( !file.good()){
		exit(1);
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

void sortTasks(){
	for(int i = 0; i < collectionData.size(); i++){
		sortData.push_back(collectionData[i]);
	}
}

void executeTasks(){
	int cMax = 0;
	int currentTime = 0;
	int timeAfterLastFinishedTask = 0;
	int startTimeAnotherTask;
	for(int i = 0; i < sortData.size(); i++){
		startTimeAnotherTask = max(timeAfterLastFinishedTask, sortData[i].getR());
		timeAfterLastFinishedTask = startTimeAnotherTask + sortData[i].getP();
		cMax = max(cMax, (startTimeAnotherTask + sortData[i].getP() + sortData[i].getQ()));
		//cout << startTimeAnotherTask << endl;
	}
	cout << cMax << endl;
}

int main(){
	loadData("data1.txt");
	sortTasks();
	executeTasks();
	return 0;
}
