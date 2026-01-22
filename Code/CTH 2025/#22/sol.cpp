#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e2+9;
const int M=5e2+9;
const int K=5;
const int V=2*N*K;
const int E=2*(2*N+M)*K;
const int inf=INT_MAX;

vector<int> e[N];
int fi[V],ne[E],to[E],w[E],adj=1;
inline void AddEdge(int x,int y,int z){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
	w[adj]=z;
}
inline void AddFlow(int x,int y,int z){
	AddEdge(x,y,z);
	AddEdge(y,x,0);
}

int cur[V],lev[V],s,t,n,m,k;
inline bool GetLevel(){
	for(int i=1;i<=2*n*k;i++) cur[i]=fi[i],lev[i]=0;
	lev[s]=1;
	queue<int> q;
	q.push(s);
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
inline int Work(int x,int k){
	if(x==t) return k;
	int rem=k;
	for(int &i=cur[x];i;i=ne[i]){
		int y=to[i];
		if(!w[i]) continue ;
		if(lev[y]!=lev[x]+1) continue ;
		int tmp=Work(y,min(rem,w[i]));
		w[i]-=tmp,w[i^1]+=tmp,rem-=tmp;
		if(!rem) return k;
	}
	return k-rem;
}
inline int MaxFlow(){
	int ans=0;
	while(GetLevel()) ans+=Work(s,inf);
	return ans;
}

vector<int> edge[N];
int c[N],dis[N],vis[N],st,ed;
inline int Id(int u,int k,int p){return u+(2*(k-1)+p)*n;}
inline void GetDis(){
	queue<int> q;
	q.push(st);
	dis[st]=1,vis[st]=1;
	while(q.size()){
		int x=q.front();
		q.pop();
		for(int y:e[x]){
			if(vis[y]) continue ;
			vis[y]=1;
			dis[y]=dis[x]+1;
			q.push(y);
		}
	}
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m>>k>>st>>ed;
	for(int i=1;i<=n;i++){
		cin>>c[i];
		for(int j=1;j<=k;j++){
			if(j+1<=k) AddFlow(Id(i,j,0),Id(i,j+1,1),inf);
			AddFlow(Id(i,j,0),Id(i,j,1),c[i]);
			edge[i].push_back(adj^1);
		}
	}
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		for(int j=1;j<=k;j++) AddFlow(Id(u,j,1),Id(v,j,0),inf);
		e[u].push_back(v);
	}
	s=Id(st,1,0),t=Id(ed,k,1);

	GetDis();
	if(!vis[ed]) cout<<0<<endl;
	else if(dis[ed]<k) cout<<-1<<endl;
	else{
		MaxFlow();
		vector<int> ans;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=k;j++){
				if(lev[Id(i,j,0)]&&!lev[Id(i,j,1)]){
					ans.push_back(i);
					break ;
				}
			}
		}
		cout<<ans.size()<<endl;
		for(int x:ans) cout<<x<<' ';cout<<endl;
	}

	return 0;
}