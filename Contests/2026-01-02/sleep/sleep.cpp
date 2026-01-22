#include<bits/stdc++.h>

using namespace std;

ifstream fin("sleep.in");
ofstream fout("sleep.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e2+9;
const int M=5e2+9;
const int C=1e5+9;
const ll inf=1e18;
const int dlt=1e9;

map<int,int> id[N];
int a[N],b[N],c[N],d[N],L[N],R[N],p[M],q[M],D[M],n,m;
inline ll F(int i,ll x){return a[i]*x*x*x+b[i]*x*x+c[i]*x+d[i];}

ll w[C];
int fi[C],ne[C],to[C],adj=1;
inline void AddEdge(int x,int y,ll z){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
	w[adj]=z;
}
inline void AddFlow(int x,int y,ll z){AddEdge(x,y,z),AddEdge(y,x,0);}

int lev[C],cur[C],s,t,tot;
inline void Clear(){
	for(int i=1;i<=tot;i++) fi[i]=0;
	for(int i=1;i<=n;i++) id[i].clear();
	adj=1,tot=0;
}
inline bool BFS(){
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
inline ll DFS(int x,ll k){
	if(x==t) return k;
	ll rem=k;
	for(int &i=cur[x];i;i=ne[i]){
		int y=to[i];
		if(!w[i]) continue ;
		if(lev[y]!=lev[x]+1) continue ;
		ll tmp=DFS(y,min(rem,w[i]));
		rem-=tmp;
		w[i]-=tmp;
		w[i^1]+=tmp;
		if(!rem) return k;
	}
	return k-rem;
}
inline ll MaxFlow(){
	ll sum=0;
	while(BFS()&&sum<inf) sum+=DFS(s,inf);
	return sum;
}

inline void Solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i]>>c[i]>>d[i]>>L[i]>>R[i];
	for(int i=1;i<=m;i++) cin>>p[i]>>q[i]>>D[i];

	s=++tot,t=++tot;
	for(int i=1;i<=n;i++){
		for(int j=L[i];j<=R[i];j++) id[i][j]=++tot;
		AddFlow(s,id[i][L[i]],inf);
		for(int j=L[i]+1;j<=R[i];j++) AddFlow(id[i][j-1],id[i][j],dlt-F(i,j-1));
		AddFlow(id[i][R[i]],t,dlt-F(i,R[i]));
	}
	for(int i=1;i<=m;i++){
		for(int j=L[p[i]];j<=R[p[i]];j++){
			if(!id[q[i]].count(j-D[i])){
				if(j-D[i]>R[q[i]]) AddFlow(id[p[i]][j],t,inf);
			}else AddFlow(id[p[i]][j],id[q[i]][j-D[i]],inf);
		}
	}

	ll ans=MaxFlow();

	if(ans<inf) cout<<1ll*dlt*n-ans<<endl;
	else cout<<"mei ji ge"<<endl;

	Clear();
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}