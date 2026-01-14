#include<bits/stdc++.h>

using namespace std;

ifstream fin("dining.in");
ofstream fout("dining.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e3+9;
const int M=3e4+9;
const int mod=1e9+9;
const ll inf=1e18;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
	int res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
inline int Inv(int x){return QPow(x,mod-2);}
inline int F(int x){return 1ll*x*x%mod;}

vector<int> dg[N];
vector<array<int,2>> e[N];
int f[N],g[N],h[N],n,m,s,t;

ll dis[N];
int vis[N];
inline void Dij(){
	for(int i=1;i<=n;i++) dis[i]=inf,vis[i]=0;
	dis[s]=0;
	priority_queue<pair<ll,int>> q;
	q.push({0,s});
	while(q.size()){
		int x=q.top().second;
		q.pop();
		if(vis[x]) continue ;
		vis[x]=1;
		for(auto p:e[x]){
			if(dis[x]+p[1]<dis[p[0]]){
				dis[p[0]]=dis[x]+p[1];
				q.push({-dis[p[0]],p[0]});
			}
		}
	}
}

signed main(){
	cin>>n>>m>>s>>t;
	map<array<int,2>,int> mp;
	for(int i=1,u,v,w;i<=m;i++){
		cin>>u>>v>>w;
		if(u==v) continue ;
		if(!mp[{u,v}]) mp[{u,v}]=w;
		else mp[{u,v}]=min(mp[{u,v}],w);
	}
	for(auto p:mp){
		e[p.first[0]].push_back({p.first[1],p.second});
		e[p.first[1]].push_back({p.first[0],p.second});
	}

	Dij();
	for(int i=1;i<=n;i++){
		for(auto p:e[i]){
			if(dis[i]-p[1]==dis[p[0]]) dg[i].push_back(p[0]);
		}
	}

	vector<int> p(n);
	iota(p.begin(),p.end(),1);
	sort(p.begin(),p.end(),[](int i,int j){return dis[i]<dis[j];});
	for(int i=1;i<p.size();i++){
		for(int j=1;j<=n;j++) h[j]=0;
		h[p[i]]=1;
		for(int j=i;~j;j--){
			for(int k:dg[p[j]]) AddAs(h[k],h[p[j]]);
		}
		for(int j:dg[p[i]]) if(j==s) AddAs(g[p[i]],1);
		f[p[i]]=F(h[s]);
		for(int j=1;j<i;j++){
			SubAs(f[p[i]],Mul(Add(g[p[j]],f[p[j]]),F(h[p[j]])));
		}
		SubAs(f[p[i]],g[p[i]]);
	}

	cout<<Add(Mul(f[t],Inv(2)),g[t])<<endl;

	return 0;
}