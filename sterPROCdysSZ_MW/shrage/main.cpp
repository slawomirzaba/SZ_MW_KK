#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <climits>
using namespace std;

struct Task{
	int nr;
	int r;
	int p;
	int q;
	int timeEntryOnMachine;
};
vector < Task > tasks;
vector < Task > ready;
vector < Task > bestPermutation;
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
		tmp.nr = i;
		file >> tmp.r >> tmp.p >> tmp.q;
		tasks.push_back(tmp);
	}
	file.close();
}
int shrage(vector <Task> & permutation){
	vector <Task> tmpTasks = permutation;
	permutation.clear();
	sortR(tmpTasks);
	Task tmp;
	int time = 0, cMax = 0;
	ready.clear();
  	while(!ready.empty() || !tmpTasks.empty()){
  		while(!tmpTasks.empty() && tmpTasks[0].r <= time){
  			tmp = tmpTasks[0];
  			ready.push_back(tmp);
  			tmpTasks.erase(tmpTasks.begin());
  		}
  		if(ready.empty()){
  			time = tmpTasks[0].r;
  		}else{
  			sortQ(ready);
  			tmp = ready[0];
  			tmp.timeEntryOnMachine = time;
  			ready.erase(ready.begin());
  			permutation.push_back(tmp);
  			time += tmp.p;
  			cMax = max(cMax, time + tmp.q);
  		}
  	}
  	return cMax;
  	
}

int shrageDivision(){
	vector <Task> tmpTasks = tasks;
	sortR(tmpTasks);
	Task tmp, actual;
	actual.q = actual.p = actual.r = 0;
	int time = 0, cMax = 0;
	ready.clear();
  	while(!ready.empty() || !tmpTasks.empty()){
  		while(!tmpTasks.empty() && tmpTasks[0].r <= time){
  			tmp = tmpTasks[0];
  			ready.push_back(tmp);
  			tmpTasks.erase(tmpTasks.begin());
  			if(tmp.q >= actual.q){
  				actual.p = time - tmp.r;
  				time = tmp.r;
  				if(actual.p > 0)
  					ready.push_back(actual);
  			}
  		}
  		if(ready.empty()){
  			time = tmpTasks[0].r;
  		}else{
  			sortQ(ready);
  			tmp = ready[0];
  			ready.erase(ready.begin());
  			actual = tmp;
  			time += tmp.p;
  			cMax = max(cMax, time + tmp.q);
  		}
  	}
  	return cMax;
}

void designateBlock(int & a, int & b, int & j, vector <Task> & permutation, int cMaxPermutation){
	int currentMax = 0;
	j = -1;

	for(int i = 0; i < n; ++i){
		if(permutation[i].timeEntryOnMachine + permutation[i].p + permutation[i].q > currentMax){
			b = i;
			currentMax = permutation[i].timeEntryOnMachine + permutation[i].p + permutation[i].q;
		}
	}
	for(a = b; a >= 0; --a){
		if(permutation[a].timeEntryOnMachine + permutation[a].p < permutation[a + 1].timeEntryOnMachine){
			break;
		}
	}

	for(int i = b - 1; i >= a; --i){
		if(permutation[i].q < permutation[b].q){
			j = i;
			break;
		}
	}

}

int minR(int start, int end, vector <Task> permutation){
	int r = INT_MAX;
	for(int i = start; i <= end; ++i)
		if(permutation[i].r < r){
			r = permutation[i].r;
		}

	return r;
}

int minQ(int start, int end, vector <Task> permutation){
	int q = INT_MAX;
	for(int i = start; i <= end; ++i)
		if(permutation[i].q < q){
			q = permutation[i].q;
		}

	return q;
}

int sumP(int start, int end, vector <Task> permutation){
	int p = 0;
	for(int i = 0; i <= end; ++i){
		p += permutation[i].p;
	}
}


void carlier(int &upBank, vector <Task> permutation){
	int cMax, a, b, j, tmpR, tmpQ, tmpP, rOryginal, qOryginal, downBank;
	cMax = shrage(permutation);
	if( cMax < upBank ){
		upBank = cMax;
		bestPermutation = permutation;
	}
	designateBlock(a, b, j, permutation, cMax);
	if(j == -1)
		return;
	tmpR = minR(j+1, b, permutation);
	tmpQ = minQ(j+1, b, permutation);
	tmpP = sumP(j+1, b, permutation);
	rOryginal = permutation[j].r;
	permutation[j].r = max(permutation[j].r, tmpR + tmpP);
	downBank = shrageDivision();
	if( downBank < upBank){
		carlier(upBank, permutation);
	}
	permutation[j].r = rOryginal;

	qOryginal = permutation[j].q;
	permutation[j].q = max(permutation[j].q, tmpQ + tmpP);
	downBank = shrageDivision();
	cout << downBank << upBank << endl;
	if( downBank < upBank){
		carlier(upBank, permutation);
	}
	permutation[j].q = qOryginal;
}

int main(){
	int max = INT_MAX;
	char file[10] = "in1.txt";
	load(file);
	carlier(max, tasks);
	for(int i = 0; i < n; i++)
		cout << bestPermutation[i].nr << " ";
	cout << endl << max << endl;
	return 0;
}
