#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e3+9;
const int mod=998244353;

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

int f[N][N],n,m;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	Init(n);
	
	int lim=__lg(m),ans=0;
	f[lim][1]=1;
	for(int i=lim;i>=0;i--){
		for(int j=0;j*(1<<i)<=m;j++){
			for(int k=0;k<=min(j,n);k+=2){
				if(i) AddAs(f[i-1][(j-k<<1)+(m>>i-1&1)],Mul(f[i][j],C(n,k)));
				else if(k==j) AddAs(ans,Mul(f[i][j],C(n,k)));
			}
		}
	}

	cout<<ans<<endl;

	return 0;
}