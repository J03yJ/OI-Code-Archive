#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;
const int mod=998244353;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
	if(y<0) y+=mod-1;
	int res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
inline int Inv(int x){return QPow(x,mod-2);}

int fa[N],siz[N],n,m;
inline void Init(){iota(fa+1,fa+n+1,1),fill(siz+1,siz+n+1,1);}
inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){
	x=Find(x),y=Find(y);
	if(x==y) return ;
	fa[y]=x;
	siz[x]+=siz[y];
}

int up[N],usiz[N];
vector<int> e[N];
inline void DFS(int x){
	usiz[x]=1;
	for(int y:e[x]){
		if(y==up[x]) continue ;
		up[y]=x;
		DFS(y);
		usiz[x]+=usiz[y];
	}
}

inline void Solve(){
	cin>>n>>m;
	Init();
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
		Merge(u,v);
	}

	DFS(n);
	if(Find(n)==Find(n-1)){
		int x=n-1,mul=1,k=0;
		while(up[x]!=n) x=up[x];
		for(int i=1;i<=n;i++) if(fa[i]==i) MulAs(mul,siz[i]),k++;
		for(int i=1;i<n;i++){
			if(i!=x) cout<<0<<' ';
			else cout<<Mul(QPow(n,k-2),mul)<<' ';
		}
		cout<<endl;
	}else{
		int mul=1,k=0;
		for(int i=1;i<=n;i++) if(fa[i]==i) MulAs(mul,siz[i]),k++;
		for(int i=1;i<n;i++){
			int P=siz[Find(n)],Q=siz[Find(i)];
			if(Find(i)==Find(n)){
				if(up[i]!=n) cout<<0<<' ';
				else cout<<Mul(QPow(n,k-2),Mul(Mul(mul,Inv(P)),usiz[i]))<<' ';
			}else if(Find(i)==Find(n-1)){
				cout<<Mul(QPow(n,k-3),Mul(Mul(Mul(mul,Inv(P)),Inv(Q)),P+Q))<<' ';
			}else{
				cout<<Mul(QPow(n,k-3),Mul(Mul(Mul(mul,Inv(P)),Inv(Q)),Q))<<' ';
			}
		}
		cout<<endl;
	}

	for(int i=1;i<=n;i++){
		up[i]=usiz[i]=0;
		e[i].clear();
	}
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}