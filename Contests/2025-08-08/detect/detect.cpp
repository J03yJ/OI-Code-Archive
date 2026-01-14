#include<bits/stdc++.h>

using namespace std;

ifstream fin("detect.in");
ofstream fout("detect.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e3+9;
const int lgN=2e1;

int deg[N],t[N],idom[N],fa[N][lgN],dep[N],s[N],n,m,d,tcnt;
vector<int> fg[N],bg[N];
inline int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int k=lgN-1;~k;k--) if(dep[fa[x][k]]>=dep[y]) x=fa[x][k];
	if(x==y) return x;
	for(int k=lgN-1;~k;k--) if(fa[x][k]!=fa[y][k]) x=fa[x][k],y=fa[y][k];
	return fa[x][0];
}

bitset<N> b[N];

signed main(){
	cin>>n>>m>>d;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		fg[u].push_back(v);
		bg[v].push_back(u);
		deg[v]++;
	}
	for(int i=1,u;i<=d;i++) cin>>u,s[u]=1;

	dep[n+1]=1;
	idom[n+1]=n+1;
	for(int i=1;i<=n;i++){
		if(!deg[i]){
			fg[n+1].push_back(i);
			bg[i].push_back(n+1);
			deg[i]++;
			b[i].set(i);
		}
	}
	queue<int> q;
	q.push(n+1);
	while(q.size()){
		int x=q.front();
		q.pop();
		t[++tcnt]=x;
		for(int y:fg[x]){
			deg[y]--;
			if(!deg[y]) q.push(y);
		}
	}

	for(int i=2;i<=tcnt;i++){
		int x=t[i];
		idom[x]=bg[x].front();
		for(int y:bg[x]) idom[x]=LCA(idom[x],y),b[x]|=b[y];
		dep[x]=dep[idom[x]]+1;
		fa[x][0]=idom[x];
		for(int k=1;k<lgN;k++) fa[x][k]=fa[fa[x][k-1]][k-1];
	}
	for(int i=1;i<=tcnt;i++){
		int x=t[i];
		if(!s[x]) continue ;
		if(s[x]==1) s[idom[x]]=-1;
	}
	for(int i=1;i<=n;i++){
		if(!s[i]) continue ;
		for(int j=1;j<=n;j++){
			if(s[j]) continue;
			if((b[i]&b[j])==b[i]) s[j]=-1;
		}
	}
	for(int i=2;i<=tcnt;i++){
		int x=t[i];
		if(!s[x]) continue ;
		for(int y:fg[x]) s[y]=-1;
	}

	for(int i=1;i<=n;i++) if(s[i]) cout<<i<<' ';
	cout<<endl;

	return 0;
}