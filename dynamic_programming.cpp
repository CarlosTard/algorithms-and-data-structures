 #include <iostream>
 #include <string>
 #include <vector>
 using namespace std;

int trim(vector<vector<int>> & v,string & s,int ini,int fin){
	if(ini >= fin){v[ini][fin] = 1; return 1;}
	else{
		if(v[ini][fin] != -1) return v[ini][fin];
		else{
			int i= ini; int j = fin;
			if(s[ini] == s[fin]){
				++ini;--fin;
				while(ini < s.size() && s[ini] == s[ini-1])++ini;
				while(ini <= fin && s[fin] == s[fin+1])--fin;
				if(ini > fin) v[i][j] = 1;
				else{
					v[i][j] = 1+trim(v,s,ini,fin);
				}
			}else{
				++ini;--fin;
				while(ini < s.size() && s[ini] == s[ini-1])++ini;
				while(ini <= fin && s[fin] == s[fin+1])--fin;
				v[i][j] = 1+ min(trim(v,s,ini,j),trim(v,s,i,fin));
			}
			return v[i][j];
		}
	}
}

bool caso(){
	string s;
	cin >> s;
	if(!cin)return false;

	vector<vector<int>> v(s.size(),vector<int> (s.size(),-1));

	cout << trim(v,s,0,s.size()-1)<< "\n";


	return true;
}

 int main(){
	while(caso());
	return 0;
}
