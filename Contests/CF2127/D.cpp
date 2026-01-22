#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;
const int mod=1e9+7;

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
#define Inv(x) QPow(x,mod-2)

int fac[N],ifac[N];
inline void Init(int lim){
	fac[0]=1;
	for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
	ifac[lim]=Inv(fac[lim]);
	for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}
inline int C(int n,int m){
	if(m<0||m>n) return 0;
	else return Mul(fac[n],Mul(ifac[m],ifac[n-m]));
}

vector<int> e[N],g[N];
int vis[N],col[N],d[N],c[N],n,m;
inline void DFS(int x,vector<int> &p,int &err){
	vis[x]=1;
	p.push_back(x);
	for(int y:e[x]){
		if(!vis[y]){
			col[y]=!col[x];
			DFS(y,p,err);
		}else if(col[y]==col[x]) err|=1;
	}

}

inline void Clear(){
	for(int i=1;i<=n;i++){
		vis[i]=col[i]=d[i]=c[i]=0;
		e[i].clear();
		g[i].clear();
	}
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1,u,v;i<=m;i++){
			cin>>u>>v;
			e[u].push_back(v);
			e[v].push_back(u);
			d[u]++,d[v]++;
		}

		Init(n);
		int ans=1,err=0;
		for(int i=1;i<=n;i++){
			if(vis[i]) continue ;
			vector<int> node;
			DFS(1,node,err);
			vector<int> p[2];
			for(int u:node) p[col[u]].push_back(u);

			bool flag=0;
			for(int k:{0,1}){
				for(int u:p[k]){
					int cnt=0;
					vector<int> p;
					for(int v:e[u]) if(d[v]>1) cnt++,p.push_back(v);
					if(cnt>2) err|=1;
					else MulAs(ans,fac[d[u]-cnt]);
					if(d[u]>1) flag|=bool(cnt);
					if(p.size()>1){
						g[p.front()].push_back(p.back());
						g[p.back()].push_back(p.front());
					}
				}
			}
			int cnt=0,tot=0;
			for(int u:node){
				MulAs(ans,fac[c[u]]);
				if(g[u].size()>2) err|=1;
				else if(g[u].size()==2) tot++;
				else if(g[u].size()==1) cnt++;
			}
			if(cnt==0&&tot) err|=1;
			if(flag) MulAs(ans,2);
			MulAs(ans,2);
		}

		cout<<Mul(ans,!err)<<endl;

		Clear();
	}

	return 0;
}