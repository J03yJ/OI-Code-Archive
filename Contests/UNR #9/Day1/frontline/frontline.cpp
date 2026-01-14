#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e5+9;
const int inf=1e9;
const ll lnf=1e18;

int fi[N],ne[N<<3],to[N<<3],w[N<<3],cst[N<<3],adj=1;
inline void AddEdge(int x,int y,int z,int c){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
	w[adj]=z;
	cst[adj]=c;
}
inline void AddFlow(int x,int y,int z,int c){
	AddEdge(x,y,z,c);
	AddEdge(y,x,0,-c);
}

int inq[N],pre[N],s,t;
ll dis[N];
inline bool SPFA(){
	for(int i=1;i<=t;i++) dis[i]=lnf,inq[i]=pre[i]=0;
	dis[s]=0;
	queue<int> q;
	q.push(s),inq[s]=1;
	while(q.size()){
		int x=q.front();
		q.pop();
		inq[x]=0;
		for(int i=fi[x];i;i=ne[i]){
			int y=to[i];
			if(!w[i]) continue ;
			if(dis[x]+cst[i]<dis[y]){
				dis[y]=dis[x]+cst[i];
				pre[y]=i;
				if(!inq[y]) q.push(y),inq[y]=1;
			}
		}
	}
	return dis[t]!=lnf;
}
inline ll Update(){
	int cur=t,mxf=1;
	while(cur){
		int i=pre[cur];
		w[i]-=mxf;
		w[i^1]+=mxf;
		cur=to[i^1];
	}
	return dis[t];
}

int a[N],b[N],n;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	sort(a+1,a+n+1),sort(b+1,b+n+1);

	s=4*n+1,t=s+1;
	for(int i=1;i<=n;i++){
		AddFlow(s,i,1,0),AddFlow(i+n,t,1,0);
		AddFlow(i+n*2,i+n,inf,-b[i]),AddFlow(i+n*3,i+n,inf,b[i]);
		if(i!=1) AddFlow(i+n*2,i-1+n*2,inf,0);
		if(i!=n) AddFlow(i+n*3,i+1+n*3,inf,0);
		int pos=upper_bound(b+1,b+n+1,a[i])-b;
		if(pos<=n) AddFlow(i,pos+n*3,inf,-a[i]);
		if(pos>1) AddFlow(i,pos-1+n*2,inf,a[i]);
	}

	ll sum=0;
	for(int i=1;i<=n;i++){
		if(SPFA()) sum+=Update();
		cout<<sum<<' ';
	}
	cout<<endl;

	return 0;
}