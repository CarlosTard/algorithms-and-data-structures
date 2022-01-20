//Carlos Tardon Rubio DG29
#include <iostream>
#include <queue>
#include <functional>
using namespace std;

struct ucm{
	int id;
	int period;
	long long int time;
};

bool operator<(ucm const& u1, ucm const& u2){
	return u1.time > u2.time || 
	u1.time == u2.time && u1.id > u2.id;
}
bool caso(){
	int n;
	cin >> n;
	if(n== 0) return false;
	priority_queue<ucm> q;
	while(n--){
		int id;int period;
		cin >> id >>  period;
		q.push({id,period,period});
	}
	int k; cin >> k;
	while(k--){
		ucm u = q.top();
		q.pop();
		cout << u.id << "\n";
		q.push({u.id,u.period,u.time + u.period});
	}
	
	cout << "---\n";
	return true;
}
int main(){
	
	while(caso());
}

