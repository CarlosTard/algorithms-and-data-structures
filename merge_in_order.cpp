//Carlos Tardón
#include <iostream>
#include <vector>
using namespace std;
//Coste O(nlog(n))
//n = fin-ini;
//T(n) = k n <= 1
//T(n) = 2T(n/2) + n + k2
using ll = long long int;

ll merge(vector<long long int> & v,const ll ini,const ll m,const ll fin){
	vector<long long int> aux(fin-ini);
	ll in = ini, fn = m, n = 0,i = 0;
	while(in < m && fn < fin){
		if(v[in] <= v[fn]){
			aux[i] = v[in];
			++in;
		}else{
			aux[i] = v[fn];
			n += m - in;
			++fn;
		}

		++i;
	}
	while(in < m){aux[i] = v[in];++in;i++;}
	while(fn < fin){aux[i] = v[fn];++fn;++i;}
	for(int j = ini; j < fin;++j)v[j] = aux[j-ini];

	return n;
}

int res(vector<long long int> &v,ll ini,ll fin){
	if(fin - ini <= 1) return 0;
	else{
		ll m = (fin + ini) / 2;
		long long int n1 = res(v,ini,m);
		long long int n2 = res(v,m,fin);
		long long int n3 = merge(v,ini,m,fin);
		return n1+n2+n3;
	}
}

bool caso(){
	long long int n;
	cin >>n;
	if(!cin) return false;
	vector<long long int> v(n);
	for(ll i = 0; i < n;++i)cin >> v[i];
	cout << res(v,0,v.size())<< "\n" ;

	return true;
}
int main(){
	while(caso());
	return 0;
}


