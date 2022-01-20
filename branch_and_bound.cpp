//Carlos Tardón Rubio
/*
 * Representación de la solución: tuplas de la forma (x0, , xn-1),
 * tal que xi es el supermercado donde compramos el producto i 
 * 
 * Restricciones: 0<=i<n 0<=xi<m, y cada supermercado aparece como mucho 3 veces
 * en la tupla. Para cumplir con esta ultima restriccion, en cada nodo llevamos
 * un vector de marcas de tamaño m, siendo marc[i] el numero de productos que hemos
 * comprado en el supermercado i 0<= marc[i] <=3
 * 
 * Utilizaré el esquema optimista-pesimista, pues siempre podemos extender a una
 * posible solución, ya que se garantiza n<=3m. Daré una version constante para la cota
 * optimista y una version constante y otra lineal O(n+m) = O(m) para la pesimista
 * 
 * Cota optimista constante: precalculamos el minimo coste de cada producto, y la cota
 *      es el coste ya acumulado mas la suma de los minimos de los productos k+1...n-1 
 *      Estas sumas se precalculan y se guardan en un vector de sumas parciales
 * 
 * Cota pesimista constante: precalculamos el maximo coste de cada producto, y la cota
 *      es el coste ya acumulado mas la suma de los maximos de los productos k+1...n-1 
 *      Estas sumas se precalculan y se guardan en un vector de sumas parciales 
 * 
 * Cota pesimista lineal: se trata de extender a una solucion. Para ello, compramos
 *      productos en un orden cualquiera en los supermercados donde hayamos comprado 
 *      menos de tres productos.
 * 
 */
#include "bits/stdc++.h"
using namespace std;
struct nodo{
    int k;
    vector<int> sol;
    vector<int> mark;
    int cost; 
    int costprior; 
};

bool operator<(nodo const& n1,nodo const& n2){
    return n1.costprior > n2.costprior;
}

int cotaPesLineal(vector<vector<int>> const& mat,int n,int m,int k,vector<int> mark,int cost){
    //coste O(n+m) tiempo O(m) espacio. Importante pasar mark por copia porque se va a modificar
    int pes = cost;
    int i = k;//indice recorre los productos
    int j = 0;//recorre los supermercados
    
    while(i < n && j < m){
        if(mark[j] == 3)
            ++j;
        else{
            mark[j]++;
            pes += mat[i][j];
            ++i;
        }
    }
    return pes;
}

void precalCotas(vector<vector<int>> const& mat,int n,int m,vector<int> &opt,vector<int> &pes){
    for (int i = 0; i < n; ++i){
        opt[i] = pes[i] = mat[i][0];
		for( int j = 0; j < m;++j){
            opt[i] = min(opt[i],mat[i][j]);
            pes[i] = max(pes[i],mat[i][j]);
        }
	}
    for(int i = n-1; i >= 0;--i){
        opt[i] += opt[i+1];
        pes[i] += pes[i+1];
    }
}
int RyP(vector<vector<int>> const& mat,int n,int m){
    priority_queue<nodo> pq;
    nodo n1; n1.k = 0;
    vector<int> opt(n+1);
    vector<int> pes(n+1);
    precalCotas(mat,n,m,opt,pes);
    n1.sol = vector<int>(n);
    n1.mark = vector<int>(m,0);
    n1.cost = 0; 
    n1.costprior = opt[0];
    pq.push(n1);
    int mejor = cotaPesLineal(mat,n,m,0,n1.mark,0);
    vector<int> solMejor = n1.sol;
    while(!pq.empty() && mejor >= pq.top().costprior){
        nodo padre = pq.top(); pq.pop();
        nodo hijo; hijo.k = padre.k + 1;hijo.sol = padre.sol;hijo.mark = padre.mark;
        hijo.cost = padre.cost;
        for(int j = 0; j < m;++j){
            if (hijo.mark[j] < 3){
                hijo.mark[j]++;
                hijo.sol[hijo.k-1] = j;
                hijo.cost += mat[hijo.k-1][j];
                hijo.costprior = hijo.cost + opt[hijo.k];
                if(hijo.costprior <= mejor){
                    if(hijo.k == n){
                        mejor = hijo.cost;
                        solMejor = hijo.sol;
                    }else{
                        pq.push(hijo);
                        mejor = min(mejor,hijo.cost + pes[hijo.k]);
                    }
                }
                hijo.cost -= mat[hijo.k-1][j];
                hijo.mark[j]--;
            }
        }
    }
    return mejor;
}

bool caso(){
	int n, m;
	cin >> n >> m;
	if(n == 0) return false;
	
	vector<vector<int>> mat(n,vector<int>(m));
	for (int i = 0; i < n; ++i){
		for( int j = 0; j < m;++j) cin >> mat[i][j];
	}
    cout << RyP(mat,n,m) << "\n";
	return true;
}

int main(){

	while(caso());
}
