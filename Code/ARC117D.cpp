#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
}

int dis[N],n;
inline void GetDis(int x,int fa){
	if(!fa) dis[x]=0;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa) continue;
		dis[y]=dis[x]+1;
		GetDis(y,x);
	}
}
int fa[N],dep[N],mxdep[N],hson[N];
inline void GetHSon(int x){
	mxdep[x]=dep[x];
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		fa[y]=x;
		dep[y]=dep[x]+1;
		GetHSon(y);
		mxdep[x]=max(mxdep[x],mxdep[y]);
		if(!hson[x]||mxdep[y]>mxdep[hson[x]]) hson[x]=y;
	}
}
int pos[N],ecnt;
inline void GetEuler(int x){
	pos[x]=++ecnt;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		if(y==hson[x]) continue ;
		GetEuler(y),ecnt++;
	}
	if(hson[x]) GetEuler(hson[x]),ecnt++;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int n;
	cin>>n;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		AddEdge(u,v);
		AddEdge(v,u);
	}

	GetDis(1,0);
	int p=max_element(dis+1,dis+n+1)-dis;
	GetHSon(p);
	GetEuler(p);

	for(int i=1;i<=n;i++) cout<<pos[i]<<' ';cout<<endl;
	
	return 0;
}