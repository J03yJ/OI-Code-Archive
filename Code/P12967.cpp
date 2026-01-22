#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
using ull=unsigned long long;
const int N=5e5+9;
const ll inf=1e18;

const ull A=7;
const ull B=998244353;
const ull C=114514191981000001;
inline ull XorShift(ull x){return x^(x<<7)^(x>>13);}

ull f[N];
ll sum[N];
map<ull,int> cnt;
vector<int> e[N];
int fa[N],dep[N],siz[N],hson[N],n,m;
inline void GetHash(int x){
	f[x]=B;
	siz[x]=1;
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		dep[y]=dep[x]+1;
		GetHash(y);
		f[x]+=A*XorShift(f[y]);
		siz[x]+=siz[y];
		sum[x]+=sum[y];
		if(!hson[x]||siz[y]>siz[hson[x]]) hson[x]=y;
	}
	f[x]%=C;
	cnt[f[x]]++;
	sum[x]+=siz[x];
}

ll mndep[N];
set<ull> res;
map<ull,array<ll,2>> c[N];
inline void Solve(int x){
	mndep[x]=-inf;
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		Solve(y);
		mndep[x]=max(mndep[x],mndep[y]);
	}
	swap(c[x],c[hson[x]]);
	auto Insert=[&x](ull key,array<ll,2> val){
		c[x][key][0]+=val[0];
		c[x][key][1]+=val[1];
		val=c[x][key];
		mndep[x]=max(mndep[x],(val[1]-cnt[key]+val[0]-1)/val[0]);
	};
	Insert(f[x],{1,dep[x]});
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		if(y==hson[x]) continue ;
		for(auto p:c[y]) Insert(p.first,p.second);
	}
	if(dep[x]>mndep[x]&&m+sum[x]==n) res.insert(f[x]);
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>m;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	GetHash(1);
	Solve(1);

	cout<<res.size()<<endl;

	return 0;
}