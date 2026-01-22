#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=3e3+9;
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

int a[N],f[N][N],n,m;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];

	Init(n);
	f[0][0]=1;
	for(int len=0;len<=n;len++){
		for(int c=len;c<=m;c++){
			AddAs(f[len][c+1],Mul(2,Mul(len,f[len][c])));
			AddAs(f[len+1][c+1],f[len][c]);
		}
	}

	int ans=0;
	for(int lp=1;lp<=n+1;lp++){
		for(int rp=lp-1;rp<=n;rp++){
			if(rp>lp&&a[rp-1]>a[rp]) break ;
			int l=lp-1,r=n-rp;
			AddAs(ans,Mul(C(l+r,l),f[l+r][m]));
		}
	}
	
	cout<<ans<<endl;

	return 0;
}