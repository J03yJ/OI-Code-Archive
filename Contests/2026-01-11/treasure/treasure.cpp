#include<bits/stdc++.h>

using namespace std;

ifstream fin("treasure.in");
ofstream fout("treasure.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e5+9;
const int lgN=2e1;
const int S=(1<<9)+9;
const int mod=998244353;
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

vector<array<int,2>> e[N];
int v[N],w[N],n,m,lim,h;

ll dep[N];
int fa[lgN][N];
inline void GetDep(int x){
	for(auto p:e[x]){
		if(p[0]==fa[0][x]) continue ;
		fa[0][p[0]]=x;
		dep[p[0]]=dep[x]+p[1];
		GetDep(p[0]);
	}
}
int sf[S][S],sg[S][S],f[N],g[N];
vector<int> to[N][2];
inline void Init(){
	for(int k=1;k<=__lg(n);k++){
		for(int i=1;i<=n;i++) fa[k][i]=fa[k-1][fa[k-1][i]];
	}
	for(int i=1;i<=n;i++){
		to[fa[0][i]][0].push_back(i);
		int x=i;
		for(int k=__lg(n);~k;k--) if(dep[fa[k][x]]>dep[i]-lim) x=fa[k][x];
		to[fa[0][x]][1].push_back(i);
	}
}
inline void Calc(int x){
	for(int i=0;i<(1<<m-h);i++){
		if(((w[x]>>h)&i)==i){
			AddAs(sf[w[x]&(1<<h)-1][i],f[x]);
			AddAs(sg[w[x]&(1<<h)-1][i],g[x]);
		}
	}
	for(int y:to[x][1]){
		for(int i=0;i<(1<<h);i++){
			if((i&(w[y]&(1<<h)-1))==(w[y]&(1<<h)-1)){
				AddAs(f[y],sf[i][w[y]>>h]);
				AddAs(g[y],sg[i][w[y]>>h]);
				AddAs(f[y],Mul(sg[i][w[y]>>h],v[y]));
			}
		}
	}
	for(int y:to[x][0]) Calc(y);
	for(int i=0;i<(1<<m-h);i++){
		if(((w[x]>>h)&i)==i){
			SubAs(sf[w[x]&(1<<h)-1][i],f[x]);
			SubAs(sg[w[x]&(1<<h)-1][i],g[x]);
		}
	}
}

signed main(){
	cin>>n>>m>>lim;
	for(int i=1;i<=n;i++) cin>>v[i];
	for(int i=1,u,v,l;i<n;i++){
		cin>>u>>v>>l;
		e[u].push_back({v,l});
		e[v].push_back({u,l});
	}
	for(int i=1;i<=n;i++){
		int k,x;
		cin>>k;
		while(k--) cin>>x,w[i]|=(1<<x-1);
	}

	GetDep(1),dep[0]=-inf,Init();
	w[0]=(1<<m)-1,g[0]=1,h=m>>1;
	Calc(0);

	int ans=0;
	for(int i=1;i<=n;i++) AddAs(ans,f[i]);

	cout<<ans<<endl;

	return 0;
}