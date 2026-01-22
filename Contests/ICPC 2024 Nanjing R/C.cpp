#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int mod=998244353;
const int N=5e3+9;

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

vector<int> e[N];
int fa[N],siz[N],f[N],g[N],n;
inline void DFS(int x){
	siz[x]=1,f[x]=g[x]=1;
	for(int y:e[x]){
		fa[y]=x;
		DFS(y);
		siz[x]+=siz[y];
		MulAs(f[x],C(siz[x]-1,siz[y]));
		MulAs(f[x],f[y]);
	}
	for(int y:e[x]) g[y]=Mul(f[x],Inv(Mul(C(siz[x]-1,siz[y]),f[y])));
}
int h[N][N],tmp[N][N];
inline void Calc(int x){
	if(x==1) h[1][1]=1;
	else{
		for(int p=1;p<=n;p++){
			tmp[x][p]=Mul(h[fa[x]][p],Mul(g[x],C(n-siz[x]-p,siz[fa[x]]-siz[x]-1)));
		}
		for(int p=1,sum=0;p<=n-siz[x]+1;p++){
			h[x][p]=sum;
			AddAs(sum,tmp[x][p]);
		}
	}
	for(int y:e[x]) Calc(y);
}

signed main(){
	cin>>n;
	for(int i=2;i<=n;i++) cin>>fa[i],e[fa[i]].push_back(i);

	Init(n);
	DFS(1);
	Calc(1);
	for(int i=1;i<=n;i++) cout<<Mul(Mul(h[i][i],f[i]),C(n-i,siz[i]-1))<<' ';cout<<endl;

	return 0;
}