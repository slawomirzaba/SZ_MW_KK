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

struct less_than_key
{
    bool operator() (Data data1, Data data2)
    {
        return ((data1.getR()) < (data2.getR()));
    }
};

void sortTasks123(){
	for(int i = 0; i < collectionData.size(); i++){
		sortData.push_back(collectionData[i]);
	}
}

void sortTasks2(){
  sortData = collectionData;
	sort(sortData.begin(), sortData.end(), less_than_key());
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
		//cout << startTimeAnotherTask << endl;
	}
	return cMax;
}

int main(){
	char fileName[20];
	int cMax;
	int cMaxAssume = 0;
	for(int i = 1; i <= 4; i++ ){
		sprintf(fileName, "data%d.txt" ,i);
		loadData(fileName);
		sortTasks2();
		cMax = executeTasks();
		cout << "dane" << i <<": " << cMax << "\t"; 
		cMaxAssume += cMax;
		collectionData.clear();
		sortData.clear();	
	}
	cout << "\nsuma: " << cMaxAssume << endl;
	return 0;
}
