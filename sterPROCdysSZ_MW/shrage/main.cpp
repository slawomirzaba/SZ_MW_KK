#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Task{
	int nr;
	int r;
	int p;
	int q;
};
vector < Task > tasks;
vector < Task > ready;
int n;

bool comparatorR (const Task & a, const Task & b){
	return a.r < b.r;
}

bool comparatorQ (const Task & a, const Task & b){
	return a.q > b.q;
}

void sortR(vector <Task> & vect){
	stable_sort(vect.begin(), vect.end(), comparatorR);
}

void sortQ(vector <Task> & vect){
	stable_sort(vect.begin(), vect.end(), comparatorQ);
}

void load(char* fileName){
	Task tmp;
	ifstream file;
	file.open(fileName);

	file >> n;
	for(int i = 0; i < n; ++i){
		tmp.nr = i + 1;
		file >> tmp.r >> tmp.p >> tmp.q;
		tasks.push_back(tmp);
	}
	file.close();
}
void shrage(){
	Task tmp;
	int time = 0, position = 0, cMax = 0;
	int* permutation = new int[n];
	ready.clear();
  	while(!ready.empty() || !tasks.empty()){
  		while(!tasks.empty() && tasks[0].r <= time){
  			tmp = tasks[0];
  			ready.push_back(tmp);
  			tasks.erase(tasks.begin());
  		}
  		if(ready.empty()){
  			time = tasks[0].r;
  		}else{
  			sortQ(ready);
  			tmp = ready[0];
  			ready.erase(ready.begin());
  			permutation[position++] = tmp.nr;
  			time += tmp.p;
  			cMax = max(cMax, time + tmp.q);
  		}
  	}
  	for(int i = 0; i < n; i++){
		cout << permutation[i] << " ";
	}
  	cout << endl << cMax << endl;
  	delete[] permutation;
}

void shrageInsert(){
	Task tmp, actual;
	actual.q = actual.p = actual.r = 0;
	int time = 0, cMax = 0;
	ready.clear();
  	while(!ready.empty() || !tasks.empty()){
  		while(!tasks.empty() && tasks[0].r <= time){
  			tmp = tasks[0];
  			ready.push_back(tmp);
  			tasks.erase(tasks.begin());
  			if(tmp.q >= actual.q){
  				actual.p = time - tmp.r;
  				time = tmp.r;
  				if(actual.p > 0)
  					ready.push_back(actual);
  			}
  		}
  		if(ready.empty()){
  			time = tasks[0].r;
  		}else{
  			sortQ(ready);
  			tmp = ready[0];
  			ready.erase(ready.begin());
  			actual = tmp;
  			time += tmp.p;
  			cMax = max(cMax, time + tmp.q);
  		}
  	}
  	cout << endl << cMax << endl;
}

int main(){
	char file[10] = "in1.txt";
	load(file);
	sortR(tasks);
	shrageInsert();
	return 0;
}
