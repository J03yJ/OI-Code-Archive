#include<bits/stdc++.h>

using namespace std;

ifstream fin("portal.in");
ofstream fout("portal.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;
const ll inf=1e18;

int n,m,s,t,l;
ll k;

struct Graph{
	int fi[N],ne[N<<1],to[N<<1],w[N<<1],adj;
	inline void AddEdge(int x,int y,int z){
		ne[++adj]=fi[x];
		fi[x]=adj;
		to[adj]=y;
		w[adj]=z;
	}

	ll dis[N];
	int vis[N];
	inline void Dij(int s){
		for(int i=1;i<=n;i++) dis[i]=inf,vis[i]=0;
		priority_queue<pair<ll,int>> q;
		q.push({dis[s]=0,s});
		while(q.size()){
			int x=q.top().second;
			q.pop();
			if(vis[x]) continue ;
			vis[x]=1;
			for(int i=fi[x];i;i=ne[i]){
				int y=to[i];
				if(dis[x]+w[i]<dis[y]){
					dis[y]=dis[x]+w[i];
					q.push({-dis[y],y});
				}
			}
		}
	}
}g,r;

signed main(){
	cin>>n>>m>>s>>t>>l>>k;
	for(int i=1,u,v,w;i<=m;i++){
		cin>>u>>v>>w;
		g.AddEdge(u,v,w);
		g.AddEdge(v,u,w);
		r.AddEdge(u,v,w);
		r.AddEdge(v,u,w);
	}

	g.Dij(s),r.Dij(t);

	if(g.dis[t]<=k){
		cout<<1ll*n*(n-1)/2<<endl;
		return 0;
	}

	ll cnt=0;
	vector<ll> v(r.dis+1,r.dis+n+1);
	sort(v.begin(),v.end());
	for(int i=1;i<=n;i++) cnt+=upper_bound(v.begin(),v.end(),k-l-g.dis[i])-v.begin();

	cout<<cnt<<endl;

	return 0;
}