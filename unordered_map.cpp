//Carlos Tardon Rubio DG231
#include <unordered_map>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct terna{
	string nombre;
	int num;
	int time;
};

bool operator<(terna const& t1, terna const& t2){
	return t1.num > t2.num  || t1.num == t2.num && t1.time < t2.time ||
	t1.num == t2.num && t1.time == t2.time && t1.nombre < t2.nombre;
	
}

void caso(){
	string nombre,problema,veredicto; int time;
	cin >> nombre;
	unordered_map<string,pair<int,int> > sol;
	//cada equipo tiene un unordered_map que indica el numero de fallos dedicados a los problemas que está resolviendo
	//un -1 indica problema ya resuelto
	unordered_map<string,unordered_map<string,int> > map;
	while(nombre != "FIN"){
		cin >> problema >> time >> veredicto;
		if(veredicto == "AC"){
			if(map[nombre][problema] != -1){
				sol[nombre].first++;
				sol[nombre].second += time + 20* map[nombre][problema];
				map[nombre][problema] = -1;
			}
		}else{
			if(map[nombre][problema] != -1){
				map[nombre][problema] += 1;
				sol[nombre];
			}
		}
	
		cin >> nombre;
	}
	vector<terna> v;
	for(auto it: sol){
		terna t;
		t.nombre = it.first;
		t.num = it.second.first;
		t.time = it.second.second;
		v.push_back(t);
	}
	sort(v.begin(),v.end());
	for(terna & t:v){
		cout << t.nombre << " " << t.num << " " << t.time << "\n";
	}
	cout << "----\n";
}
int main(){
	int n;
	cin >> n;
	while(n--)caso();
	
}
