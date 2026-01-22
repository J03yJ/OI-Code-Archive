#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e3+9;
const int Q=1e6+9;
const int V=(1<<12)+9;

char op[Q];
int u[Q],v[Q],w[Q],n,q;
vector<int> e[V],g[V],o[Q];
struct DSU{
	int fa[N];
	inline void Init(int lim){iota(fa+1,fa+lim+1,1);}
	inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
	inline void Merge(int x,int y){fa[Find(y)]=Find(x);}
	inline bool Con(int x,int y){return Find(x)==Find(y);}
}d[V];

inline void Solve(){
	cin>>n>>q;
	for(int i=1;i<=q;i++){
		cin>>op[i]>>u[i]>>v[i];
		if(op[i]=='+') cin>>w[i],g[w[i]].push_back(i);
	}

	for(int sta=(1<<12)-1;~sta;sta--){
		for(int i=0;i<12;i++){
			if(sta>>i&1) continue ;
			int tta=sta|(1<<i);
			g[sta].insert(g[sta].begin(),e[tta].begin(),e[tta].end());
		}
		d[sta].Init(n);
		sort(g[sta].begin(),g[sta].end());
		for(int i:g[sta]){
			if(d[sta].Con(u[i],v[i])) continue ;
			d[sta].Merge(u[i],v[i]);
			o[i].push_back(sta);
			e[sta].push_back(i);
		}
		d[sta].Init(n);
	}

	ll sum=0;
	for(int i=1;i<=q;i++){
		if(op[i]=='+'){
			for(int j:o[i]) d[j].Merge(u[i],v[i]);
		}else{
			int ans=0;
			for(int j=11;~j;j--){
				if(d[ans|(1<<j)].Con(u[i],v[i])) ans|=1<<j;
			}
			if(!d[0].Con(u[i],v[i])) ans=-1;
			sum+=ans;
		}
	}
	cout<<sum<<endl;

	for(int i=0;i<(1<<12);i++) e[i].clear(),g[i].clear(),d[i].Init(n);
	for(int i=1;i<=q;i++) o[i].clear();
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}