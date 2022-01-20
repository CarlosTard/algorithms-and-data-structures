//Carlos Tardon DG231
#include <vector>
#include <queue>
#include <iostream>
#include <vector>
using namespace std;
//cada cadena representa una subcadena de la clave de longitud lon y cuyo ultimo elemento tiene indice ind
struct cadena{
	int ind;
	int lon;
};
//coste: el for externo da n vueltas, y los internos q.size() como maximo.Como en q no hay repetidos, el tamaño maximo es r.
//Por tanto el coste de caso es n*r
bool caso(){
	int r,n;
	cin >> r;
	if(!cin)return false;
	vector<int> c(r);
	for(int i = 0; i < r;++i) cin >> c[i];
	cin >> n;
	queue<cadena> q;
	int mini = n;
	for(int i = 0; i < n;++i){
		int elem; cin >> elem;
		if(elem == c[0]){
			if(q.size() > 0 && q.front().ind == 0) q.pop();
			q.push({0,1});
			//se actualizan las longitudes guardadas
			for(int j = 0; j < q.size() - 1;++j){
				cadena aux = q.front();
				aux.lon++;
				q.pop();
				q.push(aux);
			}
		}else if(q.size() > 0){
			//ok se pone a false cuando ya hemos metido elem en la queue
			bool ok = true;
			for(int j = 0; j < q.size();++j){
				cadena aux = q.front();
				q.pop();
				aux.lon++;
				//si es el ultimo de la clave no se vuelve a guardar
				if(elem == c[r-1] && aux.ind == r-2 && ok){
					ok = false;
					mini = min(mini,aux.lon);
				}else{
					if(c[aux.ind + 1] == elem && ok){
						//si habia otro elemento igual al que queremos actualizar lo sacamos pues tiene una longitud mayor
						if(q.size() > 0 && q.front().ind == aux.ind + 1) q.pop();
						ok = false; aux.ind++;
					}
					q.push(aux);
				}
			}
		}
	}
	cout << mini << "\n";

	return true;
}

int main(){
	while(caso());
}
