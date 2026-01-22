#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=3e3+9;
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

int fac[N<<1],ifac[N<<1];
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

int n,m;

signed main(){
	cin>>n>>m;
	if(m>n) swap(n,m);
	Init(n<<1);

	int ans=0;
	for(int c=0;c<=2*m-n;c++){
		int tmp=Mul(C(n,c),C(m,n-m+c));
		for(int t=0;t<=c;t++){
			int res=Mul(tmp,Mul(Mul(Mul(C(c,t),C(n-m+c,t)),fac[n+c-2*t]),fac[t]));
			MulAs(res,QPow(Inv(2),n-m+c+c-t));
			if(~t&1) AddAs(ans,res);
			else SubAs(ans,res);
		}
	}

	cout<<ans<<endl;

	return 0;
}