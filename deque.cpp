//Carlos Tardon DG231
#include <string>
#include <stack>
#include <deque>
#include <iostream>
using namespace std;

bool es_vocal(char c){
	c = tolower(c);
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

void segundaFase(string & s, deque<char> & dq){
	int i = 0;
	for(; i < s.size();i += 2){
		dq.push_back(s[i]);
	}
	if(s.size() > 1){
		if(i == s.size()) i -= 1;
		else i = s.size() - 2;

		for(; i >= 0; i -= 2){
			dq.push_back(s[i]);
		}
	}
}
void vuelcaPila(string & s, stack<char> & conson){
	while(!conson.empty()){
		s.push_back(conson.top());
		conson.pop();
	}
}

void primeraFase(string & s, deque<char> & dq){
	stack<char> conson;
	while(!dq.empty()){
		if(es_vocal(dq.front())){
			vuelcaPila(s,conson);
			s.push_back(dq.front());
		}else{
			conson.push(dq.front());
		}
		dq.pop_front();
	}
	vuelcaPila(s,conson);

}

bool caso(){
	string s;
	getline(cin,s);
	if(!cin) return false;

	deque<char> dq;
	segundaFase(s,dq);
	string sol;
	primeraFase(sol,dq);

	cout << sol << "\n";

	return true;
}

int main(){
	while(caso());
}
