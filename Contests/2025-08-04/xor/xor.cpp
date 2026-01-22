#include<bits/stdc++.h>

using namespace std;

ifstream fin("xor.in");
ofstream fout("xor.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=4e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
}

int fa[N],hson[N],a[N],tag[N],f[N][2],n;
set<int> s[N];
inline void DFS(int x){
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		fa[y]=x;
		DFS(y);
		if(s[y].size()>s[hson[x]].size()) hson[x]=y;
	}
	bool flag=0;
	swap(s[x],s[hson[x]]);
	tag[x]=tag[hson[x]];
	if(s[x].count(tag[x]^a[x])) flag|=1;
	s[x].insert(tag[x]);
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		if(y==hson[x]) continue ;
		if(f[y][0]==f[y][1]) continue ;
		for(int k:s[y]) if(s[x].count(k^tag[y]^tag[x]^a[x])) flag|=1;
		for(int k:s[y]) s[x].insert(k^tag[y]^tag[x]);
		s[y].clear();
	}
	if(!flag){
		for(int i=fi[x];i;i=ne[i]){
			int y=to[i];
			if(y==fa[x]) continue ;
			f[x][0]+=f[y][0];
		}
		tag[x]^=a[x];
		f[x][1]=f[x][0]+1;
	}else{
		tag[x]=0;
		s[x].clear();
		f[x][1]=1;
		for(int i=fi[x];i;i=ne[i]){
			int y=to[i];
			if(y==fa[x]) continue ;
			f[x][1]+=f[y][0];
		}
		f[x][0]=f[x][1];
	}
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		AddEdge(u,v);
		AddEdge(v,u);
	}

	DFS(1);

	cout<<f[1][0]<<endl;

	return 0;
}