#include<bits/stdc++.h>

using namespace std;

ifstream fin("energy.in");
ofstream fout("energy.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;

vector<array<int,4>> g;
int fa[N],n,m,d;
inline void Init(){iota(fa+1,fa+n+1,1);}
inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){fa[Find(y)]=Find(x);}
inline int Solve(){
	Init();
	int wmx=0,tot=0;
	vector<array<int,4>> tmp;
	for(auto e:g){
		if(Find(e[2])==Find(e[3])) continue ;
		Merge(e[2],e[3]);
		tot+=e[1];
		wmx=e[0];
		tmp.push_back(e);
	}

	if(wmx>d) return tot;

	Init();
	for(auto e:tmp){
		if(e[0]==wmx&&e[1]) continue ;
		Merge(e[2],e[3]);
	}
	for(auto e:g){
		if(e[0]>d) break ;
		if(e[1]) continue ;
		if(Find(e[2])==Find(e[3])) continue ;
		return tot-1;
	}
	return tot;
}

signed main(){
	cin>>n>>m>>d;
	for(int i=1,u,v,w;i<=m;i++){
		cin>>u>>v>>w;
		g.push_back({w,!(i<n),u,v});
	}
	sort(g.begin(),g.end());

	cout<<Solve()<<endl;

	return 0;
}