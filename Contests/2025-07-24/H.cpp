#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e5+9;
const int K=2e1+9;
const ll inf=1e18;

vector<int> e[N];
int fa[N],n,k;
ll w[N],siz[N];
inline void Direct(int x){
	siz[x]=w[x];
	for(int y:e[x]){
		if(fa[x]==y) continue ;
		fa[y]=x;
		Direct(y);
		siz[x]+=siz[y];
	}
}
inline void Init(){
	for(int i=1;i<=n;i++){
		sort(e[i].begin(),e[i].end(),[](int x,int y){return siz[x]>siz[y];});
		if(i>1) e[i].erase(e[i].begin());
	}
}
inline void Clear(){
	for(int i=1;i<=n;i++){
		fa[i]=siz[i]=w[i]=0;
		e[i].clear();
	}
}

inline ll DFS(int x,bool &flag,ll lim){
	ll res=1;
	if(siz[x]<=lim) res|=1<<1;
	vector<int> p(k+1,0);
	for(int y:e[x]){
		ll tmp=DFS(y,flag,lim);
		if(siz[x]-siz[y]<=lim){
			for(int i=1;i<k;i++) if(tmp>>i&1) res|=1<<i+1;
		}
		if((tmp>>k&1)){
			if(siz[1]-siz[y]<=lim) flag|=1;
		}
		for(int i=1;i<k;i++){
			if(~tmp>>i&1) continue ;
			if(!p[k-i]) continue ;
			if(siz[1]-siz[y]-siz[p[k-i]]<=lim) flag|=1;
		}
		for(int i=1;i<k;i++) if((tmp>>i&1)&&!p[i]) p[i]=y;
	}
	return res;
}
inline bool Check(ll lim){
	bool flag=0;
	DFS(1,flag,lim);
	return flag;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>w[i];
		for(int i=1,u,v;i<n;i++){
			cin>>u>>v;
			e[u].push_back(v);
			e[v].push_back(u);
		}
		Direct(1);
		Init();

		ll l=-1,r=inf;
		while(l+1<r){
			ll mid=l+r>>1;
			if(Check(mid)) r=mid;
			else l=mid;
		}

		cout<<r<<endl;

		Clear();
	}

	return 0;
}