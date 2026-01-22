#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
using ull=unsigned long long;
const int N=3e5+9;

ull d[N],w[N];
vector<int> e[N];
int u[N],v[N],up[N],fa[N],vis[N],dep[N],n,m;
inline void DFS1(int x){
	vis[x]=1;
	for(int i:e[x]){
		int y=x^u[i]^v[i];
		if(vis[y]) continue ;
		fa[y]=x,up[y]=i;
		dep[y]=dep[x]+1;
		DFS1(y);
	}
}
inline void DFS2(int x){
	for(int i:e[x]){
		int y=x^u[i]^v[i];
		if(fa[y]!=x) continue ;
		DFS2(y);
		d[x]^=d[y];
	}
	w[up[x]]=d[x];
}

mt19937_64 rng(4649);

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i];
		e[u[i]].push_back(i);
		e[v[i]].push_back(i);
	}

	ull s=0;
	DFS1(1);
	for(int i=1;i<=m;i++){
		if(u[i]==fa[v[i]]||v[i]==fa[u[i]]) continue ;
		w[i]=rng();
		d[u[i]]^=w[i];
		d[v[i]]^=w[i];
		cout<<" : "<<i<<' '<<w[i]<<endl;
		if(~(dep[u[i]]+dep[v[i]])&1) s^=w[i];
	}
	DFS2(1);

	if(!s) cout<<1<<endl;
	else{
		ll ans=0;
		map<ull,int> cnt;
		for(int i=1;i<=m;i++){
			if(w[i]==s) ans++;
			else ans+=cnt[s^w[i]];
			cnt[w[i]]++;
		}
		cout<<ans<<endl;
	}

	return 0;
}