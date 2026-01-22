#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=3e5+9;
const ll inf=LLONG_MAX;

mt19937 rng(4649);
struct Node{
	int lc,rc;
	ll val;
}tr[N];
inline int Merge(int x,int y){
	if(!x||!y) return x|y;
	if(tr[x].val>tr[y].val) swap(x,y);
	if(rng()&1) swap(tr[x].lc,tr[x].rc);
	tr[x].lc=Merge(tr[x].lc,y);
	return x;
}

int h[N],n;
ll f[N],g[N],w[N],s;
vector<int> e[N];
inline void DFS(int x){
	for(int y:e[x]) DFS(y);
	g[x]=w[x];
	for(int y:e[x]) h[x]=Merge(h[x],y);
	while(h[x]&&g[x]<0){
		int y=h[x];
		h[x]=Merge(tr[y].lc,tr[y].rc);
		if(f[y]==inf) break ;
		f[x]=max(f[x],f[y]-g[x]);
		h[x]=Merge(h[x],h[y]);
		g[x]+=g[y];
	}
	if(g[x]<0) f[x]=inf;
	tr[x].val=f[x];
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>s;
	for(int i=1,fa;i<=n;i++) cin>>w[i]>>fa,e[fa].push_back(i);

	DFS(0);

	ll dlt=0;
	while(h[0]){
		int x=h[0];
		h[0]=Merge(tr[x].lc,tr[x].rc);
		if(s<f[x]) break ;
		h[0]=Merge(h[0],h[x]);
		s+=g[x],dlt+=g[x];
	}

	cout<<dlt<<endl;

	return 0;
}