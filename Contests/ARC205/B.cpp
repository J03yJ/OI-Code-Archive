#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;

int d[N],fa[N],dfn[N],n,m,dcnt;
vector<int> g[N],e[N];
inline void DFS(int x){
	dfn[x]=++dcnt;
	for(int y:g[x]){
		if(y==fa[x]) continue ;
		if(!dfn[y]){
			fa[y]=x;
			DFS(y);
			d[x]^=d[y];
		}else if(dfn[y]<dfn[x]) d[x]^=1,d[y]^1;
	}
}
int vis[N];
inline int Count(int x,int fa){
	vis[x]=1;
	int sum=0,cnt=0;
	for(int y:e[x]){
		if(y==fa) continue ;
		sum+=Count(y,x);
		cnt++;
	}
	sum+=(cnt+!fa)/2;
	return sum;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	for(int i=1;i<=n;i++) if(!dfn[i]) DFS(i);
	for(int i=1;i<=n;i++){
		if(!d[i]&&fa[i]){
			e[fa[i]].push_back(i);
			e[i].push_back(fa[i]);
		}
	}

	int sum=0;
	for(int i=1;i<=n;i++) if(!vis[i]) sum+=Count(i,0);
	
	if(n&1){
		ll ans=1ll*n*(n-1)/2;
		cout<<ans-sum<<endl;
	}else{
		ll ans=1ll*n*(n-1)/2-n/2;
		cout<<ans+sum<<endl;
	}

	return 0;
}