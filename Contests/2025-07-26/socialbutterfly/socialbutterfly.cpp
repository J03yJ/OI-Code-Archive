#include<bits/stdc++.h>

using namespace std;

ifstream fin("socialbutterfly.in");
ofstream fout("socialbutterfly.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e4+9;
const int inf=1e9;

int fi[N],ne[N<<2],to[N<<2],w[N<<2],adj=1;
inline void AddEdge(int x,int y,int z){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
	w[adj]=z;
}
inline int AddFlow(int x,int y,int z){
	AddEdge(x,y,z);
	AddEdge(y,x,0);
	return adj^1;
}

int lev[N],cur[N],s,t,tot;
inline bool BFS(int s,int t){
	for(int i=1;i<=tot;i++) lev[i]=0,cur[i]=fi[i];
	queue<int> q;
	q.push(s);
	lev[s]=1;
	while(q.size()){
		int x=q.front();
		q.pop();
		if(x==t) return 1;
		for(int i=fi[x];i;i=ne[i]){
			int y=to[i];
			if(!w[i]) continue ;
			if(lev[y]) continue ;
			lev[y]=lev[x]+1;
			q.push(y);
		}
	}
	return 0;
}
inline int DFS(int x,int c,int t){
	if(x==t) return c;
	int k=c;
	for(int &i=cur[x];i;i=ne[i]){
		int y=to[i];
		if(!w[i]) continue ;
		if(lev[y]!=lev[x]+1) continue ;
		int tmp=DFS(y,min(k,w[i]),t);
		k-=tmp;
		w[i]-=tmp;
		w[i^1]+=tmp;
		if(!k) return c;
	}
	return c-k;
}
inline int MaxFlow(int s,int t){
	int sum=0;
	while(BFS(s,t)) sum+=DFS(s,inf,t);
	return sum;
}

int u[N],v[N],e[N],n,m,lim;

signed main(){
	cin>>n>>m>>lim;
	for(int i=1;i<=m;i++) cin>>u[i]>>v[i];

	s=n+m+1,tot=t=s+1;
	for(int i=1;i<=n;i++) e[i]=AddFlow(i,t,lim);
	for(int i=1;i<=m;i++){
		AddFlow(s,i+n,1);
		AddFlow(i+n,u[i],inf);
		AddFlow(i+n,v[i],inf);
	}

	int sum=m-MaxFlow(s,t),flag=0;
	for(int i=1;i<=n;i++){
		sum+=MaxFlow(i,s);
		w[e[i]]=w[e[i]^1]=0;
		sum-=MaxFlow(s,t);
		w[e[i]]=lim;
		flag|=(sum>0);
	}

	if(flag) cout<<"Yes"<<endl;
	else cout<<"No"<<endl;

	return 0;
}