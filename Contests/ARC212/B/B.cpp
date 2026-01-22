#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;

int n,m;

int fi[N],ne[N<<1],to[N<<1],w[N<<1],adj=1;
inline void AddEdge(int x,int y,int z){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
	w[adj]=z;
}

int vis[N],p[N],s,os,b;
ll dis[N],ans=LLONG_MAX;
inline void Dij(){
	for(int i=1;i<=n;i++) vis[i]=0,dis[i]=1e18;
	priority_queue<pair<ll,int>> q;
	q.push({dis[s]=0,s});
	while(q.size()){
		int x=q.top().second;
		q.pop();
		if(vis[x]) continue ;
		vis[x]=s;
		for(int i=fi[x];i;i=ne[i]){
			int y=to[i];
			if(dis[x]+w[i]<dis[y]){
				p[y]=i;
				dis[y]=dis[x]+w[i];
				q.push({-dis[y],y});
			}
		}
	}
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	for(int i=1,u,v,w;i<=m;i++){
		cin>>u>>v>>w;
		AddEdge(u,v,w);
		if(i==1){
			b=w;
			os=u,s=v;
		}
	}

	if(s==os){
		cout<<b<<endl;
		return 0;
	}

	Dij();
	ans=dis[os]+b;

	if(ans>=1e18/2) cout<<-1<<endl;
	else cout<<ans<<endl;

	return 0;
}