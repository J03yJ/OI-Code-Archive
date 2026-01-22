#include<bits/stdc++.h>

using namespace std;

ifstream fin("drop.in");
ofstream fout("drop.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e6+9;

vector<int> e[N];
inline int SG(int x,int fa,int dep,int lim){
	if(dep==lim) return 0;
	vector<int> tmp;
	for(int y:e[x]){
		if(y==fa) continue ;
		tmp.push_back(SG(y,x,dep+1,lim));
	}
	sort(tmp.begin(),tmp.end());
	int t=tmp.size();
	tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
	if(tmp.size()==t&&(tmp.empty()||tmp.front()!=0)) return 0;
	if(tmp.size()&&tmp.front()==0) tmp.erase(tmp.begin());
	for(int i=1;i<=tmp.size();i++) if(tmp[i-1]>i) return i;
	return tmp.size()+1;
}

int n,q;

signed main(){
	cin>>n>>q;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	while(q--){
		int x,d;
		cin>>x>>d;
		if(SG(x,-1,0,d)) cout<<"TAK"<<endl;
		else cout<<"NIE"<<endl;
	}

	return 0;
}