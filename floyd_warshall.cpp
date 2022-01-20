//Carlos Tardón Rubio
/*

 * grad(i,j,k) = minimo de relaciones hay que atravesar para conectar
 * 				i con j usando como vertices intermedios 1..k
 * Caso base:
 * 	grad(i,j,0) = 0 i = j
 * 	grad(i,j,0) = grad[i][j] i!=j donde grad[i][j] es la matriz de adyacencia
 * Recursión: 
 *  grad(i,j) = min(grad(i,j,k-1,grad(i,k,k-1) + grad(k,j,k-1));
 * 
 * 	1<=i,j,k<=n
 * 
 */
#include "bits/stdc++.h"
using namespace std;
int grado(vector<vector<int>> & grad){
	//coste: tiempo O(n^3) espacio O(1)
	int n = grad.size() - 1;
	for(int i = 1;i <=n;++i) grad[i][i] = 0;
	for(int k = 1; k<= n;++k){
		for(int i = 1; i <= n;++i){
			for(int j = 1;j <= n;++j){
				if(grad[i][k] < INT_MAX && grad[k][j] < INT_MAX)
					grad[i][j] = min(grad[i][j], grad[i][k] + grad[k][j] );
			}
		}
	}
	int maxGrado = grad[1][1];
	for(int i = 1; i <= n;++i){
		for(int j = 1;j <= n;++j){
			maxGrado = max(maxGrado,grad[i][j]);
		}
	}
	return maxGrado;
}

bool caso(){
	int n, r;
	cin >> n >> r;
	if(!cin) return false;
	int k = 1;//maxima persona encontrada;
	unordered_map<string,int> m;
	vector<vector<int> > grad(n+1,vector<int> (n+1,INT_MAX));
	for(int i = 0; i < r;++i){
		string a,b;
		cin >> a >> b;
		if(m[a] == 0){
			m[a] = k;
			++k;
		}
		if(m[b] == 0){
			m[b] = k;
			++k;
		}
		grad[m[a]][m[b]] = 1;
		grad[m[b]][m[a]] = 1;
	}
	int maxGrado = grado(grad);
	if(maxGrado == INT_MAX)
		cout<< "DESCONECTADA\n";
	else cout << maxGrado <<"\n";
	
	return true;
}

int main(){

	while(caso());
}
