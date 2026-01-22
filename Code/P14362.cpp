#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

using ll=long long;
const int N=1e4+9;
const int M=1e6+9;
const int K=1e1+9;
const int S=(1<<10)+9;

int c[K],a[K][N],n,m,k;
vector<array<int,3>> e[S],o[K],g;

int f[N+K];
inline int Find(int x){return f[x]==x?x:f[x]=Find(f[x]);}
inline void Merge(int x,int y){f[Find(y)]=Find(x);}

inline vector<array<int,3>> Conb(vector<array<int,3>> u,vector<array<int,3>> v){
	vector<array<int,3>> ans;
	ans.reserve(u.size()+v.size());
	reverse(u.begin(),u.end());
	reverse(v.begin(),v.end());
	while(u.size()&&v.size()){
		if(u.back()<v.back()) ans.push_back(u.back()),u.pop_back();
		else ans.push_back(v.back()),v.pop_back();
	}
	while(u.size()) ans.push_back(u.back()),u.pop_back();
	while(v.size()) ans.push_back(v.back()),v.pop_back();
	return ans;
}

signed main(){
	cin>>n>>m>>k;
	for(int i=1,u,v,w;i<=m;i++){
		cin>>u>>v>>w;
		g.push_back({w,u,v});
	}
	for(int i=1;i<=k;i++){
		cin>>c[i];
		for(int j=1;j<=n;j++) cin>>a[i][j],o[i].push_back({a[i][j],n+i,j});
		sort(o[i].begin(),o[i].end());
	}

	sort(g.begin(),g.end());
	for(int i=1;i<=n+k;i++) f[i]=i;
	for(auto t:g){
		if(Find(t[1])==Find(t[2])) continue ;
		Merge(t[1],t[2]);
		e[0].push_back(t);
	}

	for(int sta=1;sta<(1<<k);sta++){
		int p=__lg(sta&-sta)+1;
		vector<array<int,3>> tmp=Conb(e[sta^(1<<p-1)],o[p]);
		for(int i=1;i<=n+k;i++) f[i]=i;
		for(auto t:tmp){
			if(Find(t[1])==Find(t[2])) continue ;
			Merge(t[1],t[2]);
			e[sta].push_back(t);
		}
	}

	ll ans=1e18;
	for(int sta=0;sta<(1<<k);sta++){
		ll res=0;
		for(int i=1;i<=k;i++) if(sta>>i-1&1) res+=c[i];
		for(auto t:e[sta]) res+=t[0];
		ans=min(ans,res);
	}

	cout<<ans<<endl;

	return 0;
}