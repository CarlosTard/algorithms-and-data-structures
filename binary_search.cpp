//Carlos Tardon Rubio
#include "01.h"
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>

horas::horas(): h(0),min(0),sec(0){}

horas::horas(int hor,int m,int s): h(hor), min(m), sec(s){
	if(hor < 0 || hor >=24 || min < 0 || min >= 60
	|| sec < 0 || sec >= 60) throw domain_error("ERROR");

}

bool horas::operator<(const horas & h1) const{
	return h < h1.h || h == h1.h && min < h1.min
			|| h == h1.h && min == h1.min && sec < h1.sec;

}
string horas::toString() const{
	stringstream ss;
	ss << setfill('0') << setw(2) << h << ':';
	ss << setfill('0') << setw(2) << min << ':';
	ss << setfill('0') << setw(2) << sec ;
	return ss.str();
}

ostream & operator<<(ostream & out,const horas& h){
	out << h.toString() <<'\n';
	return out;
}

istream & operator>>(istream & in,horas * h){
	int ho,mi,se;
	char c;
	in >> ho >> c >> mi >> c >> se;
	horas hor(ho,mi,se);
	*h = hor;
	return in;

}
void binary_search(vector<horas> & v,const horas & h,int ini,int fin,int & pos){
	if(ini == fin) pos = ini;
	else{
		int m = (ini +fin -1)/2;
		if(v[m] < h) return binary_search(v,h,m+1,fin,pos);
		else if(h < v[m]) return binary_search(v,h,ini,m,pos);
		else pos = m;
	}
}

bool caso(){
	int t,h;
	cin >> t >> h;
	if(t== 0 && h == 0)return false;
	vector<horas> v(t);
	for(int i = 0; i < t;++i) cin >> &v[i];
	for(int i = 0; i < h; ++i){
		horas hor;
		try{
			cin >> &hor;
			int pos;
			binary_search(v,hor,0,t,pos);
			if(pos == t) cout << "NO\n";
			else cout << v[pos];
		}catch(domain_error const& de){
			cout << "ERROR\n";
		}
	}

	cout << "---\n";
	return true;
}


int main(){
	while(caso());
}
