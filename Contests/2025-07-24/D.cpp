#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;
const ll inf=1e18;
const double eps=1e-8;

int fi[N],ne[N<<1],to[N<<1],w[N<<1],adj;
inline void AddEdge(int x,int y,int z){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
	w[adj]=z;
}

double dis[N];
int cnt[N],vis[N],n,m,k;
inline void Dijkstra(double k){
	cout<<k<<" : "<<endl;
	for(int i=1;i<=n;i++) dis[i]=inf,cnt[i]=vis[i]=0;
	dis[1]=0;
	priority_queue<pair<double,int>> q;
	q.push({-dis[1],1});
	while(q.size()){
		int x=q.top().second;
		q.pop();
		if(vis[x]) continue ;
		vis[x]=1;
		for(int i=fi[x];i;i=ne[i]){
			int y=to[i];
			if(dis[x]+w[i]+k<dis[y]){
				dis[y]=dis[x]+w[i]+k;
				cnt[y]=cnt[x]+1;
				cout<<x<<" -> "<<y<<' '<<dis[y]<<endl;
				q.push({-dis[y],y});
			}
		}
	}
}
inline bool Check(double x){
	Dijkstra(x);
	return cnt[n]<=x;
}
inline void Clear(){
	for(int i=1;i<=n;i++) fi[i]=0;
	adj=0;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n>>m>>k;
		for(int i=1;i<=m;i++){
			int u,v,w;
			cin>>u>>v>>w;
			AddEdge(u,v,w);
		}

		double l=-1e11,r=1e11;
		while(l+eps<r){
			double mid=(l+r)/2;
			if(Check(mid)) r=mid;
			else l=mid;
		}

		Check(l);
		cout<<cnt[n]<<' '<<dis[n]<<' '<<l<<endl;
		cout<<round(dis[n]-cnt[n]*l)<<endl;

		Clear();
	}

	return 0;
}