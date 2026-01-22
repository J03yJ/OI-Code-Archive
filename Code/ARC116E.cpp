#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
}

int dis[N][2],imp[N],n,k;
inline void DFS(int x,int fa,int p){
	dis[x][1]=1e9;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa) continue ;
		DFS(y,x,p);
		dis[x][1]=min(dis[x][1],dis[y][1]+1);
	}
	if(dis[x][1]>p) dis[x][0]=0;
	else dis[x][0]=-1e9;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa) continue ;
		if(dis[y][0]+1+dis[x][1]>p) dis[x][0]=max(dis[x][0],dis[y][0]+1);
		// cout<<x<<" <- "<<y<<endl;
	}
	if(dis[x][0]==p||dis[x][0]>=0&&!~fa) imp[x]=1,dis[x][0]=-1e9,dis[x][1]=0;
	// cout<<x<<' '<<p<<" : "<<dis[x][0]<<' '<<dis[x][1]<<endl;
}
inline bool Check(int d){
	fill(imp+1,imp+n+1,0);
	DFS(1,-1,d);
	// cout<<d<<" : ";for(int i=1;i<=n;i++) cout<<imp[i]<<' ';cout<<endl;
	return accumulate(imp+1,imp+n+1,0)<=k;
}

signed main(){
	cin>>n>>k;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		AddEdge(u,v);
		AddEdge(v,u);
	}

	int l=0,r=n+1;
	while(l+1<r){
		int mid=l+r>>1;
		if(Check(mid)) r=mid;
		else l=mid;
	}

	cout<<r<<endl;

	return 0;
}