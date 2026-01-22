#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e5+9;

int fi[N],ne[N<<1],to[N<<1],adj=1;
inline void AddEdge(int x,int y){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
}

int f[N<<1],d[N],dfn[N],dcnt,n,m;
inline void DFS(int x,int fa){
	dfn[x]=++dcnt;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa) continue ;
		if(d[y]!=d[x]) continue ;
		if(!dfn[y]) DFS(y,x),f[i]=1;
		else if(dfn[y]<dfn[x]) f[i]=1;
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		AddEdge(u,v);
		AddEdge(v,u);
	}
	for(int i=1;i<=n;i++) cin>>d[i];

	for(int x=1;x<=n;x++){
		if(!dfn[x]) DFS(x,-1);
		for(int i=fi[x];i;i=ne[i]){
			int y=to[i];
			if(d[y]<d[x]) f[i]=1;
		}
	}

	for(int i=1;i<=m;i++) cout<<(f[i<<1]?"->":"<-")<<endl;

	return 0;
}