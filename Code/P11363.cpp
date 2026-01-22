#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e5+9;
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
inline int Inv(int x){return QPow(x,mod-2);}

int fac[N],ifac[N];
inline void InitFac(int lim){
	fac[0]=1;
	for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
	ifac[lim]=Inv(fac[lim]);
	for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}
inline int C(int n,int m){
	if(m<0||m>n) return 0;
	else return Mul(fac[n],Mul(ifac[m],ifac[n-m]));
}

vector<int> e[N];
int u[N],v[N],imp[N],id[N],d[N],fa[N],dep[N],n,k,root;
inline void Init(int x){
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		dep[y]=dep[x]+1;
		Init(y);
	}
}
int f[N][2],ans;
inline void Calc(int x){
	bool flag=0;
	int inv=d[x]==1?1:Mul(ifac[d[x]-1],fac[d[x]-2]);
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		flag=1;
		Calc(y);
		for(int p:{0,1}){
			for(int q:{0,1}){
				if(p|q|imp[y]) AddAs(ans,Mul(f[x][p],f[y][q]));
			}
		}
		for(int c:{0,1}) AddAs(f[x][c|imp[y]],Mul(f[y][c],inv));
	}
	if(!flag) AddAs(f[x][0],inv);
}
inline void Clear(){
	for(int i=1;i<=n;i++){
		imp[i]=d[i]=dep[i]=fa[i]=f[i][0]=f[i][1]=0;
		e[i].clear();
	}
	ans=0;
}

inline void Solve(){
	cin>>n>>k;
	for(int i=1;i<n;i++){
		cin>>u[i]>>v[i];
		e[u[i]].push_back(v[i]);
		e[v[i]].push_back(u[i]);
		d[u[i]]++,d[v[i]]++;
	}
	for(int i=1;i<=k;i++) cin>>id[i];

	if(n==2){
		cout<<1<<endl;
		Clear();
		return ;
	}

	InitFac(n);
	root=max_element(d+1,d+n+1)-d;
	Init(root);
	for(int i=1;i<=k;i++) imp[dep[u[id[i]]]>dep[v[id[i]]]?u[id[i]]:v[id[i]]]=1;
	Calc(root);

	for(int i=1;i<=n;i++) MulAs(ans,fac[d[i]-1]);

	cout<<ans<<endl;

	Clear();
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int c,T;
	cin>>c>>T;
	while(T--) Solve();

	return 0;
}